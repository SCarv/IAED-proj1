struct Person {

	bool visited;
	unsigned low;
	unsigned depth;
	unsigned children_count;
	struct Relation* relations_head;
};

struct Relation {

	struct Person* friend;
	struct Person* next_friend;
};

int main()
{

}
