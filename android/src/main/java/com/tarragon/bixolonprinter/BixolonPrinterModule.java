package com.tarragon.bixolonprinter;

import android.Manifest;
import android.bluetooth.BluetoothDevice;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import com.bixolon.labelprinter.BixolonLabelPrinter;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableMap;

import java.util.Set;

public class BixolonPrinterModule extends ReactContextBaseJavaModule {

    private BixolonLabelPrinter printer;
    private boolean isConnected = false;
    private Promise connectPromise;
    private Promise pairedDevicesPromise;

    static {
        try {
            System.loadLibrary("bxl_common");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public BixolonPrinterModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Override
    public String getName() {
        return "BixolonPrinter";
    }

    private final Handler handler = new Handler(Looper.getMainLooper()) {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case BixolonLabelPrinter.MESSAGE_STATE_CHANGE:
                    switch (msg.arg1) {
                        case BixolonLabelPrinter.STATE_CONNECTED:
                            isConnected = true;
                            if (connectPromise != null) {
                                connectPromise.resolve(true);
                                connectPromise = null;
                            }
                            break;
                        case BixolonLabelPrinter.STATE_NONE:
                            isConnected = false;
                            break;
                    }
                    break;

                case BixolonLabelPrinter.MESSAGE_BLUETOOTH_DEVICE_SET:
                    if (pairedDevicesPromise != null) {
                        WritableArray devices = Arguments.createArray();
                        if (msg.obj != null) {
                            Set<BluetoothDevice> pairedDevices = (Set<BluetoothDevice>) msg.obj;
                            for (BluetoothDevice device : pairedDevices) {
                                WritableMap map = Arguments.createMap();
                                try {
                                    map.putString("name", device.getName() != null ? device.getName() : "");
                                    map.putString("macAddress", device.getAddress() != null ? device.getAddress() : "");
                                    map.putString("serialNumber", device.getAddress() != null ? device.getAddress() : "");
                                    map.putString("address", device.getAddress() != null ? device.getAddress() : "");
                                } catch (SecurityException e) {
                                    map.putString("name", "Unknown");
                                    map.putString("macAddress", "");
                                    map.putString("serialNumber", "");
                                    map.putString("address", "");
                                }
                                devices.pushMap(map);
                            }
                        }
                        pairedDevicesPromise.resolve(devices);
                        pairedDevicesPromise = null;
                    }
                    break;
            }
        }
    };

    private boolean hasBluetoothPermissions() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            return ContextCompat.checkSelfPermission(getReactApplicationContext(),
                    Manifest.permission.BLUETOOTH_CONNECT) == PackageManager.PERMISSION_GRANTED
                && ContextCompat.checkSelfPermission(getReactApplicationContext(),
                    Manifest.permission.BLUETOOTH_SCAN) == PackageManager.PERMISSION_GRANTED;
        }
        return true;
    }

    private void requestBluetoothPermissions(Promise promise) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S && getCurrentActivity() != null) {
            ActivityCompat.requestPermissions(getCurrentActivity(),
                new String[]{
                    Manifest.permission.BLUETOOTH_CONNECT,
                    Manifest.permission.BLUETOOTH_SCAN
                }, 1);
            promise.reject("PERMISSIONS_REQUESTED", "Bluetooth permissions requested. Please try again.");
        } else {
            promise.reject("NO_ACTIVITY", "Cannot request permissions without an active activity.");
        }
    }

    @ReactMethod
    public void open(Promise promise) {
        try {
            if (printer == null) {
                printer = new BixolonLabelPrinter(getReactApplicationContext(), handler, Looper.getMainLooper());
            }
            promise.resolve(true);
        } catch (Exception e) {
            promise.reject("OPEN_FAILED", "Failed to initialize SDK", e);
        }
    }

    @ReactMethod
    public void getPairedDevices(Promise promise) {
        if (printer == null) {
            promise.reject("NOT_OPEN", "SDK not initialized. Call open() first.");
            return;
        }
        if (!hasBluetoothPermissions()) {
            requestBluetoothPermissions(promise);
            return;
        }
        pairedDevicesPromise = promise;
        printer.findBluetoothPrinters();
    }

    @ReactMethod
    public void connectWithSerialNumber(String address, Promise promise) {
        if (printer == null) {
            promise.reject("NOT_OPEN", "SDK not initialized. Call open() first.");
            return;
        }
        if (!hasBluetoothPermissions()) {
            requestBluetoothPermissions(promise);
            return;
        }
        if (isConnected) {
            printer.disconnect();
            isConnected = false;
        }
        connectPromise = promise;
        new Thread(() -> printer.connect(address)).start();
    }

    @ReactMethod
    public void connectWithMacAddress(String address, Promise promise) {
        connectWithSerialNumber(address, promise);
    }

    @ReactMethod
    public void disconnect(Promise promise) {
        if (printer != null) {
            printer.disconnect();
        }
        isConnected = false;
        promise.resolve(true);
    }

    @ReactMethod
    public void isConnected(Promise promise) {
        promise.resolve(isConnected);
    }

    @ReactMethod
    public void drawTextDeviceFont(String text, int xPosition, int yPosition,
                                   String fontSize, int fontWidth, int fontHeight,
                                   Promise promise) {
        if (printer == null || !isConnected) {
            promise.reject("NOT_CONNECTED", "Printer not connected");
            return;
        }
        try {
            int font = BixolonLabelPrinter.FONT_SIZE_10;
            if (fontSize != null && fontSize.length() > 0) {
                char c = fontSize.charAt(0);
                switch (c) {
                    case '0': font = BixolonLabelPrinter.FONT_SIZE_6; break;
                    case '1': font = BixolonLabelPrinter.FONT_SIZE_8; break;
                    case '2': font = BixolonLabelPrinter.FONT_SIZE_10; break;
                    case '3': font = BixolonLabelPrinter.FONT_SIZE_12; break;
                    case '4': font = BixolonLabelPrinter.FONT_SIZE_15; break;
                    case '5': font = BixolonLabelPrinter.FONT_SIZE_20; break;
                    case '6': font = BixolonLabelPrinter.FONT_SIZE_30; break;
                    case '7': font = BixolonLabelPrinter.FONT_SIZE_14; break;
                    case '8': font = BixolonLabelPrinter.FONT_SIZE_18; break;
                    case '9': font = BixolonLabelPrinter.FONT_SIZE_24; break;
                }
            }
            printer.drawText(text, xPosition, yPosition, font,
                    fontWidth, fontHeight, 0,
                    BixolonLabelPrinter.ROTATION_NONE,
                    false, false, BixolonLabelPrinter.TEXT_ALIGNMENT_NONE);
            promise.resolve(true);
        } catch (Exception e) {
            promise.reject("DRAW_TEXT_FAILED", "Failed to draw text", e);
        }
    }

    @ReactMethod
    public void drawBarcode1D(String data, int xPosition, int yPosition,
                              int barcodeType, int widthNarrow, int widthWide,
                              int height, int hri, Promise promise) {
        if (printer == null || !isConnected) {
            promise.reject("NOT_CONNECTED", "Printer not connected");
            return;
        }
        try {
            printer.draw1dBarcode(data, xPosition, yPosition,
                    barcodeType, widthNarrow, widthWide, height, hri,
                    0, BixolonLabelPrinter.ROTATION_NONE);
            promise.resolve(true);
        } catch (Exception e) {
            promise.reject("DRAW_BARCODE_FAILED", "Failed to draw barcode", e);
        }
    }

    @ReactMethod
    public void doPrint(int copies, Promise promise) {
        if (printer == null || !isConnected) {
            promise.reject("NOT_CONNECTED", "Printer not connected");
            return;
        }
        try {
            printer.beginTransactionPrint();
            printer.print(copies, copies);
            printer.endTransactionPrint();
            promise.resolve(true);
        } catch (Exception e) {
            promise.reject("PRINT_FAILED", "Failed to print", e);
        }
    }

    @ReactMethod
    public void setLength(int labelLength, int gapLength, Promise promise) {
        if (printer == null || !isConnected) {
            promise.reject("NOT_CONNECTED", "Printer not connected");
            return;
        }
        try {
            printer.setLength(labelLength, gapLength, BixolonLabelPrinter.MEDIA_TYPE_GAP, 0);
            promise.resolve(true);
        } catch (Exception e) {
            promise.reject("SET_LENGTH_FAILED", "Failed to set length", e);
        }
    }

    @ReactMethod
    public void close(Promise promise) {
        if (printer != null) {
            printer.disconnect();
            printer = null;
        }
        isConnected = false;
        promise.resolve(true);
    }
}
