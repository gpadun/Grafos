#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

// As definições a seguir devem estar em um arquivo de cabeçalho (.h)
typedef struct aux{
	int vertice;
	// Peso peso; // Remova se o grafo não for ponderado
	struct aux* prox;
} ElementoLista, *POINT;

typedef struct{
	int numVertices;
	int numArestas;
	ElementoLista** A;
}Grafo;

// --- Implementação da Busca em Profundidade (DFS) ---

void visitaProfundidade(Grafo* g, int atual, bool* visitado, int anterior){
	printf("Visitando vertice: %3i (anterior: %3i)\n", atual, anterior);
	visitado[atual] = true;
	ElementoLista* end = g->A[atual];
	while (end) {
		if (!visitado[end->vertice])
			visitaProfundidade(g, end->vertice, visitado, atual);
		end = end->prox;
	}
}

void buscaEmProfundidade(Grafo* g){
	if (!g || g->numVertices < 1) return;
	int x;
	bool* visitado = (bool*) malloc(sizeof(bool) * g->numVertices);
	if (!visitado) return; // Verifica a alocação de memória
	
	for (x = 0; x < g->numVertices; x++) visitado[x] = false;
	
	for (x = 0; x < g->numVertices; x++)
		if (!visitado[x]) visitaProfundidade(g, x, visitado, -1);
	
	free(visitado);
}

// --- Implementação da Busca em Profundidade com Cores (DFS Colors) ---

void visitaDFSCores(Grafo* g, int atual, int* tempo, int* cor, int* tDescoberta, int* tTermino, int* anterior){
	(*tempo)++;
	cor[atual] = 1; // CINZA
	tDescoberta[atual] = *tempo;
	int w;
	ElementoLista* end = g->A[atual];
	while (end){
		w = end->vertice;
		if(cor[w] == 0){ // BRANCO
			anterior[w] = atual;
			visitaDFSCores(g, w, tempo, cor, tDescoberta, tTermino, anterior);
		}
		end = end->prox;
	}
	cor[atual] = 2; // PRETO
	(*tempo)++;
	tTermino[atual] = *tempo;
}

void DFSCores(Grafo* g){
	if (!g || g->numVertices < 1) return;
	int* cor = (int*) malloc(sizeof(int)*g->numVertices);
	int* tDescoberta = (int*) malloc(sizeof(int)*g->numVertices);
	int* tTermino = (int*) malloc(sizeof(int)*g->numVertices);
	int* anterior = (int*) malloc(sizeof(int)*g->numVertices);

    // Verifica se a alocação falhou
    if (!cor || !tDescoberta || !tTermino || !anterior) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    
	int tempo = 0;
	int x;
	for (x = 0; x < g->numVertices; x++){
		cor[x] = 0; // BRANCO
		tDescoberta[x] = -1;
		tTermino[x] = -1;
		anterior[x] = -1;
	}
	for (x = 0; x < g->numVertices; x++)
		if (cor[x] == 0) visitaDFSCores(g, x, &tempo, cor, tDescoberta, tTermino, anterior);
	
	printf("Resumo da Busca em Profundidade:\n");
	printf("No\tanterior\tDescoberta\tTermino\tCor:\n");
	for (x = 0; x < g->numVertices; x++)
		printf("%2i\t%8i\t%10i\t%7i\t%3i\n", x, anterior[x], tDescoberta[x], tTermino[x], cor[x]);
	printf("\n");
	free(cor);
	free(tDescoberta);
	free(tTermino);
	free(anterior);
}