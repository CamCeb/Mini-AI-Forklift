#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/asio.hpp>

int main()
{       
	// create buffer for encoded frame
	std::vector<uchar> buf;

	// init for openCV
	cv::VideoCapture cap(0); 

	// init for tcp stream
	boost::asio::io_context io;
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 9000));
	tcp::socket socket(io);
	acceptor.accept(socket);	

	while(true){
		cv::Mat frame;
		cap >> frame; // put current frame in memory

		cv::imencode(".jpg", frame, buf); // encode frame to send
		uint32_t len = htonl(buf.size()); // get length of encoded frame
		
		boost::asio::write(socket, boost::asio::buffer(&len, 4)); //send 4-byte length header
		boost::asio::write(socket, boost::asio::buffer(buf)); // send JPEG bytes
		std::this_thread::sleep_for(std::chrono::milliseconds(250)); // wait 1/4 seconds
    }

}