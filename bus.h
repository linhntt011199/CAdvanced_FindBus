#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"
#include "dllist.h"
#define MAX 1000000
#define INFINITIVE_VALUE 10000000
typedef struct Graph{
    JRB BEN;
    JRB DIEM;
}Graph;
typedef struct Xe{
    int ID;
    int So;
}Xe;
Graph creartGraph();
int dropGraph(Graph graph);
int outdegree(Graph graph, int v, int* output);
double shortestPath(Graph graph, int s, int t, int *path, int *length);
double getEdgeValue(Graph graph, int v1, int v2);
int Timbus(Graph graph,int *A,int length,JRB tree);
int ThemGraph(Graph graph,JRB Node,JRB NewNode,int n,int k);
int Chen(Graph graphBus,char *S,int n,int k,int* i);
int DocFile(Graph graphBus,FILE *ptr);
int ChonXeBus(int **A,int Xe[100],int k);
int XeDi(Graph graph,JRB Node1,JRB Node2,int **A,int k);
int SuaXau(char Xau[100]);
JRB CayDacBiet();
JRB TraveNode(Graph graph,char *S);
int check(JRB Node,Xe *part,int i);
int check1(JRB Node,Xe *part,int i);
int BusitNhat(Graph graph,int Start,int Stop,int i,Xe *part,int min,int *soxe);
