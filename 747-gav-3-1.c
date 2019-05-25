#include <stdio.h> 
#include <stdlib.h> 

typedef struct node //описание элемента списка
{ 
    int value; 
    struct node *next; //ссылка на след элемент
} node; 

void printNode(node *l){ 
    while (l){ 
        printf("%d ", l->value); 
        l = l->next; 
    }     
    printf("\n"); 
}  

typedef struct list // описание всего списка
{ 
    int value; 
    struct node * next; 
    struct node * tale; 
} list; 

void init(node * s){ 
    s = (node *)malloc(sizeof(node)); 
} 

void clear(node * a){ 
 
    node * b = a; 
    node * next = b->next;
    while (b->next != NULL){
        free(b); 
        b = b->next;

        *a = *b;
    }     

    a->next = NULL;
    

  
} 
 
int isEmpty(node *a){ 
    if (a == NULL){ 
        return 1;  
    } else { 
        return 0; 
    } 
} 

node * find (node * a, int value){ 
    node * b = a; 
    while (b){ 
      if (b->value == value){ 
          return b; 
      } 
      b = b->next; 
    } 
    return NULL; 
} 


int push_back(node **a, int value) { 
    node *b = (node*) malloc(sizeof(node)); 
    b->value = value; 
    if (*a == NULL){ 
        b->next = NULL; 
    } else { 
        b->next = (*a); 
    } 
    *a = b; 
    return 0;
} 
 
int push_front(node **a, int value) { 
    node * b = (node *) malloc(sizeof(node)); 
    b->value = value; 
    b->next = NULL; 
    if (*a == NULL){
      *a = b;
    } else {
      node * c = *a; 
           while (c->next != NULL){ 
           c = c->next; 
      } 
      c->next = b;
    }
    return 0;
} 

int insertAfter (node * n, int value){
    node * next = n->next;
    node * b = (node *) malloc(sizeof(node)); 
    b->value = value;
    b->next = next;
    n->next = b;
    return 0;
}

int removeDigit (node * a, int value){

    node * b = a; 
    node * last = NULL;
    while (b){ 
      if (b->value == value){ 
          node * next = b->next;          
          
          free(b);
          
          if (last != NULL){
            last->next = next;
          } else {
            *a = *next;
          }
          

                  
          return 0; 
      } 
      last = b;
      b = b->next; 
    } 

    return 1;
}
  

int main() // main

{ 

    int n;
    scanf("%d", &n);

    node* l = NULL; 
    init(l); 

    for (int i = 0; i < n; i++){
      int ni;
      scanf("%d", &ni);
      push_front(&l, ni);
    }

    printNode(l);

    int k;
    for (int i = 0; i < 3; i++){
      scanf("%d", &k);
      node * f = find(l, k);
      if (f == NULL){
        printf("0");
      } else {
        printf("1");
      }
    }

    printf("\n");

    int m;
    scanf("%d", &m);
    push_front(&l, m);
    printNode(l);

    int t;
    scanf("%d", &t);
    push_back(&l, t);
    printNode(l);

    int j, x;
    scanf("%d %d", &j, &x);

    node * b = l;
    for (int i = 1; i < j; i++){
      b = b->next;
    }
    insertAfter(b, x);
    printNode(l);
    
    int z;
    scanf("%d", &z);
    removeDigit(l, z);
    printNode(l);
    clear(l);
	

    return 0; 

} 
