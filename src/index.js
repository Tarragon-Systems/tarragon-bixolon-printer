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

export async function printLabel(text) {
  if (!connected) {
    console.warn('PrinterService: No printer connected');
    return false;
  }
  try {
    const maxCharsPerLine = 25;
    const lineHeight = 30;
    const startY = 15;

    // Split by newlines, then wrap long lines
    const rawLines = text.split('\n');
    const wrappedLines = [];
    for (const line of rawLines) {
      if (line.length <= maxCharsPerLine) {
        wrappedLines.push(line);
      } else {
        const words = line.split(' ');
        let current = '';
        for (const word of words) {
          if (current && (current + ' ' + word).length > maxCharsPerLine) {
            wrappedLines.push(current);
            current = word;
          } else {
            current = current ? current + ' ' + word : word;
          }
        }
        if (current) wrappedLines.push(current);
      }
    }

    for (let i = 0; i < wrappedLines.length; i++) {
      if (wrappedLines[i].trim()) {
        await BixolonPrinter.drawTextDeviceFont(
          wrappedLines[i],
          20,                        // xPosition
          startY + i * lineHeight,   // yPosition
          i === 0 ? '2' : '1',      // fontSize: first line larger
          1,                         // fontWidth
          1,                         // fontHeight
        );
      }
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
