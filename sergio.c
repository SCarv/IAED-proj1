#define → -> /* B R A V O */ 

/* A person on this network. Members set up for the algorithm. */
struct Person {

	bool visited;
	unsigned low;
	unsigned depth;
	unsigned children_count;
	struct Person_node* head_friend;
};

/* Abstractly, relations are a linked list. */
struct Person_node {

	struct Person* person;
	struct Person_node* next_person;
};

int main()
{
 
/* Read the first line of input given, which should be how many people
exist and how many 'relations' exist between these people. */

	unsigned people_count;
	unsigned relation_count;
	struct Person* people;

	scanf("%u %u", &people_count, &relation_count);
	people = calloc(sizeof(struct Person) * people_count);

	get_relations(input, BUFFER_SIZE);
	
}

/* Get all lines given in the input until we read a line that isn't two unsigned decimals. 
 * These decimals represent a 'relation' between two people. */
void get_relations(struct Person* people) 
{
	unsigned first_id;
	unsigned second_id;

	while (scanf(" %u %u", &first_id, &second_id) == 2)
		new_relation(first_id, second_id);
}

void new_relation(struct Person* all_people, unsigned first_id, unsigned second_id)
{
	struct Person* first_person = people[first_id] ?: new_person(first_id);
	struct Person* second_person = people[second_id] ?: new_person(second_id);
	
	add_friend(first_person, second_person);
	add_friend(second_person, first_person);

	all_people[first_id] = first_person;
	all_people[second_id] = second_person;	
}

struct Person_node* push_friend(struct Person* this, struct Person* that)
{
	struct Person_node* new_node = malloc(sizeof(struct Person));

	new_node → person = that; 
	new_node → next_person = that → head_friend;

	this → head_friend = that;

	return new_node;    
}


struct Person* new_person() { return calloc(sizeof(struct Person)); }

void find_cut_verices_tarjan()
{

}
