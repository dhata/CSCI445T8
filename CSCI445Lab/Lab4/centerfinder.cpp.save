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

void turn45degreesCW(){
	fprintf(fp, "0=160\n"); //Stop
    fprintf(fp, "1=160\n"); //Stop
    fprintf(fp, "2=160\n"); //Stop
    fprintf(fp, "3=160\n"); //Stop       
    fflush(fp);
    delay(200);
    stop(300);
}

int findMaxIdx(int* arr){
	int max_idx = 0; 
	for (int i=0;i<8;i++){
		if (arr[i] > arr[max_idx]){
			max_idx = i;
		}
	}
	return max_idx;
}

int findMinIdx(int* arr){
	int min_idx = 0; 
	for (int i=0;i<8;i++){
		if (arr[i] < arr[min_idx]){
			min_idx = i;
		}
	}
	return min_idx;
}

bool foundCenter(int* arr, int MOE){
	int max_idx = findMaxIdx(arr);
	int min_idx = findMinIdx(arr);
	
	if ((arr[max_idx] - arr[min_idx]) <= MOE){
		return true;
	}
	return false;
}

int main(void) {
    setup();
	fp = fopen("/dev/servoblaster", "w");
        if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
        }

	while (true){
		int distance[8];
		for (int i=0; i<8; i++){
			distance[i] = getCM();
			if (distance[i] >= 359){
				distance[i] = 0;
			}
			turn45degreesCW();
			delay(100);
		}
	
		for (int i=0; i<8; i++){
			printf("%d :", i*45);
			printf("%d\n", distance[i]);
		}
	
		if (foundCenter(distance, 25)){
			printf("Stacy is victorious! \n");
			return 0;
		}
		delay(500);
		int max_idx = findMaxIdx(distance);
		for (int i=0; i< max_idx; i++){
			turn45degreesCW();
			delay(100);
		}
		move("182", "100", "100", "100");
		stop(750);
	
		printf("Max distance was at: %d degrees\n", (findMaxIdx(distance) * 45));
	}
    
	return 0;
}
