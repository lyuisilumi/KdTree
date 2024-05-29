#define K 2
struct tree
{
    int coord[K];
    struct tree *esq, *dir;
};
typedef struct tree Tree;

struct fila
{
    Tree *raiz;
    struct fila *prox;
};
typedef struct fila Fila;

void initFila(Fila **fila)
{
    *fila = NULL;
}

int isEmpty(Fila *fila)
{
    return fila == NULL;
}

void dequeue(Fila **fila, Tree **info)
{
    if (!isEmpty(*fila))
    {
        Fila *aux = *fila;
        *info = (*fila)->raiz;
        *fila = (*fila)->prox;
        free(aux);
    }
    else
    {
        *info = NULL;
    }
}

void enqueue(Fila **fila, Tree *raiz)
{
    Fila *novo = (Fila *)malloc(sizeof(Fila));
    novo->raiz = raiz;
    novo->prox = NULL;

    if (isEmpty(*fila))
    {
        *fila = novo;
    }
    else
    {
        Fila *temp = *fila;
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

void initTree(Tree **raiz)
{
    *raiz = NULL;
}

int Nula(Tree *raiz)
{
    return raiz == NULL;
}

Tree *CriaNo(int coord[K])
{
    int i;
    Tree *no = (Tree *)malloc(sizeof(Tree));
    no->dir = no->esq = NULL;
    for (i = 0; i < K; i++)

        no->coord[i] = coord[i];
    return no;
}

void ordernaEixoX(int ponto[][K], int inicio, int fim)
{
    int i, j;
    int(*aux)[K] = malloc((fim - inicio + 1) * sizeof(int[K]));

    for (i = inicio; i < fim; i++)
    {
        for (j = inicio; j < fim - 1; j++)
        {
            if (ponto[j][0] > ponto[j + 1][0])
            {
                aux[0][0] = ponto[j][0];
                aux[0][1] = ponto[j][1];

                ponto[j][0] = ponto[j + 1][0];
                ponto[j][1] = ponto[j + 1][1];

                ponto[j + 1][0] = aux[0][0];
                ponto[j + 1][1] = aux[0][1];
            }
        }
    }
    free(aux);
}

void ordernaEixoY(int ponto[][K], int inicio, int fim)
{
    int i, j;
    int(*aux)[K] = malloc((fim - inicio + 1) * sizeof(int[K]));

    for (i = inicio; i <= fim; i++)
    {
        for (j = inicio; j <= fim - 1; j++)
        {
            if (ponto[j][1] > ponto[j + 1][1])
            {
                aux[0][0] = ponto[j][0];
                aux[0][1] = ponto[j][1];

                ponto[j][0] = ponto[j + 1][0];
                ponto[j][1] = ponto[j + 1][1];

                ponto[j + 1][0] = aux[0][0];
                ponto[j + 1][1] = aux[0][1];
            }
        }
    }
    free(aux);
}

void insereKdTreeR(Tree **raiz, int ponto[][K], int inicio, int fim, int tamanho)
{
    int d, meio = 0;
    if (inicio <= fim)
    {
        // ordena com base no eixo
        d = tamanho % K;
        if (d == 0)
            ordernaEixoX(ponto, inicio, fim);
        else
            ordernaEixoY(ponto, inicio, fim);
            
        meio = (inicio + fim)/2;

        if (*raiz == NULL)
            *raiz = CriaNo(ponto[meio]);
        insereKdTreeR(&(*raiz)->esq, ponto, inicio, meio - 1, tamanho + 1);
        insereKdTreeR(&(*raiz)->dir, ponto, meio + 1, fim, tamanho + 1);
    }
}

void exiberPonto(int pontos[][K], int tamanho)
{
    int i;
    for (i = 0; i <= tamanho; i++)
    {
        printf("(%d, %d)", pontos[i][0], pontos[i][1]);
        if (i < tamanho)
            printf(", ");
    }
    printf("\n");
}

void exibeKdtree(Tree *tree){
	static int n = -1,i;
	if(tree != NULL){
		n++;
		exibeKdtree(tree->dir);
		for(i=0; i<5*n; i++)
			printf(" ");
		printf("(%d, %d)\n", tree->coord[0], tree->coord[1]);
		exibeKdtree(tree->esq);
		n--;
	}
}

double distanciaEuclidiana(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void buscaPontos(Tree *raiz, int pontoConsulta[K], double raio)
{
    if (raiz != NULL)
    {
        Fila *fila, *aux;
        Tree *atual;
        double distancia;
        initFila(&fila);
        initFila(&aux);
        enqueue(&fila, raiz);
        while (!isEmpty(fila))
        {
            dequeue(&fila, &atual);
            distancia = distanciaEuclidiana(pontoConsulta[0], pontoConsulta[1], atual->coord[0], atual->coord[1]);
            if (distancia <= raio)
                enqueue(&aux, atual);
            if (!Nula(atual->esq) && pontoConsulta[0] - raio <= atual->coord[0])
                enqueue(&fila, atual->esq);
            if (!Nula(atual->dir) && pontoConsulta[0] + raio >= atual->coord[0])
                enqueue(&fila, atual->dir);
        }
        if (!isEmpty(aux))
        {
            printf("Pontos no raio %.2f do ponto (%d,%d):", raio, pontoConsulta[0], pontoConsulta[1]);
            while (!isEmpty(aux))
            {
                dequeue(&aux, &atual);
                printf(" (%d,%d)", atual->coord[0], atual->coord[1]);
            }
        }
        else
        {
            printf("Nao foi encontrado pontos dento do raio %.2f do ponto (%d,%d)", raio, pontoConsulta[0], pontoConsulta[1]);
        }
    }
}
