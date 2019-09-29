// ImageDeltas.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include <boost/program_options.hpp>

// public api
std::vector<uchar> EncodePng(cv::Mat& data, int compresion_level);
cv::Mat LoadPngOrDie(std::string path);
void LocateDifferences(cv::Mat& first, cv::Mat& second);
std::vector<uchar> EncodeDifference(cv::Mat& first, cv::Mat& second, int compression_level);
void OpenCV_Xor(cv::Mat& first, cv::Mat& second);
// TODO: Reference additional headers your program requires here.
