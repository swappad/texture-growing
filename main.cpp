#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "grow_tools.h"

#define CV_LOAD_IMAGE_COLOR (-1)


using namespace cv;

int main() {
    cv::Mat image;
    image = imread("../textures/texture1.jpg", CV_LOAD_IMAGE_COLOR);
    if (!image.data)                              // Check for invalid input
    {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    //namedWindow("Display Window", WINDOW_AUTOSIZE);
    //imshow("Display Window", image);
    //std::cout << image << std::endl;

    Mat imgfloat;
    image.convertTo(imgfloat, CV_32FC1, 1 / 255.0);
    float dist = compute_distance(imgfloat, 5, Point(10, 10), Point(10, 15));
    std::cout << dist << std::endl;

    waitKeyEx(0);
    return 0;
}