//PROGRAMA PRINCIPAL
#include "gramatica2.h"
#include <iostream>
using namespace std;
int main(){
	string str;
	//scanf("%s",&str);
	cin >> str;
	Palabra a(str,0);
	a.separar();

	
	//restricciones
	a.respHiato();
	a.restMonosilabo();//si cumple la restricción se termina el programa
	a.rest4Consonante();
	a.restDiptongo();	
	a.rest3Consonante();
	a.restTriptongo();
	a.restDobleFusion();
	a.rest2RLConsonante();
	a.restConsonante();
	
	

	//1er grupo no óptimo
	/*a.restConsonante();
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
	
	puts("");	
	a.imprimir();
	puts("");
	return 0;
}