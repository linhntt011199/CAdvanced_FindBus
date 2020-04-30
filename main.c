#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bus.h"
#include <ctype.h>
void menu(){
    printf("1.Tim duong\n2.Thoat chuong trinh\nMoi Ban Chon:");
    return;
}
int main(){
    FILE *ptr=fopen("bus.txt","r");
    Graph graphBus=creartGraph();JRB tree=CayDacBiet();
    DocFile(graphBus,ptr);
    int c;
    do
    {
        menu(); scanf("%d",&c); while(getchar()!='\n');
        switch(c){
            case 1:
                {
                char *di=(char *)malloc(sizeof(char)*100);
                char *den=(char *)malloc(sizeof(char)*100);
                printf("Hay Nhap Diem Xuat Phat Cua Ban:"); scanf("%[^\n]",di); while(getchar()!='\n');
                printf("Hay Nhap Diem Den Cua Ban:"); scanf("%[^\n]",den);while(getchar()!='\n');
                JRB Node1=TraveNode(graphBus,di);
                JRB Node2=TraveNode(graphBus,den);
                if(Node1==NULL || Node2==NULL) printf("Khong Tim Thay Duong\n");
                else{
                        int di=jval_i(Node1->val),den=jval_i(Node2->val);
                        if(di==den) printf("Diem Di Va Diem Den Trung Nhau.Moi Ban Chon Lai\n");
                        else{
                            int *part=(int *)malloc(sizeof(int)*100000),lenght;
                            double pp=shortestPath(graphBus,di,den,part,&lenght);
                            if(pp<MAX)  Timbus(graphBus,part,lenght,tree);
                            free(part);
                            }
                    }
                printf("\n");
                    free(di); free(den);
                }break;
            case 2:
            {
                printf("\nCam On Ban Da Su Dung Ung Dung\n");
                fclose(ptr);
                dropGraph(graphBus);
                jrb_free_tree(tree);
            }break;
        }
    }while(c==1);
}
