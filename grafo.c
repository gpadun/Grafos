#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/*
  ***************************************************************************************************************
  * em todas as funções abaixo seguimos uma abordagem inicial de verificar validade dos parâmetros passados:    *
  * se o endereço do grafo é válido, se os indíces dos vértices são positivos e menores ou iguais à quantidade  *
  * de vértices do grafo                                                                                        *
  ***************************************************************************************************************
*/

bool inicializaGrafo(Grafo* g, int vertices, Direcionamento d, Ponderacao p){
	if(!g || vertices < 1) return false;
	g->numVertices = vertices;
	g->numArestas = 0;
	g->direcionamento = d;
	g->ponderacao = p;
	int i, j;
	int n = g->numVertices;
	
    if(p == NAO_PONDERADO){
		g->matrizAdj = (bool**)malloc(sizeof(bool*)*vertices);
		for(i = 0; i < vertices; i++){
			g->matrizAdj[i] = (bool*)malloc(sizeof(bool)*vertices);
			for(j = 0; j < vertices; j++)
				g->matrizAdj[i][j] = false;
		}
		g->matrizPesos = NULL;
	} else {
		g->matrizPesos = (int**)malloc(sizeof(int*)*vertices);
		for(i = 0; i < vertices; i++){
			g->matrizPesos[i] = (int*)malloc(sizeof(int)*vertices);
			for(j = 0; j < vertices; j++)
				g->matrizPesos[i][j] = -1;
		}
		g->matrizAdj = NULL;
	}
	return true;
}
// Implementações das funções de criação
Grafo* criarGrafoManual(int numVertices, int tipo){
    Grafo* g = malloc(sizeof(Grafo));
    if (!g) return NULL;
    
    Direcionamento d = (tipo == 3 || tipo == 4) ? DIRECIONADO : NAO_DIRECIONADO;
    Ponderacao p = (tipo == 2 || tipo == 4) ? PONDERADO : NAO_PONDERADO;

    inicializaGrafo(g, numVertices, d, p);
    
    return g;
}

// Funcao auxiliar para criar um grafo aleatório
Grafo* criarGrafoAleatorio(int numVertices, int tipo){
    printf("### Criando grafo aleatorio: v=%i ###\n", numVertices);
    
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    if (!g) return NULL;

    Direcionamento d = (tipo == 3 || tipo == 4) ? DIRECIONADO : NAO_DIRECIONADO;
    Ponderacao p = (tipo == 2 || tipo == 4) ? PONDERADO : NAO_PONDERADO;

    inicializaGrafo(g, numVertices, d, p);
    
    int x, y;
    int numArestas = numVertices * (numVertices - 1) / 4; 
    int a = 0;

    while(a < numArestas){
        x = rand() % numVertices;
        y = rand() % numVertices;
        
        if (x != y){
            if(insereAresta(g, x, y, rand() % 100 + 1)){ 
                a++;
            }
        }
    }
    
    printf("Grafo aleatorio com %i arestas criado.\n", g->numArestas);
    return g;
}

void exibeGrafo(Grafo* g){
	int i, j, n = g->numVertices;
	printf("Grafo: \nvertices: %i; arestas: %i\n", g->numVertices, g->numArestas);
	for(i = 0; i < n; i++) printf("\t%3i", i);
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%i", i);
		for(j = 0; j < n; j++){
			if(g->ponderacao == PONDERADO) printf("\t%3i", g->matrizPesos[i][j]);
			else printf("\t%3i", g->matrizAdj[i][j]);
		}
		printf("\n");
	}
}

bool insereAresta(Grafo *g, int v1, int v2, int peso){
	if(!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;

    if(g->ponderacao == PONDERADO){
        if (g->matrizPesos[v1][v2] == -1) {
            g->numArestas++;
        }
        g->matrizPesos[v1][v2] = peso;
        if(g->direcionamento == NAO_DIRECIONADO) {
            g->matrizPesos[v2][v1] = peso;
        }
    }
    else{
        if(g->matrizAdj[v1][v2] == false){
            g->matrizAdj[v1][v2] = true;
            if(g->direcionamento == NAO_DIRECIONADO){
                g->matrizAdj[v2][v1] = true;
            }
            g->numArestas++;
        }
    }
	return true;
}

bool removeAresta(Grafo *g, int v1, int v2){
	if(v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;

	if(g->ponderacao == PONDERADO){
		if(g->matrizPesos[v1][v2] == -1) return false;
		g->matrizPesos[v1][v2] = -1;
		if(g->direcionamento == NAO_DIRECIONADO) g->matrizPesos[v2][v1] = -1;
        g->numArestas--;
	}
	else{
		if(g->matrizAdj[v1][v2] == false) return false;
		g->matrizAdj[v1][v2] = false;
		if(g->direcionamento == NAO_DIRECIONADO) g->matrizAdj[v2][v1] = false;
        g->numArestas--;
	}
	return true;
}


bool arestaExiste(Grafo *g, int v1, int v2){
	if(v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2>= g->numVertices) return false;
	
    if(g->ponderacao == NAO_PONDERADO){
		return g->matrizAdj[v1][v2];
	}
	else{
		return g->matrizPesos[v1][v2] != -1;
	}
}

bool possuiVizinhos(Grafo *g, int v){
	if(!g || v < 0 || v >= g->numVertices) return false;
	int x;
	for(x = 0; x < g->numVertices; x++)
		if(g->ponderacao == NAO_PONDERADO)
			if(g->matrizAdj[v][x]) return true;
		else
			if(g->matrizPesos[v][x] != -1) return true;
	return false;
}

int grauDoVertice(Grafo* g, int v){
	if(!g || v < 0 || v >= g->numVertices) return -1;
	int i, grau = 0;

	if(g->direcionamento == DIRECIONADO){
		if(g->ponderacao == PONDERADO){
			for(i = 0; i < g->numVertices; i++){
				if(g->matrizPesos[v][i] != -1) grau++;
				if(g->matrizPesos[i][v] != -1) grau++;
			}
		} else {
			for(i = 0; i < g->numVertices; i++){
				if(g->matrizAdj[v][i]) grau++;
				if(g->matrizAdj[i][v]) grau++;
			}
		}
	} else {
		if(g->ponderacao == PONDERADO){
			for(i = 0; i < g->numVertices; i++){
				if(g->matrizPesos[v][i] != -1) grau++;
			}
		} else {
			for(i = 0; i < g->numVertices; i++){
				if(g->matrizAdj[v][i]) grau++;
			}
		}
	}
	return grau;
}

int verticeMaiorGrau(Grafo* g){
	int i, j, n = g->numVertices;
	int maiorGrau = -1;
	int indiceMaior = -1;
	for(i = 0; i < n; i++){
		int grau = 0;
		if(g->ponderacao == NAO_PONDERADO){
			if(g->direcionamento == NAO_DIRECIONADO){
				for(j = 0; j < n; j++)
					if (g->matrizAdj[i][j]) grau++;
			}
			else{
				for(j = 0; j < n; j++){
				  if (g->matrizAdj[i][j]) grau++;
                  if (g->matrizAdj[j][i]) grau++;
                }
			}
		}
		else{
			if(g->direcionamento == NAO_DIRECIONADO){
				for(j = 0; j < n; j++)
					if (g->matrizPesos[i][j] != -1) grau++;
			}
			else{
				for(j = 0; j < n; j++){
				  if (g->matrizPesos[i][j] != -1) grau++;
                  if (g->matrizPesos[j][i] != -1) grau++;
                }
			}
		}
		if (grau > maiorGrau || (grau == maiorGrau && i < indiceMaior)) {
            maiorGrau = grau;
            indiceMaior = i;
		}
	}
	return indiceMaior;
}

bool liberaGrafo(Grafo* g){
	if(!g) return false;

	if(g->ponderacao == PONDERADO){
		for(int i = 0; i < g->numVertices; i++)
			free(g->matrizPesos[i]);
		free(g->matrizPesos);
	}
	else{
		for(int i = 0; i < g->numVertices; i++)
			free(g->matrizAdj[i]);
		free(g->matrizAdj);
	}
	g->numArestas = 0;
	g->numVertices = 0;
    if(g->ponderacao == PONDERADO){
        g->matrizPesos = NULL;
    } else {
        g->matrizAdj = NULL;
    }
	return true;
}