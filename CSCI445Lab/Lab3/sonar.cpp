#include <stdio.h>
#include <stdlib.h>
#include "wiringPi.h"
#include <string>

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

void move(std::string val1, std::string val2, std::string val3, std::string val4){
    std::string str = "0=" + val1 + "\n";
    fprintf(fp, (str.c_str())); //Servo#0, Counter Clockwise
   // fprintf(fp, ("1=" + val2 + "\n")); //Servo#1, Counter Clockwise
   // fprintf(fp, ("2=" + val3 + "\n")); //Servo#2, Counter Clockwise
   // fprintf(fp, ("3=" + val4 + "\n")); //Servo#2, Counter Clockwise
    delay(750);
    fflush(fp);
}

void stop(){
    fprintf(fp, "0=150\n"); //Stop
    fprintf(fp, "1=152\n"); //Stop
    fprintf(fp, "2=150\n"); //Stop
    fprintf(fp, "3=152\n"); //Stop       
    delay(1000);
    fflush(fp);
}

int main(void) {
    setup();
	fp = fopen("/dev/servoblaster", "w");
        if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
        } 
	while (1) {
        int t0 = getCM();
        move("182","100","100","100");
        stop();
		delay(1000);
	}
        
	return 0;
}
