#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
        cv::VideoCapture cap(0);
        cv::Mat frame;

        cap >> frame;

        cv::imwrite("captured_image.jpg", frame);

        cap.release();

        std::cout << "hello";
        return 0;
}