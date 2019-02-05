#include <iostream>
#include <string>

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

    vid.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    vid.set(CV_CAP_PROP_FRAME_WIDTH, 480);
    int frame_count = 1;

    while (vid.read(frame)) {
        imshow("Test Window", frame);
        int keyCode = waitKey(1000/fps);
        if (keyCode == 27) {
            break;
        } else if (keyCode == 32) {
            std::string filename("frames/frame");
            filename += std::to_string(frame_count++);
            filename += std::string(".jpg");
            bool save_result = imwrite(filename, frame);
        } else {
            continue;
        }
    }

    cv::destroyAllWindows();

    return 0;
}
