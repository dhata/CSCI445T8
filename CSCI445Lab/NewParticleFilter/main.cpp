#include <iostream>
#include <vector>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/legacy/legacy.hpp>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "Util_Map.h"
#include "Particle.h"
#include "Util.h"

#include <stdio.h>
#include <stdlib.h>
//#include "wiringPi.h"
#include <string>
#include <sstream>

/* 
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <linux/i2c-dev.h> 
#include <math.h> 
*/

using namespace std;
using namespace cv;
/*
#define TRIG 5

FILE *fp;

void setup() {
        wiringPiSetup();
}

int getCM() {
  	pinMode(TRIG, OUTPUT);
  	digitalWrite(TRIG, LOW);
  	delay(30);
  	digitalWrite(TRIG, HIGH);
  	delay(50);
  	digitalWrite(TRIG, LOW);
	pinMode(TRIG, INPUT);

        //Wait for echo start
        while(digitalRead(TRIG) == LOW);

        //Wait for echo end
        long startTime = micros();
        while(digitalRead(TRIG) == HIGH);
        long travelTime = micros() - startTime;

        //Get distance in cm
        int distance = travelTime / 58;

        return distance;
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

void turnCW(int time){
    fprintf(fp, "0=160\n"); //Stop
    fprintf(fp, "1=160\n"); //Stop
    fprintf(fp, "2=160\n"); //Stop
    fprintf(fp, "3=160\n"); //Stop       
    fflush(fp);
    stop(time);
}

void driveForward(int time){
    fprintf(fp, "0=100\n"); //Stop
    fprintf(fp, "1=182\n"); //Stop
    fprintf(fp, "2=100\n"); //Stop
    fprintf(fp, "3=182\n"); //Stop       
    fflush(fp);
    stop(time);
}
 
const int HMC5883L_I2C_ADDR = 0x1E; 
void selectDevice(int fd, int addr, char * name) { 
	if (ioctl(fd, I2C_SLAVE, addr) < 0) { 
		fprintf(stderr, "%s not present\n", name); 
	} 
} 

void writeToDevice(int fd, int reg, int val) { 
	char buf[2]; buf[0]=reg; buf[1]=val; 
	if (write(fd, buf, 2) != 2) { 
		fprintf(stderr, "Can't write to ADXL345\n"); 
	} 
} 
double getAngle(){
	int fd; 
	unsigned char buf[16]; 
	if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) { 
		fprintf(stderr, "Failed to open i2c bus\n"); 
		return 1; 
	} 
	selectDevice(fd, HMC5883L_I2C_ADDR, "HMC5883L"); 
	writeToDevice(fd, 0x01, 32); 
	writeToDevice(fd, 0x02, 0); 
	for (int i = 0; i < 10000; ++i) { 
		buf[0] = 0x03; 
		if ((write(fd, buf, 1)) != 1) { 
			fprintf(stderr, "Error writing to i2c slave\n"); 
		} 
		if (read(fd, buf, 6) != 6) { 
			fprintf(stderr, "Unable to read from HMC5883L\n"); 
		} 
		else { 
			short x = (buf[0] << 8) | buf[1]; 
			short y = (buf[4] << 8) | buf[5]; 
			short z = (buf[2] << 8) | buf[3]; 
			float angle = atan2(y, x) * 180 / M_PI; 
			//printf("x=%d, y=%d, z=%d\n", x, y, z); 
			//printf("angle = %0.1f\n\n", angle);
			return angle; 
		} 
		usleep(600 * 1000); 
	} 
}
*/
int main(int argc, char** argv){
	//setup
	/*
	setup();
	fp = fopen("/dev/servoblaster","w");
	if (fp == NULL){
		printf("Error opening file\n");
		exit(0);
	}

	stop (100);
	double measuredAngle = getAngle();
	*/
	const int NUM_PARTICLES = 100;
	int x =25, y = 25;
	double angle = 0;
	/*
	if (measuredAngle >= -120 && measuredAngle <= -50){
		angle = 0;
	} 
	else if(abs(measuredAngle) > 145){
		angle = 90;
	}
	else if(measuredAngle >=25 && measuredAngle <= 100){
		angle = 180;
	}
	else{
		angle = 270;
	}
	cout <<"Angle: " << angle << endl;*/
	Mat img = Mat::zeros(300,300,CV_8UC3);
	drawCircle(img, x, y, true);

	vector<Point> edges;
	vector<Point> particleShoot;
	vector<Point> virus;
	vector<Point> labA;
	Point labB;
	drawMap(img,edges,virus, labA, labB);
	char main_window[] = "Particle Filter";
	imshow(main_window, img);

	//Create particle vector
	vector<Particle> particles;
	
	for (int i=0;i<NUM_PARTICLES;i++){
		Particle temp;
		particles.push_back(temp);
		particleShoot.push_back(Point(0,0));
	}
	
	char dir;
	waitKey( 100 );

	double sonarDistance = 0;

	//cout << "GetCM: " << getCM() << endl;

	while (true){
		imshow(main_window, img);
		waitKey(100);
		cout << "[t]urn clockwise, go [f]orward, or [m]easure?" << endl;
		cin >> dir;
		/*
		if (dir == 'f'){
			driveForward(500);
		}
		else if(dir == 't'){
			turnCW(923);
		}
		else if(dir == 'm'){
			sonarDistance = getCM();
			cout << "Sonar distance: " << sonarDistance << endl;
			if (sonarDistance > 300){
				cout << "Sonar failed. Try again." << endl;
				continue;
			}
		}*/
		moveCircle(img, dir, angle, x, y, particles, main_window, particleShoot, sonarDistance);
		drawParticles(img, particles, true);
	}
}
