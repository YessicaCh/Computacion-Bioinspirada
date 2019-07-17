#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#define pi acos(-1)

using namespace std;

typedef pair<double, double> squad;
typedef pair<double, squad> estate;

string st;
int t=9;
int it=0;
int largo=25;
int pI=16;

void drawLine(squad f, squad s){
	glBegin(GL_LINES);
	glVertex3f(f.first, f.second, 0);
	glVertex3f(s.first, s.second, 0);
	glEnd();
}
void drawLinePoint(squad f, squad s,double angle){
	float lado=s.first-f.first;
	glBegin(GL_POINTS);
	for(int i=0;i<lado-2;i++){
		glVertex2f(f.first,f.second);
		f.first=f.first+lado;
	}
	glEnd();
}

squad getCircleCoordinate(squad center, double r, double angle){
	center.first+=sin((angle*pi)/180)*r;
	center.second+=cos((angle*pi)/180)*r;
	return center;
}

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/ );
	glEnable(GL_DEPTH_TEST);
	vector<estate> Q;
	double ang=0;
	double x=(pI)/2;
	double y=(pI)/6;
	Q.clear();
	int cont=0;
	//cout << st << endl;
	for (int i=0;i<st.size();i++){
		//cout <<"i"<<i<<"  "<<st << endl;
		if(st[i]=='F'){
			squad beg=make_pair(x,y);
			squad end=getCircleCoordinate(make_pair(x,y),0.02, ang);
			if(it>=t){
				drawLine(beg, end);
			}
			x=end.first;
			y=end.second;
			cont++;
			cont=cont%360;
		}else if(st[i]=='G'){
			squad beg=make_pair(x,y);
			//squad end=make_pair(x+8,y+8);
			squad end=getCircleCoordinate(make_pair(x,y),0.01, ang);
			if(it>=t){
				drawLinePoint(beg,end,ang);
			}
			cont++;
		}else if(st[i]=='['){
			Q.push_back(make_pair(ang,make_pair(x,y)));
		} else if(st[i]==']'){
			ang=Q[Q.size()-1].first;
			x=Q[Q.size()-1].second.first;
			y=Q[Q.size()-1].second.second;
			Q.erase(Q.begin()+Q.size()-1);
		} else if(st[i]=='+'){
			bool vie=rand()%2;
			int cam=rand()%100+i%200;
			if(vie){
				ang+=((45.0-22.5)/4000)*cam;
			} else {
				ang-=((45.0-22.5)/4000)*cam;
			}
			ang+=45;

		} else if(st[i]=='-'){
			bool vie=rand()%2;
			int cam=rand()%100+i%200;
			if(vie){
				ang+=((45.0-22.5)/4000)*cam;
			} else {
				ang-=((45.0-22.5)/4000)*cam;
			}
			ang-=45;

		}
	}
	glFlush();
	if(it<t){
		string st2;
		for (int i=0;i<st.size();i++){
			if(st[i]=='F'){
				st2+="FF";
			} 
            else if(st[i]=='G'){
				st2+="F[-G][+G]FG";
			}
			else {
				st2+=st[i];
			}
		}
		st=st2;
	}
	it++;
	glutPostRedisplay();
	if(it>t){
		usleep(800000);
	}
	cout<<"ANgulo "<<cont<<endl;
}

int main(int argc, char **argv){
	srand (time(NULL));
	st="G";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB/*|GLUT_DEPTH*/);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" DOL -System");
	glutDisplayFunc(myDisplay);
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-0.1,largo,-0.1,largo,-0.1,largo);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();
	return 0;
}
