
#ifndef Particle_Filter_Util_h
#define Particle_Filter_Util_h

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/legacy/legacy.hpp>

#include <opencv/highgui.h>
#include <opencv/cv.h>
//#include <array>
#include "Particle.h"

using namespace std;
using namespace cv;

void drawParticles(Mat& img, vector<Particle>& particles, bool visible);
void updateAngle(double& angle);
void updateParticleShoot(Mat&, vector<Particle>&, vector<Point>&, double, vector<Point>&);
void drawMeasurementLine(char*,Mat& , double, int, int);


double getProbability(double u, double s, double x){
    double coefficient = 1.0/sqrt(2.0 * M_PI * s*s);    //s = Standard Deviation, s*s = Variance
    return coefficient * exp(-(x-u)*(x-u)/(2.0 * s*s));
}

double distToEdge(cv::Point pt1, cv::Point pt2) {
    double x = pt1.x - pt2.x;
    double y = pt1.y - pt2.y;
    
    return sqrt(pow(x, 2) + pow(y, 2));
}

void updateProbability(std::vector<Particle> &particles, std::vector<cv::Point> &particlesShoot, double distance) {
    
    float total_probabilities = 0.0;
    float new_weight = 0.0;
    float old_probabilities = 0.0;
    float new_probability = 0.0;
    double map_distance = 0.0;
    double sonar_variance = 20.0;
    
    // update all the particle probabilities
    for (int i=0; i<particles.size(); i++){
        cv::Point pos = particles[i].getPosition();
        
        // use heading to calculate the map distance from particle to wall.
        //map_distance =  distToEdge(direction,cv::Point(pos));
        map_distance = distToEdge(particles[i].getPosition(), particlesShoot[i]);
        
        // printf("Sonar: %f, Map_Distance: %f, direction: %d, Point(%d,%d), Weight: %f\n", distance, map_distance, direction, pos.i, pos.j, particles[i].getWeight());
        // Compute new probability using measured distance , map distance and sonar variance
        new_probability =  getProbability(distance, sonar_variance, map_distance); //distance by sonar report, sonar variance, given loaction
        
        

        // update each probability and compute total probabilities
        old_probabilities = particles[i].getWeight(); //P(robot@location)
        new_weight = old_probabilities * new_probability; //P(Sensor Reading| Robot @ Location) * P(robot@location)
        particles[i].setWeight(new_weight);
        total_probabilities += new_weight; //Ex: 0.25 + 0.25 + 0.3 = 0.8, so N = 1/0.8, here total_probabilities = 1/N
        //cout << "total_probabilities = " << total_probabilities << endl;
    }
    
    
    // Normalize all probabilities
    for (int i=0; i<particles.size(); i++){
        //normalized probability = probability / total probabilities
        particles[i].setWeight(particles[i].getWeight()/total_probabilities); //0.25/0.8 + 0.25/0.8 + 0.3/0.8 = 1
    }
    
}


std::vector<Particle> resampleParticles(std::vector<Particle>& oldParticles) {
    
    std::vector<Particle> newParticles;
    
    //Calculate a Cumulative Distribution Function for our particle weights
    std::vector<double> CDF;
    CDF.resize(oldParticles.size());
    CDF[0] = ((Particle)oldParticles[0]).getWeight();
    
    for(int i=1; i<CDF.size(); i++)
        CDF[i] = CDF[i-1] + oldParticles[i].getWeight();
    //Loop through our particles as if spinning a roulette wheel.
    //The random u that we start with determines the initial offset
    //and each particle will have a probability of getting landed on and
    //saved proportional to its posterior probability. If a particle has a very large
    //posterior, then it may get landed on many times. If a particle has a very low
    //posterior, then it may not get landed on at all. By incrementing by
    // 1/(numParticles) we ensure that we don't change the number of particles in our
    // returned set.
    
    int i = 0;
    double u = randomDouble()* 1.0/double(oldParticles.size());
    //double u = 1.0/double(oldParticles.size());
    
    
    for(int j=0; j < oldParticles.size(); j++){
        while(u > CDF[i]) //if i particle is very small, we don't want to let it in newparticle, so i++
            i++;
        
        Particle p = oldParticles[i]; //leave possible particles
        p.setWeight(1.0/double(oldParticles.size()));
        newParticles.push_back(p);
        
        u += 1.0/double(oldParticles.size());
    }
    
    
    return newParticles;
}

void moveParticles(vector<Particle>& particles, double angle, double distance, double variance, Mat& img){
	drawParticles(img, particles, false); //erase all particles
	for (unsigned int i=0; i<particles.size();i++){
		particles[i].moveParticle(angle, distance, variance);
	}
}

void drawCircle( Mat& img, int x, int y, bool visible )
{
      int r, g, b;
      if (visible){
	r = 0;
	g = 0;
	b = 255;
	}
	else{
	r= 0;
	g = 0;
	b = 0;
	}
      int thickness = -1;
      int lineType = 8;
      circle( img,
      Point(x,y),
      10,
      Scalar( r, g, b ),
      thickness,
      lineType );
}

void moveCircle(Mat& img, char dir, double& angle, int& x, int&y, vector<Particle>& particles, char* main_window, vector<Point>& particleShoot, double sonarDistance, vector<Point>& edges){
	cout << "Current angle is: " << angle << endl;
	if (dir == 'm'){ //for measure
		updateParticleShoot(img, particles, particleShoot, angle, edges);
		drawParticles(img, particles, false);
		double measuredDist = 0;
		//drawMeasurementLine(main_window, img, angle, x, y);
		measuredDist = sonarDistance;
		updateProbability(particles, particleShoot, (measuredDist));
		particles = resampleParticles(particles);
		double expectedX = 0, expectedY = 0;
		for(unsigned int i =0; i<particles.size();i++){
			Particle temp = particles[i];
			int temp_x = temp.getPosition().x;
			int temp_y = temp.getPosition().y;
			expectedX += (temp_x*temp.getWeight());
			expectedY += (temp_y*temp.getWeight());	
		}
		drawParticles(img, particles, true);
		circle(img, Point(expectedX,expectedY), 5, Scalar(0,0,255), -1, 8);
		return;
	}
	if (dir == 't'){
		updateAngle(angle);
		return;
	}
	//drawCircle(img, x, y, false);
	if (angle == 0){
		x = x + 9;
	}
	else if (angle == 270){
		y = y-9;
	}
	else if (angle == 180){
		x = x-9;
	}
	else{
		y = y+9;
	}
	//drawCircle(img, x, y, true);
	moveParticles(particles, angle, 9, 5, img);
}

void drawParticles(Mat& img, vector<Particle>& particles, bool visible){
	int r = 0, g = 0, b = 0;
	if (visible){
		r = 255;
		b = 255;
		g = 255;
	}
	for (unsigned int i=0;i<particles.size();i++){
		circle(img, particles[i].getPosition(), 1, Scalar(r,g,b), -1, 8);		
	}
}

void updateAngle(double& angle){
	switch ((int) angle){
		case 0:
			angle = 90;
			break;
		case 90:
			angle = 180;
			break;
		case 180:
			angle = 270;
			break;
		case 270:
			angle = 0;
			break;
		default:
			angle = 0;
	}
}

void updateParticleShoot( Mat& img, vector<Particle>& particles, vector<Point>& pshoot, double angle, vector<Point>& edges){
	int target_x, target_y;
	for (unsigned int i=0; i<particles.size();i++){
		Point particle = particles[i].getPosition();
		if (angle ==90){
			int smallest_y = 999;
			for (unsigned int j=0;j<edges.size();j=j+2){
				Point p1 = edges[j];
				Point p2 = edges[j+1];

				if ((p1.x < particle.x && p2.x > particle.x) || (p1.x > particle.x && p2.x < particle.x)){ //I'm between the points
					if ((p1.y < smallest_y) && p1.y > particle.y){
						smallest_y=p1.y;
					}
				}
			}
			Point newPoint(particle.x, smallest_y);
			pshoot[i] = newPoint;
		}
		else if(angle == 270){
			int largest_y = -99;
			for (unsigned int j=0;j<edges.size();j=j+2){
				Point p1 = edges[j];
				Point p2 = edges[j+1];

				if ((p1.x < particle.x && p2.x > particle.x) || (p1.x > particle.x && p2.x < particle.x)){ //I'm between the points
					if ((p1.y > largest_y) && p1.y < particle.y){
						largest_y=p1.y;
					}
				}
			}
			Point newPoint(particle.x, largest_y);
			pshoot[i] = newPoint;
		}
		else if(angle == 0){
			int smallest_x = 999;
			for (unsigned int j=0;j<edges.size();j=j+2){
				Point p1 = edges[j];
				Point p2 = edges[j+1];

				if ((p1.y < particle.y && p2.y > particle.y) || (p1.y > particle.y && p2.y < particle.y)){ //I'm between the points
					if ((p1.x < smallest_x) && p1.x > particle.x){
						smallest_x=p1.x;
					}
				}
			}
			Point newPoint(smallest_x, particle.y);
			pshoot[i] = newPoint;
		}
		else if(angle == 180){
			int largest_x = -99;
			for (unsigned int j=0;j<edges.size();j=j+2){
				Point p1 = edges[j];
				Point p2 = edges[j+1];

				if ((p1.y < particle.y && p2.y > particle.y) || (p1.y > particle.y && p2.y < particle.y)){ //I'm between the points
					if ((p1.x > largest_x) && p1.x < particle.x){
						largest_x=p1.x;
					}
				}
			}
			Point newPoint(largest_x, particle.y);
			pshoot[i] = newPoint;
		}
	}
	/*
	for (unsigned int i=0; i<particles.size();i++){
		Point particlePoint = particles[i].getPosition();
		int particle_x = particlePoint.x;
		int particle_y = particlePoint.y;
		if (angle == 0){
			target_x = 295;
			target_y = particle_y;			
		}
		else if (angle == 90){
			target_x = particle_x;
			target_y = 295;
		}
		else if (angle == 180){
			target_x = 0;
			target_y = particle_y;
		}
		else if (angle == 270){
			target_x = particle_x;
			target_y = 0;
		}
		Point newPoint(target_x,target_y);
		pshoot[i] = newPoint;	
	}
	*/	
}

void drawMeasurementLine(char* frame, Mat& img, double angle, int x , int y){
 	if (angle == 0){
	  line(img, Point(x+10,y),Point(295,y), Scalar(100,100,100),3,8);
	  imshow(frame,img);
	  waitKey(250);
	  line(img, Point(x+10,y),Point(295,y), Scalar(0,0,0), 3,8);
	}
	else if (angle == 90){
	  line(img, Point(x,y+10),Point(x,295), Scalar(100,100,100),3,8);
	  imshow(frame,img);
	  waitKey(250);
	  line(img, Point(x,y+10),Point(x,295), Scalar(0,0,0), 3,8);
	}
	else if (angle == 180){
	  line(img, Point(x-10,y),Point(0,y), Scalar(100,100,100),3,8);
	  imshow(frame,img);
	  waitKey(250);
	  line(img, Point(x-10,y),Point(0,y), Scalar(0,0,0), 3,8);
	}
	else if (angle == 270){
	  line(img, Point(x,y-10),Point(x,0), Scalar(100,100,100),3,8);
	  imshow(frame,img);
	  waitKey(250);
	  line(img, Point(x,y-10),Point(x,0), Scalar(0,0,0), 3,8);	
	}
}

#endif

