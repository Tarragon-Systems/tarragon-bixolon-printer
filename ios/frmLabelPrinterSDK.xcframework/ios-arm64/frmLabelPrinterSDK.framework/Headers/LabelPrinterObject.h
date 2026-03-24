
#import <Foundation/Foundation.h>
#pragma once

@interface LabelPrinterObject : NSObject
{
    NSMutableArray* _deviceFonts;
    NSMutableArray* _vectorFonts;
    NSMutableArray* _drawBlockOptions;
    NSMutableArray* _circleSizeOptions;
    NSMutableArray* _barcodeType1D;
    NSMutableArray* _barcodeHRI;
    NSInteger _dpi;
    NSInteger _maxWidth;
}

- (instancetype) initWithDpi:(NSInteger)dpi maxWidth:(NSInteger)maxWidth;

-(NSMutableArray*) getDeviceFontList;
-(NSMutableArray*) getVectorFontList;
-(NSMutableArray*) getDrawBlockOptions;
-(NSMutableArray*) getDrawCircleSizes;
-(NSMutableArray*) getBarcodeType1D;
-(NSMutableArray*) getBarcodeHRI;

-(void) setPrinter:(LabelPrinterObject*)printer;
-(void) setModelName:(NSString*)modelName;
-(void) setBluetoothDeviceName:(NSString*)bluetoothDeviceName;
-(void) setFirmwareVersion:(NSString*)firmwareVersion;
-(void) setAddress:(NSString*)address;
-(void) setPort:(NSString*)port;
-(void) setMacAddress:(NSString*)macAddress;
-(void) setSerialNumber:(NSString*)serialNumber;
-(void) setInterfaceType:(NSInteger)interfaceType;

-(NSString*) getModelName;
-(NSString*) getBluetoothDeviceName;
-(NSString*) getFirmwareVersion;
-(NSString*) getAddress;
-(NSString*) getPort;
-(NSString*) getMacAddress;
-(NSString*) getSerialNumber;
-(NSInteger) getInterfaceType;
-(NSInteger) getDpi;
-(NSInteger) getMaxWidth;
-(NSArray<NSNumber*>*) getSupportedSpeeds;

@end
