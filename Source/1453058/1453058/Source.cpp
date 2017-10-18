#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <cstring>
#pragma comment(lib, "opencv_world330d.lib")

cv::Mat originalImage;
cv::Mat processedImage;
cv::Mat grayImage;
std::vector<cv::Mat> channelsImage(3);
int channelIndex = 0;

void onSmoothChange(int value, void* userdata)
{
}

void onXChange(int value, void* userdata)
{
	cv::GaussianBlur(grayImage, processedImage, cv::Size(9, 9), value);
	cv::imshow("1453058", processedImage);
}

void onYChange(int value, void* userdata)
{
	cv::GaussianBlur(grayImage, processedImage, cv::Size(3, 3), 0.0, value);
	cv::imshow("1453058", processedImage);
}

int main(int argc, char* argv[])
{
	char *file = nullptr;
	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
		{
			if (i + 1 < argc)
			{
				file = argv[++i];
			}
			else
			{
				std::cerr << argv[i] << " option requires one argument." << std::endl;
			}
		}
	}
	if (file == nullptr)
	{
		cv::VideoCapture cap;
		// open the default camera, use something different from 0 otherwise;
		// Check VideoCapture documentation.
		if (!cap.open(0))
			return 0;
		cap >> originalImage;
		if (originalImage.empty())
		{
			std::cerr << "Could not capture originalImage!" << std::endl;
			return -1;
		}
		cap.release();
	}
	else
	{
		originalImage = cv::imread(file, CV_LOAD_IMAGE_COLOR); // Read the file

		if (originalImage.empty())                              // Check for invalid input
		{
			std::cerr << "Could not open or find the originalImage!" << std::endl;
			return -1;
		}
	}
	processedImage = originalImage;
	cv::split(originalImage, channelsImage);
	cv::cvtColor(originalImage, grayImage, CV_BGR2GRAY);

	cv::namedWindow("1453058", cv::WINDOW_AUTOSIZE); // Create a window for display.
	cv::imshow("1453058", originalImage);
	while (1)
	{
		switch (cv::waitKey(0))
		{
		case 'i':
			processedImage = originalImage;
			cv::imshow("1453058", originalImage);
			break;
		case 'w':
			cv::imwrite("out.jpg", processedImage);
			break;
		case 'g':
			processedImage = grayImage;
			cv::imshow("1453058", processedImage); 
			break;
		case 'G':
			break;
		case 'c':
			if (channelIndex > 2)
			{
				channelIndex = 0;
			}
			processedImage = channelsImage[channelIndex];
			cv::imshow("1453058", processedImage);
			++channelIndex;
			break;
		case 's':
		{
			int value = 0;
			cv::namedWindow("1453058_smooth", cv::WINDOW_AUTOSIZE); // Create a window for display.
			cv::cvtColor(originalImage, processedImage, CV_BGR2GRAY);
			cv::createTrackbar("smooth", "1453058_smooth", &value, 100, onSmoothChange);
		}
			break;
		case 'S':
			std::cerr << 'S' << std::endl;
			break;
		case 'x':
		{
			int value = 0;
			cv::namedWindow("1453058_x", cv::WINDOW_AUTOSIZE); // Create a window for display.
			cv::createTrackbar("x", "1453058_x", &value, 255, onXChange);
			cv::imshow("1453058", grayImage);
		}
			break;
		case 'y':
		{
			int value = 0;
			cv::namedWindow("1453058_y", cv::WINDOW_AUTOSIZE); // Create a window for display.
			cv::createTrackbar("y", "1453058_y", &value, 255, onXChange);
			cv::imshow("1453058", grayImage);
		}
			break;
		case 'm':
			std::cerr << 'm' << std::endl;
			break;
		case 'r':
			std::cerr << 'r' << std::endl;
			break;
		case 'h':
			std::cerr << 'h' << std::endl;
			break;
		}
	}
	return 0;
}