//
//  JSBCallbackResponse.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 18/01/2018.
//

#import <Foundation/Foundation.h>

typedef enum : NSInteger {
    JSBCallbackResponseCodeSucceed = 0,
    JSBCallbackResponseCodeFail = 1
} JSBCallbackResponseCode;

@interface JSBCallbackResponse : NSObject

@property (nonatomic, assign) JSBCallbackResponseCode code;
@property (nonatomic, copy) NSString *message;
@property (nonatomic, copy) NSDictionary *data;

- (instancetype)initWithCode:(JSBCallbackResponseCode)code message:(NSString *)message data:(NSDictionary *)data;

- (NSString *)getJsonString;

@end
