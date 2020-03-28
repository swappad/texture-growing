//
// Created by krueger on 3/27/20.
//

#ifndef TEXTURE_GROWING_GROW_TOOLS_H
#define TEXTURE_GROWING_GROW_TOOLS_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define SIGMA 4


cv::Mat getGaussianKernel(int rows, int cols, double sigmax, double sigmay);

float compute_distance(cv::Mat1f img, int width, cv::Point a, cv::Point b);


#endif //TEXTURE_GROWING_GROW_TOOLS_H
