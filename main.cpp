//PROGRAMA PRINCIPAL
#include "gramaticaEs.h"
using namespace std;

int main(){

	setlocale(LC_ALL, "");	
	//---input--
	char str[100];
	cin>>str;
	Palabra a(str);

	//---output	
	a.separarSilabasVoraz();
	a.imprimir();
	
	return 0;
}