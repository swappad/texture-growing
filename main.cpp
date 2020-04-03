
#include "grow_tools.h"

#define CV_LOAD_IMAGE_COLOR (-1)


using namespace cv;

int main() {
    cv::Mat image;
    image = imread("../textures/texture7.jpg", IMREAD_COLOR);
    if (!image.data)                              // Check for invalid input
    {
        //std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    // convert input to float
    Mat3f imgfloat;
    image.convertTo(imgfloat, CV_32FC3, 1 / 255.0);

    // copy to working layer

    Mat3f layer = Mat::zeros(Size(imgfloat.cols * SCALE + 2 * WINDOW, imgfloat.rows * SCALE + 2 * WINDOW), CV_32FC3);
    Rect rect(WINDOW, WINDOW, imgfloat.cols, imgfloat.rows);
    imgfloat.copyTo(layer(rect));



    // show combined working layer
    Mat out;

    startWindowThread();
    namedWindow("out", WINDOW_NORMAL);
    cv::normalize(layer, out, 0, 1, cv::NORM_MINMAX);
    imshow("out", out);
    // Mat layer_bin;
    // std::vector<cv::Point> zero_pix;
    // threshold(layer, layer_bin, 0, 1, THRESH_BINARY);
    // cv::findNonZero(layer_bin, zero_pix);
    // std::cout << zero_pix << std::endl;



    Point target;
    // up -> down rendering
    for(int y=WINDOW+imgfloat.rows; y < layer.rows-WINDOW; y++){
        for(int x=WINDOW; x < imgfloat.cols+WINDOW; x++) {
            find_best_match(layer, Point(x,y), &target, WINDOW+WINDOW/2, WINDOW+WINDOW/2, WINDOW/2+imgfloat.cols, WINDOW/2+imgfloat.rows);
            //std::cout << target << std::endl;
            Vec3f color = layer.at<Vec3f>(target);
            layer.at<Vec3f>(Point(x,y)) = color;
        }
        //std::cout << y << std::endl;
#ifdef OUTPUT
        cv::normalize(layer, out, 0, 1, cv::NORM_MINMAX);
        imshow("out", out);
        waitKeyEx(1);
#endif
    }

    // left -> right rendering
    for(int x=WINDOW+imgfloat.cols; x < layer.cols-WINDOW; x++) {
        for(int y=WINDOW; y < layer.cols-WINDOW; y++) {
            find_best_match(layer, Point(x,y), &target, WINDOW+WINDOW/2, WINDOW+WINDOW/2, WINDOW+imgfloat.cols, WINDOW+imgfloat.rows);
            //std::cout << target << std::endl;
            Vec3f color = layer.at<Vec3f>(target);
            layer.at<Vec3f>(Point(x,y)) = color;
        }
        //std::cout << x << std::endl;
#ifdef OUTPUT
        cv::normalize(layer, out, 0, 1, cv::NORM_MINMAX);
        imshow("out", out);
        waitKeyEx(1);
#endif
    }

    Rect rect_out(WINDOW, WINDOW, layer.cols-2*WINDOW, layer.rows-2*WINDOW);
    cv::normalize(layer(rect_out), out, 0, 1, cv::NORM_MINMAX);
    imshow("out", out);
    out.convertTo(out, CV_8UC3, 255.0);
    imwrite("../textures/synth/texture7-synth-w5.jpg", out);

    waitKeyEx(0);
    return 0;
}