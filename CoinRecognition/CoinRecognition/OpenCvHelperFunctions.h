//
//  OpenCvHelperFunctions.h
//  CoinRecognition
//
//  Created by Michal on 11/30/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#ifndef CoinRecognition_OpenCvHelperFunctions_h
#define CoinRecognition_OpenCvHelperFunctions_h

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace helpers
{

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

}  // namespace helpers
#endif
