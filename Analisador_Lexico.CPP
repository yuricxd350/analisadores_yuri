#include <iostream>
using namespace std;
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define max 50

#define TRUE 1
#define FALSE 0

#define T_LEX 32
#define N_SIMB 50

struct tab {
	int topo;
	struct simb {
		char tipo;
		char lexema[T_LEX+1];
	}simbolo[N_SIMB];
}tabs;

int vazia(void);
int existe_s(char lex[]);
void incluir(char lex[], char t);
void mostrar_tab(void);

int vazia(void) {

	if (tabs.topo != -1)
		return FALSE;

	return TRUE;

}

void mostrar_tab(void) {
	int m=0;
	while(m != tabs.topo+1) {
	std::cout<<"\n--> "<<tabs.simbolo[m].lexema;
		m++;
	}
}

void incluir(char lex[], char t) {
	if (!existe_s(lex)) {
		strcpy(tabs.simbolo[++tabs.topo].lexema,lex);
		tabs.simbolo[tabs.topo].tipo=t;
	}
}

int existe_s(char lex[]) {

	if (!vazia()) {
		for (int i=0; i < tabs.topo; i++) {
			if (strcmp(tabs.simbolo[i].lexema,lex) == 0)
				return TRUE;
		}
	}
	return FALSE;
}


char lexico(char E, char s)
{
	switch(E)
	{
		 case 'X':
			 if(s==' ')
				return('X');
			 else if((s=='+')||(s=='-')||(s=='*')||(s=='/')||(s==',')||(s=='=')||(s=='(')||(s==')')||(s=='{')||(s=='}'))
				return(s);
			 else if(isalpha(s))
				return('I');
			 else if(isdigit(s))
				return('C');
			 else if(s==';')
				return('F');
			 else
				return('E');

		 case 'I':
			 if((isalpha(s))||(isdigit(s)))
				 return('I');
			 else
				 return('E');

		 case 'C':
			 if((s=='.')||(s==','))
				return('D');
			 else if(isdigit(s))
				 return('C');
			 else return('E');

		 case 'D':
			 if(isdigit(s))
				 return('D');
			 else
				 return('E');

		 default:
			return('E');

	}
}//fim da fun‡Æo lexico


int main() {
	char saida[max], est, estant;
	char token[max], *p;			//para a tabela de simbolos

	char reservado[3][6];

	int i=0,j=0,tam,check=1;

//	int nvLinha=FALSE;
	int linhaD=FALSE;
	char tipo='T';

	strcpy(reservado[0],"int");
	strcpy(reservado[1],"float");
	strcpy(reservado[2],"char");

	system("cls"); 

	tabs.topo=-1;
	  //	incluir(lexema,tipo);

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

//			 nvLinha=TRUE;
			 linhaD=FALSE;

			 tam= strlen(linha);
			 est='X';
			 i=0;
			 j=0;

			 p=token;

			 system("cls");
			 cout << linha<<" ";
			 while(i<tam) {
				 estant=est;
				 est=lexico(est,linha[i]);



				 if((estant=='X')&&(est=='E')) {
					 cout<<"\n Erro lexico!\nSimbolo ->"<< linha[i];
					 getch();
					 check=0;
					 i=tam;
				 } else if(est=='E') {
					saida[j]=estant;
					j++;
					saida[j]='\x0'; //marcando o final da string;
					est='X';

					*p='\0';
				 //verificar o caracter
					if ( (strcmp(token,"+") == 0) ||
						  (strcmp(token,"-") == 0) ||
						  (strcmp(token,"/") == 0) ||
						  (strcmp(token,"=") == 0) ||
						  (strcmp(token,"*") == 0) ||
						  (strcmp(token,",") == 0) ) {
				 //nada
					} else {
					//verificar se e real ou inteiro
						if (estant == 'D' || estant == 'C') {
							//nada
						} else {
							cout<<"\n--> "<<token<<" <--";
							incluir(token,tipo);
						}
				 }

				 p=token;



				 } else {
					if (linha[i] != ' ')
						*p++=linha[i];
					i++;
				 }
			 }//fim do while

			 if((est=='F')||(est=='=')||(est=='I')||(est=='C')||
				  (est=='+')||(est=='-')||(est=='*')||(est=='/')||
				  (est==',')) {
				 saida[j]=est;
				 j++;
				 saida[j]='\x0';//marcando o final da string;

				 *p='\0';
				 p=token;
			 }
			 if(check==1) {
				cout <<"\nAnalise Lexica -> "<< saida;
				cout <<"\n\nI -> Identificador(a-Z) \n= -> Atribuicao(=) \nO -> Operador(-*/+) \nC -> Constante Inteira \nD -> Constante Real \nF -> Ponto e Virgula(;)  \n\n";
				getche();
			 }
			 check=1;

		 }
		 arq.close();
	} //Fim arquivo


	mostrar_tab();


getch();
}
