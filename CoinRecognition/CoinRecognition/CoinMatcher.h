//
//  CoinMatcher.h
//  CoinRecognition
//
//  Created by Michal on 11/30/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#ifndef __CoinRecognition__CoinMatcher__
#define __CoinRecognition__CoinMatcher__

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>    

class CoinMatcher
{
    typedef std::vector<cv::KeyPoint> KeyPoints;
    typedef std::vector<cv::DMatch> DMatches;

public:
    CoinMatcher(const cv::Mat& object, const std::string& name);
    void find(const cv::Mat& scene);
    void draw(cv::Mat& scene);
    int goodMatches() const;

private:
    void detectTemplateKeyPoints();
    void detectSceneKeyPoints(const cv::Mat& scene);
    void match();
    void findDistances();
    void findGoodMatches();
    void findPoints();
    
    cv::SurfFeatureDetector detector_;
    cv::SurfDescriptorExtractor extractor_;
    cv::Mat templateDescriptors_;
    cv::Mat sceneDescriptors_;
    KeyPoints templateKeyPoints_;
    KeyPoints sceneKeyPoints_;
    
    DMatches matches_;
    DMatches goodMaches_;
    double maxDistMatch_;
    double minDistMatch_;

    std::vector<cv::Point2f> templatePoints_;
    std::vector<cv::Point2f> scenePoints_;
    
    std::string name_;
    
    cv::Mat template_;
};

#endif /* defined(__CoinRecognition__CoinMatcher__) */
