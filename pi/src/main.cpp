#include <iostream>

#include "opencv/cv.hpp"

using namespace cv;

const int fps = 20;

int main()
{
    std::cout << "WORKS!" << std::endl;

    namedWindow("Test Window");
    Mat frame;

    VideoCapture vid(0);
    if (!vid.isOpened()) {
        std::cout << "Vid is closed" << std::endl;
        return -1;
    }

    while (vid.read(frame)) {
        imshow("Test Window", frame);
        if (waitKey(1000/fps) >= 0) break;
    }

    cv::destroyAllWindows();

    return 0;
}
