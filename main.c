#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
 
 
 /*
 	Fazemos um sum�rio dos m�todos para que possa ser compilado o c�digo.
*/
float calcularMedia();
void menuPrincipal();
void inserirElemento();
int removerElemento();
void imprimir();
int removerElemento();
/*
	Struct NO
	Toda atribui��o ir� gerar uma inst�ncia nova com o nome (p)
	o atributo [prox] na verdade sempre ser� o [valor] anterior.
	
	Exemplo de input de dados [1,2,3,4,5,6]
		ser� processado como  [6,5,4,3,2,1]
*/
struct no{
	int info;
	struct no * prox;
};

int main(int argc, char *argv[]) {

	setlocale(LC_ALL,"portuguese");
	int tecla = 0;
	struct no *inicio;
	int x;
	inicio = NULL;
	
	do{
		menuPrincipal();
		printf("Insira a opcao ->");
		scanf("%d",&tecla);
		menuPrincipal();
		
		switch(tecla){
			case 1:{
				inserirElemento(&inicio);
				break;
			}
			case 2:{
				imprimir(inicio);
				break;
			}
			case 3:{
			    int contagem = contar(inicio);
			    printf("%d elementos inseridos na aloca��o din�mica.",contagem);
			    getch();
				break;
			}
			case 4:{
			    float media = calcularMedia(inicio);
			    printf("%.2f media.",media);
			    getch();
				break;
			}
			case 5:{
			   int valor = removerElemento(&inicio);
			   
			   if(valor != -1){
			   	printf("%d sera o novo n�mero",valor);
			   }
			    
				break;
			}
			case 6:{
			   int valor = removerUltimoElemento(&inicio);
		 		    
				break;
			}
		}
	}while(tecla != 9);
   
}

void menuPrincipal(){
	system("cls");
	printf("--- MALLOC ---\n\n");
	printf("1) Inserir Numero\n");
	printf("2) Imprimir N�meros\n");
	printf("3) Contar\n");
	printf("4) Media\n");
	printf("5) Remover Primeiro Elemento\n");
	printf("6) Remover �ltimo Elemento\n");
	printf("\n9) Sair\n\n");
}

void inserirElemento(struct no **inicio){
	
	int x = 0;
	printf("Entre com um elemento: ");
	scanf("%d", &x);
	
	struct no *p;
 
		if((p=malloc(sizeof(struct no))) == NULL){
			printf("Erro na aloca��o de memoria \n");
		}
		else{
			p->info = x;
			p->prox = *inicio;
			*inicio = p;
		}
		
		printf("Elemento inserido!\n");
 
}
void imprimir(struct no *inicio){
 struct no *p;
 
 	p=inicio;
	 if(inicio != NULL){
 
 
 		while(p != NULL){
 			printf("--> %d <-- \n", p->info);
 			p = p->prox;
 		}
	}
	else
	{
		printf("Lista Vazia");
	}
	getch();
}
int contar(struct no *inicio){
 	struct no *p;
 	p=inicio;
 	
 	int contagem = 0;
 		
	 if(inicio != NULL){
 		while(p != NULL){
 			contagem++; 
 			p = p->prox;
 			
 		}
	}
	return contagem;
}

float calcularMedia(struct no *inicio){

 	int contagem = contar(inicio);
 	int soma = 0;
	 	
 	struct no *p;
 	p=inicio;
 	
	 if(inicio != NULL){
 		while(p != NULL){
 			soma = soma + p->info; 
 			p = p->prox;
 		}
	}
	
	if(soma == 0 || contagem == 0)
		return 0;
	
	return soma / contagem;
}

int removerElemento(struct no **inicio){

	if(inicio == NULL){
 		printf("A Lista est� vazia.");
 		return -1;
	 }
	 	
	int i = 0; 	
 	struct no *p;
 	
 	p = *inicio;
 	int valor = p->info;
 	*inicio = (*inicio)->prox; 
 
 	free (p);
	p = NULL;
 	return valor;	
}

int removerUltimoElemento(struct no **inicio){

	if(inicio == NULL){
 		printf("A Lista est� vazia.");
 		return -1;
	 }
	 	
	struct no *p;
	struct no *q;
 	p = *inicio;
 	q = *inicio;
 	
	while(q->prox != NULL){
		q = q->prox;
	}
	q->prox = p;

 	*inicio = (*inicio)->prox; 
 
 	free (p);
	p = NULL;
 	return 0;	
}
