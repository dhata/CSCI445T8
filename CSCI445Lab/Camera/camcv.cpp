#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "wiringPi.h"

FILE* fp;


using namespace cv;
using namespace std;
void setup(){
	wiringPiSetup();
}

void move(std::string val1, std::string val2, std::string val3, std::string val4 ){
    std::string str = "0=" + val1 + "\n";
    fprintf(fp, (str.c_str())); //Servo#0, Counter Clockwise
    str= "1=" + val2 + "\n";
    fprintf(fp, (str.c_str())); //Servo#1, Counter Clockwise
    str= "2=" + val3 + "\n";
    fprintf(fp, (str.c_str())); //Servo#2, Counter Clockwise
    str= "3=" + val4 + "\n";
    fprintf(fp, (str.c_str())); //Servo#2, Counter Clockwise
    delay(300);
    fflush(fp);
}

void stop(int delayVal){
    fprintf(fp, "0=151\n"); //Stop
    fprintf(fp, "1=152\n"); //Stop
    fprintf(fp, "2=151\n"); //Stop
    fprintf(fp, "3=152\n"); //Stop       
    delay(delayVal);
    fflush(fp);
}

void adjust(double a, double x){
	cout << "Difference in areas: " << a << endl;
	cout << "Difference in x: " << x << endl;
	double left_base = 151;
	double right_base = 152;
	double new_left = left_base + (x/18);
	double new_right = right_base + (x/18);

	string ls, rs;
	stringstream ss;
	ss << new_left;
	ss >> ls;
	ss.clear();
	ss << new_right;
	ss >> rs;
	cout << "New left: " << ls << endl;
	cout << "New right: " << rs << endl;

	move(ls, rs, ls, rs);
	stop(250);
	cout << a/1000<<endl;
	if (a<0){
		move ("100", "182", "182", "182");
		stop (-1*a/1000);
	} else {
		move ("182", "100", "100", "100");
		stop (a/1000);
	}
	/*new_right = right_base + (a/10000);
	new_left = left_base + (a/10000);
	string la, ra;
	ss.clear();
	ss<< new_right;
	ss>>ra;
	ss.clear();
	ss<< new_left;
	ss>>la;
	cout<< "Area new left: " << la << endl;
	cout << "area new right: " << rs<< endl;

	move(la, ra, la, ra);
	stop(250);*/
}

 int main( int argc, char** argv )
 {

 	setup();

	fp = fopen("/dev/servoblaster", "w");
        if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
        }
    VideoCapture cap(0); //capture the video from webcam
	stop (100);
    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

cap.set(CV_CAP_PROP_FRAME_WIDTH, 160);
cap.set(CV_CAP_PROP_FRAME_HEIGHT, 120);

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

  int iLowH = 170;
 int iHighH = 179;

  int iLowS = 150; 
 int iHighS = 255;

  int iLowV = 60;
 int iHighV = 255;

  //Create trackbars in "Control" window
 createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 createTrackbar("HighH", "Control", &iHighH, 179);

  createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 createTrackbar("HighS", "Control", &iHighS, 255);

  createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
 createTrackbar("HighV", "Control", &iHighV, 255);

  int iLastX = -1; 
 int iLastY = -1;

  //Capture a temporary image from the camera
 Mat imgTmp;
    imgTmp = Mat::zeros(301, 301, CV_8UC3);

 cap.read(imgTmp); 

  //Create a black image with the size as the camera output
 Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
 
int iterations = 0;
double area_sum = 0;
double x_sum = 0;
int last_area = 300000;
int last_x = 80;
    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video



         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

    Mat imgHSV;

   cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
  Mat imgThresholded;

   inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
  //morphological opening (removes small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

   //morphological closing (removes small holes from the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

   //Calculate the moments of the thresholded image
  Moments oMoments = moments(imgThresholded);

   double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;

   // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
  if (dArea > 10000)
  {
   //calculate the position of the ball
   int posX = dM10 / dArea;
   int posY = dM01 / dArea;        
        
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
    line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
 }
	
	cout << "X position is " << posX << endl;
	cout << "Area is " << dArea << endl;

	area_sum += dArea;
	x_sum += posX;
	if (iterations == 3){
		area_sum /= 3;
		x_sum /= 3;
		adjust((area_sum-last_area),(x_sum-last_x));
		//last_area = area_sum;
		//last_x = x_sum;
		area_sum = x_sum = 0;
		iterations = 0;
	}
	iterations++;
    iLastX = posX;
   iLastY = posY;
  }

   imshow("Thresholded Image", imgThresholded); //show the thresholded image

   imgOriginal = imgOriginal + imgLines;
  imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

   return 0;
}

