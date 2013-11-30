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
#import "OpenCvHelper.h"
#include "CoinMatcher.h"

@interface ViewController ()

@end

@implementation ViewController

@synthesize mainImage;

- (void)viewDidLoad
{
    [super viewDidLoad];

    cv::Mat zlTemplate = [OpenCvHelper cvMatFromUIImage:[UIImage imageNamed:@"5gr.PNG"]];
    cv::cvtColor(zlTemplate, zlTemplate, CV_BGR2GRAY);
    CoinMatcher fiveZlMatcher(zlTemplate, "5zl Matcher");
    
    cv::Mat scene = [OpenCvHelper cvMatFromUIImage:[UIImage imageNamed:@"photo.jpg"]];
    cv::cvtColor(scene, scene, CV_BGR2GRAY);
    fiveZlMatcher.find(scene);
    fiveZlMatcher.draw(scene);

    [self showCvImage:scene];
}

- (void)showImage:(UIImage *)image
{
    [self.mainImage setImage:image];
}

- (void)showCvImage:(cv::Mat)image
{
    [self showImage:[OpenCvHelper UIImageFromCVMat:image]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

@end
