//
// Created by krueger on 3/27/20.
//

#include "grow_tools.h"


int find_best_match(cv::Mat3f img, cv::Point in, cv::Point *target, int x_min, int y_min, int x_max, int y_max) {
    float min_dist = 10000;
    for(int y=y_min; y < y_max; y++) {
        float dist;
        int x;
        for(x=x_min; x < x_max; x++) {
            Vec3f val = img.at<Vec3f>(Point(x,y));
            /*if(norm(val, NORM_L1) == 0) {
                break;
            }*/
            dist = compute_distance(img, WINDOW, Point(x,y), in);
            //if(isnan(dist)) break;
            if(dist < min_dist) {
                min_dist = dist;
                *target = Point(x,y);
            }
        }
        //if(x==WINDOW) break;
    }
}

float compute_distance(cv::Mat3f in, int width, cv::Point a, cv::Point b) {
    if (width % 2 == 0) {
        std::cout << "WINDOW size must be uneven!!!" << std::endl;
        return -1;
    }
    int delta = (width - 1) / 2;


    cv::Point a0 = cv::Point(a.x - delta, a.y - delta);
    cv::Point b0 = cv::Point(b.x - delta, b.y - delta);

    cv::Rect rb(b0.x, b0.y, width, width);
    Mat3f b_sample = in(rb);

    cv::Rect ra(a0.x, a0.y, width, width);
    Mat3f a_sample = in(ra);

    // cv::Mat3f gauss = getGaussianKernel(width, colwidth, SIGMA, SIGMA);


    Mat3f mask;
    multiply(b_sample, a_sample, mask);
    threshold(mask, mask, 0, 1, THRESH_BINARY);

    Mat3f tmp;
    int nonzero = norm(mask, NORM_L1);
    // multiply(mask, gauss, mask);
    multiply(b_sample - a_sample, mask, tmp);

    return norm(tmp, NORM_L2) / nonzero;

}

/* source of this function:
 * https://codereview.stackexchange.com/a/169675
*/
cv::Mat3f getGaussianKernel(int rows, int cols, double sigmax, double sigmay) {
    auto gauss_x = cv::getGaussianKernel(cols, sigmax, CV_32F);
    auto gauss_y = cv::getGaussianKernel(rows, sigmay, CV_32F);
    return gauss_y * gauss_x.t();
}