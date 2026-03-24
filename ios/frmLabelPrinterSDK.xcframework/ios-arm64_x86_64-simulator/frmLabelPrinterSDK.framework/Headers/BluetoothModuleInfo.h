//
//  BluetoothModuleInfo.h
//  LabelPrinterSDK
//
//  Created by TaeKyeongKim on 2023/04/14.
//  Copyright © 2023 savin. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "BxlSlcsComm.h"

#ifndef BluetoothModuleInfo_h
#define BluetoothModuleInfo_h

@interface  BluetoothModuleInfo : NSObject
@property NSString* bluetoothInterfaceType;
@property NSString* SSPMode;
@property NSString* MACAddress;
@property NSString* connectionMode;
@property NSString* PINCode;
@property NSString* encryption;
@property NSString* bluetoothName;

-(__SDK_RESULT_CODES_)getBluetoothModuleInfo:(NSTimeInterval)timeOut comm:(BxlSlcsComm*)comm slcs:(BxlCommandSLCS*) slcs;
-(__SDK_RESULT_CODES_)setBluetoothModuleInfo:(NSTimeInterval)timeOut comm:(BxlSlcsComm*)comm slcs:(BxlCommandSLCS*) slcs newName:(NSString *) newName;

@end
#endif /* BluetoothModuleInfo_h */
