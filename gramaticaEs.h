//Libreria de gramática española 
//desarrollador: carlos chavez laguna.
#ifndef GRAMATICA_ES
 #define GRAMATICA_ES
 #include <string>
 #include <string.h>
 #include <wchar.h>
 #include <vector>
 #include <wchar.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>

 class Letra{
 	public:
 		wchar_t _letra;
 		bool _vocal,_debil,_lr,_revisado,_nulo;
 	
		Letra(){	
			init();
		}
		Letra(wchar_t _l,bool _r):_letra(_l),_revisado(_r){
			init();
		} 			
		/*Letra(char _l){
			mbstowcs(this->_letra,_l , 1);
			wcsncpy ( this->_letra, _l, 1);
			init();
		} */
		
		Letra(wchar_t _l){			
			this->_letra=_l;
			init();
		} 
		/*
			Letra(wchar_t _l):_letra(_l){
				init();
			} 
		*/			
		Letra(wchar_t _l,bool _v,bool _LR):_letra(_l),_vocal(_v),_lr(_LR){
			init();
		}
		void init(){
			_vocal=_debil=_lr=_revisado=_nulo=false;
		}

 };
 class Palabra{
 	private:
 		wchar_t _palabra[200]; 		
 		wchar_t _vocalesDebiles[3+1],_vocalesFuertes[4+5],_lr[3];
 		std::vector<Letra> _letras; 		
	public:

		Palabra(){			
			this->init();
			mbstowcs(this->_palabra," ", 100);
		}

 		Palabra(char p[]){
 			this->init();
 			mbstowcs(this->_palabra,p, 100);
 		}
 		void init(){ 			
 			mbstowcs(this->_vocalesDebiles,"iuü", 10);
			mbstowcs(this->_vocalesFuertes,"aeoáéíóú", 10);
			mbstowcs(this->_lr,"lr", 10);
 		}
 		void print(){

 			for(int i=0;i<wcslen(_palabra);i++)
			//	wprintf(L"%lc",_palabra[i]);
 				this->_letras.push_back(Letra(_palabra[i]));


 		}
 		void separar(){ 			
 			    int size=wcslen(_palabra),
 			    	vF=wcslen(_vocalesFuertes),
 			    	vD=wcslen(_vocalesDebiles),
 			    	lR=wcslen(_lr);

	 			for(int i=0;i<size;i++){		
	 				this->_letras.push_back(Letra(_palabra[i]));
	 				//ver si es vocal
		 				//fuerte		 				
		 				for(int ii=0;ii<vF;ii++)
			 				if(_palabra[i]==_vocalesFuertes[ii]){//es vocal
			 						this->_letras[i]._vocal=true;			 					
			 					break;
			 				}
						//debil
		 				for(int ii=0;ii<vD;ii++)
			 				if(_palabra[i]==_vocalesDebiles[ii]){//es vocal
			 						this->_letras[i]._vocal=true;
			 						this->_letras[i]._debil=true;			 						
			 					break;
			 				}
			 		  //Y como débil
			 			if(_palabra[i]==L'y')
			 				this->_letras[i]._debil=true;

			 				
		 			//ver si es lr
			 		if(!this->_letras[i]._vocal)
			 			for(int ii=0;ii<lR;ii++)
			 				if( _palabra[i]==_lr[ii]){//es lr
			 						this->_letras[i]._lr=true;
			 					break;
			 				}
		 			//printf("%c(%c)",this->_letras[i]._letra,(this->_letras[i]._vocal?'v':'c'));
	 			}
	 			this->_letras.insert(this->_letras.begin(),Letra(L' '));//un caracter comodín
	 			//this->_letras.push_back(Letra(' '));//un caracter comodín
	 			this->_letras[0]._nulo=true;
	 			//this->_letras[this->_letras.size()-1]._nulo=true;
 		}
 		
 		void setPalabra(char  *p){
 			mbstowcs(this->_palabra,p , 100);
 		}
 		
 		
 		// restricciones (recorrido voraz)
 		void restMonosilabo(){ 			
 			//una sola sílaba (no se pueden dividir)
 			int k=0; 			
 			for(int i=1;i<this->_letras.size();i++)
 				if(!this->_letras[i-1]._vocal and this->_letras[i]._vocal)
 						k++;

 			if(k==1){
 				//si la palabra es monosílaba no es necesario seguir evaluando el resto de las restricciones
 				printf("\nla palabra es monosilaba\n");
 				exit(0);
 			}
 		} 	
 		void restConsonante(){
 			//Una consonante entre dos vocales se agrupa con la vocal de la derecha 	
			bool cumple=false; 			
 			for(int i=2;i<this->_letras.size();i++)
				if(
					!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
					!this->_letras[i-2]._vocal and this->_letras[i-1]._vocal and !this->_letras[i]._vocal
				  )
				 { 
					//printf("-%c%c-%c ",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
					this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=true;
					this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
					if(i<this->_letras.size()-2)
						this->_letras.insert(this->_letras.begin()+i+1,Letra('-',true));
					cumple=true;
				 }
				 else if(
					 	!this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
						!this->_letras[i-1]._vocal and this->_letras[i]._vocal
				 	    )
				 {
				 	//-%c%c 
			 		this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
					this->_letras.insert(this->_letras.begin()+i-1,Letra('-',true));
					
					cumple=true;

				 }
			if(cumple)
			 std::wcout<<"->cons"<<std::endl;
 		}
 		void rest2RLConsonante(){
 			//Si la segunda consonante es r o l, las dos consonantes se agrupan con la segunda vocal			
 			bool cumple=false;
 			for(int i=2;i<this->_letras.size();i++)
				if(
				!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and !this->_letras[i-2]._nulo 
				)
				{	
					
					if( (!this->_letras[i-2]._vocal and !this->_letras[i-2]._lr )and this->_letras[i-1]._lr and this->_letras[i]._vocal)
					    {
							//printf("%c%c%c-",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);						
							this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
							this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
						cumple=true;					
				  		}
				    else if(!this->_letras[i-2]._vocal and !this->_letras[i-1]._vocal)//excepción
						{
							//printf("%c-%c%c",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);						
							this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
							this->_letras.insert(this->_letras.begin()+i-1,Letra('-',true));
						cumple=true;
						}					
					
				}
		if(cumple)
			 std::wcout<<"->LR"<<std::endl;
 		}
 		void rest3Consonante(){
			/* Cuando hay TRES consonantes ENTRE VOCALES, las primeras 
			dos se unen con la primera vocal y la tercera se une a la segunda vocal*/

			/*Excepción: Si la tercera consonante es r o l, la primera consonante 
			se une con la primera vocal y las otras dos con la siguiente. */
 			bool cumple=false;
 			if(this->_letras.size()>5)
	 			for(int i=4;i<this->_letras.size();i++)
					if(
						!this->_letras[i-4]._revisado and !this->_letras[i-3]._revisado and !this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
						this->_letras[i-4]._vocal and !this->_letras[i-3]._vocal and !this->_letras[i-2]._vocal and (!this->_letras[i-1]._vocal and !this->_letras[i-1]._lr) and this->_letras[i]._vocal)
					{
							//printf("%c%c%c-%c%c-",this->_letras[i-4]._letra,this->_letras[i-3]._letra,this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
							this->_letras[i-4]._revisado=this->_letras[i-3]._revisado=this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
							this->_letras.insert(this->_letras.begin()+i-1,Letra('-',true));
							cumple=true;						
					}
					else //excepción
						if(
							!this->_letras[i-4]._revisado and !this->_letras[i-3]._revisado and !this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
							this->_letras[i-4]._vocal and !this->_letras[i-3]._vocal and !this->_letras[i-2]._vocal and this->_letras[i-1]._lr and this->_letras[i]._vocal){
							//printf("%c%c-%c%c%c-",this->_letras[i-4]._letra,this->_letras[i-3]._letra,this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
							this->_letras[i-4]._revisado=this->_letras[i-3]._revisado=this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
							this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
							cumple=true;
						}


			if(cumple)
			 std::wcout<<"->3cons"<<std::endl;
 		}

 		void rest4Consonante(){
 			/*Cuando hay cuatro consonantes ENTRE VOCALES, las primeras dos se unen 
			 a la primera vocal y las otras dos se unen a la segunda vocal.*/
 			bool cumple=false;
 			if(this->_letras.size()>6)
	 			for(int i=5;i<this->_letras.size();i++)
					if(
						!this->_letras[i-5]._revisado and !this->_letras[i-4]._revisado and !this->_letras[i-3]._revisado and !this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
						
						this->_letras[i-5]._vocal and //vocal
					   !this->_letras[i-4]._vocal and //consonante
					   !this->_letras[i-3]._vocal and 
					   !this->_letras[i-2]._vocal and 
					   !this->_letras[i-1]._vocal and 
					    this->_letras[i]._vocal) {//vocal
						/*printf("%c%c%c-%c%c%c-",this->_letras[i-5]._letra,
							 					this->_letras[i-4]._letra,
							 					this->_letras[i-3]._letra,
							 					this->_letras[i-2]._letra,
							 					this->_letras[i-1]._letra,
							 					this->_letras[i]._letra);*/
						this->_letras[i-5]._revisado=this->_letras[i-4]._revisado=this->_letras[i-3]._revisado=this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
						this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
						cumple=true;
						
				}
			
			if(cumple)
			 std::wcout<<"->4cons"<<std::endl;
 		}
 		void restDobleFusion(){//no sirve
 			/*Recuerda que las consonantes dobles: ch, ll, rr representan un solo fonema, 
 			por lo que para efectos de la división silábica 
 			cuentan como una sola consonante (no se separan). Se aplica entonces la regla*/
 			bool cumple=false;
 			for(int i=2;i<this->_letras.size();i++)
					if(
						!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
						(
							(this->_letras[i-2]._letra==L'c' and this->_letras[i-1]._letra==L'h') or
						    (this->_letras[i-2]._letra==L'r' and this->_letras[i-1]._letra==L'r') or 
						    (this->_letras[i-2]._letra==L'l' and this->_letras[i-1]._letra==L'l')
						     //this->_letras[i-2]._letra==this->_letras[i-1]._letra 
					    )
					   and this->_letras[i]._vocal
						){
							//printf("%c%c%c-",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
							this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
							//this->_letras.insert(this->_letras.begin()+i+1,Letra('-',true));
							this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
							cumple=true;							
						}

		if(cumple)
			 std::wcout<<"->2f"<<std::endl;
					
 		}
 		//Los diptongos y los triptongos forman una sola sílaba, por lo que no podemos separarlos. 
 		void restDiptongo(){
 			/*Llamamos diptongo a la unión de una vocal fuerte (a, e, o) y
 			 una vocal débil (i, u) o la unión de dos vocales débiles.(i, u)*/
 			bool cumple=false;
	 			for(int i=2;i<this->_letras.size();i++)								//débil o fuerte	
	 				if (
	 					!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
	 					!this->_letras[i-2]._vocal and this->_letras[i-1]._debil and this->_letras[i]._vocal)
	 				{
			 			//printf("%c%c%c-",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);			 			
						this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
						this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
						cumple=true;						
			 		}
		if(cumple)
			 std::wcout<<"->dipt"<<std::endl;
 		}
 		//triptongo
 		void restTriptongo(){ 
 		bool cumple=false;				
 				for(int i=2;i<this->_letras.size();i++)
 					if (!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado
 					 and this->_letras[i-2]._debil and (this->_letras[i-1]._vocal and !this->_letras[i-1]._debil) and this->_letras[i]._debil){
 						//printf("%c%c%c-",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
 						this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
						this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
						cumple=true;
 					}
		if(cumple)
			 std::wcout<<"->trip"<<std::endl;
 		}
 		//hiato
 		void respHiato(){
 			/*DOS VOCALES FUERTES (a, e, o) requieren que se agrupen 
 			en sílabas diferentes. A este procedimiento le llamamos hiato.
			í y ú serán tomadas como vocales fuertes
 			*/

 			bool cumple=false;
 			for(int i=1;i<this->_letras.size();i++)
 				if (
 					!this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
 					this->_letras[i-1]._vocal and this->_letras[i]._vocal and
 					!this->_letras[i-1]._debil and !this->_letras[i]._debil)
 				{
 				//	printf("%c-%c-",this->_letras[i-1]._letra,this->_letras[i]._letra);
 					//this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
					this->_letras.insert(this->_letras.begin()+i,Letra('-',true));
					cumple=true;
				}
 		if(cumple)
			 std::wcout<<"->hiato"<<std::endl;
 		}
 		void imprimir(){

 			for(int i=1;i<this->_letras.size();i++)
				wprintf(L"%lc",this->_letras[i]._letra);
			//	wprintf(L"%lc",(this->_letras[i]._vocal?L'v':L'c'));


 		}
 		//
 };


//sobrecargando operadores
/*void operator>>(Palabra &a,wchar_t str[]){
		//Palabra x;
		std::wcin>>str;
		a.setPalabra(str);
}*/

#endif