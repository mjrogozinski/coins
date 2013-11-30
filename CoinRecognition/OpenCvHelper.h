//
//  OpenCvHelper.h
//  CoinRecognition
//
//  Created by Michal on 11/30/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

@interface OpenCvHelper : NSObject

+ (cv::Mat)cvMatFromUIImage:(UIImage *)image;
+ (cv::Mat)cvMatGrayFromUIImage:(UIImage *)image;
+ (UIImage *)UIImageFromCVMat:(cv::Mat)cvMat;

@end
