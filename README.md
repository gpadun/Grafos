# Estruturas de Dados: Grafos em C

Este projeto é uma implementação em linguagem C de um conjunto de operações e algoritmos para manipulação de grafos. O objetivo principal foi aprofundar o conhecimento sobre estruturas de dados, gerenciamento de memória e a lógica por trás de conceitos complexos de forma manual e de baixo nível.

## O que são Grafos?
Em ciência da computação, um grafo é uma estrutura de dados não-linear que consiste em vértices (ou nós) e arestas (ou conexões) que ligam esses vértices. Eles são usados para modelar relações em cenários do mundo real, como redes sociais, rotas de navegação (GPS), conexões de redes de computadores, entre outros.
Este projeto é uma aplicação introdutória, desenvolvida para proporcionar um contato inicial com o conceito de grafos e seu funcionamento de forma interativa. Aqui, o usuário pode fazer manipulações básicas em um grafo, como criá-lo do zero, gerar um grafo aleatório e realizar operações de busca e consulta.
O objetivo não é ser uma aplicação real e completa, mas sim um ambiente de aprendizado onde é possível visualizar o comportamento dessas estruturas de dados e dos algoritmos de forma prática.
Neste projeto, o grafo é representado por uma **matriz de adjacência**. A matriz de adjacência é uma matriz quadrada onde o valor de cada célula `(i, j)` indica a existência de uma aresta entre o vértice `i` e o vértice `j`.

## Por que este projeto foi feito em C?
Este projeto foi desenvolvido em C para proporcionar um aprendizado mais aprofundado sobre o funcionamento de estruturas de dados e do próprio computador. Diferentemente de linguagens de alto nível, C exige que o desenvolvedor lide diretamente com a alocação e liberação de memória (`malloc` e `free`), ponteiros e a implementação manual de cada estrutura. Esse processo desafiador resulta em um entendimento mais robusto e fundamental da computação.

## Algoritmos e Operações Implementadas
Este projeto inclui as seguintes funcionalidades para manipulação de grafos:
### Operações Básicas
- **Criação de Grafos**: Suporta a criação de grafos direcionados, não-direcionados, ponderados e não-ponderados.
- **Manipulação de Arestas**: Funções para inserir e remover arestas entre vértices.
- **Consulta de Propriedades**: Funções para verificar a existência de arestas, encontrar o grau de um vértice e identificar o vértice com o maior grau.

### Algoritmos de Busca
- **Busca em Largura (BFS - Breadth-First Search)**: Um algoritmo para percorrer ou buscar uma árvore ou um grafo. Ele explora todos os vizinhos de um vértice, e depois os próximos, garantindo o caminho mais curto.
- **Busca em Profundidade (DFS - Depth-First Search)**: Um algoritmo que explora o máximo possível de cada ramificação antes de retroceder. É útil para encontrar ciclos e componentes conectados.

## Como Compilar e Executar o Código
1.  Certifique-se de ter um compilador C (como GCC) instalado.
2.  Abra o terminal na pasta do projeto.
3.  Compile o código usando o comando:
    `main.c grafo.c buscaProfundidade.c buscaEmLargura.c -o meuGrafo`
4.  Execute o programa:
    `./meuGrafo`

