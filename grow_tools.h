//
// Created by krueger on 3/27/20.
//

#ifndef TEXTURE_GROWING_GROW_TOOLS_H
#define TEXTURE_GROWING_GROW_TOOLS_H

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

#define SIGMA 100
#define SCALE 2
#define WINDOW 35

//#define OUTPUT

using namespace cv;

cv::Mat3f getGaussianKernel(int rows, int cols, double sigmax, double sigmay);

float compute_distance(cv::Mat3f in, int width, cv::Point a, cv::Point b);

int find_best_match(cv::Mat3f img, cv::Point in, cv::Point *target, int x_min, int y_min, int x_max, int y_max);


#endif //TEXTURE_GROWING_GROW_TOOLS_H
