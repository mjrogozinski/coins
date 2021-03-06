//
//  ImageAnalyzer.h
//  CoinRecognition
//
//  Created by Michal on 11/11/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#ifndef __CoinRecognition__ImageAnalyzer__
#define __CoinRecognition__ImageAnalyzer__

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageAnalyzer
{
public:
    ImageAnalyzer(cv::Mat& image);
    
    void applyCvtColor(int filerCode);
    void drawCircles();
    void findCircles();
    void gaussianBlur();
    void sobel();
    void thresholdToZero(int thresh);
    void threshold(int thresh);
    void invert();
    void findContours();
    void drawContours();
    cv::Mat getChannel(int number);
    cv::Mat getImage() const;
    void setImage(cv::Mat image);
    void erode();

private:
    std::vector<cv::Vec3f> circles_;
    std::vector<std::vector<cv::Point> > contours_;
    std::vector<cv::Vec4i> hierarchy_;
    cv::Mat& image_;
};

#endif /* defined(__CoinRecognition__ImageAnalyzer__) */

    //equalizeHist(greyImage, greyImage);
    //cv::threshold(greyImage, greyImage, 200, 255, cv::THRESH_BINARY);
    

    /*cv::GaussianBlur(greyImage,
                     greyImage,
                     cv::Size(9, 9),
                     2,
                     2);*/
//matImage = equalizeIntensity(matImage);