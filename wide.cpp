//probando caracteres unicode
#include <string>
#include <iostream>
#include <string.h>
#include <wchar.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;
int main() {

	setlocale(LC_ALL, "");
    /*char *str;
    cin>>str;
    wchar_t buf[100]; 

    mbstowcs(buf, str, 20);
   	int size=wcslen(buf);
   	if(buf[0]==L'ó')
    	for(int i=0;i<size;i++)
			wprintf(L"%lc", buf[i]);*/
	wchar_t a;
    wchar_t b;
	wcin>>a;
    b=a;
	wprintf(L"%lc\n", b);
	//wprintf(L"%ls has %zu wide characters\n", buf, wcslen(buf));
	//printf ("Enter a string: ");
    //wcin>> string;
    //scanf("%ls",string);

    //printf("%lc\n",a[0]);

    //wcout<< string <<endl;
    //printf("String Entered: %ls: length: %dn", string, wcslen(string));

    return 0;
}
