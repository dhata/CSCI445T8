#ifndef motor_h_
#define motor_h_

#include <stdio.h>
#include <stdlib.h>
#include "wiringPi.h"
#include <string>
#include <sstream>

#define TRIG 5

void setup(){
	wiringPiSetup();
}

int getCM(){
	pinMode(TRIG, OUTPUT);
	digitalWrite(TRIG, LOW);
	delay(30);
	digitalWrite(TRIG, HIGH);
	delay(50);
	digitalWrite(TRIG,LOW);
	pinMode(TRIG, INPUT);

	while (digitalRead(TRIG) == LOW);

	long startTime = micros();
	while (digitalRead(TRIG) == HIGH);
	long travelTime = micros() - startTime;


	int distance = travelTime / 58;

	return distance;
}

void move(File* fp, std::string val1, std::string val2, std::string val3, std::string val4 ){
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

void stop(File* fp, int delayVal){
    fprintf(fp, "0=151\n"); //Stop
    fprintf(fp, "1=152\n"); //Stop
    fprintf(fp, "2=151\n"); //Stop
    fprintf(fp, "3=152\n"); //Stop       
    delay(delayVal);
    fflush(fp);
}

void turn45degreesCW(File* fp){
    fprintf(fp, "0=160\n"); //Stop
    fprintf(fp, "1=160\n"); //Stop
    fprintf(fp, "2=160\n"); //Stop
    fprintf(fp, "3=160\n"); //Stop       
    fflush(fp);
    delay(200);
    stop(300);
}


#endif
