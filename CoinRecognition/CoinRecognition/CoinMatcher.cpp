//
//  CoinMatcher.cpp
//  CoinRecognition
//
//  Created by Michal on 11/30/13.
//  Copyright (c) 2013 Pwr. All rights reserved.
//

#include "CoinMatcher.h"

CoinMatcher::CoinMatcher(const cv::Mat& object, const std::string& name)
    : detector_(1000)
    , name_(name)
    , maxDistMatch_(0)
    , minDistMatch_(100)
{
    template_ = object;
}

void CoinMatcher::find(const cv::Mat& scene)
{
    detectTemplateKeyPoints();
    detectSceneKeyPoints(scene);
    findGoodMatches();
}

void CoinMatcher::detectTemplateKeyPoints()
{
    templateKeyPoints_.clear();
    detector_.detect(template_, templateKeyPoints_);
    extractor_.compute(template_, templateKeyPoints_, templateDescriptors_);
}

void CoinMatcher::detectSceneKeyPoints(const cv::Mat& scene)
{
    sceneKeyPoints_.clear();
    detector_.detect(scene, sceneKeyPoints_);
    extractor_.compute(scene, sceneKeyPoints_, sceneDescriptors_);
}

void CoinMatcher::match()
{
    cv::BFMatcher matcher;//(cv::NORM_HAMMING, true);
    matcher.match(templateDescriptors_, sceneDescriptors_, matches_);
}

void CoinMatcher::findDistances()
{
    for( int i = 0; i < templateDescriptors_.rows; i++ )
    {
        double dist = matches_[i].distance;
        if( dist < minDistMatch_ ) minDistMatch_ = dist;
        if( dist > maxDistMatch_ ) maxDistMatch_ = dist;
    }
    printf("-- -- --\n");
    printf("-- %s\n", name_.c_str());
    printf("-- Max dist : %f \n", maxDistMatch_ );
    printf("-- Min dist : %f \n", minDistMatch_ );
}

void CoinMatcher::findGoodMatches()
{
    match();
    findDistances();
    for( int i = 0; i < templateDescriptors_.rows; i++ )
    {
        if( matches_[i].distance < 1.2*minDistMatch_ )
        {
            goodMaches_.push_back(matches_[i]);            
        }
    } // TODO: choose min avg distance from good matches.
    printf("-- GoodMatches Count : %li \n", goodMaches_.size() );
    printf("-- -- --\n");
}

void CoinMatcher::draw(cv::Mat& scene)
{
    printf("-- drawing %s\n", name_.c_str());
    cv::Mat img_matches;
    drawMatches( template_, templateKeyPoints_, scene, sceneKeyPoints_,
                goodMaches_, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    scene = img_matches;
}

int CoinMatcher::goodMatches() const
{
    return goodMaches_.size();
}
