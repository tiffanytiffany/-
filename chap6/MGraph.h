#ifndef _MGRAPH_H_
#define _MGRAPH_H_




#include <stdio.h>
#include <stdlib.h>
#define maxSize 50
#define maxVertices 30   //图中顶点数目的最大值
#define maxEdges 900     //最大边数
#define maxWeight 32767   //最大权值（相当于∞）
#define impossibleValue '#'
#define impossibleWeight -1  
typedef char Type;     //顶点数据的数据类型
typedef int Weight;     //带权图边上权值的数据类型

/*程序6-1  用邻接矩阵表示的图的结构定义*/
typedef struct{
  int numVertices,numEdges;   //图中实际顶点个数和边的条数
  Type VerticesList[maxVertices];   //顶点表
  Weight Edge[maxVertices][maxVertices];  //邻接矩阵
}MGraph;



//函数声明

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
void DFS_Traversal ( MGraph &G,int v);    //从顶点v出发，对图G进行深度优先遍历的主过程
void BFSTraverse(MGraph &G);

void calcComponents ( MGraph &G );
#endif