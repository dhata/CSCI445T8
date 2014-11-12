#include "A_star.h"

using namespace std;

int main(){
    srand(time(NULL));
	//int map[10][12];
    //readFile("map.txt");

	
	
	//SET START AND FINISH
    int xA = 1, yA = 1, xB = 9, yB = 9;
    
    cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
    cout<<"Start: "<<xA<<","<<yA<<endl;
    cout<<"Finish: "<<xB<<","<<yB<<endl;
	
    // get the route
    clock_t start = clock();
	
    string route=pathFind(xA, yA, xB, yB);
    if(route=="") cout<<"An empty route generated!"<<endl;
    clock_t end = clock();
    double time_elapsed = double(end - start);
    cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
    cout<<"Route:"<<endl;
    cout<<route<<endl<<endl;
    
    return(0);
}