#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_headers.h"




/*程序6-2  用邻接矩阵存储的图的存取操作的实现*/

//从顶点的数据值找出该顶点的顶点号，如果查找失败，函数返回-1
int getVertexPos (MGraph &G,Type x)
{
	for (int i = 0; i < G.numVertices; i++ )
		if (G.VerticesList[i] == x) return i;
	return -1;
}

//给出顶点v的第一个邻接顶点，如果找不到，则函数返回-1
int FirstNeighbor (MGraph &G, int v)
{
	if (v != -1){
		for (int j = 0; j < G.numVertices; j++)
			if (G.Edge[v][j] > 0 && G.Edge[v][j] < maxWeight ) return j;
	}
	return -1;
}

//给出顶点v的某邻接顶点w的下一个邻接顶点
int NextNeighbor (MGraph &G, int v, int w){
	if (v != -1 && w != -1){   //v、w顶点号合法
		for (int j = w+1; j < G.numVertices; j++)
			if (G.Edge[v][j] > 0 && G.Edge[v][j]<maxWeight)  return j;
	}
	return -1;
}

//函数返回图中已有的顶点个数
int NumberOfVertices (MGraph &G){
	return G.numVertices;
}


//函数返回图中已有的边数
int NumberOfEdges (MGraph &G){
	return G.numEdges;
}

//取顶点v的值
Type getValue (MGraph &G, int v){
	if( v != -1) return G.VerticesList[v];
	else return impossibleValue;  //该不可能值在MGraph.h中定义
}


//取连接顶点v到w的边的权值
Weight getWeight (MGraph &G, int v, int w){
	if (v != -1 && w != -1)  return G.Edge[v][w];
	else return impossibleWeight;    //该不可能值在MGraph.h中定义
}



/*程序6-3 从输入序列建立用邻接矩阵存储的带权无向图*/  //时间复杂度O(n^2)

void createMGraph ( MGraph& G,int n,int e,int d){
	G.numVertices = n; G.numEdges = e;
	int i,j,k; Type val,e1,e2; Weight cost;
	for ( i = 0; i < G.numVertices; ++i ){
		printf("请输入顶点数据\n");
		scanf("%c",&val);
		fflush(stdin);     //清除缓存区（调试时人为缓存了回车）
	//	printf("%c\n",val);   //调试试验用的
		G.VerticesList[i] = val;
	//	printf("处于%d的元素是%c\n",i,G.VerticesList[i]);    //调试时为了看清步骤用的
		for (j = 0; j < G.numVertices; j++ )
			G.Edge[i][j] = (i == j)? 0 : maxWeight;
	}
	k = 0;
	while ( k < G.numEdges ){
		printf("输入两个顶点及与其相连接的边:");
		scanf ("%c %c %d", &e1,&e2,&cost); 
		fflush(stdin);      //清除缓存区，蛮好用的
		i = getVertexPos ( G, e1);
	//	printf("%c所在的序号是%d\n",e1,i);   //调试时为看清步骤用的
     	j = getVertexPos ( G, e2 );
	//	printf("%c所在的序号是%d\n",e2,j);    //调试时为看清步骤用的
		if ( i != -1 && j != -1 ){
			G.Edge[i][j] = cost;
			if ( d == 0 ) G.Edge[j][i] = cost;
			k++;
		}
		else printf ( "边两端顶点信息有误，重新输入！\n");
	}  
}

/*程序6-4 邻接矩阵的输出*/  //时间复杂度O(n^2)

void printMGraph(MGraph &G,int d)
{
//若d=1，按有向图输出；若d=0，按无向图输出
	int i,j,s,n,e;
	Weight w;
	n = G.numVertices;
	e = G.numEdges;
	printf("顶点数=%d,边数=%d\n",n,e);
	printf("顶点数据为\n");
	for(i=0;i<n;i++)    //输出顶点数据
		printf("%d,%c\n",i,G.VerticesList[i]);
	printf("\n");
	printf("输出边，形式为(i,j),w:  \n");
	for (i=0;i<n;i++){
		s = (d==0)? i:0;   //若为无向图，仅打印上三角
	    for(j=s;j<n;j++){//若为有向图，则0<j<n
			w = G.Edge[i][j];   //取边的权值
			if (w>0 && maxWeight)  //输出边的信息
				printf("(%d,%d),%d\n",i,j,w);
		}
	}
	
}


/*程序6-9 【无向图或有向图都能遍历】连通图的深度优先搜索（遍历）算法  ----递归*/
//从顶点位置v出发，以深度优先的次序访问所有可读入的尚未访问过的顶点
//算法中用到一个辅助数组visited，对已访问过的顶点作访问标记
//算法中使用了邻接矩阵，
void DFS_recur (MGraph &G,int v,int visited[]){
	printf("->%c", getValue(G,v)); visited[v]=1;  //访问顶点v，作访问标记
	int w = FirstNeighbor(G,v);   //取v的第一个邻接顶点w
	while ( w != -1){    //若w存在
		if ( !visited[w]) DFS_recur (G,w,visited);   //且w为访问过，递归访问w
		w = NextNeighbor(G,v,w);   //取v的下一个邻接顶点w
	}
}

//从顶点v出发，对图G进行深度优先遍历的主过程
void DFS_Traversal ( MGraph &G,int v){
	int i, n = NumberOfVertices(G);   //取图中顶点个数
	int visited[maxVertices];
	for( i = 0; i < n; i++)  visited[i] = 0;
	DFS_recur(G,v,visited);
	printf("\n");
}

/*程序 6-10 【无向图或有向图都能遍历】广度优先搜索算法（遍历）----非递归*/
//算法实现图G的广度优先搜索，其中使用了一个队列vexno，队头和队尾指针分别为front和rear。
//此外，算法中使用了邻接矩阵
void BFSTraverse(MGraph &G){
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
void calcComponents ( MGraph &G ){
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

