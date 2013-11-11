//
//  ImageAnalyzer.cpp
//  CoinRecognition
//
//  Created by Michal on 11/11/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#include "ImageAnalyzer.h"

ImageAnalyzer::ImageAnalyzer(const cv::Mat& image)
: image_(image)
{}

void ImageAnalyzer::drawCircles()
{
    for (size_t i = 0; i < circles_.size(); i++)
    {
        std::cout << "Circle position x = "
            << circles_[i][0] << ", y = "
            << circles_[i][1] << ", radius = "
            << circles_[i][2] << "\n";

        cv::Point center(cvRound(circles_[i][0]), cvRound(circles_[i][1]));
        int radius = cvRound(circles_[i][2]);

        circle(image_, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        circle(image_, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }
}

void ImageAnalyzer::findCircles()
{
    cv::HoughCircles(image_, circles_, CV_HOUGH_GRADIENT, 1, 8);
}

cv::Mat ImageAnalyzer::getChannel(int number)
{
    std::vector<cv::Mat> channels;
    cv::split(image_, channels);

    assert(channels.size() > number);
    return channels[number];
}

void ImageAnalyzer::setImage(cv::Mat image)
{
    image_ = image;
}

void ImageAnalyzer::applyCvtColor(int filerCode)
{
    cv::cvtColor(image_, image_, filerCode);
}

cv::Mat ImageAnalyzer::getImage() const
{
    return image_;
}

void ImageAnalyzer::gaussianBlur()
{
    cv::GaussianBlur(image_,
                     image_,
                     cv::Size(9, 9),
                     2,
                     2);
}