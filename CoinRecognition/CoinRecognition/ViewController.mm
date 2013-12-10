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
#include <algorithm>
#include <functional>
#import "ViewController.h"
#include "ImageAnalyzer.h"
#include "OpenCvHelperFunctions.h"
#import "OpenCvHelper.h"
#include "CoinMatcher.h"


@interface ViewController ()

@end

@implementation ViewController

@synthesize mainImage;
@synthesize photoAfterCalculations;

- (void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)recognizeCoin:(UIImage*)photo
{
    NSLog(@"%s", __FUNCTION__);

    [self showImage:photo];
    cv::Mat scene = [OpenCvHelper cvMatFromUIImage:photo];
    ImageAnalyzer sceneAnalyzer(scene);
    sceneAnalyzer.applyCvtColor(CV_BGR2GRAY);

    std::vector<CoinMatcher> coinMatchers = [self getMatchers];

    std::for_each(coinMatchers.begin(), coinMatchers.end(), boost::bind(&CoinMatcher::find, _1, scene));

    std::max_element(coinMatchers.begin(), coinMatchers.end(),
        boost::bind(&CoinMatcher::goodMatches, _2) > boost::bind(&CoinMatcher::goodMatches, _1))->draw(scene);

    [self showCvImage:scene];
}

- (NSArray*)getTemplateNames
{
    NSArray* templates = [NSArray arrayWithObjects:
                          @"1gr",
                          @"2gr",
                          @"5grReal",
                          @"10gr",
                          @"20gr",
                          @"50gr",
                          @"1zl",
                          @"2zl",
                          @"5zl",
                          @"5grReal",
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
        ImageAnalyzer templateAnalyzer(currentTemplate);
        templateAnalyzer.applyCvtColor(CV_BGR2GRAY);
        matchers.push_back(CoinMatcher(currentTemplate, [currentFileName UTF8String]));
    }

    return matchers;
}

- (void)showImage:(UIImage *)image
{
    NSLog(@"%s", __FUNCTION__);
    if ([self mainImage] == nil)
    {
        self.photoAfterCalculations = image;
    }
    else
    {
        [self.mainImage setImage:image];
    }
}

-(void)viewDidAppear:(BOOL)animated
{
    [self showImage:photoAfterCalculations];
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
