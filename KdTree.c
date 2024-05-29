#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "Tad.h"
#define K 2

int main(){
	int n = 6, i, pontos[n][K],pontoBusca[K];
	double raio = 60.0;
	Tree *raiz;
	//prenchendo com pontos
	srand(time(NULL));
	for (i = 0; i < n; i++)
    {
    	pontos[i][0] = rand() % 100;
    	pontos[i][1] = rand() % 100;
    }
    printf("Pontos gerados por n = %d:",n);
    exiberPonto(pontos, n - 1);

    initTree(&raiz);
    n = sizeof(pontos) / sizeof(pontos[0]);//pega o tamanho da matriz
    insereKdTreeR(&raiz, pontos, 0, n - 1, 0);
    printf("\nVendo a Arvore:\n\n");
    exibeKdtree(raiz);
    printf("\nBusca Pontos:\n\n");
    pontoBusca[0] = rand() % 100;
    pontoBusca[1] = rand() % 100;
    buscaPontos(raiz, pontoBusca, raio);
}
