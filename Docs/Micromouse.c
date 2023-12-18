#include <stdio.h>
#include <stdlib.h>

// <------------- Fila ------------->

typedef 
struct fila
{ 
    int *vet;
    int qtd;
    int inicio;
    int fim;
    int ocupados;
} fila;

fila 
*criar_fila(int n)
{
    fila* f = (fila*) malloc(sizeof(fila));
    
    f->vet = malloc(n * sizeof(int));
    f->qtd = n;
    f->inicio = -1;
    f->fim = 0;
    f->ocupados = 0;   

    return f;
}		

int 
enfileira(fila *f, int no) 
{
    if(f->ocupados >= f->qtd) return 0;

    f->vet[f->fim] = no;
    f->fim = (f->fim + 1) % f->qtd;
    f->ocupados++;

    return 1;
}

int 
desenfileira(fila *f) 
{
    int no = f->vet[f->inicio];

    f->ocupados--;
    f->inicio = (f->inicio + 1) % f->qtd;

    return no;
}

int 
fila_vazia(fila *f) {
    return f->ocupados == 0;
}

void 
destroi_fila(fila *f) 
{
    free(f->vet);
    free(f);
}

// <------------- No -------------> 

typedef 
struct no 
{
    int valor;
    struct no *prox;
    int dir, esq, frt, trs; // Direita, esquerda, frente, trás
    int visitado;
} no;

no 
*cria_no(int n) 
{
    no *novo = malloc(sizeof(no));
    novo->valor = n;
    novo->prox = NULL;
    novo->dir = novo->esq = novo->frt = novo->trs = 0;
    
    return novo;
}

// <------------- Grafo ------------->

typedef 
struct grafo 
{
    no **adj;
    int n;
} grafo;

grafo 
*cria_grafo() 
{
    grafo *g = malloc(sizeof(struct grafo));
    g->n = 0;
    g->adj = NULL;
    
    return g;
}

int 
insere_vertice(grafo *g) 
{
    g->n++;
    g->adj = realloc(g->adj, g->n * sizeof(no*));
    g->adj[g->n - 1] = NULL;

    return g->n - 1;
}

void 
insere_vertice_aresta(grafo *g) 
{
    g->n++;
    g->adj = realloc(g->adj, g->n * sizeof(no*));
    g->adj[g->n - 1] = g->adj[g->n - 2];
}

void 
insere_aresta(grafo *g, int u, int v) 
{
    no *no_u = cria_no(u);
    no_u = g->adj[u];

    no_u->prox = g->adj[v];
    g->adj[v] = no_u;

    no *no_v = cria_no(v);
    no_v = g->adj[v];

    no_v->prox = g->adj[u];
    g->adj[u] = no_v;
}

void 
imprimir_grafo(grafo *g) 
{
    for (int i = 0; i < g->n; i++) {
        no *atual = g->adj[i];
        printf("Vértice %d: ", i);

        while (atual != NULL) {
            if (atual->dir)
                printf("R");
            if (atual->esq)
                printf("E");
            if (atual->frt)
                printf("F");
            if (atual->trs)
                printf("T");

            printf("[%d] -> ", atual->valor);
            atual = atual->prox;
        }

        printf("Null \n");
    }
}

void
visita_vertice(grafo *g, int u) {
    g->adj[u]->visitado = 1;
    for (int i = 0; i < g->n; i++) {
        for (no *atual = g->adj[i]; atual != NULL; atual = atual->prox) {
            if (atual->valor == u) atual->visitado = 1;
        }
    }
}

int 
*busca_em_largura(grafo *g, int u) 
{
    int v;
    int *pai = malloc(g->n * sizeof(int));
    int visitado[g->n];

    fila *f = criar_fila(g->n);
    enfileira(f, u);

    for (int i = 0; i < g->n; i++) 
    {
        pai[i] = -1;
        visitado[i] = 0;
    }

    while(!fila_vazia(f)) {
        v = desenfileira(f);

        for (no *w = g->adj[v]; w != NULL; w = w->prox) 
        {
            if (!visitado[w->valor]) 
            {
                visitado[w->valor] = 1;
                pai[w->valor] = v;
                enfileira(f, w->valor);
            }
        }
    }
    destroi_fila(f);
    return pai;
}

// <-------- Funções do rato -------->

int *
trata_sensor(int codigo) 
{
    int *paredes = malloc(4 * sizeof(int));

    int paredes[0] = (codigo >> 0) & 1;
    int paredes[1] = (codigo >> 1) & 1;
    int paredes[2] =  (codigo >> 2) & 1;
    int paredes[3] = (codigo >> 3) & 1;

    return paredes;
}

int 
interpretar_cmd(grafo *g, int atual, char cmd, int saida) 
{
    if (saida == 10) {
        return;
    }

    switch (cmd)
    {
    case 'l':
        if (saida == 0) {
            
        }
        if (saida == 1) {

        }
        if (saida == 2) {

        }
        break;
        
    case 'r':
        if (saida == 0) {

        }
        if (saida == 1) {

        }
        if (saida == 2) {
            
        }
        break;
        
    case 'w':
        if (saida == 0) {
            printf("c\n");
            fflush(stdout);

            scanf("%d", &saida);
            fflush(stdout);

            int *paredes = trata_sensor(saida);

            for (int i = 0; i < 4; i++) {
                if (!paredes[i]) {
                    int vertice = insere_vertice(g);
                    insere_aresta(g, atual, vertice);
                }
            }

        }
        if (saida == 1) {
            atual++;
            int vertice = insere_vertice(g);
            visita_vertice(g, vertice);

            printf("w\n");

            scanf("%d", &saida);
            fflush(stdout);

            interpretar_cmd(g, atual, 'w', saida);
        }
        if (saida == 2) {
            interpretar_cmd(g, atual, NULL, 10);
        }
        break;

    case 'j':
        if (saida == 0) {

        }
        if (saida == 1) {

        }
        if (saida == 2) {
            
        }
        break;
        
    case 's':
        if (saida == 0) {

        }
        if (saida == 1) {

        }
        if (saida == 2) {
            
        }
        break;
        
    case 'c':
        
        break;
        
    case 'd':
        
        break;
        
    }
}

int 
main(int argc, char **argv) 
{
    int rato_pos = 0, saida, queijo = 0;
    grafo *g = cria_grafo();

    printf("w\n");
    fflush(stdout);

    scanf("%d", &saida);
    fflush(stdout);

    while (queijo != 10) {
        queijo = interpretar_cmd(g, 0, 'w', saida);
    }

    return 0;
}
