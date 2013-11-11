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

@interface ViewController ()

@end

cv::Mat equalizeIntensity(const cv::Mat& inputImage)
{
    if(inputImage.channels() >= 3)
    {
        cv::Mat rgb;

        cvtColor(inputImage, rgb, CV_BGR2RGB);

        std::vector<cv::Mat> channels;
        cv::split(rgb, channels);

        for (int i = 0; i < 3; ++i)
        {
            equalizeHist(channels[i], channels[i]);
        }

        cv::Mat result;
        cv::merge(channels, rgb);

        cvtColor(rgb,result,CV_RGB2BGR);

        return result;
    }
    return cv::Mat();
}

@implementation ViewController

@synthesize mainImage;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

    UIImage * testImage = [UIImage imageNamed:@"photo.jpg"];

    /*UIAlertView * alert = [[UIAlertView alloc]
                           initWithTitle:@"Hello!"
                           message:@"Welcome to Open"
                           delegate:self
                           cancelButtonTitle:@"Continue"
                           otherButtonTitles:nil];
    [alert show];*/

    [self showImage:testImage];
    
    ImageAnalyzer coinFinder([self cvMatFromUIImage:testImage]);
    coinFinder.applyCvtColor(CV_BGR2GRAY);
    coinFinder.gaussianBlur();

    //coinFinder.setImage(coinFinder.getChannel(2));
    coinFinder.findCircles();
    coinFinder.drawCircles();
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

- (cv::Mat)cvMatFromUIImage:(UIImage *)image
{
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(image.CGImage);
    CGFloat cols = image.size.width;
    CGFloat rows = image.size.height;

    cv::Mat cvMat(rows, cols, CV_8UC4); // 8 bits per component, 4 channels

    CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,                 // Pointer to  data
                                                    cols,                       // Width of bitmap
                                                    rows,                       // Height of bitmap
                                                    8,                          // Bits per component
                                                    cvMat.step[0],              // Bytes per row
                                                    colorSpace,                 // Colorspace
                                                    kCGImageAlphaNoneSkipLast |
                                                    kCGBitmapByteOrderDefault); // Bitmap info flags

    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), image.CGImage);
    CGContextRelease(contextRef);
    CGColorSpaceRelease(colorSpace);

    return cvMat;
}

- (cv::Mat)cvMatGrayFromUIImage:(UIImage *)image
{
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(image.CGImage);
    CGFloat cols = image.size.width;
    CGFloat rows = image.size.height;

    cv::Mat cvMat(rows, cols, CV_8UC1); // 8 bits per component, 1 channels

    CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,                 // Pointer to data
                                                    cols,                       // Width of bitmap
                                                    rows,                       // Height of bitmap
                                                    8,                          // Bits per component
                                                    cvMat.step[0],              // Bytes per row
                                                    colorSpace,                 // Colorspace
                                                    kCGImageAlphaNoneSkipLast |
                                                    kCGBitmapByteOrderDefault); // Bitmap info flags

    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), image.CGImage);
    CGContextRelease(contextRef);
    CGColorSpaceRelease(colorSpace);

    return cvMat;
}

-(UIImage *)UIImageFromCVMat:(cv::Mat)cvMat
{
    NSData *data = [NSData dataWithBytes:cvMat.data length:cvMat.elemSize()*cvMat.total()];
    CGColorSpaceRef colorSpace;

    if (cvMat.elemSize() == 1) {
        colorSpace = CGColorSpaceCreateDeviceGray();
    } else {
        colorSpace = CGColorSpaceCreateDeviceRGB();
    }

    CGDataProviderRef provider = CGDataProviderCreateWithCFData((__bridge CFDataRef)data);

    // Creating CGImage from cv::Mat
    CGImageRef imageRef = CGImageCreate(cvMat.cols,                                 //width
                                        cvMat.rows,                                 //height
                                        8,                                          //bits per component
                                        8 * cvMat.elemSize(),                       //bits per pixel
                                        cvMat.step[0],                            //bytesPerRow
                                        colorSpace,                                 //colorspace
                                        kCGImageAlphaNone|kCGBitmapByteOrderDefault,// bitmap info
                                        provider,                                   //CGDataProviderRef
                                        NULL,                                       //decode
                                        false,                                      //should interpolate
                                        kCGRenderingIntentDefault                   //intent
                                        );


    // Getting UIImage from CGImage
    UIImage *finalImage = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpace);
    
    return finalImage;
}

@end
