//
//  ViewController.m
//  CoinRecognition
//
//  Created by Michal on 11/9/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#import "ViewController.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageAnalyzer.h"
#include "OpenCvHelperFunctions.h"

@interface ViewController ()

@end

@implementation ViewController

@synthesize mainImage;

- (void)viewDidLoad
{
    [super viewDidLoad];

    UIImage * testImage = [UIImage imageNamed:@"photo2.jpg"];

    [self showImage:testImage];

    ImageAnalyzer coinFinder(helpers::cvMatFromUIImage:testImage);
    [self showCvImage:coinFinder.getImage()];
}

- (void)showImage:(UIImage *)image
{
    [self.mainImage setImage:image];
}

- (void)showCvImage:(cv::Mat)image
{
    [self showImage:[self UIImageFromCVMat:image]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
