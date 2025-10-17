#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;
typedef float Peso; 

typedef struct aux{
	int vertice;
	Peso peso;
	struct aux* prox;
} ElementoLista, *POINT;

typedef struct{
	int numVertices;
	int numArestas;
	ElementoLista** A;
}Grafo;

typedef struct auxNo{
	int valor;
	struct auxNo* prox;
} No;

typedef struct{
	No* inicio;
	No* fim;
} Fila;


void inicializaFila(Fila* f){
	f->inicio = NULL;
	f->fim = NULL;
}

bool filaVazia(Fila* f){
	return (f->inicio == NULL);
}

void insereFila(Fila* f, int valor){
	No* novo = (No*) malloc(sizeof(No));
	if (!novo) return; 
	novo->prox = NULL;
	novo->valor = valor;
	if (f->inicio == NULL){
		f->inicio = novo;
		f->fim = novo;
	} else {
		f->fim->prox = novo;
		f->fim = novo;
	}
}

No* excluiFila(Fila* f){
	if (!f->inicio) return NULL;
	No* atual = f->inicio;
	f->inicio = atual->prox;
	if (!f->inicio) f->fim = NULL;
	return atual;
}

// busca em Largura (BFS) para listas de adjacência

void buscaEmLargura(Grafo* g, int inicial, bool* visitado){
	if (!g || inicial < 0 || inicial >= g->numVertices) return;

	Fila f;
	inicializaFila(&f);
	
	insereFila(&f, inicial);
	visitado[inicial] = true;
	
	No* no;
	ElementoLista* end;

	while(!filaVazia(&f)){
		no = excluiFila(&f);
		int atual = no->valor;
		printf("Visitando vertice %d\n", atual); 
		free(no);

		end = g->A[atual];
		while (end){
			int verticeVizinho = end->vertice;
			if (!visitado[verticeVizinho]){
				insereFila(&f, verticeVizinho);
				visitado[verticeVizinho] = true;
			}
			end = end->prox;
		}
	}
}

void buscaEmLarguraCompleta(Grafo* g){
	if (!g || g->numVertices < 1) return;
	
	bool* visitado = (bool*)malloc(sizeof(bool) * g->numVertices);
	if (!visitado) return; 

	for (int x = 0; x < g->numVertices; x++){
        visitado[x] = false;
    }
	
	for (int x = 0; x < g->numVertices; x++){
		if (!visitado[x]){
            printf("Iniciando busca a partir do vertice %d\n", x);
            buscaEmLargura(g, x, visitado);
        }
    }
    
	free(visitado);
}
