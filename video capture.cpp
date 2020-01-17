/*@author gihan tharanga*/

#include "VideoCap.h"

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "opencv2\objdetect\objdetect.hpp"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;
using namespace cv;


int FaceDetector(string &classifier){

	
	CascadeClassifier face_cascade;
	string window = "Capture - face detection";

	if (!face_cascade.load(classifier))
	{
		cout << " Error loading file" << endl;
		return -1;
	}

	VideoCapture cap(0);
	

	if (!cap.isOpened())
	{
		cout << "exit" << endl;
		return -1;
	}

	//double fps = cap.get(CV_CAP_PROP_FPS);
	//cout << " Frames per seconds " << fps << endl;

	namedWindow(window, 1);
	long count = 0;

	string name = "gihan";
	while (true)
	{
		vector<Rect> faces;
		Mat frame;
		Mat greyScaleFrame;
		Mat cropImg;

		cap >> frame;
		
		count++;               //count frames;

		if (!frame.empty()){

			//convert image to gray scale
			cvtColor(frame, greyScaleFrame, CV_BGR2GRAY);
			
			//equalize
			equalizeHist(greyScaleFrame, greyScaleFrame);

			face_cascade.detectMultiScale(greyScaleFrame, faces, 1.1, 3, 0, cv::Size(190, 190), cv::Size(200, 200));

			cout << faces.size() << " faces detected" << endl;
			std::string frameset = std::to_string(count);
			std::string faceset = std::to_string(faces.size());

			int width = 0, height = 0;

			//region of interest [crop region]
			cv::Rect roi;

			for (int i = 0; i < faces.size(); i++)
			{
				rectangle(greyScaleFrame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(255, 0, 255), 1, 1, 0);
				cout << "Width: " << faces[i].width << "      Height: " << faces[i].height << endl;
				width = faces[i].width; height = faces[i].height;

				//select the roi
				roi.x = faces[i].x; roi.width = faces[i].width;
				roi.y = faces[i].y; roi.height = faces[i].height;

				//get the roi from orginal frame

				cropImg = greyScaleFrame(roi);
				cv::imshow("ROI", cropImg);
                cv::imwrite("F://cropped image.png", cropImg);

			}

			std::string wi = std::to_string(width);
			std::string he = std::to_string(height);

			cv::putText(greyScaleFrame, "Frames: " + frameset, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
			cv::putText(greyScaleFrame, "Faces Detected: " + faceset, cvPoint(30, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
			cv::putText(greyScaleFrame, "Resolution " + wi + " x " + he, cvPoint(30, 90), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
			

			cv::imshow(window, greyScaleFrame);
		}
		if (waitKey(30) >= 0) break;
	}
}

int videoCapturing()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "camera is not opened" << endl;
		return -1;
	}

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		if (!frame.empty()) {
			cvtColor(frame, edges, CV_HLS2BGR);
			GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
			//Canny(edges, edges, 0, 30, 3);
			imshow("edges", edges);
		}
		if (waitKey(30) == 10) break;
	}

	return 0;
}

int videoCapOriginal()
{
	/*camera*/
	VideoCapture cap(0);

	/*initiallize*/
	if (!cap.isOpened())
	{
		cout << "exit" << endl;
		return -1;
	}

	/*create window for display video*/
	
	int counter = 0;
	string name;
	while (true)
	{
		name = counter + " window ";
		namedWindow(name, 1);
		/*reads each frame and assign to mat*/
		Mat frame;
		cap >> frame;
		
		if (!frame.empty()){
			
			imshow(name, frame);
		}
		if (waitKey(30) >= 0) break;
	}
	return 0;
}

/**
 * Rotate an image
 */
void rotate(cv::Mat& src, double angle, cv::Mat& dst)
{
    int len = std::max(src.cols, src.rows);
    cv::Point2f pt(len/2., len/2.);
    cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

    cv::warpAffine(src, dst, r, cv::Size(len, len));
}


int photo_face_detector(string &classifier)
{
	
	CascadeClassifier face_cascade;
	//-- 1. Load the cascades
	if (!face_cascade.load(classifier))
	{ 
		printf("--(!)Error loading\n"); 
		return -1; 
	};

	
	Mat  frame, rotated;
	frame = imread("F:/Data Base/Shahzeb/02.png");


	if (!frame.empty())
	{	
		
		Mat greyScaleFrame;
		Mat cropImg;
		vector<Rect> faces;


		/*int eye1_x = 135, eye1_y = 181, eye2_x = 201, eye2_y = 198;

		double difference =  eye1_y - eye2_y ;
		double denom = (eye1_x - eye2_x );
		double ratio = difference / denom;
		double angle_rad = atan(ratio);
		double angle = angle_rad*57.13;

		


		cout << "Angle is: " << angle << "\tDen: " << denom;*/
	//	rotate(frame, angle , rotated);

		////convert image to gray scale
		//cvtColor(frame, greyScaleFrame, CV_BGR2GRAY);
		//	
		////equalize
		//equalizeHist(greyScaleFrame, greyScaleFrame);

		face_cascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(190, 190), cv::Size(200, 200));


		int width = 0, height = 0;

		//region of interest [crop region]
			cv::Rect roi;
			cout << "Number of faces: " << faces.size();
			for (int i = 0; i < faces.size(); i++)
			{
				rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(255, 0, 255), 1, 1, 0);
				cout << "Width: " << faces[i].width << "      Height: " << faces[i].height << endl;
				width = faces[i].width; height = faces[i].height;

				//select the roi
				roi.x = faces[i].x; roi.width = faces[i].width;
				roi.y = faces[i].y; roi.height = faces[i].height;

				//get the roi from orginal frame

				cropImg = frame(roi);
				cv::imshow("Cropped and rotated", cropImg);
				
                cv::imwrite("F:/Data Base/Shahzeb/04.png", cropImg);

			}

				
			imshow("original", frame);

		if (waitKey(30) == 10)
		return 0;
	}


	else
	{	
	cout << "Error";
	cin.get();
	}

	return 0;
}
