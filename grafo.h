#ifndef GRAFO_H
#define GRAFO_H

#define true 1
#define false 0
typedef int bool;

typedef enum{
	NAO_DIRECIONADO = 0,
	DIRECIONADO = 1
}Direcionamento;

typedef enum{
	NAO_PONDERADO = 0,
	PONDERADO = 1
}Ponderacao;

//estrutura do tipo grafo
typedef struct{
	int numVertices;
	int numArestas;
	int** matrizPesos; //matriz de pesos que irá representar o grafo ponderado. será NULL se não ponderado
	bool** matrizAdj; //matriz de adjacencias que irá representar o grafo nao ponderado
	Direcionamento direcionamento;
	Ponderacao ponderacao;
}Grafo;

bool inicializaGrafo(Grafo* g, int vertices, Direcionamento d, Ponderacao p);
bool insereAresta(Grafo* g, int v1, int v2, int peso);
bool removeAresta(Grafo* g, int v1, int v2);
void exibeGrafo(Grafo* g);
bool arestaExiste(Grafo* g, int v1, int v2);
int grauDoVertice(Grafo* g, int v);
int verticeMaiorGrau(Grafo* g);
bool possuiVizinhos(Grafo* g, int v);
bool liberaGrafo(Grafo* g);
void buscaEmLarguraCompleta(Grafo* g);
void DFSCores(Grafo* g);

#endif