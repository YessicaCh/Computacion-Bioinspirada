#define GLUT_DISABLE_ATEXIT_HACK	
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#define KEY_ESC 27
#define GL_PI 3.14159f
using namespace std;

class Punto
{
	public:
		float x;
		float y;
		Punto(){}
		Punto(float _x, float _y){
			x=_x;
			y=_y;
		}
		void print(){
			cout<<"("<<x<<","<<y<<")"<<endl;
		}	
};

Punto v1(0,0);
Punto v2(90,90);
//float AREA=90*90;
void alfombraSirpienki(Punto v1,Punto v2,int fase){
	float lado=(v2.x-v1.x);
	if(fase==0){
		glColor3f(1.0,1.0,1.0);
		glBegin (GL_QUADS); 
				glVertex3f(v1.x,v1.y, 0.0f);  
				glVertex3f(v2.x,v1.y, 0.0f); 
				glVertex3f(v2.x,v2.y, 0.0f); // 
				glVertex3f(v1.x,v2.y, 0.0f); // arriba derecha 
        glEnd (); 
      //  cout<<"AREA"<<AREA<<endl;
	}
	else{
		//AREA=AREA-(lado*lado);
		alfombraSirpienki(v1,Punto(v1.x+(lado/3),v1.y+(lado/3)),fase-1);
		alfombraSirpienki(Punto(v1.x+(lado/3),v1.y),Punto(v1.x+2*(lado/3),v1.y+(lado/3)),fase-1);
		alfombraSirpienki(Punto(v1.x+2*(lado/3),v1.y),Punto(v2.x,v1.y+(lado/3)),fase-1);

		alfombraSirpienki(Punto(v1.x,v1.y+(lado/3)),Punto(v1.x+(lado/3),v1.y+2*(lado/3)),fase-1);
		alfombraSirpienki(Punto(v1.x+2*(lado/3),v1.y+(lado/3)),Punto(v2.x,v1.y+2*(lado/3)),fase-1);

		alfombraSirpienki(Punto(v1.x,v1.y+2*(lado/3)),Punto(v1.x+(lado/3),v2.y),fase-1);
		alfombraSirpienki(Punto(v1.x+(lado/3),v1.y+2*(lado/3)),Punto(v1.x+2*(lado/3),v2.y),fase-1);
		alfombraSirpienki(Punto(v1.x+2*(lado/3),v1.y+2*(lado/3)),v2,fase-1);
	}

}
GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);//light 0 "on": try without it
	glEnable(GL_LIGHT0);//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0, 0, 255, 0);
}
GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//PARA BORRAR EL MATRIZ DE POSITIONRS
	glOrtho(-2.0f, 100.0f, -5.0f, 100.0f, -5.0f, 100.0f);
 	alfombraSirpienki(v1,v2,1);
	glutSwapBuffers();
	glFlush();
}
GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0f, 25.0f, -10.0f, 25.0f, -10.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}
void init_scene(){}//video juego int a=0,a+=0.1(speeding rapido)*dt(el tiempo transcurrido)

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" Practica11:Alfombra de Sirpienkins");

	initGL();
	init_scene();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);

	glutMainLoop();
	return 0;
}