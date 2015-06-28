#ifndef GRAMATICA
 #define GRAMATICA 
 #include <string>
 #include <string.h>
 #include <vector>
 #include <stdio.h>
 #include <stdlib.h>
 //using namespace std;
 class Letra{
 	public:
 		char _letra;
 		bool _vocal=false,_debil=false,_lr=false,_revisado=false;

		Letra(){			
		}
		Letra(char _l,bool _r):_letra(_l),_revisado(_r){			
		} 			
		Letra(char _l):_letra(_l){			
		} 			
		Letra(char _l,bool _v,bool _LR):_letra(_l),_vocal(_v),_lr(_LR){

		}


 };
 class Palabra{
 	private:
 		std::string _palabra;
 		std::vector<std::string> _silaba;
 		std::string _vocalesDebiles="iu",_vocalesFuertes="aeo",_lr="lr";
 		std::vector<Letra> _letras;
 		int _acento;
	public:
	
 		void separar(){ 			
 			    
	 			for(int i=0;i<_palabra.length();i++){	 				
	 				this->_letras.push_back(Letra(_palabra[i]));
	 				//ver si es vocal
		 				//fuerte		 				
		 				for(int ii=0;ii<_vocalesFuertes.length();ii++)
			 				if(_palabra[i]==_vocalesFuertes[ii]){//es vocal
			 						this->_letras[i]._vocal=true;
			 					break;
			 				}
						//debil
		 				for(int ii=0;ii<_vocalesDebiles.length();ii++)
			 				if(_palabra[i]==_vocalesDebiles[ii]){//es vocal
			 						this->_letras[i]._vocal=true;
			 						this->_letras[i]._debil=true;
			 					break;
			 				}
			 		  //Y como débil
			 			if(_palabra[i]=='y')
			 				this->_letras[i]._debil=true;

			 				
		 			//ver si es lr
			 		if(!this->_letras[i]._vocal)
			 			for(int ii=0;ii<_lr.length();ii++)
			 				if( _palabra[i]==_lr[ii]){//es lr
			 						this->_letras[i]._lr=true;
			 					break;
			 				}
		 			//printf("%c(%c)",this->_letras[i]._letra,(this->_letras[i]._vocal?'v':'c'));
	 			}
	 			this->_letras.insert(this->_letras.begin(),Letra(' '));//un caracter comodín
 		}

 		void dividir(){
 			int from;
 			bool separar;
 			 for(int i=0;i<_palabra.length();i++)
	 			 		printf(" %c ",_palabra[i]);
 			

 		}
 		void setPalabra(std::string p){
 			_palabra=p;			
 		}
 		Palabra(){}

 		Palabra(std::string p,int ac){
 			_palabra=p;
 			_acento=ac;
 		}

 		/*vector<string> getSilaba(){
 			return ;
 		}*/

 		void imprimirSilaba(){ 			
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
 			//printf("%c\n",this->_letras[0]._letra);

 			for(int i=2;i<this->_letras.size();i++)
				if(
					!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
					!this->_letras[i-2]._vocal and this->_letras[i-1]._vocal and !this->_letras[i]._vocal
				 )
				 { 
					//printf("%c%c-%c ",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
					this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=true;//this->_letras[i]._revisado=true;
					this->_letras.insert(this->_letras.begin()+i,Letra('-',true));							
				 }
					
		//	//printf("\nhay %d silabas\n",k);
			//puts("");
 		}
 		void rest2RLConsonante(){
 			//Si la segunda consonante es r o l, las dos consonantes se agrupan con la segunda vocal			
 			for(int i=2;i<this->_letras.size();i++)
				if(
					!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado
				)
				{	
					
					if((!this->_letras[i-2]._vocal and !this->_letras[i-2]._lr )and this->_letras[i-1]._lr and this->_letras[i]._vocal)
					    {
							//printf("%c%c%c-",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);						
							this->_letras.insert(this->_letras.begin()+i+1,Letra('-',true));
							this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
				  		}
				    else if(!this->_letras[i-2]._vocal and !this->_letras[i-1]._vocal)//excepción
						{
							this->_letras.insert(this->_letras.begin()+i-1,Letra('-',true));
							this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
						}
					/*else if((this->_letras[i-2]._letra=='c' and this->_letras[i-1]._letra=='h') or
						     this->_letras[i-2]._letra==this->_letras[i-1]._letra ) //exceción
						{
							this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
							this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
						}*/
					
				}
 		}
 		void rest3Consonante(){
			/* Cuando hay TRES consonantes ENTRE VOCALES, las primeras 
			dos se unen con la primera vocal y la tercera se une a la segunda vocal*/

			/*Excepción: Si la tercera consonante es r o l, la primera consonante 
			se une con la primera vocal y las otras dos con la siguiente. */
 			int k=0;
 			if(this->_letras.size()>5)
	 			for(int i=4;i<this->_letras.size();i++)
					if(
						this->_letras[i-4]._revisado and !this->_letras[i-3]._revisado and !this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
						this->_letras[i-4]._vocal and !this->_letras[i-3]._vocal and !this->_letras[i-2]._vocal and (!this->_letras[i-1]._vocal and !this->_letras[i-1]._lr) and this->_letras[i]._vocal){
						//printf("%c%c%c-%c%c-",this->_letras[i-4]._letra,this->_letras[i-3]._letra,this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
						this->_letras[i-4]._revisado=this->_letras[i-3]._revisado=this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
						this->_letras.insert(this->_letras.begin()+i-1,Letra('-',true));
					}
					else //excepción
						if(
							!this->_letras[i-4]._revisado and !this->_letras[i-3]._revisado and !this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
							this->_letras[i-4]._vocal and !this->_letras[i-3]._vocal and !this->_letras[i-2]._vocal and this->_letras[i-1]._lr and this->_letras[i]._vocal){		
							//printf("%c%c-%c%c%c-",this->_letras[i-4]._letra,this->_letras[i-3]._letra,this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
							this->_letras[i-4]._revisado=this->_letras[i-3]._revisado=this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
							this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
						}


			//puts("");
 		}

 		void rest4Consonante(){
 			/*Cuando hay cuatro consonantes ENTRE VOCALES, las primeras dos se unen 
			 a la primera vocal y las otras dos se unen a la segunda vocal.*/
 			int k=0;
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
						
				}
			//		puts("");
 		}
 		void restDobleFusion(){//no sirve
 			/*Recuerda que las consonantes dobles: ch, ll, rr representan un solo fonema, 
 			por lo que para efectos de la división silábica 
 			cuentan como una sola consonante (no se separan). Se aplica entonces la regla*/
 			for(int i=2;i<this->_letras.size();i++)
					if(
						!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
						(
							(this->_letras[i-2]._letra=='c' and this->_letras[i-1]._letra=='h') or
						     this->_letras[i-2]._letra==this->_letras[i-1]._letra 
					    )
					   and this->_letras[i]._vocal
						){
							//printf("%c%c%c-",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
							this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
							//this->_letras.insert(this->_letras.begin()+i+1,Letra('-',true));
							this->_letras.insert(this->_letras.begin()+i-2,Letra('-',true));
						}
					
 		}
 		//Los diptongos y los triptongos forman una sola sílaba, por lo que no podemos separarlos. 
 		void restDiptongo(){
 			/*Llamamos diptongo a la unión de una vocal fuerte (a, e, o) y
 			 una vocal débil (i, u) o la unión de dos vocales débiles.(i, u)*/
	 			for(int i=2;i<this->_letras.size();i++)								//débil o fuerte	
	 				if (
	 					!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
	 					!this->_letras[i-2]._vocal and this->_letras[i-1]._debil and this->_letras[i]._vocal)
	 				{
			 			//printf("%c%c%c-",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);			 			
						this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
						this->_letras.insert(this->_letras.begin()+i+1,Letra('-',true));
						
			 		}
			 		//puts("");
 		}
 		//triptongo
 		void restTriptongo(){ 				
 				for(int i=2;i<this->_letras.size();i++)
 					if (!this->_letras[i-2]._revisado and !this->_letras[i-1]._revisado and !this->_letras[i]._revisado
 					 and this->_letras[i-2]._debil and (this->_letras[i-1]._vocal and !this->_letras[i-1]._debil) and this->_letras[i]._debil){
 						//printf("%c%c%c-",this->_letras[i-2]._letra,this->_letras[i-1]._letra,this->_letras[i]._letra);
 						this->_letras[i-2]._revisado=this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
						this->_letras.insert(this->_letras.begin()+i+1,Letra('-',true));
 					}

				//puts("");
 		}
 		//hiato
 		void respHiato(){
 			/*DOS VOCALES FUERTES (a, e, o) requieren que se agrupen 
 			en sílabas diferentes. A este procedimiento le llamamos hiato.*/
 			for(int i=1;i<this->_letras.size();i++)
 				if (
 					!this->_letras[i-1]._revisado and !this->_letras[i]._revisado and
 					this->_letras[i-1]._vocal and this->_letras[i]._vocal and
 					!this->_letras[i-1]._debil and !this->_letras[i]._debil)
 				{
 				//	printf("%c-%c-",this->_letras[i-1]._letra,this->_letras[i]._letra);
 					this->_letras[i-1]._revisado=this->_letras[i]._revisado=true;
					this->_letras.insert(this->_letras.begin()+i,Letra('-',true));
				}
 				//puts("");
 		}
 		void imprimir(){
 			
			for(int i=1;i<this->_letras.size();i++)			
				printf("%c",this->_letras[i]._letra);


				 /*if(this->_letras[i]._letra!='-')		
					printf("%c",(this->_letras[i]._vocal?'v':'c'));*/
 		}
 		//
 };
#endif