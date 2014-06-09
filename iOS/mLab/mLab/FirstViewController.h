//
//  FirstViewController.h
//  mLab
//
//  Created by Chenyang  on 3/3/14.
//  Copyright (c) 2014 Chenyang . All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RESideMenu.h"
#import "NVGalleryViewController.h"

@interface FirstViewController : NVGalleryViewController<NSStreamDelegate>{
    NSInputStream *inputStream;
    NSOutputStream *outputStream;
    UIWebView *webView;
}

- (IBAction)showMenu;
@property (nonatomic, retain) NSInputStream *inputStream;
@property (nonatomic, retain) NSOutputStream *outputStream;
@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, assign) NSInteger frameNumber;
@property (nonatomic, strong) NSMutableArray *image_obj;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *subViewButton;
@property (nonatomic, strong) NSMutableArray *imageArray;
@property (strong, nonatomic) IBOutlet UIImageView *titleImage;
@property (strong, nonatomic) UIImage *imageOfTitle;
- (void) initNetworkCommunication;
- (void) joinChat;
- (void) sendMessage;
- (void) setSubview;

@end