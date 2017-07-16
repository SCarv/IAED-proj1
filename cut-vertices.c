/*\ count_cut_vertices_tarjan.c
 * 
 * This algorithm was written by students of INSTITUTO SUPERIOR TÉCNICO, in Portugal, on 19/03/2016,
 * for the Análise e Síntese de Algoritmos class.
 *
 * Authors:
 * Sérgio Carvalho: ist181513
 * Daniel Chaves  : ist181651
 * 
 * This program was written to solve the number of 
 * However this problem is equivalent to counting the 'cut vertices'
 * so this problem is given as a generalization.
 * 
 * The program intends to find all vertices with a given
 * The breadth of this program is in the function with the same name as the program.
 *
 * The input should be any number of lines containing solely two integers
 * separated by spaces. Example:
 * Intended compilation command: gcc -ansi -pedantic -Wall -O3
\*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#

#define MAX(A,B) (A > B ? A : B)
#define MIN(A,B) (A < B ? A : B) 


/*** PART 1: STRUCTS. None of them are typedefd. ***/

/*\
 * struct Vertex: A vertex on this graph.
 * The members are set up for the main algorithm to be executed.
 *
 * depth   : the finding time for this vertex. Same as the number of recursive
 * 	     calls necessary for the algorithm to reach this vertex. 
 * low     : The lowest possible 'depth' value for this vertex.
 * parent  : the node through which we got to this vertex.
 * adj_head: the complete adjacency list for this vertex. 
\*/

struct Vertex {

	unsigned depth;
	unsigned low;
	struct Vertex* parent;
	struct Adj_list* adj_head;
};


/*\
 * struct Adj_list: An adjacency list for a vertex. 
 * Only makes sense within a vertex.
 * 
 * vertex_index : this vertex's index in the vector which has all the existing vertices.
 * next		: the next node (also a (smaller) adjacency list) on this vertex's
 * 		  adjacency list, which should have a different 'vertex_index'.
\*/
 
struct Adj_list {

	unsigned vertex_index;
	struct Adj_list* next;
};

/**************************** PART 2: FUNCTIONS ******************************/

/* function new_vertex: returns a new vertex. 
 * note: calloc zeroes all struct members, which is the correct value for all. */
struct Vertex* new_vertex(void) 
{
	return calloc(1, sizeof(struct Vertex));
}

/* function new_adjacency: adds an edge from 'this' to 'that'. */
void new_adjacency(struct Vertex* all_vertices[], unsigned this_index, unsigned that_index)
{
	struct Vertex* this = all_vertices[this_index];

	struct Adj_list* new_adj_list = malloc(sizeof(struct Adj_list));

	new_adj_list->vertex_index     = that_index;
	new_adj_list->next 	       = this->adj_head;

	this->adj_head = new_adj_list;
}


/* Get all lines given in the input until we read a line that isn't two unsigned decimals. 
 * These decimals represent an edge that connects two vertices. 
 */
void get_edges(struct Vertex* all_vertices[]) 
{
	unsigned this_index;
	unsigned that_index;

	while (scanf("%u %u ", &this_index, &that_index) == 2) {

		/*This graph is bidirectional: make a new adjacency for both vertices*/

		new_adjacency(all_vertices, this_index, that_index);
		new_adjacency(all_vertices, that_index, this_index);
	}
}


void count_cut_vertices_tarjan(struct Vertex* all_vertices[], unsigned top_index, unsigned depth, unsigned result[])
{
	if (!all_vertices || !top_index || !depth || !result) 
		fputs("UNEXPECTED NULL VALUE!", stderr), exit(1);

	struct Adj_list* adjacency;
	unsigned adjacent_index;
	struct Vertex* adjacent;
	
	struct Vertex* top = all_vertices[top_index];

	unsigned* count = result + 0;
	unsigned* min   = result + 1;
	unsigned* max   = result + 2;	

	unsigned children_count = 0;

	bool maybe_fundamental = false; 

	top->depth  = depth; 
	top->low    = depth;

	adjacency = top->adj_head;

	while (adjacency) {

		adjacent_index 	= adjacency->vertex_index;
		adjacent 	= all_vertices[adjacent_index];
	
		if (!adjacent->depth) { /*if this vertex hasn't been visited before */

			++children_count;

			adjacent->parent = top;

			count_cut_vertices_tarjan(all_vertices, adjacent_index, depth+1, result);

			if (adjacent->low >= top->depth)
				maybe_fundamental = true;

			top->low = MIN(top->low, adjacent->low);
			  
		}

		else if (top->parent != adjacent)
			top->low = MIN(top->low, adjacent->depth);

		adjacency = adjacency->next;
	}

	if ((top->parent && maybe_fundamental) ||
		(!top->parent && children_count > 1)) {
	
			/*then we have found a cut vertex!*/
		
		*count += 1;
		*min    = MIN(*min, top_index); 
		*max    = MAX(*max, top_index);
	}
}


int main()
{
/*Read the first line of input given, which should be how many all_vertices
  exist and how many 'relations' exist between these all_vertices.
  However we only need the first one.*/

	/*\ Declarations:
	 *  	all_vertices:
	\*/


	struct Vertex**  all_vertices;
	unsigned 	 vertex_count;
	unsigned 	 grandfather_index;

	unsigned 	 output[3];

	scanf("%u %*u ", &vertex_count);

	output[0] = 0; 
	output[1] = -1; 
	output[2] = 0;


	/* XXX: Make 'all_vertices' a one-indexed vector! 
		The input file should id vertices with positive integers only.
		Hence we make it so 'all_vertices''s indexes agree with this.
		Begins at 
		Ends at all all_vertices[
	*/

	/* Never use index 0 of 'all_vertices'. Allocate two extra positions to cap off
	   the beginning and the end with a NULL. */ 
	all_vertices = malloc(sizeof(struct Vertex) * (vertex_count+2));

	/* Cap off 'all_vertices' at the beginning with a NULL. */
	all_vertices[0] = NULL;
	all_vertices[vertex_count+1] = NULL;

	/* Fill all 'all_vertices''s indexes with the required amount of vertices.*/
	while (vertex_count) 
		all_vertices[vertex_count--] = new_vertex();


	/* Choose a random index to start the cut vertex search algorithm.
	   Have blind faith that this will help with the algorithm's performance. 
	   Note: + 1 to not choose the zeroth index; - 1 to not go over 'all_vertices' size */
	srand(time(NULL));
	/*grandfather_index = (rand() % (vertex_count - 1)) + 1;*/
	grandfather_index = 1;
	get_edges(all_vertices);

	count_cut_vertices_tarjan(all_vertices, grandfather_index, 1, output);

	if (output[0])
		printf("%u\n%d %d\n", output[0], output[1], output[2]);
	else 
		puts("0\n-1 -1");

	return EXIT_SUCCESS;
}	
