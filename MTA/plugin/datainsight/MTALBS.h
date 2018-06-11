//
//  mtalbs.h
//  mtalbs
//
//  Created by xiang on 31/10/2017.
//  Copyright © 2017 xiangchen. All rights reserved.
//

#import <Foundation/Foundation.h>

//默认会自动启动采集
@interface MTALBS : NSObject

+(instancetype)getInstance;

//启动LBS采集。如果App之前没有申请过LBS权限,请在合适的时机进行调用，第一次会有弹框
-(void)start;

//停止LBS采集
-(void)stop;

@end
