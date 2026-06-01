import { NativeModules } from 'react-native';

const { BixolonPrinter } = NativeModules;

let sdkOpened = false;
let connected = false;

async function ensureOpen() {
  if (!sdkOpened) {
    await BixolonPrinter.open();
    sdkOpened = true;
  }
}

export async function getPairedPrinters() {
  try {
    await ensureOpen();
    const devices = await BixolonPrinter.getPairedDevices();
    return devices.map((d) => ({
      name: d.name || d.modelName || 'Unknown',
      serialNumber: d.serialNumber,
      macAddress: d.macAddress,
      address: d.address,
    }));
  } catch (error) {
    console.warn('PrinterService: Failed to get paired devices', error);
    return [];
  }
}

export async function connectToPrinter(serialNumber) {
  try {
    await ensureOpen();
    if (connected) {
      await disconnect();
    }
    await BixolonPrinter.connectWithSerialNumber(serialNumber);
    connected = true;
    return true;
  } catch (error) {
    console.warn('PrinterService: Failed to connect', error);
    connected = false;
    return false;
  }
}

export async function printLabel({ title, useBy, body = [], callout } = {}) {
  if (!connected) {
    console.warn('PrinterService: No printer connected');
    return false;
  }
  try {
    const xMargin = 20;
    const startY = 15;

    const bigCfg = { fontSize: '3', w: 1, h: 1, charLimit: 21, lineHeight: 35 };
    const smallCfg = { fontSize: '1', w: 1, h: 1, charLimit: 28, lineHeight: 30 };

    const wrap = (line, limit) => {
      if (line.length <= limit) return [line];
      const words = line.split(' ');
      const out = [];
      let cur = '';
      for (const w of words) {
        if (cur && (cur + ' ' + w).length > limit) {
          out.push(cur);
          cur = w;
        } else {
          cur = cur ? cur + ' ' + w : w;
        }
      }
      if (cur) out.push(cur);
      return out;
    };

    const drawSegment = async (line, cfg, yStart) => {
      const wrapped = wrap(String(line), cfg.charLimit);
      let cursor = yStart;
      for (const w of wrapped) {
        if (w.trim()) {
          await BixolonPrinter.drawTextDeviceFont(
            w,
            xMargin,
            cursor,
            cfg.fontSize,
            cfg.w,
            cfg.h,
          );
        }
        cursor += cfg.lineHeight;
      }
      return cursor;
    };

    let y = startY;
    if (title) y = await drawSegment(title, bigCfg, y);
    if (useBy) y = await drawSegment(useBy, bigCfg, y);
    for (const line of body) y = await drawSegment(line, smallCfg, y);

    if (callout) {
      // Anchor in the lower-right area of the label; if body extends past
      // the anchor, push the callout down to avoid horizontal overlap.
      // Anchor was 195 but the bottom of FONT_SIZE_30 was clipping at the
      // label edge on standard stock — 170 leaves margin for the full
      // letter strokes (descenders and bottom serifs).
      const calloutY = Math.max(170, y + 5);
      await BixolonPrinter.drawTextDeviceFont(
        String(callout).toUpperCase(),
        180,
        calloutY,
        '6',
        1,
        1,
      );
    }

    await BixolonPrinter.doPrint(1);
    return true;
  } catch (error) {
    console.warn('PrinterService: Failed to print', error);
    return false;
  }
}

// ---------------------------------------------------------------------------
// Low-level label primitives
//
// printLabel() above is a fixed renderer for the legacy 1.25"x2.25" stock.
// These primitives instead let the client own the layout: set the physical
// media size, draw each element at explicit dot coordinates, then print. That
// way a consumer can target any label stock (e.g. 1"x2") without the geometry
// being hardcoded here. All positions/sizes are in printer dots; Bixolon label
// printers are typically 203 dpi (1 inch = 203 dots).
// ---------------------------------------------------------------------------

const DEFAULT_DPI = 203;

/**
 * Tell the printer the physical media size. `heightIn` is the feed-direction
 * length of one label (the gap-to-gap distance) and `gapIn` is the liner gap
 * between labels. Call this before drawing so content isn't clipped to a stale
 * media length. `widthIn` is fixed by the print head, so it's only echoed back
 * (as dots) for the caller's layout math, not sent to the printer.
 *
 * @returns {Promise<false|{widthDots:number,heightDots:number,gapDots:number,dpi:number}>}
 */
export async function setLabelSize({ widthIn, heightIn, dpi = DEFAULT_DPI, gapIn = 0.12 } = {}) {
  if (!connected) {
    console.warn('PrinterService: No printer connected');
    return false;
  }
  const heightDots = Math.round((heightIn || 0) * dpi);
  const gapDots = Math.round((gapIn || 0) * dpi);
  try {
    await BixolonPrinter.setLength(heightDots, gapDots);
    return { widthDots: Math.round((widthIn || 0) * dpi), heightDots, gapDots, dpi };
  } catch (error) {
    console.warn('PrinterService: Failed to set label size', error);
    return false;
  }
}

/**
 * Draw a single line of device-font text at the given dot coordinates. `font`
 * is the Bixolon device-font selection ('1' ~ FONT_SIZE_8, '3' ~ FONT_SIZE_12,
 * '6' ~ FONT_SIZE_30); `w`/`h` are integer scale factors.
 */
export async function drawText(text, x, y, font = '2', w = 1, h = 1) {
  if (!connected) {
    console.warn('PrinterService: No printer connected');
    return false;
  }
  try {
    await BixolonPrinter.drawTextDeviceFont(String(text), x, y, String(font), w, h);
    return true;
  } catch (error) {
    console.warn('PrinterService: Failed to draw text', error);
    return false;
  }
}

/** Flush the drawing buffer to the printer. */
export async function print(copies = 1) {
  if (!connected) {
    console.warn('PrinterService: No printer connected');
    return false;
  }
  try {
    await BixolonPrinter.doPrint(copies);
    return true;
  } catch (error) {
    console.warn('PrinterService: Failed to print', error);
    return false;
  }
}

/**
 * Greedy word-wrap a line to a character limit. Returns an array of lines so
 * the caller can advance its own y cursor per line.
 */
export function wrapText(line, limit) {
  const str = String(line);
  if (!limit || str.length <= limit) return [str];
  const words = str.split(' ');
  const out = [];
  let cur = '';
  for (const w of words) {
    if (cur && (cur + ' ' + w).length > limit) {
      out.push(cur);
      cur = w;
    } else {
      cur = cur ? cur + ' ' + w : w;
    }
  }
  if (cur) out.push(cur);
  return out;
}

export async function disconnect() {
  try {
    await BixolonPrinter.disconnect();
  } catch (error) {
    console.warn('PrinterService: Failed to disconnect', error);
  }
  connected = false;
}

export function isConnected() {
  return connected;
}
