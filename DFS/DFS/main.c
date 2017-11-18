/*
 Autores:
 Piera Carolina Marchesini Dutra - TIA: 31581773
 Ana Carolina dos Santos Silva - TIA:
 Michelle Faifer dos Santos - TIA:
 Priscilla - TIA:
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_QUEUE  100

#define NONE -1
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct edge{
    int name;
    struct edge *prox;
}Edge;

typedef struct vert{
    int name;
    int color;
    int predecessor;
    int d;
    int f;
    Edge *first;
}Vertex;

int varTime;

void printGraphProperties(Vertex G[], int order);
void printGraph(Vertex G[], int order);
void createDigraph(Vertex **G, int order);
void addEdge(Vertex G[], int order, int v1, int v2);
int calcSize(Vertex G[], int order);
void dfs(Vertex G[], int order);
void dfsVisit(Vertex G[], int v);

typedef struct queue{
    int vector[MAX_QUEUE];
    int front;
    int back;
}Queue;

void initializeEmpty(Queue *f);
int isEmpty(Queue f);
void enqueue(Queue *f, int elem);
int dequeue(Queue *f);

void initializeEmpty(Queue *f){
    f->front= f->back= 0;
}
int isEmpty(Queue f){
    return f.back == f.front;
}

void enqueue(Queue *f, int elem);
int dequeue(Queue *f);

void createDigraph(Vertex **G, int order){
    int i;
    *G= (Vertex*) malloc(sizeof(Vertex)*order);
    
    for(i=0; i<order; i++){
        (*G)[i].name= i;
        (*G)[i].color= NONE;
        (*G)[i].predecessor= -1;
        (*G)[i].d = -1;
        (*G)[i].f = -1;
        (*G)[i].first= NULL;
    }
}

void addEdge(Vertex G[], int order, int v1, int v2){
    if (v1<0 || v1 >= order)
        return;
    if (v2<0 || v2 >= order)
        return;
    
    //As its name implies, a digraph is pointing to only one vertex
    Edge *A1= (Edge *) malloc(sizeof(Edge));
    A1->name= v2;
    A1->prox= G[v1].first;
    G[v1].first= A1;
}

void dfs(Vertex G[], int order){
    int i;
    
    for (i=0; i<order; i++){
        G[i].color = WHITE;
        G[i].predecessor = -1;
    }
    varTime = 0;
    for (i=0; i<order; i++){
        if (G[i].color == WHITE) {
            dfsVisit(G, i);
        }
    }
}

void dfsVisit(Vertex G[], int v){
    int j;
    G[v].color = GRAY;
    varTime += 1;
    G[v].d = varTime;
    
    Edge *aux = G[v].first;
    if (aux != NULL)
    for(j=0; aux != NULL; aux= aux->prox, j++){
        if (G[aux->name].color == WHITE) {
            G[aux->name].predecessor = v;
            dfsVisit(G, j);
        }
    }
    G[v].color = BLACK;
    varTime += 1;
    G[v].f = varTime;
}

int calcSize(Vertex G[], int order){
    int i;
    int totalEdges=0;
    
    for (i=0; i<order; i++){
        int j;
        Edge *aux= G[i].first;
        for(j=0; aux != NULL; aux= aux->prox, j++);
        totalEdges += j;
    }
    return totalEdges + order;
}

void printGraph(Vertex G[], int order){
    int i;
    
    for (i=0; i<order; i++){
        printf("\nV%d: ", i);
        Edge *aux= G[i].first;
        for( ; aux != NULL; aux= aux->prox)
            printf("%3d", aux->name);
    }
    printf("\n\n");
}

void printGraphProperties(Vertex G[], int order){
    int i;
    printf("- Vertex number\n");
    for(i=0; i<order; i++)
        printf("%3d ",G[i].name);
    printf("\n");
    printf("- d\n");
    for(i=0; i<order; i++)
        printf("%3d ",G[i].d);
    printf("\n");
    printf("- f (f > d)\n");
    for(i=0; i<order; i++)
        printf("%3d ",G[i].f);
    printf("\n");
    printf("- Color (2 means black, that is the examine of vertex was finished)\n");
    for(i=0; i<order; i++)
        printf("%3d ",G[i].color);
    printf("\n");
    printf("- Predecessor (-1 means that the vertex doesn't have a predecesor)\n");
    for(i=0; i<order; i++)
        printf("%3d ",G[i].predecessor);
    printf("\n");
    
}

int main(int argc, char *argv[]) {
    Vertex *G;
    //Quantity of vertices
    int orderG= 10;
    
    Queue f;
    initializeEmpty(&f);
    
    createDigraph(&G, orderG);
    addEdge(G,orderG,3,4);
    addEdge(G,orderG,4,2);
    addEdge(G,orderG,5,4);
    addEdge(G,orderG,2,3);
    addEdge(G,orderG,3,7);
    
    printf("\nSize of created digraph: %d\n\n",calcSize(G, orderG));
    printf("Adjacency list of digraph");
    printGraph(G, orderG);
    
    dfs(G, orderG);
    
    printf("Properties of digraph after the DFS\n");
    printGraphProperties(G, orderG);
    
    printf("\n");
    
    return 0;
}
