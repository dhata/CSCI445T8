pseudo code for brain

0 2 2 3 4 1 
Point robotLoc=1,1;
path = call A_star() //0 2 2 3 4 1 
stringstream ss;
path>> ss; 
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
for(int i = 0; i<particles.size(); i++){	//direction x+=9 distance needs to be 30
	moveCircle(img, dir, angle, x, y, particles, main_window, particleShoot, sonarDistance,1SQUARE);
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
	//diffX is a pixel, use our scaling to figure out how many seconds to drive
	turnto some direction
	move with seconds function
	moveCircle(img, dir, angle, x, y, particles, main_window, particleShoot, sonarDistance,DIFFX);
	//MOVE IN Y DIRECTION
	turn to some direction
	moveCircle(img, dir, angle, x, y, particles, main_window, particleShoot, sonarDistance,DIFFY);
	move(seconds)
	turnToAngle(angleGoal);
	//measure
	//adjust
	return;
}

