#ifndef _ALGRAPH_H_
#define _ALGRAPH_H_

/*程序6-5 用邻接表表示的图的结构定义*/

typedef struct Enode{      //边结点的定义
   int dest;    //边的另一顶点位置
   Weight cost;      //边上的权值
   struct Enode *link;     //下一条边指针
}EdgeNode;

typedef struct Vnode{      //顶点的定义
   Type data;       //顶点的名字
   struct Enode *adj;    //边链表的头指针
}VertexNode;

typedef struct {         //图的定义
   VertexNode VerticesList[maxVertices];      //顶点表 （各边链表的头结点）
   int numVertices, numEdges;    //图中实际顶点个数和边的条数
}ALGraph;




/*函数声明*/
int getVertexPos(ALGraph &G,Type v);
int NumberOfVertices (ALGraph &G);
int NumberOfEdges (ALGraph &G);
int FirstNeighbor (ALGraph &G, int v);
int NextNeighbor (ALGraph &G, int v, int w);
Type getValue (ALGraph &G, int v);
Weight getWeight(ALGraph &G, int v, int w);


void createALGraph (ALGraph &G, int n, int e, int d);
void printALGraph (ALGraph &G, int d);



void DFS_recur (ALGraph &G,int v,int visited[]);    //深度优先搜索
void DFS_Traversal ( ALGraph &G,int v);   //从顶点v出发，对图G进行深度优先遍历的主过程
void BFSTraverse(ALGraph &G);

void calcComponents ( ALGraph &G );    //求非连通图的连通分量

#endif