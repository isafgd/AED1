#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include<time.h>

typedef struct registro {
	int chave;
}Registro;

typedef struct no {
	Registro Reg;
	struct no * pEsq; 
	struct no * pDir;
}No;

bool EhArvoreAvl(No* pRaiz);
int FB (No* pRaiz);
int Altura (No* pRaiz);
void RSE (No** ppRaiz);
void RSD (No** ppRaiz);
int BalancaEsquerda(No** ppRaiz);
int BalancaDireita(No** ppRaiz);
int Balanceamento(No** ppRaiz);
int Insere(No** ppRaiz,Registro* x);
int GeraChaves(int nNodos);
void ImprimeNo(int c, int b);
void ExibirArvore(No* pRaiz);

int nNodos;
No* pRaiz;

int main(){
	printf ("Quantos elementos terá na árvore? ");
	scanf("%d",&nNodos);
	GeraChaves(nNodos);
	printf("\n");
	ExibirArvore(pRaiz);
	bool ehArvore = EhArvoreAvl(pRaiz);
	if(ehArvore == true){
		printf ("\n\nÉ Árvore AVL!\n");
	}else{
		printf ("\n\nNão é Árvore AVL :(");
	}
}

//Exibe arvore Em Ordem (com parenteses para os filhos)    
void ExibirArvore(No* raiz){
	if (raiz == NULL) return;
	printf("%i",raiz->Reg.chave);
	printf("(");     
	ExibirArvore(raiz->pEsq);
	ExibirArvore(raiz->pDir);
	printf(")");     
}

//Fator de Balanceamento
int FB (No* pRaiz){
	if(pRaiz == NULL){
		return 0;
	}

	return Altura (pRaiz->pEsq) - Altura (pRaiz->pDir);
}

int Altura (No* pRaiz){
	int iEsq, iDir;

	if(pRaiz == NULL){
		return 0;
	}

	iEsq = Altura (pRaiz->pEsq);
	iDir = Altura (pRaiz->pDir);

	if(iEsq	> iDir){
		return iEsq + 1;
	}else{
		return iDir + 1;
	}
}

//Rotação Simples Esquerda
void RSE (No** ppRaiz){
	No* pAux;

	pAux = (*ppRaiz)->pDir;
	(*ppRaiz)->pDir = pAux->pEsq;
	pAux->pEsq = (*ppRaiz);
	(*ppRaiz) = pAux;
}

//Rotação Simples Direita
void RSD (No** ppRaiz){
	No* pAux;

	pAux = (*ppRaiz)->pEsq;
	(*ppRaiz)->pEsq = pAux->pDir;
	pAux->pDir = (*ppRaiz);
	(*ppRaiz) = pAux;
}

int BalancaEsquerda(No** ppRaiz){
	int fbe = FB ( (*ppRaiz)->pEsq );
	if (fbe > 0){
		RSD(&(*ppRaiz));
		return 1;
	}else if (fbe < 0){ 
		RSE(&((*ppRaiz)->pEsq));
		RSD(&(*ppRaiz) ); 
		return 1;
	}
	return 0;
}

int BalancaDireita(No** ppRaiz){
	int fbd = FB((*ppRaiz)->pDir);
	if (fbd < 0){
		RSE (&(*ppRaiz));
		return 1;
	}else if (fbd > 0){ 
		RSD(&((*ppRaiz)->pDir));
		RSE(&(*ppRaiz)); 
		return 1;
	}
	return 0;
}

int Balanceamento(No** ppRaiz){
	int fb = FB(*ppRaiz);
	if ( fb > 1){
		return BalancaEsquerda(&(*ppRaiz));
	}else if (fb < -1 ){
		return BalancaDireita(&(*ppRaiz));
	}else{
		return 0;
	}	
}

int Insere(No** ppRaiz, Registro* x){
	if (*ppRaiz == NULL){
		*ppRaiz = (No*)malloc(sizeof(No));
		(*ppRaiz)->Reg = *x;
		(*ppRaiz)->pEsq = NULL;
		(*ppRaiz)->pDir = NULL;
		return 1;
	}else if ((*ppRaiz)->Reg.chave > x->chave){
		if ( Insere(&(*ppRaiz)->pEsq,x) ){
			if (Balanceamento(&(*ppRaiz))){
				return 0;
			}
			else{
				return 1;
			}
		}
	}else if((*ppRaiz)->Reg.chave < x->chave){
		if ( Insere(&(*ppRaiz)->pDir,x) ){
			if (Balanceamento(&(*ppRaiz))){
				return 0;
			}
			else{
				return 1;
			}
		}else{
			return 0;
		}
	}else{
		return 0; 
	}
	return 0;
}

bool EhArvoreAvl(No* pRaiz){
	int fb;
	if (pRaiz == NULL){
		return true;
	}
	if (!EhArvoreAvl(pRaiz->pEsq)){
		return false;
	}
	if (!EhArvoreAvl(pRaiz->pDir)){
		return false;
	}
	fb = FB (pRaiz);
	if ( ( fb > 1 ) || ( fb < -1) ){
		return false;
	}
	else{
		return true;
	}
}

//Gera nNodos valores aleatorios para os nodos
int GeraChaves(int nNodos){
	srand(time(0)); 
	int i;
	for (i=0; i<nNodos; i++){
		Registro* x = malloc(sizeof(Registro));
		x->chave = rand() % 100;
		Insere(&pRaiz, x);
		free(x);
	}
	return 0;
}






