//
//  fbicontacts.h
//  fbicontacts
//
//  Created by xiang on 19/10/2017.
//  Copyright © 2017 xiangchen. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FBIContactsProtocol <NSObject>

@required
-(void)didGotContacts:(NSArray *)contactsArr;

@optional
-(void)didIsGranted:(BOOL)isGranted;
-(void)systemVersionIsOld;

@end

@interface FBIContacts : NSObject<FBIContactsProtocol>

@property (nonatomic,strong) NSMutableArray *contactArr;

@property (nonatomic,weak) id<FBIContactsProtocol> delegate;

+(instancetype)getInstance;

@end
