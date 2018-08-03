** 本文档针对 iOS 信鸽 <font color="#FF0000"> SDK 3.1.0 及以上 </font>  版本 **

## 功能说明
在 iOS 平台上，对于信鸽可能提供的关于精准消息推送的能力来说，IDFA 是比较有效的识别参数，所以 信鸽 SDK 采用插件化的方式来实现按需集成的需要.

## 集成步骤

信鸽 iOS SDK 集成 idfa 模块的步骤：
1.在下载的 SDK 文件包中打开 idfa 目录，获取 libxgidfa.a 静态库文件
2.将 libxgidfa.a 静态库文件，添加到工程即可完成 idfa 插件的集成，如图：
![](/assets/xgidfa.png)

** 注意 **

如果您期望采集IDFA但是并未使用任何广告，可以采用以下方法通过Appstore审核
![](http://docs.developer.qq.com/mta/assets/用户画像.png)

1.serve advertisements within the app

应用内广告服务，适用于应用内集成了广告的场景，如果您的情况符合，需要勾选此选项。

2.Attribute this app installation to a previously served advertisement.

用于跟踪和统计广告带来的安装量，需要勾选。

3.Attribute an action taken within this app to a previously served advertisement

用于跟踪和统计广告安装后带来的用户行为，需要勾选。

4.Limit Ad Tracking setting in iOS

此项属于确认项，需要勾选。
##iOS Extension SDK API (iOS 10+)
**上报推送消息回执，此接口的目的是统计推送消息是否抵达终端**
```objective-c
/**
  @brief   信鸽推送处理抵达到终端到消息            
  @param request   推送请求
  @param appID     信鸽应用ID
  @param handler   处理消息的回执，回调方法中处理关联的富媒体文件               
  @note            关联的富媒体文件，需要在推送前端设置资源的完整URL地址，SDK内部会自动下载        
*/
  - (void)handleNotificationRequest:(nonnull UNNotificationRequest *)request
  appID:(uint32_t)appID contentHandler:(nullable void(^)( NSArray
  <UNNotificationAttachment *>* _Nullable attachments,  NSError * _Nullable
  error))handler;
```
**说明 ：
为了使用extension SDK，操作步骤如下：**
1.新增Target
![](https://ws1.sinaimg.cn/large/006tKfTcgy1ftwbphy06ej30sc0kn0y8.jpg)

2.配置Target，添加依赖库文件：libXGExtension.a, libz.tbd, libsqlite3.tbd

![](https://ws4.sinaimg.cn/large/006tKfTcgy1ftwbsl0ei3j30sj0ahtb1.jpg)
3.调用SDK统计上报接口
**示例**
```Objective-C
- (void)didReceiveNotificationRequest:(UNNotificationRequest *)request
  withContentHandler:(void (^)(UNNotificationContent *
  _Nonnull))contentHandler {
      [[XGExtension defaultManager] handleNotificationRequest:request appID:
  <#your xg AppID#> contentHandler:nil];
      self.contentHandler = contentHandler;
      self.bestAttemptContent = [request.content mutableCopy];
      self.contentHandler(self.bestAttemptContent);
      }
```






