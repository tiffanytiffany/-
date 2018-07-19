#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_headers.h"


/*程序6-6  用邻接表存储的图的存取操作的实现*/


/*根据顶点的值v查找顶点序号。函数返回对应顶点序号，如果非法，返回-1*/

int getVertexPos(ALGraph &G,Type v)
{
   int i = 0;
   while (i<G.numVertices && G.VerticesList[i].data != v)  i++;
   if(i<G.numVertices)  return i;
   else return -1;
}

/*函数返回图中当前已有的顶点个数*/
int NumberOfVertices (ALGraph &G)
{
	return G.numVertices;
}

/*函数返回图中当前已有的边数*/
int NumberOfEdges (ALGraph &G)
{
	return G.numEdges;
}

/*给出顶点v的第一个邻接顶点，如果找不到，则函数返回-1*/
int FirstNeighbor (ALGraph &G, int v)
{
   if (v != -1){              //顶点v存在
	   EdgeNode *p = G.VerticesList[v].adj;   //对应边链表第一个边结点
	   if (p != NULL) return p->dest;     //存在，返回第一个邻接顶点
   }
   return -1;     //第一个邻接顶点不存在
}


/*给出顶点v的邻接顶点w的下一个邻接顶点，如果找不到，则函数返回-1*/
int NextNeighbor (ALGraph &G, int v, int w)
{
   if (v != -1){   //顶点v存在
	   EdgeNode *p = G.VerticesList[v].adj;  //对应边链表第一个边结点
	   while (p != NULL && p->dest != w) p=p->link; 
	   if (p != NULL && p->link !=NULL)  return p->link->dest;
   }
   return -1;    //下一邻接顶点不存在
}

/*取出顶点v的数据值*/
Type getValue (ALGraph &G, int v)
{
	if (v != -1) return G.VerticesList[v].data;
	else return impossibleValue;
}

/*取边（v,w）上的权值*/
Weight getWeight(ALGraph &G, int v, int w)
{
	EdgeNode *p = G.VerticesList[v].adj;
	while (p != NULL && p->dest != w) p=p->link;
	if (p != NULL)  return p->cost;
	else return impossibleWeight;
}


/*程序6-7 从输入序列建立用邻接表存储的带权图*/

void createALGraph (ALGraph &G, int n, int e, int d)
{
//算法输入n个顶点的数据和e条边的信息，建立图G的邻接表表示
//d=0，建立带权无向图，d=1，建立带权有向图
	int i, j, k; Type val, e1, e2;  Weight c;  EdgeNode *q, *p;
	G.numVertices = n;  G.numEdges = e;   //图的顶点数与边数
	for ( i = 0; i < G.numVertices; i++)      //建立顶点表
	{
	   printf("请输入一个顶点：");
	   scanf("%c", &val);
	   fflush(stdin);
	   G.VerticesList[i].data = val;    //顶点数据为字符
	   G.VerticesList[i].adj = NULL;
	}
	i = 0;
	while (i < G.numEdges)    //建立各顶点的边链表
	{
	   printf("请输入两个顶点及与其相连的边的权值：");
	   scanf("%c %c %d", &e1, &e2, &c);   //顶点为字符，边上权值为整数
	   fflush(stdin);
	   j = getVertexPos(G,e1);
	   k = getVertexPos(G,e2);
	   if( j != -1 && k != -1)
	   {
		   p = G.VerticesList[j].adj;    //顶点j的边链表头指针
		   while ( p != NULL && p->dest != k)  p = p->link;
		   if ( p == NULL )
		   {
			     q = ( EdgeNode * )malloc ( sizeof (EdgeNode ));
				 q->dest = k; q->cost = c;
				 q->link = G.VerticesList[j].adj;   //前插，链入顶点j的边链表
				 G.VerticesList[j].adj = q;
				 if ( d == 0 )    //无向图，在对称边链表插入
				 {
				    q = ( EdgeNode* )malloc ( sizeof (EdgeNode));
					q->dest = j; q->cost = c;
					q->link = G.VerticesList[k].adj;   //前插，链入顶点k的边链表
					G.VerticesList[k].adj = q;
				 }
				 i++;
		  }
		 else printf("边重复，请重新输入！\n");

	   }
	   else printf("边两端顶点信息有误，请重新输入！\n");
	}
}


/*程序6-8 输出用邻接表存储的带权图*/
//因为建立边链表采用了前插法，输出依附于每个顶点的边的顺序与当初输入的边的顺序是相反的

void printALGraph (ALGraph &G, int d){
	//输出带权图。d=0时，输出带权无向图；d=1时，输出带权有向图。
	int i; EdgeNode *p;
	printf("图G的顶点数是%d\n",G.numVertices);  //输出顶点数
	printf("顶点向量的值是\n");
	for ( i = 0; i < G.numVertices; i++)  //输出顶点数据
		printf("%c ", G.VerticesList[i].data);
	printf("\n");
	printf("图G的边数是\n", G.numEdges);   //输出边数
	for (i = 0; i < G.numVertices; i++){  //各顶点边链表
		for (p = G.VerticesList[i].adj; p != NULL; p =p->link){
			if (d==0 && p->dest < i ) continue;   //无向图的对称元素不输出
			printf("(%d,%d) %d",i,p->dest,p->cost);
		}
		printf("\n");
	}
}


/*程序6-9 【无向图或有向图都能遍历】连通图的深度优先搜索（遍历）算法  ----递归*/
//从顶点位置v出发，以深度优先的次序访问所有可读入的尚未访问过的顶点
//算法中用到一个辅助数组visited，对已访问过的顶点作访问标记
//算法中使用了邻接表定义ALGraph.h，如果向使用邻接矩阵，请换MGraph.h即可
void DFS_recur (ALGraph &G,int v,int visited[]){
	printf("->%c", getValue(G,v)); visited[v]=1;  //访问顶点v，作访问标记
	int w = FirstNeighbor(G,v);   //取v的第一个邻接顶点w
	while ( w != -1){    //若w存在
		if ( !visited[w]) DFS_recur (G,w,visited);   //且w为访问过，递归访问w
		w = NextNeighbor(G,v,w);   //取v的下一个邻接顶点w
	}
}

//从顶点v出发，对图G进行深度优先遍历的主过程
void DFS_Traversal ( ALGraph &G,int v){
	int i, n = NumberOfVertices(G);   //取图中顶点个数
	int visited[maxVertices];
	for( i = 0; i < n; i++)  visited[i] = 0;
	DFS_recur(G,v,visited);
	printf("\n");
}


/*程序 6-10 【无向图或有向图都能遍历】广度优先搜索算法（遍历）----非递归*/
//算法实现图G的广度优先搜索，其中使用了一个队列vexno，队头和队尾指针分别为front和rear。
//此外，算法中使用了邻接表定义ALGraph.h，如果想使用邻接矩阵，请换MGraph.h即可
void BFSTraverse(ALGraph &G){
	int i, j, w, n = NumberOfVertices(G);  EdgeNode *p;
	int visited[maxVertices];  //访问标志数组初始化
	for ( i = 0; i < n; i++) visited[i]=0;//顺序扫描所有顶点
	int vexno[maxVertices]; int front = 0, rear = 0;    //设置队列并置空
	for( i = 0; i < n; i++)
		if ( !visited[i]){     //若顶点i未访问过
			printf("->%c",getValue(G,i));   //访问顶点i
			visited[i]=1;  vexno[rear++]=i;    //做访问标记并进队列
			while ( front < rear ){   //队列不空时执行
				j = vexno[front++];     //队头j出队
				w = FirstNeighbor (G,j);   //取j的第一个邻接顶点w
				while ( w != -1 ){    //若顶点w存在
					if ( ! visited[w] ){   //若顶点w未访问过
						printf("->%c",getValue(G,w));  //访问顶点w
						visited[w] = 1;   //做访问标记
						vexno[rear++] = w;   //顶点w进队列
					}
					w = NextNeighbor (G,j,w);   
				}
			}
		}
}



/*程序6-11  求非连通图的连同分量*/
//从顶点v出发，对图G进行深度优先搜索求连通分量
void calcComponents ( ALGraph &G ){
	int i, k, n = NumberOfVertices (G);    //取图中顶点个数
	int visited[maxSize];   //创建辅助数组
	for (i=0;i<n;i++) visited[i] = 0;   //辅助数组visited初始化
	k = 0;   //连通分量计数
	for(i=0;i<n;i++)   //顺序扫描所有顶点
		if ( !visited[i]){    //若未访问过，则访问
			printf("输出第%d个连通分量的边：\n", ++k);
			DFS_recur(G,i,visited); //  DFS遍历一个连通分量
		}
}




