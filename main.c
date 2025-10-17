#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// protótipos das funções auxiliares
Grafo* criarGrafoManual(int numVertices, int tipo);
Grafo* criarGrafoAleatorio(int numVertices, int tipo);
void menuOperacoes(Grafo* g);

int main(){
    int opcaoTipo, opcaoCriacao, numVertices;

    printf("Escolha o tipo de grafo\n");
    printf("1 - Nao direcionado e nao ponderado\n");
    printf("2 - Nao direcionado e ponderado\n");
    printf("3 - Direcionado e nao ponderado\n");
    printf("4 - Direcionado e ponderado\n");
    scanf("%d", &opcaoTipo);

    if (opcaoTipo < 1 || opcaoTipo > 4) {
        printf("\nOpcao invalida! Encerrando programa\n");
        return 1;
    }

    printf("Vamos criar o grafo:\n");
    printf("1 - Criar manualmente\n");
    printf("2 - Criar grafo aleatorio\n");
    scanf("%d", &opcaoCriacao);

    if (opcaoCriacao != 1 && opcaoCriacao != 2) {
        printf("\nOpcao invalida! Encerrando programa\n");
        return 1;
    }

    Grafo* g = NULL;

    if (opcaoCriacao == 1) {
        printf("Digite o numero de vertices: ");
        scanf("%d", &numVertices);
        g = criarGrafoManual(numVertices, opcaoTipo);
    } 
	else {
        g = criarGrafoAleatorio(5, opcaoTipo); 
    }

    if (g == NULL) {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }

    menuOperacoes(g);
    liberaGrafo(g);

    return 0;
}



void menuOperacoes(Grafo *g){
	int opcao, v1, v2;
    int peso = 1;
    
	do{
        printf("\n");
		printf("Digite a opcao desejada\n0 - Sair\n1 - Inserir aresta\n2 - Remover aresta\n3 - Imprimir grafo");
		printf("\n4 - Verificar a existencia de vizinhos\n5 - Verificar grau do vertice\n6 - Busca em largura (BFS)\n");
		printf("7 - Busca em profundidade (DFS)\n8 - Vertice de maior grau\n");
		scanf("%d", &opcao);

		switch(opcao){
		case 1:
			printf("Insira os vertices para a criacao da aresta:\n");
			scanf("%d%d", &v1, &v2);
			if (g->ponderacao == PONDERADO){
    			printf("Digite o peso da aresta: \n");
    			scanf("%d", &peso);
			}	
			insereAresta(g, v1, v2, peso);
			break;
		case 2:
			printf("Insira os vertices para a remocao de aresta:\n");
			scanf("%d%d", &v1, &v2);
			removeAresta(g, v1, v2);
			break;
		case 3:
			exibeGrafo(g);
			break;
		case 4:
			printf("Insira o vertice para verificar a existencia de vizinhos:\n");
			scanf("%d", &v1);
			if(possuiVizinhos(g, v1))
				printf("Possui vizinhos\n");
			else
				printf("Nao possui vizinhos\n");
			break;
		case 5:
			printf("Insira o vertice para verificar o seu grau:\n");
			scanf("%d", &v1);
			printf("Grau do vertice %d: %d\n", v1, grauDoVertice(g, v1));
			break;
		case 6:
            printf("\n-> Executando Busca em Largura (BFS)\n");
            if (g != NULL) {
                buscaEmLarguraCompleta(g);
            } else {
                printf("Erro: O grafo não foi criado.\n");
            }
            break;
		case 7:
            printf("\n-> Executando Busca em Profundidade (DFS com cores)\n");
            if (g != NULL) {
                DFSCores(g);
            } else {
                printf("Erro: O grafo não foi criado.\n");
            }
            break;
        case 8:
            printf("Vertice de maior grau: %d\n", verticeMaiorGrau(g));
            break;
		default:
			if(opcao < 0 || opcao > 8) printf("Opcao invalida!\n");
		}
	}while(opcao != 0);
}
