//
//  CameraViewController.h
//  CoinRecognition
//
//  Created by Michal on 12/10/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CameraViewController :
    UIViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (strong, nonatomic) IBOutlet UIImageView *photo;

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker;
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info;

- (IBAction)takePhoto:   (UIButton *)sender;
- (IBAction)analyzeImage:(UIButton *)sender;

@end
