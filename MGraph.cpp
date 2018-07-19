#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_headers.h"




/*����6-2  ���ڽӾ���洢��ͼ�Ĵ�ȡ������ʵ��*/

//�Ӷ��������ֵ�ҳ��ö���Ķ���ţ��������ʧ�ܣ���������-1
int getVertexPos (MGraph &G,Type x)
{
	for (int i = 0; i < G.numVertices; i++ )
		if (G.VerticesList[i] == x) return i;
	return -1;
}

//��������v�ĵ�һ���ڽӶ��㣬����Ҳ�������������-1
int FirstNeighbor (MGraph &G, int v)
{
	if (v != -1){
		for (int j = 0; j < G.numVertices; j++)
			if (G.Edge[v][j] > 0 && G.Edge[v][j] < maxWeight ) return j;
	}
	return -1;
}

//��������v��ĳ�ڽӶ���w����һ���ڽӶ���
int NextNeighbor (MGraph &G, int v, int w){
	if (v != -1 && w != -1){   //v��w����źϷ�
		for (int j = w+1; j < G.numVertices; j++)
			if (G.Edge[v][j] > 0 && G.Edge[v][j]<maxWeight)  return j;
	}
	return -1;
}

//��������ͼ�����еĶ������
int NumberOfVertices (MGraph &G){
	return G.numVertices;
}


//��������ͼ�����еı���
int NumberOfEdges (MGraph &G){
	return G.numEdges;
}

//ȡ����v��ֵ
Type getValue (MGraph &G, int v){
	if( v != -1) return G.VerticesList[v];
	else return impossibleValue;  //�ò�����ֵ��MGraph.h�ж���
}


//ȡ���Ӷ���v��w�ıߵ�Ȩֵ
Weight getWeight (MGraph &G, int v, int w){
	if (v != -1 && w != -1)  return G.Edge[v][w];
	else return impossibleWeight;    //�ò�����ֵ��MGraph.h�ж���
}



/*����6-3 ���������н������ڽӾ���洢�Ĵ�Ȩ����ͼ*/  //ʱ�临�Ӷ�O(n^2)

void createMGraph ( MGraph& G,int n,int e,int d){
	G.numVertices = n; G.numEdges = e;
	int i,j,k; Type val,e1,e2; Weight cost;
	for ( i = 0; i < G.numVertices; ++i ){
		printf("�����붥������\n");
		scanf("%c",&val);
		fflush(stdin);     //���������������ʱ��Ϊ�����˻س���
	//	printf("%c\n",val);   //���������õ�
		G.VerticesList[i] = val;
	//	printf("����%d��Ԫ����%c\n",i,G.VerticesList[i]);    //����ʱΪ�˿��岽���õ�
		for (j = 0; j < G.numVertices; j++ )
			G.Edge[i][j] = (i == j)? 0 : maxWeight;
	}
	k = 0;
	while ( k < G.numEdges ){
		printf("�����������㼰���������ӵı�:");
		scanf ("%c %c %d", &e1,&e2,&cost); 
		fflush(stdin);      //����������������õ�
		i = getVertexPos ( G, e1);
	//	printf("%c���ڵ������%d\n",e1,i);   //����ʱΪ���岽���õ�
     	j = getVertexPos ( G, e2 );
	//	printf("%c���ڵ������%d\n",e2,j);    //����ʱΪ���岽���õ�
		if ( i != -1 && j != -1 ){
			G.Edge[i][j] = cost;
			if ( d == 0 ) G.Edge[j][i] = cost;
			k++;
		}
		else printf ( "�����˶�����Ϣ�����������룡\n");
	}  
}

/*����6-4 �ڽӾ�������*/  //ʱ�临�Ӷ�O(n^2)

void printMGraph(MGraph &G,int d)
{
//��d=1��������ͼ�������d=0��������ͼ���
	int i,j,s,n,e;
	Weight w;
	n = G.numVertices;
	e = G.numEdges;
	printf("������=%d,����=%d\n",n,e);
	printf("��������Ϊ\n");
	for(i=0;i<n;i++)    //�����������
		printf("%d,%c\n",i,G.VerticesList[i]);
	printf("\n");
	printf("����ߣ���ʽΪ(i,j),w:  \n");
	for (i=0;i<n;i++){
		s = (d==0)? i:0;   //��Ϊ����ͼ������ӡ������
	    for(j=s;j<n;j++){//��Ϊ����ͼ����0<j<n
			w = G.Edge[i][j];   //ȡ�ߵ�Ȩֵ
			if (w>0 && maxWeight)  //����ߵ���Ϣ
				printf("(%d,%d),%d\n",i,j,w);
		}
	}
	
}


/*����6-9 ������ͼ������ͼ���ܱ�������ͨͼ����������������������㷨  ----�ݹ�*/
//�Ӷ���λ��v��������������ȵĴ���������пɶ������δ���ʹ��Ķ���
//�㷨���õ�һ����������visited�����ѷ��ʹ��Ķ��������ʱ��
//�㷨��ʹ�����ڽӾ���
void DFS_recur (MGraph &G,int v,int visited[]){
	printf("->%c", getValue(G,v)); visited[v]=1;  //���ʶ���v�������ʱ��
	int w = FirstNeighbor(G,v);   //ȡv�ĵ�һ���ڽӶ���w
	while ( w != -1){    //��w����
		if ( !visited[w]) DFS_recur (G,w,visited);   //��wΪ���ʹ����ݹ����w
		w = NextNeighbor(G,v,w);   //ȡv����һ���ڽӶ���w
	}
}

//�Ӷ���v��������ͼG����������ȱ�����������
void DFS_Traversal ( MGraph &G,int v){
	int i, n = NumberOfVertices(G);   //ȡͼ�ж������
	int visited[maxVertices];
	for( i = 0; i < n; i++)  visited[i] = 0;
	DFS_recur(G,v,visited);
	printf("\n");
}

/*���� 6-10 ������ͼ������ͼ���ܱ�����������������㷨��������----�ǵݹ�*/
//�㷨ʵ��ͼG�Ĺ����������������ʹ����һ������vexno����ͷ�Ͷ�βָ��ֱ�Ϊfront��rear��
//���⣬�㷨��ʹ�����ڽӾ���
void BFSTraverse(MGraph &G){
	int i, j, w, n = NumberOfVertices(G);  EdgeNode *p;
	int visited[maxVertices];  //���ʱ�־�����ʼ��
	for ( i = 0; i < n; i++) visited[i]=0;//˳��ɨ�����ж���
	int vexno[maxVertices]; int front = 0, rear = 0;    //���ö��в��ÿ�
	for( i = 0; i < n; i++)
		if ( !visited[i]){     //������iδ���ʹ�
			printf("->%c",getValue(G,i));   //���ʶ���i
			visited[i]=1;  vexno[rear++]=i;    //�����ʱ�ǲ�������
			while ( front < rear ){   //���в���ʱִ��
				j = vexno[front++];     //��ͷj����
				w = FirstNeighbor (G,j);   //ȡj�ĵ�һ���ڽӶ���w
				while ( w != -1 ){    //������w����
					if ( ! visited[w] ){   //������wδ���ʹ�
						printf("->%c",getValue(G,w));  //���ʶ���w
						visited[w] = 1;   //�����ʱ��
						vexno[rear++] = w;   //����w������
					}
					w = NextNeighbor (G,j,w);   
				}
			}
		}
}




/*����6-11  �����ͨͼ����ͬ����*/
//�Ӷ���v��������ͼG�������������������ͨ����
void calcComponents ( MGraph &G ){
	int i, k, n = NumberOfVertices (G);    //ȡͼ�ж������
	int visited[maxSize];   //������������
	for (i=0;i<n;i++) visited[i] = 0;   //��������visited��ʼ��
	k = 0;   //��ͨ��������
	for(i=0;i<n;i++)   //˳��ɨ�����ж���
		if ( !visited[i]){    //��δ���ʹ��������
			printf("�����%d����ͨ�����ıߣ�\n", ++k);
			DFS_recur(G,i,visited); //  DFS����һ����ͨ����
		}
}

