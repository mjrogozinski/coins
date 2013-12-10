//
//  ImageAnalyzer.cpp
//  CoinRecognition
//
//  Created by Michal on 11/11/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#include "ImageAnalyzer.h"

ImageAnalyzer::ImageAnalyzer(cv::Mat& image)
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
    double dp = 1;
    double minDist = 80;
    double param1 = 100;
    double param2 = 115;
    cv::HoughCircles(image_, circles_, CV_HOUGH_GRADIENT, dp, minDist, param1, param2);
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
                     cv::Size(3, 3),
                     2,
                     2, cv::BORDER_REPLICATE);
}

void ImageAnalyzer::sobel()
{
    cv::Mat afterSobel;
    cv::Sobel(image_, afterSobel, -1, 0, 1);
    cv::Sobel(image_, afterSobel, -1, 1, 0);
    image_ = afterSobel;
}

void ImageAnalyzer::thresholdToZero(int thresh)
{
    cv::threshold(image_, image_, thresh, 255, cv::THRESH_TOZERO);
}

void ImageAnalyzer::invert()
{
    // seriously?! There is no simple function to invert image in whole opencv?!!?!
    cv::Mat ones = cv::Mat::ones(image_.size(), image_.type())*255;
    cv::Mat newImage = cv::Mat::zeros(image_.size(), image_.type());
    subtract(ones, image_, newImage);
    image_ = newImage;
    
}

void ImageAnalyzer::findContours()
{
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(image_, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
    contours_ = contours;
    hierarchy_ = hierarchy;
}

void ImageAnalyzer::drawContours()
{
    std::cout << contours_.size();
    int firstContour = hierarchy_[0][0];
    for (int i = firstContour; i >= 0; i = hierarchy_[i][0])
    {
        cv::Scalar color( rand()&255, rand()&255, rand()&255 );
        cv::drawContours(image_, contours_, i, color, CV_FILLED, 8, hierarchy_);

    }
}

void ImageAnalyzer::threshold(int thresh)
{
    cv::threshold(image_, image_, thresh, 255, cv::THRESH_BINARY);
}

void ImageAnalyzer::erode()
{
    cv::erode(image_, image_, cv::Mat());
}
