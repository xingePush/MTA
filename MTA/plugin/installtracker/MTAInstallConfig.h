//
//  MTAInstallConfig.h
//  installtracker
//
//  Created by xiang on 13/09/2017.
//  Copyright © 2017 xiangchen. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MTAInstallConfig : NSObject

@property uint32_t sendPeriodMinutes;

+(instancetype)getInstance;

@end
