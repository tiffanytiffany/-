#ifndef _MGRAPH_H_
#define _MGRAPH_H_




#include <stdio.h>
#include <stdlib.h>
#define maxSize 50
#define maxVertices 30   //ͼ�ж�����Ŀ�����ֵ
#define maxEdges 900     //������
#define maxWeight 32767   //���Ȩֵ���൱�ڡޣ�
#define impossibleValue '#'
#define impossibleWeight -1  
typedef char Type;     //�������ݵ���������
typedef int Weight;     //��Ȩͼ����Ȩֵ����������

/*����6-1  ���ڽӾ����ʾ��ͼ�Ľṹ����*/
typedef struct{
  int numVertices,numEdges;   //ͼ��ʵ�ʶ�������ͱߵ�����
  Type VerticesList[maxVertices];   //�����
  Weight Edge[maxVertices][maxVertices];  //�ڽӾ���
}MGraph;



//��������

int getVertexPos (MGraph &G,Type x);
int FirstNeighbor (MGraph &G, int v);
int NextNeighbor (MGraph &G, int v, int w);
int NumberOfVertices (MGraph &G);
int NumberOfEdges (MGraph &G);
Type getValue (MGraph &G, int v);
Weight getWeight (MGraph &G, int v, int w);
void createMGraph (MGraph &G, int n, int e, int d);
void printMGraph(MGraph &G,int d);



void DFS_recur (MGraph &G,int v,int visited[]);
void DFS_Traversal ( MGraph &G,int v);    //�Ӷ���v��������ͼG����������ȱ�����������
void BFSTraverse(MGraph &G);

void calcComponents ( MGraph &G );
#endif