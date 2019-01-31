//
//  MTA+Account.h
//  accountext
//
//  Created by tyzual on 2018/4/9.
//  Copyright © 2018 tyzual. All rights reserved.
//

#pragma once

#import "MTA.h"


/**
账号类型枚举
 */
typedef NS_ENUM(NSUInteger, MTAAccountTypeExt) {
	MTAAccountUndefined = 0,
	MTAAccountPhone = 1, // 电话
	MTAAccountEmail = 2, // 邮箱
	MTAAccountQQNum = 3, // QQ号

	MTAAccountWeixin = 1000,	// 微信
	MTAAccountQQOpenid = 1001,  // QQ开放平台Openid
	MTAAccountWeibo = 1003,		// 新浪微博
	MTAAccountAlipay = 1003,	// 支付宝
	MTAAccountTaobao = 1004,	// 淘宝
	MTAAccountDouban = 1005,	// 豆瓣
	MTAAccountFacebook = 1006,  // facebook
	MTAAccountTwitter = 1007,   // twitter
	MTAAccountGoogle = 1008,	// 谷歌
	MTAAccountBaidu = 1009,		// 百度
	MTAAccountJD = 1010,		// 京东
	MTAAccountDing = 1011,		// 钉钉
	MTAAccountXiaomi = 1012,	// 小米
	MTAAccountLinkin = 1013,	// linkedin
	MTAAccountLine = 1014,		// line
	MTAAccountInstagram = 1015, // instagram
	MTAAccountGuest = 2000,		// 游客登录
	MTAAccountCustom = 2001,	// 用户自定义以上的账号类别请使用2001以及2001以上的枚举值
};


/**
 账号登录类型枚举
 */
typedef NS_ENUM(NSInteger, MTAAccountRequestType) {
	MTAAccountRequestUndefined = -1,   // 未定义
	MTAAccountRequestLogin = 1,		   // 新登录
	MTAAccountRequestRefleshToken = 2, // 刷新token
	MTAAccountRequestExShort = 3,	  // 交换短票据
	MTAAccountRequestExThridParty = 4, //交换第三方票据
};


/**
 账号状态枚举
 */
typedef NS_ENUM(NSInteger, MTAAccountStatus) {
	MTAAccountStatusUndefined = -1, // 未定义
	MTAAccountStatusNormal = 1,		// 正常使用
	MTAAccountStatusLogout = 0,		// 登出
};


/**
 账号信息
 */
@interface MTAAccountInfo : NSObject <NSCopying>


/**
 账号类型，默认值为 MTAAccountUndefined，用户必须手动填写
 */
@property (nonatomic, assign) MTAAccountTypeExt type;

/**
 账号id，默认值为nil, 用户必须手动填写
 */
@property (nonatomic, strong) NSString *account;

/**
 账号登录类型，默认未定义
 */
@property (nonatomic, assign) MTAAccountRequestType requestType;

/**
 账号状态，默认未定义
 */
@property (nonatomic, assign) MTAAccountStatus accountStatus;

/**
 账号过期时间，默认nil
 */
@property (nonatomic, strong) NSDate *expireDate;

/**
 账号上次更新时间，默认nil
 */
@property (nonatomic, strong) NSDate *lastUpdateDate;

@end

@interface MTA(MTAAccountExt)

/**
 上报主账号

 @param infos 账号信息
 */
+ (void)reportAccountExt:(NSArray<MTAAccountInfo *> *)infos;

@end

