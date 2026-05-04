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
    const smallCfg = { fontSize: '1', w: 1, h: 1, charLimit: 22, lineHeight: 30 };

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

    const bodyStartY = y;
    for (const line of body) y = await drawSegment(line, smallCfg, y);

    if (callout) {
      // Bottom-right callout, positioned beside (not below) body text so it
      // stays inside the printable area on short labels.
      await BixolonPrinter.drawTextDeviceFont(
        String(callout).toUpperCase(),
        240,
        bodyStartY,
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
