#include <stdio.h>
#include <stdlib.h>

typedef struct node_tree {
	struct node_tree *left;
	struct node_tree *right;
	struct node_tree *parent;
	int value;
}node;

typedef struct bin_tree {
	node *root;
	int size;
}tree;

typedef struct node_ochered {
	struct node_ochered *next;
	node *ptr_node_tree;
}node_ochered;

typedef struct ochered {
	node_ochered *head;
	node_ochered *tail; 
}ochered;

void init_ochered(ochered *och){
	och -> head = NULL;
	och -> tail = NULL;
};

int isEmpty(ochered *och) {
	if (och -> head == NULL && och -> tail == NULL)
		return 1;
	return 0;
}

int push(ochered *och , node* n){
	node_ochered *new_node_ochered = malloc(sizeof(node_ochered));
	new_node_ochered -> ptr_node_tree = n;
	new_node_ochered -> next = NULL;
	if (!(och -> head))
		och -> head = new_node_ochered;
	else och -> tail -> next = new_node_ochered;
	och -> tail = new_node_ochered; 
	return 1;
}

node* pop(ochered *och){

	if (!(och -> head))
		return 0;

	node_ochered *node_ochered_pop;
	node *node_ochered_return = NULL;
	node_ochered_return = och -> head -> ptr_node_tree;
	node_ochered_pop = och -> head;
	och -> head = och -> head -> next;

	if (och -> head == NULL)
		och -> tail = NULL;
	free(node_ochered_pop);
	return node_ochered_return;
}

void clear_ochered(ochered *och) 
{
	node_ochered *tmp , *node_ochered_pop;
	tmp = och -> head;
	do{
		node_ochered_pop = tmp;
		tmp = tmp -> next;
		free(node_ochered_pop); 
 	} while(tmp);
	och -> head = NULL;
	och -> tail = NULL;
}

void init(tree* t){
	t -> root = NULL;
	t -> size = 0;
}

int insert(tree* t, int var){
	node *new_node = malloc(sizeof(node));
	if (new_node == NULL)
		return 2;
	new_node -> value = var;
	new_node -> left = NULL;
	new_node -> right = NULL;
	node *tmp = t -> root;
	node *node_dop = NULL;
	if (!(tmp)){
		new_node -> parent = NULL;
		t -> root = new_node;
		t -> size = 1;
		return 0;
	}

	while(tmp) {
		if ( var < tmp -> value){
			node_dop = tmp;
			tmp = tmp -> left;
		}
	else if(var == tmp -> value)
		return 1;
	else{ 
		node_dop = tmp;
		tmp = tmp -> right;
 		} 
	}
	new_node -> parent = node_dop;
	if ( new_node -> value > new_node -> parent -> value )
		new_node -> parent -> right = new_node;
	else new_node -> parent -> left = new_node;

	(t -> size)++; 
	return 0;
}


typedef struct elem_stack {
	struct elem_stack *next;
	node* ptr_node_tree;
}elem_stack;


typedef struct stack {
	elem_stack *head;
	
}stack;

void init_s(stack *st){
	st -> head = NULL;
};

int isEmpty_s(stack *st) {
	if (st -> head == NULL)
		return 1;
	else return 0;
}

void clear_s(stack *st) {
	elem_stack *tmp , *elem_stack_pop;
	tmp = st -> head;

	do{
		elem_stack_pop = tmp;
		tmp = tmp -> next;
		free(elem_stack_pop);   
	}
	while(tmp != NULL);
	st -> head = NULL;

}

int push_s(stack* st, node* n){

	elem_stack *new_elem_stack = malloc(sizeof(elem_stack));
	new_elem_stack -> ptr_node_tree = n;

	if (!(st -> head))
		new_elem_stack -> next = NULL;
	else new_elem_stack -> next = st -> head;

	st -> head = new_elem_stack; 
	return 0;
}

node* pop_s(stack* st){
	if (!(st -> head))
		return NULL;
	elem_stack *elem_stack_pop;
	node* elem_stack_return = NULL;

	elem_stack_return = st -> head -> ptr_node_tree;

	elem_stack_pop = st -> head;
	if (st -> head -> next == NULL){
		st -> head = NULL;
	}
	else st -> head = st -> head -> next;
	free(elem_stack_pop);
	return elem_stack_return;
}

void print(node* n){
	if ( n == NULL)
		return;

	node* tmp = n;
	node * temp = NULL;
	while(tmp -> right){
		tmp = tmp -> right;
	}
	int max_right = tmp -> value ;

	stack s , *ptr_s;
	ptr_s = &s;
	init_s(ptr_s);
	push_s (ptr_s , n);

	while (ptr_s -> head != NULL ){

		temp = pop_s(ptr_s);

		if (temp -> value == max_right )
			printf("%d\n" , temp -> value );
		else printf("%d " , temp -> value );

		if ( temp -> right != NULL ){
			push_s(ptr_s , temp -> right);
		}

		if ( temp -> left != NULL ){
			push_s(ptr_s , temp -> left);
		}

		
	}

}
int main(void) {

	tree tree;
	init(&tree);
	int num; 
	
	for (int i = 0 ; i < 7 ; i++){
		scanf("%d" , &num);
		insert(&tree , num);
	}
print(tree.root);
return 0;
}	

