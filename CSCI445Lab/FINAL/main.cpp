//Standard imports
#include <iostream>
#include <vector>
#include <fstream>

//Open CV imports
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv/highgui.h>
#include <opencv/cv.h>

//Motor imports
#include <stdio.h>
#include <stdlib.h>
#include "wiringPi.h"
#include <string>
#include <sstream>

//Compass imports
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <linux/i2c-dev.h> 
#include <math.h>

//Particle filtering imports
#include "Util_Map.h"
#include "Particle.h"
#include "Util.h"

//namespaces
using namespace std;

//define pin 5 as the Sonar pin
#define SONAR_PIN 5

//motor file pointer
FILE *fp;

//FUNCTION PROROTYPES
void setup();
int getCM();
void move(string, string, string, string);
void stop(int);
void driveForward(int);
void turnCW(int);
void turn CCW(int);
void selectDevice(int, int, char*);
void writeToDevice(fd, reg, val);
double getAngle();
void turnToAngle(int);

//wiring pi setup
void setup() {
        wiringPiSetup();
}

//Sonar reading function
int getCM() {
  	pinMode(SONAR_PIN, OUTPUT);
  	digitalWrite(SONAR_PIN, LOW);
  	delay(30);
  	digitalWrite(SONAR_PIN, HIGH);
  	delay(50);
  	digitalWrite(SONAR_PIN, LOW);
	pinMode(SONAR_PIN, INPUT);

        //Wait for echo start
        while(digitalRead(SONAR_PIN) == LOW);

        //Wait for echo end
        long startTime = micros();
        while(digitalRead(SONAR_PIN) == HIGH);
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

//MOTOR FUNCTIONS
void stop(int delayVal){
    fprintf(fp, "0=151\n"); 
    fprintf(fp, "1=152\n"); 
    fprintf(fp, "2=151\n"); 
    fprintf(fp, "3=152\n");       
    delay(delayVal);
    fflush(fp);
}

void driveForward(int time){
    fprintf(fp, "0=100\n"); 
    fprintf(fp, "1=182\n"); 
    fprintf(fp, "2=100\n"); 
    fprintf(fp, "3=182\n"); 
    fflush(fp);
    stop(time);
}

void turnCW(int time){
    fprintf(fp, "0=160\n"); 
    fprintf(fp, "1=160\n"); 
    fprintf(fp, "2=160\n"); 
    fprintf(fp, "3=160\n");        
    fflush(fp);
    stop(time);
}

void turnCCW(int time){
	fprintf(fp, "0=160\n"); 
    fprintf(fp, "1=160\n"); 
    fprintf(fp, "2=160\n"); 
    fprintf(fp, "3=160\n");        
    fflush(fp);
    stop(time);
}

//COMPASS STUFF
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

//turn to compass angle
void turnToAngle(int desiredAngle){
	double measuredAngle = getAngle();
	int realAngle = (int) ((measuredAngle * -1) + 150);
	realAngle = realAngle % 360;

	while (abs(realAngle-desiredAngle) > 6){
		turnCW(100);
		stop(250);
		measuredAngle = getAngle();
		realAngle = (int) ((measuredAngle * -1) + 150);
		realAngle = realAngle % 360;
	}
}

int main(int argc, char** argv){
	//set up wiring pi
	setup();
	fp = fopen("/dev/servoblaster","w");
	if (fp == NULL){
		printf("Error opening file\n");
		exit(0);
	}
	//stop any residual servo motors
	stop (100);
	
	
}