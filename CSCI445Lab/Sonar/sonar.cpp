#include <stdio.h>
#include <stdlib.h>
#include "wiringPi.h"
#include <string>
#include <sstream>

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
    delay(100);
    fflush(fp);
}

void stop(){
    fprintf(fp, "0=151\n"); //Stop
    fprintf(fp, "1=152\n"); //Stop
    fprintf(fp, "2=151\n"); //Stop
    fprintf(fp, "3=152\n"); //Stop       
    delay(300);
    fflush(fp);
}

int main(void) {
    setup();
	fp = fopen("/dev/servoblaster", "w");
        if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
        }

	int t0 = getCM();
	move("182","100","100","100");
	int sum = 0;
	while (1) {
        	int t1 = getCM();
		int error = t1-10;
        	int P = error*2;
		int D = (error - (t0-10))*1;
		if (abs(error) < 5){
			sum = sum + error;
		}
		else{
			sum = 0;
		}
		int I =  sum*1;
		int v1 = 105+P+I+D;
		int v2 = 100 -P-I-D;
		int v3 = 105 -P -I -D;
		int v4 = 100 -P-I-D;
		std::stringstream ss;
		ss << v1;
		std::string s1 = ss.str();
		std::stringstream ss2;
		ss2 << v2;
		std::string s2 = ss2.str();
		std::stringstream ss3;
		ss3 << v3;
		std::string s3 = ss3.str();
		std::stringstream ss4;
		ss4 <<v4;
		std::string s4 = ss4.str();
		move(s1, s2, s3, s4);
        	stop();
		delay(300);
		t0 = getCM();
	}
        
	return 0;
}
