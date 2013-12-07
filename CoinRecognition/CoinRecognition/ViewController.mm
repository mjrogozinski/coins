//
//  ViewController.m
//  CoinRecognition
//
//  Created by Michal on 11/9/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/bind.hpp>
#import "ViewController.h"
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

    cv::Mat scene = [OpenCvHelper cvMatFromUIImage:[UIImage imageNamed:@"photo 1.JPG"]];
    cv::cvtColor(scene, scene, CV_BGR2GRAY);
    
    std::vector<CoinMatcher> coinMatchers = [self getMatchers];

    std::for_each(coinMatchers.begin(), coinMatchers.end(), boost::bind(&CoinMatcher::find, _1, scene));

    [self showCvImage:scene];
}

- (NSArray*)getTemplateNames
{
    NSArray* templates = [NSArray arrayWithObjects:
                          @"1gr",
                          @"2gr",
                          @"5gr",
                          @"10gr",
                          @"20gr",
                          @"50gr",
                          @"1zl",
                          @"2zl",
                          @"5zl",
                          nil];
    return templates;
}

- (std::vector<CoinMatcher>)getMatchers
{
    std::vector<CoinMatcher> matchers;
    NSArray* templates = [self getTemplateNames];

    for (NSString* templateName in templates)
    {
        NSString* currentFileName = [templateName stringByAppendingString:@".PNG"];
        cv::Mat currentTemplate = [OpenCvHelper cvMatFromUIImage:[UIImage imageNamed:currentFileName]];
        cv::cvtColor(currentTemplate, currentTemplate, CV_BGR2GRAY);
        matchers.push_back(CoinMatcher(currentTemplate, [currentFileName UTF8String]));
    }

    return matchers;
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
