#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
 
 
/*
 	Fazemos um sum�rio dos m�todos para que possa ser compilado sem erros pelo Dev-c++ o c�digo.
*/
float calcularMedia();
void menuPrincipal();
void inserirElemento();
int removerElemento();
void imprimir();
int removerElemento();
void inserirUltimoElemento();
int maiorNumeroVetor();
int removerUltimoElemento();
void iniciarMeio();

/*
	Struct NO
	Toda atribui��o ir� gerar uma inst�ncia nova com o nome (p)
	o atributo [prox] na verdade sempre ser� o [valor] anterior.
	
	Exemplo de input de dados [1,2,3,4,5,6]
		ser� processado como  [6,5,4,3,2,1] 
		Pois � uma pilha, ou melhor uma lista encadeada.
*/

struct no{
	int info;
	struct no * prox;
};

/*
 	M�todo Main, ser� respons�vel por administrar o valor
 	input do menu principal, e distribuir seus valores
 	a suas devidas a��es.
*/
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
			   	printf("%d � o numero removido",valor);
			   	getch();
			   }
			    
				break;
			}
			case 6:{
			   int valor = removerUltimoElemento(&inicio);
		 	   if(valor != -1){
			   	printf("%d � o numero removido",valor);
			   	getch();
			   }
			
			
				break;
			}
			case 7:{
			     inserirUltimoElemento(&inicio);
		 		    
				break;
			}
			case 8:{
			    procurarExistencia(&inicio);
				getch();
				break;
			}
			case 10:{
		   		int valor = maiorNumeroVetor(&inicio);
		      	if(valor != -1){
			   	printf("%d � o maior n�mero",valor);
			   		getch();
			  	}
		
				break;
			}
			case 11:{
		   	  iniciarMeio(&inicio);
		   	  	break;
				}
		
			
		}
	}while(tecla != 9);
   
}

/*
 	Menu principal � respons�vel por printar
 	na tela, todas as op��es dispon�veis
*/
void menuPrincipal(){
	system("cls");
	printf("--- MALLOC ---\n\n");
	printf("1) Inserir Numero\n");
	printf("2) Imprimir N�meros\n");
	printf("3) Contar\n");
	printf("4) Media\n");
	printf("5) Remover Primeiro Elemento\n");
	printf("6) Remover �ltimo Elemento\n");
	printf("7) Adicionar no final\n");
	printf("8) Procurar n�mero\n");
	printf("10) Maior n�mero\n");
	printf("11) Verifica exist�ncia / caso n�o insere no meio \n");
	printf("\n9) Sair\n\n");
}

/*
	Inserir elemento
	Podemos simular o seguinte cen�rio
	1) Nenhum valor foi armazenado ainda, sendo assim de forma simples para
		a explica��o, pegaremos a instancia do struct NULL, instanciamos uma nova
		struct p sem valores em [p=malloc(sizeof(struct no))]
		
		struct no p
		{
			info : 0,
			prox : NULL
		}
	
		apontamos o atributo -> info para a vari�vel x ( Supomos que seja o valor 7)
		e tamb�m atribuimos o atributo->prox = inicio (Lembrando que inicio � null)
		
		struct no p
		{
			info : x (7),
			prox : inicio (NULL)
		}
		
		no final apontamos inicio como p, ficando assim:
		
		struct no inicio
		{
			info : 7,
			prox : inicio (NULL)
		}	
			
	2) Nese cen�rio, j� temos um valor apontando para inicio, sendo que sua struct estar� como
	
		struct no inicio
		{
			info : 7,
			prox : NULL
		}
		assim iremos gerar uma instancia, iremos atribuir o valor x que ser� (3) para info,
		e para prox, apontamos o Inicio, sendo assim ele ir� ficar assim:
	
		struct no p
		{
			info : x (3),
			prox : 	struct no Inicio
					{
						info : x (7),
						prox : inicio (NULL)
					}
		}
		
		Toda vez chamando o m�todo, teremos uma lista encadeada infinita, desde que tenhamos
		mem�ria dispon�vel no sistema.
		
		
*/
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


void inserirUltimoElemento(struct no **inicio){
	
	int x = 0;
	printf("Entre com um elemento: ");
	scanf("%d", &x);
	
	struct no *p, *q;
   
  	if((p=malloc(sizeof(struct no))) == NULL){
  		printf("Falha na aloca��o da mem�ria\n\n");
  		getch();
	  }
	  else{
	  	p->info = x;
	  	p->prox = NULL;
	  	
	  	if(*inicio == NULL)
	  		*inicio = p;
	  	else{
	  		q = *inicio;
	  		
			while(q->prox != NULL)
				q = q->prox;
				
			q->prox = p;
				
		 }
	  }

 	*inicio = q; 
	printf("Elemento %d inserido!\n",x);
	getch();
 
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

	if(*inicio == NULL){
 		printf("A Lista est� vazia.");
 		getch();
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

	if(*inicio == NULL){
 		printf("A Lista est� vazia.");
 		getch();
 		return -1;
	 }
	 	
	struct no *p;	
	struct no *q;		
	p = *inicio;
	q = *inicio;
	
	if(p->prox == NULL){
		int valor = p->info;
	
		*inicio = (*inicio)->prox; 
		free (p);
		p = NULL;
		return valor;
	}
	
	while(p->prox != NULL){
		q = p;
		p = p->prox;
	}
	
	q->prox = NULL;
	
	inicio = q;
	return p->info;
 
}

void procurarExistencia (struct no ** inicio)
{
	int x = 0;
	printf("Entre com um elemento: ");
	scanf("%d", &x);
   
  	struct no *p;
 	p= *inicio;
 	
   while (p != NULL && p->info != x) 
      p = p->prox; 
      
    if(p == NULL){
    	printf("N�o foi encontrado \n");
	}
	else{
		printf("Foi encontrado \n");
	}
	getch();
   
}

void iniciarMeio(struct no ** inicio)
{
	int x = 0;
	printf("Entre com um elemento para buscar: ");
	scanf("%d", &x);
   
  	struct no *p;
 	p= *inicio;
 
   while (p != NULL) {
   	
   	    if(p->info == x){
			printf("Foi encontrado, n�o vamos inserir \n");
			getch();
			return;
    	
		}
		p = p->prox;
   }
     
      

 	struct no *q;
 	
	if((q=malloc(sizeof(struct no))) == NULL){
		printf("Falha na aloca��o da mem�ria\n\n");
		getch();
 	}
	  
 	
	printf("N�o foi encontrado, vamos inserir no meio \n");
 
	int contagem = 0;
	p= *inicio;
	while(p != NULL){
		contagem++; 
		p = p->prox;
	}
	
	int posicao = 0;
 
		posicao  = (contagem / 2) + 1;
		int i = 0;
		p= *inicio;
		while(p != NULL){
		
			if(posicao == i)
			{
				q->info = x;
				q->prox = p->prox;
				p = q;
			}
			else{
				p = p->prox;
			}
			
				i++; 
		}
		inicio = p;
		
 }
 
int maiorNumeroVetor(struct no **inicio){
	
	int mostValue = 0;
	struct no *p;
	p = *inicio;
	  while (p != NULL && p->info != mostValue) {
	  	if(p->info > mostValue){
	  		mostValue = p->info;
		  }
	  	p = p->prox; 
	  }
	  
	  return mostValue;
}

