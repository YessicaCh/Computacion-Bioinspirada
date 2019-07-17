#include <iostream>
using namespace std;

void stateInit(bool **&s,int l){
	s=new bool*[l];
	for(int i=0;i<l;++i){
		s[i]=new bool[l];
		if(i==0){
			for(int j=0;j<l;j++){
				if(j==(l/2))
					s[i][j]=1;
				else
					s[i][j]=0;
			}
		}
	}
}
bool regla(bool a,bool b, bool c){
	if(a==b and b==c and a==c)
		return 0;
	else if(a==0 and b==1 and c==1)
		return 0;
	else if(a==1 and b==0 and c==1)
		return  0;
	else
		return 1;
}
void print(bool **b,int f){
	for(int i=0;i<f;i++){
		for(int j=0;j<2*f;j++){
			if(b[i][j]==0)
			{
				cout<<" ";
			}
			else
			{
				cout<<"1";
			}
		}
		cout<<endl;
	}

}
bool Triangulo(bool **b,int l){
	bool ant;
	bool post;
	bool act;
	for(int i=0;i<l-1;++i){
		for(int j=0;j<l;j++){
			if(j==0){
				ant=0;
			    post=b[i][j+1];}
			else if(j==(l-1)){
				ant=b[i][j-1];
			    post=0;}
			else{
				ant=b[i][j-1];
				post=b[i][j+1];
			}
			b[i+1][j]=regla(ant,b[i][j],post);
		}
	}



}


int main(int argc, char const *argv[])
{
	bool **S;
	int fila;


	cout<<"Triangulo de sierpinski "<<endl;
	cout<<"Ingrese # fila "<<endl;
	cin>>fila;
	fila=fila*2;
	stateInit(S,fila);
	Triangulo(S,fila);
	cout<<"   Dibujando "<<endl;
    fila=fila/2;
	print(S,fila);

	return 0;
}