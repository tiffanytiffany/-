#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_headers.h"


/*以下内容为【无向图】的邻接矩阵、邻接表的相互转换*/


void DispAdj(ALGraph *G){
	//输出邻接表G
	int i=0;
	EdgeNode *p;
	printf("顶点个数是%d\n",G->numVertices);
	for (i=0;i<G->numVertices;i++){
		p = G->VerticesList[i].adj;
		printf("顶点%d的边链表中的结点有:",i);
		while (p!=NULL){
			printf("%d,",p->dest);
			p=p->link;
		}
		printf("\n");
	}
}


/*将邻接矩阵g转换成邻接表G*/
void MatToList(MGraph g,ALGraph *&G)
{
    int i,j;
    EdgeNode *p;
    G=(ALGraph *)malloc(sizeof(ALGraph));
    for (i=0; i<g.numVertices; i++)                //给邻接表中所有头节点的指针域置初
        G->VerticesList[i].adj=NULL;
    for (i=0; i<g.numVertices; i++)                //检查邻接矩阵中每个元素
        for (j=g.numVertices-1; j>=0; j--)
            if (g.Edge[i][j]!=0)       //存在一条边
            {
                p=(EdgeNode *)malloc(sizeof(EdgeNode));   //创建一个节点*p
                p->dest=j;
                p->link=G->VerticesList[i].adj;        //采用头插法插入*p
                G->VerticesList[i].adj=p;
            }
    G->numVertices=g.numVertices;
    G->numEdges=g.numEdges;
}



/*将邻接表G转换成邻接矩阵g*/
void ListToMat(ALGraph *G,MGraph &g)
{
    int i;
    EdgeNode *p;
    for (i=0; i<G->numVertices; i++)
    {
        p=G->VerticesList[i].adj;
        while (p!=NULL)
        {
            g.Edge[i][p->dest]=1;
            p=p->link;
        }
    }
    g.numVertices=G->numVertices;
    g.numEdges=G->numEdges;
}



/*输出邻接矩阵g*/
void DispMat(MGraph g)
{
    int i,j;
    for (i=0; i<g.numVertices; i++)
    {
        for (j=0; j<g.numVertices; j++)
            printf("%d",g.Edge[i][j]);
        printf("\n");
    }
}