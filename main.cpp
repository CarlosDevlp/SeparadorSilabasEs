//PROGRAMA PRINCIPAL
#include "gramaticaEs.h"
using namespace std;

int main(){
	setlocale(LC_ALL, "");	
	char str[100];
	cin>>str;
	Palabra a(str);
	//a.setPalabra(str);

	a.separar();
	
	//wcout<<endl<<"in the end"<<endl;
	
	
	//restricciones
	a.respHiato();
	a.restMonosilabo();//si cumple la restricción se termina el programa
	a.rest4Consonante();
	a.restDobleFusion();
	a.restDiptongo();	
	a.rest3Consonante();
	a.restTriptongo();	
	a.rest2RLConsonante();
	a.restConsonante();
	
	

	/*
	//1er grupo no óptimo
	a.restConsonante();
	a.rest2RLConsonante();
	a.rest3Consonante();
	a.rest4Consonante();
	a.restDobleFusion();
	a.restDiptongo();
	a.restTriptongo();
	a.respHiato();*/

	//2do grupo mejor
	/*a.respHiato();
	a.restTriptongo();
	a.restDiptongo();
	a.restDobleFusion();
	a.rest4Consonante();
	a.rest3Consonante();
	a.rest2RLConsonante();
	a.restConsonante();*/	
	a.imprimir();
	wcout<<endl;
	return 0;
}