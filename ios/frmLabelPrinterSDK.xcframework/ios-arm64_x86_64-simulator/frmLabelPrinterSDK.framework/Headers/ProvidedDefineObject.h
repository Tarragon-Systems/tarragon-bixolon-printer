
#import <Foundation/Foundation.h>

@interface ProvidedDefineObject:NSObject{}
@property (atomic, strong) NSString* name;
@property (assign) char defineValue;
- (id)initWithName:(NSString*)stringName defineValue:(char)chDefineValue;
@end
