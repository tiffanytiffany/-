#ifndef _ALGRAPH_H_
#define _ALGRAPH_H_

/*����6-5 ���ڽӱ��ʾ��ͼ�Ľṹ����*/

typedef struct Enode{      //�߽��Ķ���
   int dest;    //�ߵ���һ����λ��
   Weight cost;      //���ϵ�Ȩֵ
   struct Enode *link;     //��һ����ָ��
}EdgeNode;

typedef struct Vnode{      //����Ķ���
   Type data;       //���������
   struct Enode *adj;    //�������ͷָ��
}VertexNode;

typedef struct {         //ͼ�Ķ���
   VertexNode VerticesList[maxVertices];      //����� �����������ͷ��㣩
   int numVertices, numEdges;    //ͼ��ʵ�ʶ�������ͱߵ�����
}ALGraph;




/*��������*/
int getVertexPos(ALGraph &G,Type v);
int NumberOfVertices (ALGraph &G);
int NumberOfEdges (ALGraph &G);
int FirstNeighbor (ALGraph &G, int v);
int NextNeighbor (ALGraph &G, int v, int w);
Type getValue (ALGraph &G, int v);
Weight getWeight(ALGraph &G, int v, int w);


void createALGraph (ALGraph &G, int n, int e, int d);
void printALGraph (ALGraph &G, int d);



void DFS_recur (ALGraph &G,int v,int visited[]);    //�����������
void DFS_Traversal ( ALGraph &G,int v);   //�Ӷ���v��������ͼG����������ȱ�����������
void BFSTraverse(ALGraph &G);

void calcComponents ( ALGraph &G );    //�����ͨͼ����ͨ����

#endif