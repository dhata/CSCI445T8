#ifndef Util_Map_h
#define Util_Map_h

#include <iostream>
#include <vector>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/legacy/legacy.hpp>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "Util.h"
#include "Particle.h"
//#include <array>

using namespace std;
using namespace cv;

void parseFile(std::vector<Point> &edges) {
    std::ifstream myfile;
    //myfile.open ("map.txt");
    myfile.open ("map_origin.txt");
    
    if (myfile.is_open()){
        while (!myfile.eof()){
            cv::Point p1;
            cv::Point p2;
            int type;// 0 is wall,1 is rocket, 2 is docking
            if (myfile >> p1.x >> p1.y >> p2.x >> p2.y >> type ) {
                p1.x = p1.x*25;//convert ft to cm
                p1.y = p1.y*25;//convert ft to cm
                p2.x = p2.x*25;//convert ft to cm
                p2.y = p2.y*25;//convert ft to cm
                if(type == 0) {
                    //wall
                    edges.push_back(p1);
                    edges.push_back(p2);
                }
            }
        }
    }
    myfile.close();
}

void drawMap(Mat& img, std::vector<Point> &edges) {
    parseFile(edges);
    
    int thickness = 6; //6
    int lineType = 8; //8

    //Draw Wall
    for(unsigned int i = 0;i < edges.size()-1; i+=2){
        cv::Point p1 = edges[i];
        cv::Point p2 = edges[i+1];
        cv::line (img, p1, p2, Scalar(255, 0, 0), thickness, lineType);
    }
   
}

#endif

