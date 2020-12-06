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
void RSE (No* pRaiz);
void RSD (No* pRaiz);
int BalancaEsquerda(No* pRaiz);
int BalancaDireita(No* pRaiz);
int Balanceamento(No* pRaiz);
int Insere(No* pRaiz,Registro* x);
int GeraChaves(int nNodos);
void MostraArvore(No* a, int b);
void ImprimeNo(int c, int b);

int nNodos;
No* pArv;

int main(){
	pArv = NULL;
/* 	printf ("Quantos elementos terá na árvore? ");
	scanf("%d",&nNodos); */
	GeraChaves(5);
	MostraArvore(pArv, 7);
	bool ehArvore = EhArvoreAvl(pArv);
	if(ehArvore == true){
		printf ("É Árvore AVL!\n");
	}else{
		printf ("Não é Árvore AVL :(");
	}
}

void MostraArvore(No* a, int b) {
    if (a == NULL) {
		return;
    }
MostraArvore(a->pDir, b+1);
ImprimeNo(a->Reg.chave, b);
MostraArvore(a->pEsq, b+1);
}

void ImprimeNo(int c, int b) {
    int i;
    for (i = 0; i < b; i++) printf("   ");
    printf("%d\n", c);
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
void RSE (No* pRaiz){
	No* pAux;

	pAux = (pRaiz)->pDir;
	(pRaiz)->pDir = pAux->pEsq;
	pAux->pEsq = (pRaiz);
	(pRaiz) = pAux;
}

//Rotação Simples Direita
void RSD (No* pRaiz){
	No* pAux;

	pAux = (pRaiz)->pEsq;
	(pRaiz)->pEsq = pAux->pDir;
	pAux->pDir = (pRaiz);
	(pRaiz) = pAux;
}

int BalancaEsquerda(No* pRaiz){
	int fbe = FB ( (pRaiz)->pEsq );
	if (fbe > 0){
		RSD(pRaiz);
		return 1;
	}else if (fbe < 0){ 
		RSE((pRaiz)->pEsq);
		RSD( pRaiz ); 
		return 1;
	}
	return 0;
}

int BalancaDireita(No* pRaiz){
	int fbd = FB( (pRaiz)->pDir);
	if (fbd < 0){
		RSE (pRaiz);
		return 1;
	}else if (fbd > 0){ 
		RSD((pRaiz)->pDir);
		RSE( pRaiz ); 
		return 1;
	}
	return 0;
}

int Balanceamento(No* pRaiz){
	int fb = FB(pRaiz);
	if ( fb > 1){
		return BalancaEsquerda(pRaiz);
	}else if (fb < -1 ){
		return BalancaDireita(pRaiz);
	}else{
		return 0;
	}	
}

int Insere(No* pRaiz, Registro* x){
	if (pArv == NULL){
		pArv = (No*)malloc(sizeof(No));
		pArv->Reg = *x;
		pArv->pEsq = NULL;
		pArv->pDir = NULL;
		printf ("pArv = NULL x = %d\n",pArv->Reg.chave);
		return 1;
	}else if (pRaiz == NULL){
		pRaiz = (No*)malloc(sizeof(No));
		pRaiz->Reg = *x;
		pRaiz->pEsq = NULL;
		pRaiz->pDir = NULL;
		printf ("pRaiz = NULL x = %d\n",pRaiz->Reg.chave);
		return 1;
	}else if (pRaiz->Reg.chave > x->chave){
		if ( Insere(pRaiz->pEsq,x) ){
			if (Balanceamento(pRaiz)){
				return 0;
			}
			else{
				return 1;
			}
		}
	}else if(pRaiz->Reg.chave < x->chave){
		if ( Insere(pRaiz->pDir,x) ){
			if (Balanceamento(pRaiz)){
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

int GeraChaves(int nNodos){
	srand(time(0)); 
	int i;
	for (i=0; i<nNodos; i++){
		Registro* x = malloc(sizeof(Registro));
		x->chave = rand() % 100;
		Insere(pArv, x);
		free(x);
	}
	return 0;
}






