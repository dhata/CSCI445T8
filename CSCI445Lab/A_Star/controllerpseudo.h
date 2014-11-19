pseudo code for brain

0 2 2 3 4 1 
Point robotLoc=1,1;
path = call A_star() //0 2 2 3 4 1 
stringstream ss;
while(path>> ss ){
	int angleGoal;
	if (ss == 0){			//down
		angleGoal=90;
		robotLoc.x++;
	} else if(ss==1){		//left
		angleGoal=180;
		robotLoc.y--;
	} else if (ss == 2) {	//up
		angleGoal=270;
		robotLoc.x--;
	} else if (ss == 3) {	//right
		angleGoal=0;
		robotLoc.y++;
	}
	
	//direction x+=9 distance needs to be 30
	moveCircle(img, dir, angle, x, y, particles, main_window, particleShoot, sonarDistance,30);
	//use 1SQUARE as the distance to add to x/y
		
	}
	moveToAngle(angleGoal);
	moveNumBlocks(1);
	measure()/moveCircle(dir=m) //update moveCircle(dir=m) to update x,y with expectedX,expectedY

	Point goalPoint=GridToPoint(robotLoc){
		goalPoint.x = robotLoc.x*30-15;
		goalPoint.y = robotLoc.y*30-15;
	}

	adjust(x, y, goalPoint, angleGoal){
		diffX = x-goalPoint.x;
		diffY = y-goalPoint.y;
		//MOVE IN X DIRECTION FIRST
		//based on direction facing, and whether diffX,diffY are pos/neg then turn and move very small step
		if(diffX=0){
		} else if(diffX>0){
			turnToAngle(down);
			angle=down;
		} else if(diffX<0){
			turnToAngle(up);
			angle=up;
		}
		
		//diffX is a pixel, use our scaling to figure out how many seconds to drive
		double convertedX;
		if(diffX=0){	
			convertedX=0;
		} else {
			convertedX = abs(diffX)*72.6666666667;
		} 
		driveForward(convertedX);
		moveCircle(img, dir, angle, x, y, particles, main_window, particleShoot, sonarDistance,diffX);
		
		//MOVE IN Y DIRECTION
		if(diffY=0){
		} else if(diffY>0){
			turnToAngle(left);
		} else if(diffY<0){
			turnToAngle(right);
		}
		
		double convertedY;
		if(diffY=0){
			convertedY=0;
		} else {
			convertedY = abs(diffY)*72.6666666667;
		}
		driveForward(convertedY);
		moveCircle(img, dir, angle, x, y, particles, main_window, particleShoot, sonarDistance,diffY);
		
		//remeasure
		//adjust
		return;
	}
}
