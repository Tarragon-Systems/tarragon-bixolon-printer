#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>
@import frmLabelPrinterSDK;

@interface BixolonPrinterModule : RCTEventEmitter <RCTBridgeModule, LabelPrinterSDKDelegate>
@end

@implementation BixolonPrinterModule {
  LabelPrinterSDK *_printer;
  BOOL _isConnected;
}

RCT_EXPORT_MODULE(BixolonPrinter);

- (instancetype)init {
  self = [super init];
  if (self) {
    _printer = [[LabelPrinterSDK alloc] init];
    _isConnected = NO;
  }
  return self;
}

+ (BOOL)requiresMainQueueSetup {
  return NO;
}

- (NSArray<NSString *> *)supportedEvents {
  return @[@"onPrinterConnect", @"onPrinterDisconnect", @"onPrinterError"];
}

#pragma mark - React Native Methods

RCT_EXPORT_METHOD(open:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  long result = [_printer open];
  if (result == _SDK_RESULT_SUCCESS) {
    _printer.delegate = self;
    resolve(@YES);
  } else {
    reject(@"OPEN_FAILED", @"Failed to open SDK", nil);
  }
}

RCT_EXPORT_METHOD(getPairedDevices:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  NSArray *devices = [_printer getPairedDevices];
  NSMutableArray *result = [NSMutableArray array];

  for (LabelPrinterObject *device in devices) {
    [result addObject:@{
      @"name": [device getBluetoothDeviceName] ?: @"",
      @"modelName": [device getModelName] ?: @"",
      @"serialNumber": [device getSerialNumber] ?: @"",
      @"macAddress": [device getMacAddress] ?: @"",
      @"address": [device getAddress] ?: @"",
      @"interfaceType": @([device getInterfaceType]),
    }];
  }

  resolve(result);
}

RCT_EXPORT_METHOD(connectWithSerialNumber:(NSString *)serialNumber
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  if (_isConnected) {
    [_printer disconnect];
    _isConnected = NO;
  }

  long result = [_printer connectWithSerialNumber:serialNumber];
  if (result == _SDK_RESULT_SUCCESS) {
    _isConnected = YES;
    resolve(@YES);
  } else {
    reject(@"CONNECT_FAILED", @"Failed to connect to printer", nil);
  }
}

RCT_EXPORT_METHOD(connectWithMacAddress:(NSString *)macAddress
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  if (_isConnected) {
    [_printer disconnect];
    _isConnected = NO;
  }

  long result = [_printer connectWithAddress:macAddress port:@""];
  if (result == _SDK_RESULT_SUCCESS) {
    _isConnected = YES;
    resolve(@YES);
  } else {
    reject(@"CONNECT_FAILED", @"Failed to connect to printer", nil);
  }
}

RCT_EXPORT_METHOD(disconnect:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  long result = [_printer disconnectWithTimeout:10];
  _isConnected = NO;
  if (result == _SDK_RESULT_SUCCESS) {
    resolve(@YES);
  } else {
    reject(@"DISCONNECT_FAILED", @"Failed to disconnect", nil);
  }
}

RCT_EXPORT_METHOD(isConnected:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  resolve(@([_printer isConnected]));
}

RCT_EXPORT_METHOD(drawTextDeviceFont:(NSString *)text
                  xPosition:(NSInteger)xPosition
                  yPosition:(NSInteger)yPosition
                  fontSize:(NSString *)fontSize
                  fontWidth:(NSInteger)fontWidth
                  fontHeight:(NSInteger)fontHeight
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  char fontSelection = [fontSize length] > 0 ? [fontSize characterAtIndex:0] : '2';
  long result = [_printer drawTextDeviceFont:text
                                   xPosition:xPosition
                                   yPosition:yPosition
                               fontSelection:fontSelection
                                   fontWidth:fontWidth
                                  fontHeight:fontHeight
                   rightSideCharacterSpacing:0
                                fontRotation:0
                                     reverse:NO
                                        bold:NO
                               textAlignment:0];
  if (result == _SDK_RESULT_SUCCESS) {
    resolve(@YES);
  } else {
    reject(@"DRAW_TEXT_FAILED", @"Failed to draw text", nil);
  }
}

RCT_EXPORT_METHOD(drawBarcode1D:(NSString *)data
                  xPosition:(NSInteger)xPosition
                  yPosition:(NSInteger)yPosition
                  barcodeType:(NSInteger)barcodeType
                  widthNarrow:(NSInteger)widthNarrow
                  widthWide:(NSInteger)widthWide
                  height:(NSInteger)height
                  hri:(NSInteger)hri
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  long result = [_printer drawBarcode1D:data
                              xPosition:xPosition
                              yPosition:yPosition
                            barcodeType:barcodeType
                            widthNarrow:widthNarrow
                              widthWide:widthWide
                                 height:height
                                    hri:hri
                         quietZoneWidth:0
                               rotation:0];
  if (result == _SDK_RESULT_SUCCESS) {
    resolve(@YES);
  } else {
    reject(@"DRAW_BARCODE_FAILED", @"Failed to draw barcode", nil);
  }
}

RCT_EXPORT_METHOD(doPrint:(NSInteger)copies
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  long result = [_printer doPrint:copies];
  if (result == _SDK_RESULT_SUCCESS) {
    resolve(@YES);
  } else {
    reject(@"PRINT_FAILED", @"Failed to print", nil);
  }
}

RCT_EXPORT_METHOD(setLength:(NSInteger)labelLength
                  gapLength:(NSInteger)gapLength
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  long result = [_printer setLength:labelLength gapLength:gapLength mediaType:'G' offsetLength:0];
  if (result == _SDK_RESULT_SUCCESS) {
    resolve(@YES);
  } else {
    reject(@"SET_LENGTH_FAILED", @"Failed to set label length", nil);
  }
}

RCT_EXPORT_METHOD(close:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
  long result = [_printer close];
  if (result == _SDK_RESULT_SUCCESS) {
    resolve(@YES);
  } else {
    reject(@"CLOSE_FAILED", @"Failed to close SDK", nil);
  }
}

#pragma mark - LabelPrinterSDKDelegate

- (void)willConnect:(LabelPrinterSDK *)controller printer:(LabelPrinterObject *)printer {
}

- (void)didConnect:(LabelPrinterSDK *)controller printer:(LabelPrinterObject *)printer {
  _isConnected = YES;
  if (self.bridge) {
    [self sendEventWithName:@"onPrinterConnect" body:@{@"name": [printer getBluetoothDeviceName] ?: @""}];
  }
}

- (void)didNotConnect:(LabelPrinterSDK *)controller printer:(LabelPrinterObject *)printer withError:(NSError *)error {
  _isConnected = NO;
  if (self.bridge) {
    [self sendEventWithName:@"onPrinterError" body:@{@"error": error.localizedDescription ?: @"Connection failed"}];
  }
}

- (void)didDisconnect:(LabelPrinterSDK *)controller printer:(LabelPrinterObject *)printer {
  _isConnected = NO;
}

- (void)didBeBrokenConnection:(LabelPrinterSDK *)controller printer:(LabelPrinterObject *)printer withError:(NSError *)error {
  _isConnected = NO;
  if (self.bridge) {
    [self sendEventWithName:@"onPrinterDisconnect" body:@{@"error": error.localizedDescription ?: @"Connection broken"}];
  }
}

- (void)willLookupPrinter:(LabelPrinterSDK *)controller {
}

- (void)didFindPrinter:(LabelPrinterSDK *)controller printer:(LabelPrinterObject *)printer {
}

- (void)didLookupPrinters:(LabelPrinterSDK *)controller printerList:(NSArray *)printerList {
}

- (void)canNotFoundPrinter {
}

@end
