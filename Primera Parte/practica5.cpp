#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <random>
#include <ctime>	
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#define KEY_ESC 27
using namespace std;
#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
#define GL_PI 3.14159f
int W=5;

//COMPILAR
//g++ -std=c++11 -o c practica5.cpp -lglut -lGL
//./c

using namespace std;

float rand_FloatRange(float a, float b)
{
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}
void Circle(float x,float y ,float r)
{
	 float i;
	 int precision = 20;
	 
	 glBegin(GL_LINE_LOOP);
		
	       for (i=0; i< GL_PI*2; i = i + (GL_PI/precision)) {
		      glVertex2f(r*cosf(i)+x,r*sinf(i)+y);
	  		}
    glEnd();
}
void drawCircle(){

   glBegin(GL_LINES);
      glColor3f(1.0f,1.0f,1.0f);
      glVertex2f(-W,0);
      glVertex2f(W,0);
      glVertex2f(0,-W);
      glVertex2f(0,W);
   glEnd();

    glColor3d(255,255,0);
    Circle(-1,-1,0.1);
    
    glColor3d(255,0,0);
    Circle(-1,1,0.1);

    glColor3d(255,0,0);
    Circle(1,-1,0.1);

    glColor3d(255,255,0);//CUANDO ES 1 =AMARILLO
    Circle(1,1,0.1);

}

class Perceptron
{
    public:
    Perceptron();
	Perceptron(float nLearning);
	//~Perceptron();
    public:

    	
    	void initEntry(vector<vector<int>> Input);
    	void initExpected(vector<int> Out);
    	void mixEntry();
    	void print();
    	void train();
    	
    private:
    	void init();
    	void initWeight();
    	float ActiveFuntion(float x);
    	void UpdateWeight(float error);

    	void dibujarRecta();
    private:
	vector<vector<int>> Input;
	vector<int> Output;
	vector<float> weight;

	int nInput;
	int nPatterns;
	float nLearning;
	float Bias;
};
Perceptron::Perceptron(){}
Perceptron::Perceptron(float nLearn){
	nLearning=nLearn;
	init();
}
void Perceptron::init(){
    nPatterns=4;
	cout<<"# nPatterns :"<<nPatterns<<endl;
	//cin>>nPatterns;cout<<endl;

    nInput=2;
	cout<<"# nInput :"<<nInput<<endl;;
	//cin>>nInput;cout<<endl;

    Input.resize(nPatterns);
	for(int i=0;i<nPatterns;i++){
		Input[i].resize(nInput);
	}


	//Init
	Output.resize(nPatterns);
	weight.resize(nInput);

	Bias=rand_FloatRange(0,5);
	cout<<" Bias : "<<Bias<<endl;
	initWeight();

}

void Perceptron::initEntry(vector<vector<int>> Inp){

	
	for(int i=0;i<nPatterns;i++)
	{
		cout<<"  Patterns "<<i+1<<"  :"<<endl;

		for(int j=0;j<nInput;j++){
			Input[i][j]=Inp[i][j];
			cout<<"   "<<Input[i][j];
		}
		cout<<endl;
	}

}
void Perceptron::initExpected(vector<int> Out){
	cout<<" expected ......."<<endl;
	for(int i=0;i<nPatterns;i++)
	{
		cout<<" 	Patterns  "<<i+1<<endl;
		Output[i]=Out[i];
		cout<<"  "<<Output[i];
	}
	cout<<endl;
}
void Perceptron::initWeight(){

 cout<<" weight ......."<<endl;
	for(int i=0;i<nInput;i++)
	{
		weight[i]=rand_FloatRange(0,1);
		cout<<" "<<weight[i]<<"; ";
	}
}
float Perceptron::ActiveFuntion(float x){
	//J = −1siV ≤ 0; 1siV > 0
	if (x<=0)
		return -1;
	else
		return 1;
}
void Perceptron::UpdateWeight(float error){
	//W = W − α ∗ E
	for(int i=0;i<weight.size();i++){
		weight[i]=weight[i]-nLearning*error;
		//weight[i].second=weight[i].second-nLearning*error;
	}
}
void Perceptron::mixEntry(){
	
	int index,indext;
	float tmp;
	for(int i=0;i<nPatterns;i++){
		index=rand_FloatRange(0,nPatterns);
        while(index==i){
        	index=rand_FloatRange(0,nPatterns);
        }
         swap(Input[i],Input[index]);
         swap(Output[i],Output[index]);
         //puede ser que falten los pesos
	}
}
void Perceptron::dibujarRecta(){
	float tmp=0;
	float m;
	float b;
	glBegin(GL_LINES);
	    m=-weight[0]/weight[1];
	    b=-Bias/weight[1];
		glVertex2f(-5,m*-5+b);
		glVertex2f(5,m*5+b);
		cout<<"Ecuacion  y= "<<m<<" x +"<<b<<endl;
	   
    glEnd();
}
void Perceptron::train(){

	float error=100;
	float V,V_old,J;
	float z;
	int Cont;
	int iT=0;
	int nTrain;
	drawCircle();
	nTrain=126;
	int conT=0;
	while(iT<nTrain)
	{
		//cout<<"contador:"<<conT<<endl;
		conT=0;
		for(int i=0;i<nPatterns;i++){

			z=Input[i][0]*weight[0]+Input[i][1]*weight[1];
			V=z+Bias;
			J=ActiveFuntion(V);
			error=Output[i]-J;

			if (error==0)
			{
				conT+=1;
			}
			else{
				UpdateWeight(error);
			}	 
		}
        /*if(nTrain-iT==1 and abs(error)>0.0001){
        	iT-=1;
        }*/
		mixEntry();// 
		iT+=1;
	}
	dibujarRecta();
	cout<<"cuanto salio el error  "<<error<<endl;
	cout<<" weight :"<<weight[0]<<"  "<<weight[1]<<endl;
	cout<<"  Bias  :"<<Bias<<endl;
}
void Perceptron::print(){
	cout<<"print"<<endl;
	for(int i=0;i<nPatterns;i++){
		for(int j=0;j<nInput;j++){
			cout<<Input[i][j]<<"  "<<endl;
		}
	}
	cout<<"expected xxx"<<endl;
	for(int i=0;i<nPatterns;i++){
		cout<<Output[i]<<endl;
	}
}


Perceptron *RNP;
vector<vector<int>> patronAND;
void funcionAND(){
	float nLearning;
	cout<<"****************RED NEURAL PERCEPTRON**********"<<endl;
	cout<<"******Funcion AND **********"<<endl;
	cout<<"tasa de aprendizaje entre 0 y 1 :";
	cin>>nLearning;
	//Cuatro patrones con dos entradas;
    vector<vector<int>> patronAND;
    patronAND.resize(4);
    for(int i=0;i<4;i++){patronAND[i].resize(4);}
    patronAND[0][0]=-1;patronAND[0][1]=-1;
    patronAND[1][0]=-1;patronAND[1][1]=1;
    patronAND[2][0]=1;patronAND[2][1]=-1;
    patronAND[3][0]=1;patronAND[3][1]=1;

    //Esperado
    vector<int> esperado;
    esperado.resize(4);
    esperado[0]=-1;
    esperado[1]=-1;
    esperado[2]=-1;
    esperado[3]=1;

	//Perceptron RNP(nLearning);
	RNP=new Perceptron(nLearning);
	RNP->initEntry(patronAND);
	RNP->initExpected(esperado);
	cout<<"ENtrenando *********"<<endl;
	//RNP.train();
}

void funcionOR(){
	float nLearning;
	cout<<"****************RED NEURAL PERCEPTRON**********"<<endl;
	cout<<"******Funcion AND **********"<<endl;
	cout<<"tasa de aprendizaje entre 0 y 1 :";
	cin>>nLearning;
	//Cuatro patrones con dos entradas;
    vector<vector<int>> patronAND;
    patronAND.resize(4);
    for(int i=0;i<4;i++){patronAND[i].resize(4);}
    patronAND[0][0]=-1;patronAND[0][1]=-1;
    patronAND[1][0]=-1;patronAND[1][1]=1;
    patronAND[2][0]=1;patronAND[2][1]=-1;
    patronAND[3][0]=1;patronAND[3][1]=1;

    //Esperado
    vector<int> esperado;
    esperado.resize(4);
    esperado[0]=-1;
    esperado[1]=1;
    esperado[2]=1;
    esperado[3]=1;

	//Perceptron RNP(nLearning);
	RNP=new Perceptron(nLearning);
	RNP->initEntry(patronAND);
	RNP->initExpected(esperado);
	cout<<"ENtrenando *********"<<endl;
}
void funcionXOR(){
	float nLearning;
	cout<<"****************RED NEURAL PERCEPTRON**********"<<endl;
	cout<<"******Funcion AND **********"<<endl;
	cout<<"tasa de aprendizaje entre 0 y 1 :";
	cin>>nLearning;
	//Cuatro patrones con dos entradas;
    vector<vector<int>> patronAND;
    patronAND.resize(4);
    for(int i=0;i<4;i++){patronAND[i].resize(4);}
    patronAND[0][0]=-1;patronAND[0][1]=-1;
    patronAND[1][0]=-1;patronAND[1][1]=1;
    patronAND[2][0]=1;patronAND[2][1]=-1;
    patronAND[3][0]=1;patronAND[3][1]=1;

    //Esperado
    vector<int> esperado;
    esperado.resize(4);
    esperado[0]=1;
    esperado[1]=-1;
    esperado[2]=-1;
    esperado[3]=1;

	//Perceptron RNP(nLearning);
	RNP=new Perceptron(nLearning);
	RNP->initEntry(patronAND);
	RNP->initExpected(esperado);
	cout<<"ENtrenando *********"<<endl;
}


GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}

GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//PARA BORRAR EL MATRIZ DE POSITIONRS
	glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f);


	//dibuja
 	RNP->train();
	glutSwapBuffers();

	glFlush();
}
GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	//glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f);


	glMatrixMode(GL_MODELVIEW);
}
void init_scene(){}
//video juego int a=0,a+=0.1(speeding rapido)*dt(el tiempo transcurrido)
GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}
//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	//Inicializacion de la GLUT
	funcionXOR();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" Red Neuronal");


	initGL();
	init_scene();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}
