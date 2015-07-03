//PROGRAMA PRINCIPAL
#include "gramaticaEs.h"
using namespace std;

int main(){

	setlocale(LC_ALL, "");	
	
	char str[200];
	Palabra a;	
	while(true){

			//---input--	
			cin>>str;

		if(str[0]=='0')
			break;

			a.setPalabra(str);
			//---output	
			a.separarSilabasVoraz();
			a.imprimir();

	}
	return 0;
}
