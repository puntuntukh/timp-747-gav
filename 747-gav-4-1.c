#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
    struct node *par;
}node;

typedef struct
{
    node *head;
    int size;
}tree;


//структура для очереди
typedef struct node_queue
{
	node *ptr_node_tree;
	struct node_queue *next;
}node_queue;

typedef struct queue
{
	node_queue *head;
	node_queue *tail;
}queue;

void init_queue(queue *q)
{
	q->head = NULL;
	q->tail = NULL;
};

int push(queue *q, node *n)
{
	node_queue *new_node_queue = malloc(sizeof(node_queue));
	new_node_queue->ptr_node_tree = n;
	new_node_queue->next = NULL;
	if (q->head)
		q->tail->next = new_node_queue;	
	else 
		q->head = new_node_queue;
	q->tail = new_node_queue; 
	return 0;
}

node *pop(queue *q)
{
	if (q->head)
	{
		node_queue *node_queue_pop;
		node *tmp = NULL;
		tmp = q->head->ptr_node_tree;
		node_queue_pop = q->head;
		q->head = q->head->next;
		if (q->head == NULL)
			q->tail = NULL;
		free(node_queue_pop);
		return tmp;
	}
	else 
		return NULL;
}
void clear_queue(queue  *q)
{
	node_queue *tmp, *nq;
	tmp = q->head;
	do
	{
		nq = tmp;
		tmp = tmp->next;
		free(nq);   
	}
	while(tmp);
	q->head = NULL;
	q->tail = NULL;
}

//реализация бинарного дерева поиска

//инициализация
void init(tree *t)
{
	t->head = NULL;
	t->size = 0;
}

//поиск элемента по значению

int find(tree *t, int value, node **n)
{
	node *tmp = t->head;
	while (tmp)
	{
		if (value < tmp->value)
			tmp = tmp->left;
		else if (value > tmp->value)
			tmp = tmp->right;
		else
		{
			*n = tmp;
			return 0;
		}
	}
	*n = tmp;
	return 1;
}

//вставка
int insert(tree *t, int value)
{
	node *tmp = malloc(sizeof(node));
	if (tmp == NULL)
		return 2;
	node *p = t->head;
	node *q = NULL;
	if (p)
	{
		while(p)
		{
			if (value < p->value)
			{
				q = p;
				p = p->left;
			}
			else if (value > p->value)
			{
				q = p;
				p = p->right;
			}
			else
				return 1; 
		}
		tmp->value = value;
		tmp->left = tmp->right = NULL;
		tmp->par = q;
		if (tmp->value > q->value)
			q->right = tmp;
		else 
			q->left = tmp;
		t->size++;
		return 0;
	}
	else
	{
		t->head = tmp;
		t->head->value = value;
		t->head->par = NULL;
		t->head->left = t->head->right = NULL;
		t->size++;
		return 0;
	}
}

//удаление элемента
int removeT(tree *t, int value)
{
	node *tmp = t->head;
	while (tmp->value != value)
	{
		if (value < tmp->value)
			tmp = tmp->left;
		else if (value > tmp->value)
			tmp = tmp->right;
	}
	if (tmp == NULL)
		return 1;
	if (tmp->left == NULL && tmp->right == NULL)
	{
		if (tmp->par->value > value)
			tmp->par->left = NULL;
		else
			tmp->par->right = NULL;
		free(tmp);
	}
	else if (tmp->left != NULL && tmp->right == NULL)
	{
		tmp->left->par = tmp->par;
		if (tmp->par->value > value)
			tmp->par->left = tmp->left;
		else
			tmp->par->right = tmp->left;
		free(tmp);
	}
	else if (tmp->left == NULL && tmp->right != NULL)
	{
		tmp->right->par = tmp->par;
		if (tmp->par->value > value)
			tmp->par->left = tmp->right;
		else
			tmp->par->right = tmp->right;
		free(tmp);
	}
	else if (tmp->left != NULL && tmp->right != NULL)
	{
		node *p = tmp->right;
		if (p->left == NULL)
		{
			tmp->value = p->value;
			if (p->right == NULL)
			{
				tmp->right = NULL;
				free(tmp->right);
			}
			else
			{
				tmp->right = tmp->right->right;
				p->right->par = tmp;
				free(p);
			}		
		}	
		else
		{
			while(p->left)
				p = p->left;
			tmp->value = p->value;
			if (p->right)
			{
				tmp->value = p->value;
				p->value = p->right->value;
				tmp->right = NULL;
				free(p->right);
			}
			else 
			{
				tmp->value = p->value;
				p->par->left = NULL;
				free(p);
			}
		}
	}
	t->size--;
	return 0;
}

//удаление минимального элемента
int removeMin(node *n, tree *t)
{
	if (t->size == 1)
	{
		t->head = NULL;
		t->size = 0;
		free(t->head);
		return 0;
	}
	while(n->left)
		n = n->left;
	if (n->right)
	{
		n->right->par = n->par;
		if (n == t->head)
			t->head = n->right;
		else
			n->par->left = n->right;
	}
	else 
	{
		n->par->left = NULL;
	}
	int m = n->value;
	free(n);
	t->size--;
	return m;
}

//очистка
void clear(tree *t)
{
	while (t->head)
		removeMin(t->head, t);
}

//правое вращения дерева
int rotateRight(node **n)
{
	node *tmp = (*n)->left;
	if (tmp == NULL)
		return 1;
	(*n)->left = tmp->right;
	tmp->right = (*n);
	tmp->par = (*n)->par;
	(*n)->par = tmp;
	(*n) = tmp;
	return 0;
}

//левое вращение
int rotateLeft(node **n)
{
	node *tmp = (*n)->right;
	if (tmp == NULL)
		return 1;
	(*n)->right = tmp->left;
	tmp->left = (*n);
	tmp->par = (*n)->par;
	(*n)->par = tmp;
	(*n) = tmp;
	return 0;
}

//вывод дерева из-под дерева
void print(node *n)
{
	if (n)
	{
		queue queue1, queue2;
		queue *ptr_queue1 = &queue1;
		queue *ptr_queue2 = &queue2;
		init_queue(ptr_queue1);
		init_queue(ptr_queue2);
		node *tmp = NULL;
		node_queue *q = NULL;
		int c = 0, val = n->value, j = 0;
		node *l = n->left;
		node *r = n->right;
		push(ptr_queue1, n);
		while(1)
		{
			while(ptr_queue1->head)
			{
				tmp = pop(ptr_queue1);
				if(ptr_queue1->head == NULL)
				{
					if (tmp->value == val && c == 1)
						printf("_\n");
					else
						printf("%d\n", tmp->value);
				}
				else if(tmp->value == val && c == 1)
					printf("_ ");
				else
					printf("%d ", tmp->value);
				if (tmp->left)
					push(ptr_queue2, tmp->left);
				else 
					push(ptr_queue2, n);
				if (tmp->right)
					push(ptr_queue2, tmp->right);
				else 
					push(ptr_queue2, n);
			}
			n->left = n->right = NULL;
			c = 1;
			q = ptr_queue2->head;
			while(ptr_queue2->head->ptr_node_tree->value == val)
			{
				ptr_queue2->head = ptr_queue2->head->next;
				if(ptr_queue2->head->next == NULL)
					if(ptr_queue2->head->ptr_node_tree->value == val)
					{
						j = 1;
						n->left = l;
						n->right = r;
						clear_queue(ptr_queue2);
						break;
					}
			}
			ptr_queue2->head = q;
			if(j == 1) 
				break;
			ptr_queue1->head = ptr_queue2->head;
			ptr_queue1->tail = ptr_queue2->tail;
			ptr_queue2->head = NULL;
			ptr_queue2->tail = NULL;	
		}	
	}
	else
		printf("-\n");
}

//вывод
void printTree(tree *t)
{
	print(t->head);
}

int main()
{
	unsigned int i;
	int a;
	tree t;
	init(&t);
	for (i = 0; i < 4; i++)
	{
		scanf("%d", &a);
		insert(&t, a);
	}
	printTree(&t);

	for (i = 0; i < 3; i++)
	{
		scanf("%d", &a);
		insert(&t, a);
	}
	printTree(&t);

	for (int i = 0; i < 2; i++) //5ое и 6ое задание в это цикле
	{
		scanf("%d", &a);
		node *n = NULL;
		int j = find(&t, a, &n);
		if (j == 0)
		{
			if (n->par)
				printf("%d ", n->par->value);
			else printf("_ ");
			if (n->left)
				printf("%d ", n->left->value);
			else printf("_ ");
			if (n->right)
				printf("%d\n", n->right->value);
			else printf("_\n");
		}
		else printf("-\n");
	}
	
	scanf("%d", &a); 
	removeT(&t, a);
	printTree(&t);


	while(rotateLeft(&t.head) == 0){;}
	printTree(&t);

	while(rotateRight(&t.head) == 0){;}
	printTree(&t);

	printf("%d\n", t.size);

	clear(&t);
	printTree(&t);
    return 0;
}

