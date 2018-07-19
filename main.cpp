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
	printf("该图的深度遍历为：\n");
	DFS_Traversal(G,0);
	printf("该图的广度遍历为：\n");
	BFSTraverse(G);

	printf("该图的连通分量为");
	calcComponents(G);
return 0;
}
