#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <conio.c>
#include <string.h>
#include <ctype.h>

//Obs: ficou igual ao sintatico, 
//mas com verificacao de tipo
char semantico(char E, char s)
{
	switch(E) {
		case '1':
			if (s=='I') //exp int
            return('2');
			else if (s=='R')  //exp float
			   return('A');
         else
				return('X');  //erro

		case '2': 
			if(s=='=')  //exp int
				return('3');
			else
				return('!');  //erro falta de atribuicao

		case '3': 
			if ((s=='I')||(s=='C')) //exp int
				return('4');  
			else
				return('@');  //erro esperado I ou C

		case '4':
			if((s=='+')||(s=='-')||(s=='*')) //exp int
				return('3');
			else if (s==';') //se S=fim de linha (;);
				return('Z');  //fim de exp
			else
				return('#');  //erro operador faltando

		case 'A':
			if(s=='=')  //exp float
				return('B');
         else
            return('!');   //erro atribuicao 

      case 'B':
         if ((s=='R')||(s=='D')||(s=='I')||(s=='C'))  //exp float
            return('C');
         else
            return('%');   //erro  R D I C
            
      case 'C':
         if ((s=='+')||(s=='-')||(s=='*')||(s=='/'))
            return('B');   //exp float
         else if (s==';')
            return('Z');   //fim exp
         else
            return('&');   //erro operador com /
           
		 default:
			return('X');   //erro

	}
}//fim da funcao semantico

void mostraErro(char erro, int pos) {
   
   switch(erro) {
      case '!':
         cout<<"\nErro na posicao >> "<<pos<<" <<";
         cout<<"\n\nAtribuicao '=' esperada.";
         break;
      case '@':
         cout<<"\nErro na posicao >> "<<pos<<" <<";
         cout<<"\n\nIdentificador int 'I' ou constante int 'C' esperado";
         break;
      case '#':
         cout<<"\nErro na posicao >> "<<pos<<" <<";
         cout<<"\n\nOperador '+' , '-' ou '*' esperado.";
         break;
      case '%':
         cout<<"\nErro na posicao >> "<<pos<<" <<";
         cout<<"\n\nIdentificador int 'I', identificador float 'R',";
         cout<<"\nconstante int 'C' ou constante float 'D' esperado.";
         break;
      case '&':
         cout<<"\nErro na posicao >> "<<pos<<" <<";
         cout<<"\n\nOperador '+', '-', '*' ou '/' esperado.";
         break;      
      default:
         cout<<"\n\nErro encontrado na expressao";
         
   };
}
void main() {
	char est, estant;

	int i=0,tam;

	clrscr();

	//Abrir Arquivo
	char linha[255], teste[30];
	
	cout << "Digite o Nome do Arq.: ";
	cin >> teste;
	ifstream arq(teste);
	cout << "\n";
	
   if(arq.fail())
	  cout << "Erro na Abertura do Arq.";
	else {
      while(!arq.eof()) {
			arq.getline(linha, 255);
			tam= strlen(linha);
			est='1';
			i=0;
			clrscr();
			cout << linha<<" ";
			while(i<tam) {
            estant=est;
				est=semantico(est,linha[i]);
				 
				if ( est=='Z') {
					if((estant=='4') || (estant=='C') ) {
						//saida ok
						clrscr();
						cout<<linha<<"\n";
						cout<<"Nenhum erro encontrado";
					} else {
                  clrscr();
						cout<<linha<<"\n";
                  mostraErro(est,i);
						getch();
						i=tam;
					}
					getch();
				} else if ((est=='X')||(est=='!')||(est=='@')||
                       (est=='#')||(est=='%')||(est=='&')) {
					clrscr();
					cout<<linha<<"\n";
               mostraErro(est,i);
					getch();
					i=tam;
				}
				i++;
			}
		}
		 arq.close();
	} //Fim arquivo

getch();
}

