#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_headers.h"


/*����6-6  ���ڽӱ�洢��ͼ�Ĵ�ȡ������ʵ��*/


/*���ݶ����ֵv���Ҷ�����š��������ض�Ӧ������ţ�����Ƿ�������-1*/

int getVertexPos(ALGraph &G,Type v)
{
   int i = 0;
   while (i<G.numVertices && G.VerticesList[i].data != v)  i++;
   if(i<G.numVertices)  return i;
   else return -1;
}

/*��������ͼ�е�ǰ���еĶ������*/
int NumberOfVertices (ALGraph &G)
{
	return G.numVertices;
}

/*��������ͼ�е�ǰ���еı���*/
int NumberOfEdges (ALGraph &G)
{
	return G.numEdges;
}

/*��������v�ĵ�һ���ڽӶ��㣬����Ҳ�������������-1*/
int FirstNeighbor (ALGraph &G, int v)
{
   if (v != -1){              //����v����
	   EdgeNode *p = G.VerticesList[v].adj;   //��Ӧ�������һ���߽��
	   if (p != NULL) return p->dest;     //���ڣ����ص�һ���ڽӶ���
   }
   return -1;     //��һ���ڽӶ��㲻����
}


/*��������v���ڽӶ���w����һ���ڽӶ��㣬����Ҳ�������������-1*/
int NextNeighbor (ALGraph &G, int v, int w)
{
   if (v != -1){   //����v����
	   EdgeNode *p = G.VerticesList[v].adj;  //��Ӧ�������һ���߽��
	   while (p != NULL && p->dest != w) p=p->link; 
	   if (p != NULL && p->link !=NULL)  return p->link->dest;
   }
   return -1;    //��һ�ڽӶ��㲻����
}

/*ȡ������v������ֵ*/
Type getValue (ALGraph &G, int v)
{
	if (v != -1) return G.VerticesList[v].data;
	else return impossibleValue;
}

/*ȡ�ߣ�v,w���ϵ�Ȩֵ*/
Weight getWeight(ALGraph &G, int v, int w)
{
	EdgeNode *p = G.VerticesList[v].adj;
	while (p != NULL && p->dest != w) p=p->link;
	if (p != NULL)  return p->cost;
	else return impossibleWeight;
}


/*����6-7 ���������н������ڽӱ�洢�Ĵ�Ȩͼ*/

void createALGraph (ALGraph &G, int n, int e, int d)
{
//�㷨����n����������ݺ�e���ߵ���Ϣ������ͼG���ڽӱ��ʾ
//d=0��������Ȩ����ͼ��d=1��������Ȩ����ͼ
	int i, j, k; Type val, e1, e2;  Weight c;  EdgeNode *q, *p;
	G.numVertices = n;  G.numEdges = e;   //ͼ�Ķ����������
	for ( i = 0; i < G.numVertices; i++)      //���������
	{
	   printf("������һ�����㣺");
	   scanf("%c", &val);
	   fflush(stdin);
	   G.VerticesList[i].data = val;    //��������Ϊ�ַ�
	   G.VerticesList[i].adj = NULL;
	}
	i = 0;
	while (i < G.numEdges)    //����������ı�����
	{
	   printf("�������������㼰���������ıߵ�Ȩֵ��");
	   scanf("%c %c %d", &e1, &e2, &c);   //����Ϊ�ַ�������ȨֵΪ����
	   fflush(stdin);
	   j = getVertexPos(G,e1);
	   k = getVertexPos(G,e2);
	   if( j != -1 && k != -1)
	   {
		   p = G.VerticesList[j].adj;    //����j�ı�����ͷָ��
		   while ( p != NULL && p->dest != k)  p = p->link;
		   if ( p == NULL )
		   {
			     q = ( EdgeNode * )malloc ( sizeof (EdgeNode ));
				 q->dest = k; q->cost = c;
				 q->link = G.VerticesList[j].adj;   //ǰ�壬���붥��j�ı�����
				 G.VerticesList[j].adj = q;
				 if ( d == 0 )    //����ͼ���ڶԳƱ��������
				 {
				    q = ( EdgeNode* )malloc ( sizeof (EdgeNode));
					q->dest = j; q->cost = c;
					q->link = G.VerticesList[k].adj;   //ǰ�壬���붥��k�ı�����
					G.VerticesList[k].adj = q;
				 }
				 i++;
		  }
		 else printf("���ظ������������룡\n");

	   }
	   else printf("�����˶�����Ϣ�������������룡\n");
	}
}


/*����6-8 ������ڽӱ�洢�Ĵ�Ȩͼ*/
//��Ϊ���������������ǰ�巨�����������ÿ������ıߵ�˳���뵱������ıߵ�˳�����෴��

void printALGraph (ALGraph &G, int d){
	//�����Ȩͼ��d=0ʱ�������Ȩ����ͼ��d=1ʱ�������Ȩ����ͼ��
	int i; EdgeNode *p;
	printf("ͼG�Ķ�������%d\n",G.numVertices);  //���������
	printf("����������ֵ��\n");
	for ( i = 0; i < G.numVertices; i++)  //�����������
		printf("%c ", G.VerticesList[i].data);
	printf("\n");
	printf("ͼG�ı�����\n", G.numEdges);   //�������
	for (i = 0; i < G.numVertices; i++){  //�����������
		for (p = G.VerticesList[i].adj; p != NULL; p =p->link){
			if (d==0 && p->dest < i ) continue;   //����ͼ�ĶԳ�Ԫ�ز����
			printf("(%d,%d) %d",i,p->dest,p->cost);
		}
		printf("\n");
	}
}


/*����6-9 ������ͼ������ͼ���ܱ�������ͨͼ����������������������㷨  ----�ݹ�*/
//�Ӷ���λ��v��������������ȵĴ���������пɶ������δ���ʹ��Ķ���
//�㷨���õ�һ����������visited�����ѷ��ʹ��Ķ��������ʱ��
//�㷨��ʹ�����ڽӱ���ALGraph.h�������ʹ���ڽӾ����뻻MGraph.h����
void DFS_recur (ALGraph &G,int v,int visited[]){
	printf("->%c", getValue(G,v)); visited[v]=1;  //���ʶ���v�������ʱ��
	int w = FirstNeighbor(G,v);   //ȡv�ĵ�һ���ڽӶ���w
	while ( w != -1){    //��w����
		if ( !visited[w]) DFS_recur (G,w,visited);   //��wΪ���ʹ����ݹ����w
		w = NextNeighbor(G,v,w);   //ȡv����һ���ڽӶ���w
	}
}

//�Ӷ���v��������ͼG����������ȱ�����������
void DFS_Traversal ( ALGraph &G,int v){
	int i, n = NumberOfVertices(G);   //ȡͼ�ж������
	int visited[maxVertices];
	for( i = 0; i < n; i++)  visited[i] = 0;
	DFS_recur(G,v,visited);
	printf("\n");
}


/*���� 6-10 ������ͼ������ͼ���ܱ�����������������㷨��������----�ǵݹ�*/
//�㷨ʵ��ͼG�Ĺ����������������ʹ����һ������vexno����ͷ�Ͷ�βָ��ֱ�Ϊfront��rear��
//���⣬�㷨��ʹ�����ڽӱ���ALGraph.h�������ʹ���ڽӾ����뻻MGraph.h����
void BFSTraverse(ALGraph &G){
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
void calcComponents ( ALGraph &G ){
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




