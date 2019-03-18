#include <iostream>
#include <string>
#include <thread>

#include "opencv/cv.hpp"
#include "opencv2/dnn.hpp"

#include "arduino_control.hpp"
#include "udp_reciever.hpp"

int main()
{
    ArduinoController arduino_controller;

    // TODO test that works asynchonoously
    // start udp socket to listen for gui command
    std::cout << "Starting UDP listener" << std::endl;
    boost::asio::io_service io_service;
    UDP_Receiver udp_receiver(io_service, arduino_controller, 5008);
    std::thread udp_thread{[&io_service](){io_service.run();}};

    bool init_success = arduino_controller.initialize();
    if (!init_success) {
        std::cerr << "Failed to connect to arduino" << std::endl;
        // TEMP remove below comment when arduino is connected
        //return 1;
    }

    // start camera
    cv::VideoCapture cam;
    cam.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cam.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    cam.set(CV_CAP_PROP_BUFFERSIZE, 1);
    bool cam_opened = cam.open(0);
    std::chrono::milliseconds retry_delay(500);
    std::this_thread::sleep_for(retry_delay);
    if (!cam_opened) {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }

    // Open window
    cv::namedWindow("Window");

    cv::Mat frame;
    cv::Mat output;

    cv::dnn::Net neural_net = cv::dnn::readNetFromTensorflow("frozen_inference_graph.pb", "graph.pbtxt");

    const int idx[4] = {0, 0, 0, 0};
    int attempts = 0;
    std::cout << "got to while" << std::endl;
    while (true) {
        std::cout << "Getting frame" << std::endl;
	bool got_frame = cam.read(frame);
	std::cout << "checking frame" << std::endl;
        if (!got_frame) {
            if (attempts++ > 3) {
                break;
	    } else {
                std::this_thread::sleep_for(retry_delay);
                continue;
	    }
	}
	attempts = 0;
	std::cout << "Setting nn input" << std::endl;
        neural_net.setInput(cv::dnn::blobFromImage(frame, 1.0, cv::Size(320, 240)));
	std::cout << "pushing through nn" << std::endl;
        output = neural_net.forward();
	std::cout << "got through nn" << std::endl;

        float *data = (float*) output.data;
        for (size_t i = 0; i < output.total(); i+= 7) {
            float confidence = data[i+2];
            if (confidence > 0.3) {
                int classId = (int) data[i+1];
                int left = (int) (data[i+3] * 320);
                int top = (int) (data[i+4] * 240);
                int right = (int) (data[i+5] * 320);
                int bottom = (int) (data[i+6] * 240);
                int width = right - left + 1;
                int height = bottom - top + 1;
                cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar::all(255));
                std::string label = std::to_string(classId+10) + " : " + std::to_string((int) (confidence * 100)) + "%";
                int base_line;
                cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &base_line);
                top = cv::max(top, labelSize.height);
                cv::rectangle(frame, cv::Point(left, top-labelSize.height), cv::Point(left+labelSize.width, top + base_line), cv::Scalar::all(255), cv::FILLED);
                cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar());
            }
        }

        double freq = cv::getTickFrequency() / 1000;
        std::vector<double> layer_times;
        double t = neural_net.getPerfProfile(layer_times) / freq;
        std::string label = "Inference Time: " + std::to_string(t) + " ms";
        cv::putText(frame, label, cv::Point(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));
        cv::imshow("Window", frame);
        int c = cv::waitKey(1);
        if (c != -1) break;
    }

    // Begin while loop, waiting for exit code

    //bool exit = false;
    //std::string input;

    //std::cout << "Q: con1 speed up\nZ: con1 speed down\nA: con1 stop\n" <<
    //        "W: con2 speed up\nX: con2 speed down\nS: con2 stop\n" <<
    //        "Any number sends bin number to sorter" << std::endl;

    //while(!exit) {
    //    std::getline(std::cin, input);

    //    if (input == "exit" || input == "quit") {
    //        exit = true;
    //        break;
    //    } else {
    //        bool success = arduino_controller.send_command(input);
    //    }
    //}

    std::cout << "Finished Sucessfully" << std::endl;
    return 0;
}
