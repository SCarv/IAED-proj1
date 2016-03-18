#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(A,B) (A > B ? A : B)
#define MIN(A,B) (A < B ? A : B) 

/* A person on this network. Members set up for the algorithm. */
struct Person {

	unsigned low;
	unsigned depth;
	struct Person* parent;
	struct Person_node* friend_list;
};


/* Abstractly, relations are a linked list. */
struct Person_node {

	struct Person* person;
	struct Person_node* next;
};


struct Person* new_person(void) 
{
	return calloc(sizeof(struct Person_node), 1); 
}


struct Person_node* push_relation(struct Person* this, struct Person* that)
{
	struct Person_node* new_node = malloc(sizeof(struct Person_node));

	new_node -> person = that; 
	new_node -> next = that -> friend_list;
	this -> friend_list = new_node;

	return new_node;    
}


void new_relation(struct Person* this, struct Person* that)
{
	push_relation(this, that);
	push_relation(that, this);
}

/* Get all lines given in the input until we read a line that isn't two unsigned decimals. 
 * These decimals represent a 'relation' between two all_people. */
void get_relations(struct Person** all_people) 
{
	unsigned first_id;
	unsigned second_id;

	while (scanf(" %u %u", &first_id, &second_id) == 2)
		new_relation (
			all_people[first_id], 
			all_people[second_id]
		);	
}


unsigned count_cut_vertices_tarjan(struct Person* parent, int current_depth, int* min, int* max)
{
	struct Person* current_person; 
	unsigned lower_fundamentals;
	unsigned children_count		 = 0;
	bool maybe_fundamental 		 = false;
	struct Person_node* current_node = parent->friend_list;

	person->depth = current_depth; 
	person->low   = current_depth;

	while (current_node) {

		current_person = current_node->person;
		
		if (! current_person->depth) { /* this person hasn't been visited before */

			current_person->parent = parent;	
			lower_fundamentals = 
			count_cut_vertices_tarjan(current_person, current_depth + 1, min, max);

			if (current_person->low >= current_depth)
				maybe_fundamental = true;

			parent->low = MIN(parent->low, current_person->depth);
			  
		}

		else if (parent->parent != current_person)
			parent->low = MIN(parent->low, current_person->depth);


		current_node = current_node -> next;	
	}

	if (
		(current_person->parent && maybe_fundamental ||
		!(current_person->parent) && child_count > 1)

	)/*then*/{
		
		*max = MAX(*max, parent->depth;
		*min = MIN(*min, parent->depth);
		return 1 + lower_fundamentals; 
	}

	else return lower_fundamentals; 
}


int main()
{
/* Read the first line of input given, which should be how many all_people
exist and how many 'relations' exist between these all_people. */

	struct Person** all_people;
	unsigned all_people_count;
	unsigned fundamental_people_count;
	int min = -1;
	int max = -1; 

	scanf("%u %*u", &all_people_count);
	all_people = malloc(sizeof(struct Person*) * all_people_count);

	while (all_people_count--)
		all_people[all_people_count] = new_person();

	get_relations(all_people);

	fundamental_people_count = count_cut_vertices_tarjan(all_people, 1, &min, &max);

	printf("%u\n%d %d\n", fundamental_people_count, min, max);

	return EXIT_SUCCESS;
}
