#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dllist.h"
#include "bus.h"
Graph creartGraph(){
    Graph g;
    g.BEN=make_jrb();
    g.DIEM=make_jrb();
    return g;
}
int dropGraph(Graph graph){
    jrb_free_tree(graph.BEN);
    jrb_free_tree(graph.DIEM);
    return 0;
}
int DocFile(Graph graphBus,FILE *ptr){
    int n,i=0,h=0;
 while(!feof(ptr)){ 
             char *S1=(char *)malloc(sizeof(char)*10000000);
             char *S2=(char *)malloc(sizeof(char)*10000000);
             int k=fscanf(ptr,"%d",&n);fseek(ptr,sizeof(char),SEEK_CUR);
             
             fscanf(ptr,"%[^\n]",S1);fseek(ptr,sizeof(char),SEEK_CUR);
             fscanf(ptr,"%[^\n]",S2);
                Chen(graphBus,S1,n,8,&i);
                Chen(graphBus,S2,n,9,&i);
    }
    fclose(ptr);
}
int Chen(Graph graphBus,char *S,int n,int k,int *i){
    JRB NewNode=NULL,Node=NULL;
    char *token=(char *)malloc(sizeof(char)*1000);
    token=strtok(S,"-");
        while(token!=NULL){
          SuaXau(token);
            NewNode=jrb_find_str(graphBus.DIEM,token);
            if(NewNode==NULL){
                JRB tree=make_jrb();
                jrb_insert_str(graphBus.DIEM,token,new_jval_i(*i));
                NewNode=jrb_insert_int(graphBus.BEN,*i,new_jval_v(tree));
                (*i)++;
                ThemGraph(graphBus,Node,NewNode,n,k);
            }
            else{
                NewNode=jrb_find_int(graphBus.BEN,jval_i(NewNode->val));
                ThemGraph(graphBus,Node,NewNode,n,k);
            }
            Node=NewNode;
            token=strtok(NULL,"-");       
        }
}  
int ThemGraph(Graph graph,JRB Node,JRB NewNode,int n,int k){
    JRB Node1,Node2;
    if(Node==NULL || NewNode==NULL) return 1;
    Node1=jrb_find_int((JRB)jval_v(Node->val),jval_i(NewNode->key));
    if(Node1!=NULL){
        jrb_insert_int((JRB)jval_v(Node1->val),(n*10+k),new_jval_i(1));
    }
    else {
        JRB tree=make_jrb();
        jrb_insert_int((JRB)jval_v(Node->val),jval_i(NewNode->key),new_jval_v(tree));
        jrb_insert_int(tree,(n*10+k),new_jval_i(1));
    }
    return 1;
}
double shortestPath(Graph graph, int s, int t, int *path, int *length){
    // Khoi tao cac distance = 0
    double distance[100000], min;
    int previous[100000], u, visit[10000];
    
    for (int i=0; i<100000; i++){
        distance[i] = INFINITIVE_VALUE;
        visit[i] = 0;
        previous[i] = 0;
    }
    distance[s] = 0;
    previous[s] = s;
    visit[s] = 1;
    
    Dllist ptr, queue, node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(s));
    
    // Duyet Queue
    while (!dll_empty(queue)){
        min = INFINITIVE_VALUE;
        dll_traverse(ptr, queue){
            // Lay ra min{distance}
            u = jval_i(ptr->val);
            if (min > distance[u]){
                min = distance[u];
                node = ptr;
            }
        }
        u = jval_i(node->val);
        visit[u] = 1;
        dll_delete_node(node);
        if (u == t) break;
        
        int output[100];
        int n = outdegree(graph, u, output);//Ham kiem tra xem so luong dinh nao noi voi u
        
        // Cap nhap distance cua tat ca cac dinh ma lien ke voi dinh min
        for (int i=0; i<n; i++){
            int v = output[i];
            double w = getEdgeValue(graph, u, v);
            if (distance[v] > distance[u] + w){
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
            if (visit[v] == 0){
                dll_append(queue, new_jval_i(v));
            }
        }
    }
        
    // Truy vet lai de lay duong di tuw s ---> t va luu trong path[]
    double distance_s_t = distance[t]; int count=0;
    if (distance[t] != INFINITIVE_VALUE){
        path[count++] = t;
        while (t != s){
            t = previous[t];
            path[count++] = t;
        }
    *length=count;
    }
    return distance_s_t;
}
double getEdgeValue(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.BEN, v1);
    if (node == NULL)
    {
        return INFINITIVE_VALUE;
    }
    JRB tree = (JRB)jval_v(node->val);
    JRB node1 = jrb_find_int(tree, v2);
    if (node1 == NULL) {
        return INFINITIVE_VALUE;
    }
    return 1;
}

int outdegree(Graph graph, int v, int* output){
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.BEN, v);
    if (node==NULL)
        return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree){
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}
int ChonXeBus(int **A,int Xe[1000000],int k){
    int count[1000000];
    for(int i=0;i<k;i++) Xe[i]=0;
    for(int i=0;i<1000000;i++) count[i]=0;
    for(int i=0;i<k;i++){
        for(int j=0;A[i][j]!=0;j++){
            count[A[i][j]]++;
        }
    }
    int i,max;
    while(1){
        max=count[0],i=0;
        for(int j=0;j<1000000;j++){
            if(count[j]>max){
                max=count[j];
                i=j;
                }
            }
        for(int h=0;h<k;h++){
        for(int j=0;A[h][j]!=0;j++){
            if(A[h][j]==i){
                if(Xe[h]==0){Xe[h]=i;}
                }
            }
        }
    
        for(int p=0;Xe[p]!=0;p++){
            if(p==(k-1)) return 1;
        }   
    count[i]=0;
    }
}
int XeDi(Graph graph,JRB Node1,JRB Node2,int **A,int k){
    if(Node1==NULL || Node2==NULL) return 1; 
    JRB Node3=jrb_find_int(graph.BEN,jval_i(Node1->val));
    Node3=jrb_find_int((JRB)jval_v(Node3->val),jval_i(Node2->val));
    JRB Node4;
    Node3=(JRB)jval_v(Node3->val);int i=0;
    jrb_traverse(Node4,Node3){
        A[k][i++]=jval_i(Node4->key);
    }
    A[k][i]=0;
    return 1;
} 
int Timbus(Graph graph,int *A,int length,JRB tree){
    printf("Duong di:");JRB NewNode=NULL;
    char **S=(char **)malloc(sizeof(char)*MAX);
    for(int i=0;i<100;i++) S[i]=(char *)malloc(sizeof(char)*MAX);
    int **B=(int **)malloc(sizeof(int *)*1000),k=-1;
    for(int i=0;i<1000;i++){B[i]=(int *)malloc(sizeof(int)*1000);}
    for(int i=length-1;i>=0;i--){
        JRB Node;
        jrb_traverse(Node,graph.DIEM){
            if(jval_i(Node->val)==A[i]){
                strcpy(S[k+1],jval_s(Node->key));
                XeDi(graph,NewNode,Node,B,k++);
                NewNode=Node;
            }
        }   
    }
    int Xe[1000000];
    ChonXeBus(B,Xe,k);int j=0;
    for(int i=0;i<k;i++){
        JRB Node=jrb_find_int(tree,Xe[i]);
        if(Node!=NULL){
            if(Xe[i]==Xe[i-1] && i>=1){
                printf("->%s",S[++j]);
            }
            else{
                printf("\n-%s :%s",jval_s(Node->val),S[j]); printf("->%s",S[++j]);
            }
        }
        else{
            if(Xe[i]==Xe[i-1] && i>=1){
                printf("->%s",S[++j]);
            }
            else{
                printf("\n%d :%s",Xe[i],S[j]); printf("->%s",S[++j]);
          }
        }
    }
    printf("\n");
}

int SuaXau(char Xau[100]){
    for(int i=0;i<strlen(Xau);i++){
                Xau[i]=tolower(Xau[i]);
            }
        return 1;
}
JRB CayDacBiet(){
    JRB tree=make_jrb();FILE * ptr=fopen("chieuxe.txt","r");int n;char *S;
     while(!feof(ptr)){
        S=(char *)malloc(sizeof(char)*10);
        fscanf(ptr,"%d %[^\n]",&n,S);
        jrb_insert_int(tree,n,new_jval_s(S));
    }
    fclose(ptr);
    free(S);
    return tree;
}
JRB TraveNode(Graph graph,char *S){
    char *Data=(char *)malloc(sizeof(char)*100);
    JRB Node;
    SuaXau(S);
    int i;
    Node=jrb_find_str(graph.DIEM,S);
    if(Node==NULL){
        jrb_traverse(Node,graph.DIEM){
            i=0;
            strcpy(Data,jval_s(Node->key));
            if(strlen(Data)>strlen(S))
            {
                while(i<strlen(Data)){
                if(strncmp(S,Data+i,strlen(S))==0) return Node;
                i++;
                }
            }
            else
            {
                while(i<strlen(Data)){
                if(strncmp(S,Data+i,strlen(S))==0) return Node;
                i++;
                }
            }   
        }
        return NULL;
    }
    else return Node;
}
