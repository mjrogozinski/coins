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
    ImageAnalyzer(const cv::Mat& image);
    
    void applyCvtColor(int filerCode);
    void drawCircles();
    void findCircles();
    cv::Mat getChannel(int number);
    cv::Mat getImage() const;
    void setImage(cv::Mat image);

private:
    std::vector<cv::Vec3f> circles_;
    cv::Mat image_;
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