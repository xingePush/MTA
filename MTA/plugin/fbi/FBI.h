//
//  FBI.h
//  注意:使用本功能必须引用IDFA插件(具体使用见IDFA文档)
//
//  Created by xiang on 31/07/2017.
//  Copyright © 2017 xiangchen. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MTA.h"

@interface FBI : NSObject

+(instancetype)getInstance;

//页面行为,所有页面名称定义在PageName.h
-(void)trackPageBegin:(NSString *)pageName extendInfo:(NSDictionary *)extendInfo;

/**
 @param pageName 页面标识
 @param duration 时长，精确到毫秒级
 @param extendInfo 扩展信息
*/
-(void)trackPageEnd:(NSString *)pageName duration:(unsigned long)duration extendInfo:(NSDictionary *)extendInfo;

//输入行为
-(void)trackOnFocusChange:(NSString *)actionName isFocus:(BOOL)isFocus extendInfo:(NSDictionary *)extendInfo;

/**
 @param actionName 用户行为名称
 @param txtValue 文本内容
 @param needEncoding 是否需要FBI编码(不可逆)
 @param extendInfo 扩展信息
 */
-(void)trackOnTextChange:(NSString *)actionName txtValue:(NSString *)txtValue needEncoding:(BOOL)needEncoding extendInfo:(NSDictionary *)extendInfo;

//点击行为
-(void)trackOnClick:(NSString *)actionName extendInfo:(NSDictionary *)extendInfo;

//提交行为
-(void)trackOnSubmit:(NSString *)actionName result:(BOOL)result msg:(NSString *)msg extendInfo:(NSDictionary *)extendInfo;

//登录相关
-(void)trackOnLoginSuccess:(NSString *)loginMethod userID:(NSString *)userID extendInfo:(NSDictionary *)extendInfo;
-(void)trackOnLogout:(NSDictionary *)extendInfo;


//处理JS SDK请求
-(id)bindToWebView:(id)webView preDelegate:(id)preDelegate;
@end

