# 信鸽 iOS SDK 开发指南

## 简介
信鸽iOS SDK是一个能够提供Push服务的开发平台，提供给开发者简便、易用的API接口，方便快速接入。

## 接入方法
1. 获取 AppId 和 AppKey
2. 工程配置

### 获取 AppId 和 AppKey
前往[http://xg.qq.com](http://xg.qq.com)注册并获取AppKey

### 工程配置
1. 下载信鸽 SDK, 解压缩。
2. 将XGPush.h 以及 libXG-SDK.a 添加到工程
3. 添加以下库/framework 的引用 CoreTelephony.framework, SystemConfiguration.framework, UserNotifications.framework, libXG-SDK.a 以及 libz.tbd, libsqlite3.0.tbd 添加完成以后,库的引用如下:
  ![](/assets/iOSAddFramework.png)
4. 在工程配置和后台模式中打开推送,如下图
  ![projcfg](/assets/iOSProjectConfig.png)
5. 添加编译参数-ObjC
  ![](/assets/iOSLinkFlag.png)
  __注意：checkTargetOtherLinkFlagForObjc报错，是因为build setting中，Other link flags未添加-ObjC__
6. 参考 Demo, 添加相关代码

### 管理信鸽推送服务

#### 开启 Debug
打开 Debug 模式以后可以在终端看到详细的信鸽 Debug 信息，方便定位问题

__示例__
```obj-c
//打开debug开关
[[XGPush defaultManager] setEnableDebug:YES];
//查看debug开关是否打开
BOOL debugEnabled = [[XGPush defaultManager] isEnableDebug];
```
#### 启动信鸽推送服务
__接口__
```obj-c
- (void)startXGWithAppID:(uint32_t)appID appKey:(nonnull NSString *)appKey delegate:(nullable id<XGPushDelegate>)delegate ;
```
__示例__
```obj-c
[[XGPush defaultManager] startXGWithAppID:2200262432 appKey:@"I89WTUY132GJ" delegate:<#your delegate#>];
```

#### 终止信鸽推送服务
终止信鸽推送服务以后，将无法通过信鸽推送服务向设备推送消息

__接口__
```obj-c
- (void)stopXGNotification;
```

__示例__
```obj-c
[[XGPush defaultManager] stopXGNotification];
```

#### 统计推送效果

为了更好的了解每一条推送消息的运营效果，需要将用户对消息的行为上报

##### 统计消息推送的抵达情况

需要在UIApplicationDelegate的回调方法(如下)中调用上报数据的接口

```obj-c
- (BOOL)application:(UIApplication *)application
	didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
```

__接口__

```obj-c
- (void)reportXGNotificationInfo:(nonnull NSDictionary *)info;
```

__示例__

```obj-c
- (BOOL)application:(UIApplication *)application
	didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
      [[XGPush defaultManager] reportXGNotificationInfo:launchOptions];
}
```

##### 统计消息被点击情况

- iOS 10 以前的系统版本，需要在 UIApplicationDelegate 的回调方法(如下)中调用上报数据的接口

  ```obj-c
  - (void)application:(UIApplication *)application
  	didReceiveRemoteNotification:(NSDictionary *)userInfo;
  ```

  __接口__

  ```obj-c
  - (void)reportXGNotificationInfo:(nonnull NSDictionary *)info;
  ```

  __示例__

  ```obj-c
  - (void)application:(UIApplication *)application
  	didReceiveRemoteNotification:(NSDictionary *)userInfo {
  	[[XGPush defaultManager] reportXGNotificationInfo:userInfo];
  }
  ```

- iOS 10 or later  需要实现 XGPushDelegate 的回调方法(如下),并在其中调用上述上报接口

  ```obj-c
  - (void)xgPushUserNotificationCenter:(UNUserNotificationCenter *)center
  	didReceiveNotificationResponse:(UNNotificationResponse *)response
  	withCompletionHandler:(void(^)())completionHandler;
  ```

  __示例__：

  ```obj-c
  - (void)xgPushUserNotificationCenter:(UNUserNotificationCenter *)center
  	didReceiveNotificationResponse:(UNNotificationResponse *)response
  	withCompletionHandler:(void(^)())completionHandler {
        [[XGPush defaultManager] reportXGNotificationInfo:response.notification.request.content.userInfo];
        
  	completionHandler()
  }
  ```




- 如果需要实现应用在前台时，也可以展示推送消息，需要实现以下方法，并在其中调用上报接口

  ```obj-c
  - (void)xgPushUserNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler
  ```

  __示例__

  ```obj-c
  - (void)xgPushUserNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler {
  [[XGPush defaultManager] reportXGNotificationInfo:notification.request.content.userInfo];
      completionHandler(UNNotificationPresentationOptionBadge | UNNotificationPresentationOptionSound | UNNotificationPresentationOptionAlert);
  }
  ```



#### 信鸽推送服务协议(XGPushDelegate)

设置信鸽推送协议代理对象是为了方便查看接口调用的情况，开发者可根据自己的需求选择实现协议的方法

协议方法如下：

```obj-c
/**
 处理iOS 10 UNUserNotification.framework的对应的方法

 @param center [UNUserNotificationCenter currentNotificationCenter]
 @param notification 通知对象
 @param completionHandler 回调对象，必须调用
 */
- (void)xgPushUserNotificationCenter:(nonnull UNUserNotificationCenter *)center willPresentNotification:(nullable UNNotification *)notification withCompletionHandler:(nonnull void (^)(UNNotificationPresentationOptions options))completionHandler __IOS_AVAILABLE(10.0);


/**
 处理iOS 10 UNUserNotification.framework的对应的方法

 @param center [UNUserNotificationCenter currentNotificationCenter]
 @param response 用户对通知消息的响应对象
 @param completionHandler 回调对象，必须调用
 */
- (void)xgPushUserNotificationCenter:(nonnull UNUserNotificationCenter *)center didReceiveNotificationResponse:(nullable UNNotificationResponse *)response withCompletionHandler:(nonnull void (^)(void))completionHandler __IOS_AVAILABLE(10.0);

/**
 @brief 监控信鸽推送服务地启动情况

 @param isSuccess 信鸽推送是否启动成功
 @param error 信鸽推送启动错误的信息
 */
- (void)xgPushDidFinishStart:(BOOL)isSuccess error:(nullable NSError *)error;

/**
 @brief 监控信鸽服务的终止情况

 @param isSuccess 信鸽推送是否终止
 @param error 信鸽推动终止错误的信息
 */
- (void)xgPushDidFinishStop:(BOOL)isSuccess error:(nullable NSError *)error;


/**
 @brief 监控信鸽服务上报推送消息的情况

 @param isSuccess 上报是否成功
 @param error 上报失败的信息
 */
- (void)xgPushDidReportNotification:(BOOL)isSuccess error:(nullable NSError *)error;
```

#### 

#### 管理设备Token

#### 注册设备token

启动推送服务以后,如果注册推送成功，则应用会调用UIApplicationDelegate代理对象的回调方法(如下)，开发者可以在其中调用注册设备token的接口(非必须)

```obj-c
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
```

__接口__

```obj-c
- (void)registerDeviceToken:(nonnull NSData *)deviceToken;
```

__示例__

```obj-c
- (void)application:(UIApplication *)application
	didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
      [[XGPushTokenManager defaultTokenManager] registerDeviceToken:deviceToken];
}
```

#### 绑定/解绑标签和账号

开发者可以针对不同的用户绑定标签,然后对该标签推送.对标签推送会让该标签下的所有设备都收到推送.一个设备可以绑定多个标签.

__接口__

```obj-c
- (void)bindWithIdentifier:(nullable NSString *)identifier type:(XGPushTokenBindType)type;
- (void)unbindWithIdentifer:(nullable NSString *)identifier type:(XGPushTokenBindType)type;
```

__示例__

```obj-c
绑定标签：
[[XGPushTokenManager defaultTokenManager] bindWithIdentifier:@"your tag" type:XGPushTokenBindTypeTag];

解绑标签
[[XGPushTokenManager defaultTokenManager] unbindWithIdentifer:@"your tag" type:XGPushTokenBindTypeTag];

绑定账号：
  [[XGPushTokenManager defaultTokenManager] bindWithIdentifier:@"your account" type:XGPushTokenBindTypeAccount];

解绑账号：
[[XGPushTokenManager defaultTokenManager] unbindWithIdentifer:@"your account" type:XGPushTokenBindTypeAccount];
```

__注1: 一个账号最多绑定15台设备,超过之后会随机解绑一台设备,然后再进行注册.__  

#### 管理设备Token协议(XGPushTokenManagerDelegate)

设置设备token绑定协议代理对象是为了方便查看token绑定的结果，开发者可根据自己的需求选择实现协议的方法

__示例__

```obj-c
[[XGPushTokenManager defaultTokenManager].delegatge = <#your delegate#>;
```

协议方法如下：

```obj-c
/**
 @brief 监控token对象绑定的情况

 @param identifier token对象绑定的标识
 @param type token对象绑定的类型
 @param error token对象绑定的结果信息
 */
- (void)xgPushDidBindWithIdentifier:(nullable NSString *)identifier type:(XGPushTokenBindType)type error:(nullable NSError *)error;


/**
 @brief 监控token对象解绑的情况

 @param identifier token对象绑定的标识
 @param type token对象绑定的类型
 @param error token对象绑定的结果信息
 */
- (void)xgPushDidUnbindWithIdentifier:(nullable NSString *)identifier type:(XGPushTokenBindType)type error:(nullable NSError *)error;
```

#### 

#### 本地推送

本地推送相关功能请参考[苹果开发者文档](https://developer.apple.com/library/content/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/SchedulingandHandlingLocalNotifications.html#//apple_ref/doc/uid/TP40008194-CH5-SW1).
