//PROGRAMA PRINCIPAL
#include "gramatica.h"
#include <iostream>
using namespace std;
int main(){
	string str;
	//scanf("%s",&str);
	cin >> str;
	Palabra a(str,0);
	a.separar();

	a.restMonosilabo();//fijo
	//restricciones
	a.respHiato();
	a.restTriptongo();
	a.restDiptongo();
	a.restDobleFusion();
	a.rest4Consonante();
	a.rest3Consonante();
	a.rest2RLConsonante();
	a.restConsonante();
	a.imprimirSobrante();
	
	/* //1er grupo
	a.restConsonante();
	a.rest2RLConsonante();
	a.rest3Consonante();
	a.rest4Consonante();
	a.restDobleFusion();
	a.restDiptongo();
	a.restTriptongo();
	a.respHiato();*/
	puts("");
	return 0;
}