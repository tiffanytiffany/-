#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_headers.h"


/*��������Ϊ������ͼ�����ڽӾ����ڽӱ���໥ת��*/


void DispAdj(ALGraph *G){
	//����ڽӱ�G
	int i=0;
	EdgeNode *p;
	printf("���������%d\n",G->numVertices);
	for (i=0;i<G->numVertices;i++){
		p = G->VerticesList[i].adj;
		printf("����%d�ı������еĽ����:",i);
		while (p!=NULL){
			printf("%d,",p->dest);
			p=p->link;
		}
		printf("\n");
	}
}


/*���ڽӾ���gת�����ڽӱ�G*/
void MatToList(MGraph g,ALGraph *&G)
{
    int i,j;
    EdgeNode *p;
    G=(ALGraph *)malloc(sizeof(ALGraph));
    for (i=0; i<g.numVertices; i++)                //���ڽӱ�������ͷ�ڵ��ָ�����ó�
        G->VerticesList[i].adj=NULL;
    for (i=0; i<g.numVertices; i++)                //����ڽӾ�����ÿ��Ԫ��
        for (j=g.numVertices-1; j>=0; j--)
            if (g.Edge[i][j]!=0)       //����һ����
            {
                p=(EdgeNode *)malloc(sizeof(EdgeNode));   //����һ���ڵ�*p
                p->dest=j;
                p->link=G->VerticesList[i].adj;        //����ͷ�巨����*p
                G->VerticesList[i].adj=p;
            }
    G->numVertices=g.numVertices;
    G->numEdges=g.numEdges;
}



/*���ڽӱ�Gת�����ڽӾ���g*/
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



/*����ڽӾ���g*/
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