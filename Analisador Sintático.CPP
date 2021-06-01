#include <iostream>
using namespace std;
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//#include <conio.c>
#include <string.h>
#include <ctype.h>

char sintatico(char E, char s)
{
	switch(E) {
		case '1':
		//r - identificador real;
		//i - identificador inteiro;
		//a - identificador char;
			if((s=='R')||(s=='I')||(s=='A'))
				return('2');

	//t - int;
	//f - float;
	//h - char;
			else if ((s=='T')||(s=='F')||(s=='H'))
				return('5');
			else
	//x - erro;
				return('X');

		case '2':
			if(s=='=')
				return('3');
			else
				return('X');

		case '3':
			if ((s=='R')||(s=='I')||(s=='A')||(s=='C')||(s=='D')||(s=='E'))
				return('4');
			else
				return('X');

		case '4':
			if((s=='+')||(s=='-')||(s=='*')||(s=='/'))
				return('3');
			else if (s==';') //se S=fim de linha (;);
				return('Z');
			else
				return('X');

		case '5':
			if((s=='R')||(s=='I')||(s=='A'))
				return('6');
         else
            return('X');

      case '6':
         if (s==',')
            return('5');
         else if (s==';')
            return('Z');
         else
            return('X');
           
		 default:
			return('X');

	}
}//fim da funcao sintatico


int main() {
	char est, estant;

	int i=0,tam;

	system("cls");

	//Abrir Arquivo
	char linha[255], teste[30];
	
	std::cout << "Digite o Nome do Arq.: ";
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
			system("cls");
			cout << linha<<" ";
			while(i<tam) {
            estant=est;
				est=sintatico(est,linha[i]);
				 
				if ( est=='Z') {
					if((estant=='4') || (estant=='6') ) {
						//saida ok
						system("cls");
						cout<<linha<<"\n";
						cout<<"Nenhum erro encontrado";
					} else {
						system("cls");
						cout<<linha<<"\n";
						cout<<"Erro encontrado na posicao "<<i;
						getch();
						i=tam;
					}
					getch();
				} else if (est=='X') {
					system("cls");
					cout<<linha<<"\n";
					cout<<"Erro encontrado na posicao "<<i;
					getch();
					i=tam;
				}
				if (strlen(linha)==1) {
					system("cls");
					cout<<linha<<"\n";
					cout<<"Erro encontrado na posicao "<<i;
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

