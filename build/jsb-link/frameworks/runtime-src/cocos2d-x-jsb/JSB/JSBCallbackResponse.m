//
//  JSBCallbackResponse.m
//  Agora-iOS-Cocos
//
//  Created by Agora on 18/01/2018.
//

#import "JSBCallbackResponse.h"

@implementation JSBCallbackResponse

- (instancetype)init
{
    self = [super init];
    if (self) {
        _code = JSBCallbackResponseCodeSucceed;
        _message = @"";
        _data = @{};
    }
    return self;
}

- (instancetype)initWithCode:(JSBCallbackResponseCode)code message:(NSString *)message data:(NSDictionary *)data
{
    self = [self init];
    if (self) {
        self.code = code;
        self.message = message;
        self.data = data;
    }
    return self;
}

- (NSString *)getJsonString
{
    NSMutableDictionary *resDic = [[NSMutableDictionary alloc] init];
    resDic[@"code"] = @(_code);
    resDic[@"message"] = _message;
    resDic[@"data"] = _data;
    return [JSBCallbackResponse jsonStringFromNSDictionary:resDic];
}

+ (NSString *)jsonStringFromNSDictionary:(NSDictionary *)dict
{
    NSString *res = nil;
    if (dict && [dict isKindOfClass:[NSDictionary class]] && [NSJSONSerialization isValidJSONObject:dict]) {
        NSError *error = nil;
        NSData *data  = [NSJSONSerialization dataWithJSONObject:dict options:kNilOptions error:&error];
        if (!error) {
            res = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        }
    }
    return res;
}

@end
