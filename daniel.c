#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define NUMBER 0
#define HIGH 1
#define LOW 2
#define BUFFER 20

struct node {
	unsigned int *end_vertexes;
	unsigned int lenght;
};

void read_line(unsigned int* P1,unsigned int* P2);
void create_adj_list(struct node** list);
unsigned int BFS(struct node** list, unsigned int i2,unsigned int i3,unsigned int * checked);
unsigned int N=0;
unsigned int L=0;
void seek_fundamentals(struct node** list,int* fundamentals);
unsigned int check_disconection(struct node** list,unsigned int i, unsigned int * checked);
void free_list(struct node** list);



void initialize_list (struct node** list) 
{
	unsigned int i;
	for (i = 0; i < N; ++i)
	{
		list[i] = malloc(sizeof(struct node));
		list[i]-> lenght = 0;
		list[i]-> end_vertexes = malloc(sizeof(unsigned int));
	}
}

void add_node(struct node **list,unsigned int P1, unsigned int P2) 
{	
	unsigned int* end_vertexes1,* end_vertexes2;

	realloc_retry:
	end_vertexes1 = realloc(list[P1]->end_vertexes,(sizeof(unsigned int)*++list[P1]->lenght));
	end_vertexes2 = realloc(list[P2]->end_vertexes,(sizeof(unsigned int)*++list[P2]->lenght));

	if (end_vertexes1 == NULL || end_vertexes2 == NULL)
	{
		--list[P1]->lenght;
		--list[P2]->lenght;
		goto realloc_retry;
	}

	list[P1]->end_vertexes = end_vertexes1;
	list[P2]->end_vertexes = end_vertexes2;

	list[P1]->end_vertexes[list[P1]->lenght-1] = P2;
	list[P2]->end_vertexes[list[P2]->lenght-1] = P1;

	return;
}

int main(int argc, char const *argv[])
{
	struct node** list;
	int fundamentals[3];
	read_line(&N,&L);
	list = calloc(N,sizeof(struct node*));
	initialize_list(list);
	create_adj_list(list);
	seek_fundamentals(list,fundamentals);
	printf("%d\n%d %d\n",fundamentals[NUMBER],fundamentals[LOW],fundamentals[HIGH]);
	free_list(list);
	return 0;
}

void free_list(struct node** list)
{
	unsigned int i;
	for (i = 0; i < N; ++i)
	{
		free(list[i]->end_vertexes);
	}
	free(list);
	return;
}


void read_line(unsigned int* P1,unsigned int* P2) 
{
	char* string;
	unsigned int n;
	n = 80;
	string = malloc(n + 1);
	string = fgets(string,n,stdin);
	sscanf(string,"%u %u\n",P1,P2);
	free(string);
	return;
}

void create_adj_list(struct node** list) 
{
	unsigned int P1,P2;
	unsigned int i;
	P1 = P2 = 0;
	
	for (i = 0; i < L; ++i)
	{
		read_line(&P1,&P2);
		add_node(list,P1-1,P2-1);
	}
	return;
}


void seek_fundamentals(struct node** list,int* fundamentals)
{
	unsigned int i;
	unsigned int * checked;
	fundamentals[NUMBER] = 0;
	fundamentals[HIGH] = -1;
	fundamentals[LOW] = -1;
	checked = calloc(N,sizeof(unsigned int));
	for (i = 0; i < N; ++i)
	{
		if (checked[i])
		{
			fundamentals[NUMBER]++;
			if (fundamentals[NUMBER] == 1) 
			{
				fundamentals[HIGH] = i+1;
				fundamentals[LOW] = i+1;
			}
			else
			{
				if (i+1 > fundamentals[HIGH]){fundamentals[HIGH] = i+1;}
				if (i+1 < fundamentals[LOW]){fundamentals[LOW] = i+1;}	
			}
		}
		else if (check_disconection(list,i,checked))
		{
			fundamentals[NUMBER]++;
			if (fundamentals[NUMBER] == 1) 
			{
				fundamentals[HIGH] = i+1;
				fundamentals[LOW] = i+1;
			}
			else
			{
				if (i+1 > fundamentals[HIGH]){fundamentals[HIGH] = i+1;}
				if (i+1 < fundamentals[LOW]){fundamentals[LOW] = i+1;}	
			}
		} 
	}
	free(checked);
	return;
}

unsigned int check_disconection(struct node** list,unsigned int i, unsigned int * checked) 
{
	unsigned int i2,depth;
	if (i == 1) i2 = 2;
	else i2 = 1;
	depth = BFS(list,i2,i,checked);
	if (depth == N - 1) {return 0;}
	return 1;
}

unsigned int BFS(struct node** list,unsigned int i2,unsigned int i3, unsigned int * checked)
{

	unsigned int i,g,j,index;
	struct node* el;
	unsigned int *visited;
	unsigned int *queue;
	if (list[i3]->lenght == 1)
	{
		checked[list[i3]->end_vertexes[0]] = 1;
		return N-1;
	}
	queue = calloc(N+1,sizeof(unsigned int));
	visited = calloc(N,sizeof(unsigned int));
	queue[0] = i2;
	for (i = 1; i < N; ++i)
	{
		queue[i] = -1;
		visited[i-1] = 0;
	}
	visited[N-1] = 0;
	queue[i+1] = -1;
	visited[i2] = 1;

	index = 1;

	for (g = 0;(queue[g] !=-1); ++g)
	{
		el = list[queue[g]];
		for ( j = 0; j < el->lenght;j++)
		{
			if ((!visited[el->end_vertexes[j]]) && (el->end_vertexes[j]!=i3)){ queue[index++] = el->end_vertexes[j];}
			visited[el->end_vertexes[j]] = 1;
		}
	}
	
	free(queue);
	free(visited);
	return index;
}