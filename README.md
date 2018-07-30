# 信鸽推送基础介绍

## 信鸽提供什么样的服务？

在移动应用的开发和运营过程中，推送消息（Push Notification）是非常重要的用户触达手段，通过推送消息可以形成和用户的互动，进一步带来产品使用度的提升。

**信鸽帮助开发者集成移动推送能力，管理推送消息，衡量推送效果。**

### 信鸽 PUSH SDK

信鸽提供了全链路的移动推送能力，只需接入信鸽的SDK（[10分钟即可完成接入，点击这里查看教程](http://docs.developer.qq.com/xg/android_access.html)），就可以立即将推送消息送达到用户的移动设备。

### 信鸽网页管理台

同时，信鸽还提供了操作便捷的网页端管理台，方便开发者进行推送消息管理，推送数据查看，推送调试。您只需要进行简单的配置，即可发送消息，并且实时的观测数据

### 高级定制API

为了帮助您灵活的定制推送相关业务逻辑，信鸽也提供了全面的终端和后台API，通过这些API您可以实现个性化的触达等高级使用场景


## 信鸽推送流程总览

在这个部分，我们将介绍信鸽推送的流程，包含「消息下发」和「数据上报」两个链路。

![](/assets/信鸽服务流程总览.png)


## 基本概念解释

### 概述

在这个部分中给出信鸽服务中部分「基本概念」的释义， ** 阅读这个部分可以帮助您更好的理解信鸽服务，以及其他文档。** 

### 消息类型

**[通知栏消息]**
由操作系统展现在通知栏的消息，用户可以点击消息并且打开应用

**[应用内消息]**
直接透传给Android终端的消息，不会主动展示在通知栏，由App在接受后进行处理

### 推送通道

**[Android 厂商通道]**
由 Android 手机厂商提供的系统级推送通道，可以实现不启动应用就接收并展现消息。当前国内主流手机厂商均推出了这项服务，详细的介绍请请见[Android厂商通道](http://docs.developer.qq.com/xg/android_access/huawei_push.html)

**[APNs]**
Apple Push Notification Service 的缩写，iOS 系统推送通道。所有的 iOS 推送消息均通过 APNs 下发到设备

**[Android 信鸽通道]**
信鸽推送自建的推送通道，通过特有的共享通道机制，维持设备和信鸽服务器间的连接，以保障推送消息的触达

**[FCM通道]**
FCM是 FireBase Cloud Messaging 的缩写，是由 Google 官方推出的推送服务&通道，在海外场景下具备系统级推送的能力

**[信鸽多通道整合]**
信鸽提供了根据不同的使用场景，智能选择推送通道的方式。会根据设备类型和需求的不同选择最合适的推送通道进行消息下发，保障最有效的触达


### 信鸽服务形态

**[信鸽管理台]**
信鸽提供的可视化推送管理界面，具备推送发送，历史查询，数据分析，开发调试等功能。在信鸽官网[登入]()后即可进行使用。

**[Rest API]**
信鸽提供的后台API，包含推送消息，管理设备映射关系，数据查询等功能。方便您更好的进行定制化推送，并且和您现有的业务逻辑进行兼容。详情请阅读[信鸽后台REST_API](http://docs.developer.qq.com/xg/server_api.html)

**[移动端SDK]**
信鸽提供了 iOS&Android 两个平台的推送SDK，SDK主要完成推送消息展现，数据统计的功能。此外SDK侧也提供了一系列的API接口，帮助您实现精准推送的业务逻辑。详情请看[Android 终端 SDK_API ](http://docs.developer.qq.com/xg/android_access/android_api.html)，[iOS 终端 SDK_API](http://docs.developer.qq.com/xg/ios_access/ios_api.html)


### 推送流程

**[Push_Token]**
Push_Token是由信鸽生成的，对一个设备的标识（下文简称Token），用于对设备进行推送，是推送的最小单位。

**[设备推送注册]**
设备的推送注册，表示着设备和信鸽服务器成功的建立了长连接。设备将会和服务器进行通信

**[长连接]**
长连接是信鸽 Android SDK 维持的和信鸽后台的持续连接，在连接有效时能够将推送消息进行下发和展示。当长连接无法建立时，推送消息会被存储在信鸽后台，等待连接成功后下发

**[账号]**
在精准推送中会用到的概念，其他的推送系统中也称作别名/Alias。账号可以在终端SDK & 信鸽后台进行设置和管理。在完成绑定之后就可以使用账号来作为推送目标来进行消息推送了

**[标签]**
同样是精准推送中会用到的概念，开发者可以调用信鸽SDK & 后台API，为设备绑定一个/多个标签。在完成绑定之后，就可以针对标签来进行推送了，方便进行更精细化的运营


