#include <stdio.h>
#include <stdlib.h>


#include "my_headers.h"

int main()
{
	MGraph G;
	createMGraph(G,9,8,1);
	printMGraph(G,1);

	//ALGraph G;
	//createALGraph(G,9,8,0);
	//printALGraph (G,0);
	printf("��ͼ����ȱ���Ϊ��\n");
	DFS_Traversal(G,0);
	printf("��ͼ�Ĺ�ȱ���Ϊ��\n");
	BFSTraverse(G);

	printf("��ͼ����ͨ����Ϊ");
	calcComponents(G);
return 0;
}
