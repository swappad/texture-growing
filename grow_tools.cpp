//
// Created by krueger on 3/27/20.
//

#include <iostream>
#include "grow_tools.h"

using namespace cv;

float compute_distance(cv::Mat1f *img, int width, cv::Point a, cv::Point b) {
    if (width % 2 == 0)
        return -1;
    int delta = (width - 1) / 2;


    cv::Point a0 = cv::Point(a.x - delta, a.y - delta);
    cv::Point b0 = cv::Point(b.x - delta, b.y - delta);

    //if(a0.x < 0 || a0.y < 0 || a0.x > img.cols || a0.y > img.rows) return -1;
    //if(b0.x < 0 || b0.y < 0 || b0.x > img.cols || b0.y > img.rows) return -1;

    cv::Mat gauss = getGaussianKernel(width, width, SIGMA, SIGMA);
    cv::Rect rb(b0.x, b0.y, width, width);
    Mat b_sample = (*img)(rb).clone();

    cv::Rect ra(a0.x, a0.y, width, width);
    Mat a_sample = (*img)(ra).clone();

    Mat b_sample_tres;
    Mat a_sample_tres;

    threshold(b_sample, b_sample_tres, 0, 1, THRESH_BINARY);
    threshold(a_sample, a_sample_tres, 0, 1, THRESH_BINARY);

    Mat mask = b_sample_tres * a_sample_tres;

    Mat tmp;

    multiply(b_sample - a_sample, gauss, tmp);
    return norm(tmp, NORM_L2, mask);

}


/* source of this function:
 * https://codereview.stackexchange.com/a/169675
*/
cv::Mat getGaussianKernel(int rows, int cols, double sigmax, double sigmay) {
    auto gauss_x = cv::getGaussianKernel(cols, sigmax, CV_32F);
    auto gauss_y = cv::getGaussianKernel(rows, sigmay, CV_32F);
    return gauss_x * gauss_y.t();
}