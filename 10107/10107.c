#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// use linked list to implement
typedef struct _node {
	long data;
	struct _node* next;
} Node;

typedef struct _list {
	Node* head;
	Node* tail;
} Linked;

long median(Linked *);
void add_node(Linked *, long);
void initial_list(Linked *);
void delete_list(Linked *);
int long_compare(const void *, const void *);
void print_list(Linked *list);

int count;
int main(int argc, char *argv[]){
	char c;
	count = 0;
	FILE *fp = fopen("10107_test.txt", "r");; 
	if(fp == NULL){
		printf("read file error\n");
		exit(1);
	}
	Linked linked_list;
	initial_list(&linked_list);
	while((c = fgetc(fp)) != EOF){
		if( (c != ' ') && ((c-'0') > 0) ) {
			long value = (long)(c - '0');
			printf("%li ", value);
			add_node(&linked_list, value);
			count++;
			//print_list(&linked_list);
			printf("%li ", median(&linked_list));
		}
	}
	printf("\n");
	//print_list(&linked_list);
	delete_list(&linked_list);
	return 0;
}

// find the median from the list:
// traverse the list
long median(Linked *list){
	Node *node = list->head;
	Node *prev = list->head;
	int i;
	long temp;
	if( (count % 2) == 1 ){
		i = 0;
		while( i < count/2 ){
			//temp = *(node->data);
			//prev = node;
			node = node->next;		
			i++;
		}
		temp = node->data;
		return temp;
	} else {
	// even numbers of nodes
		i = 0;
		long temp2;
		while(i < count/2){
			prev = node;
			node = node->next;
			i++;
		}
		temp = node->data;
		temp2 = prev->data;
		return (temp+temp2)/2;
	}	
	//free(node);
	//free(prev);
}

void initial_list(Linked *list){
	list->head = NULL;
	list->tail = NULL;
}

// add new data to the "tail" of the list
void add_node(Linked *list, long value){	
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = value;
	//node->next = NULL;
	if(list->head == NULL){
	// initialize the list to point to the correct node
		list->tail = list->head = node;
		node->next = NULL;
	} else if( node->data < list->head->data ){
		node->next = list->head;
		list->head = node;
	} else if( node->data > list->tail->data ){
		list->tail->next = node;
		list->tail = node;
		node->next = NULL;
	}
	else {
		/* check where to insert the new node into the list:
		   if bigger than the tail node, add to the tail;
		   if smaller than the head node, add to the head.
		*/
		// traverse the list until find out the value of a node that is bigger than the input
		Node *temp = list->head;
		Node *prev;
		while( (temp != NULL) && ( temp->data <= node->data ) ){
			if( temp == list->tail){
				break;
			}	
			// keep track of the previous one
			prev = temp;
			temp = temp->next;
		}
		// if the node has to be added to the tail of the list
		prev->next = node;
		node->next = temp;
		//prev->next = node;
	}
}

// delete all the nodes and the list
void delete_list(Linked *list){
	Node *to_delete = list->head;
	Node *temp;
	while(to_delete != NULL){
		temp = to_delete->next;
		to_delete = NULL;
		to_delete = temp;
	}
	list->head = NULL;
	list->tail = NULL;
}

int long_compare(const void *a, const void *b){
	const int *x = (const int *)a;
	const int *y = (const int *)b;
	return *x - *y;
	// return negative integer if b>a
}

// function to print all the long values of the list
void print_list(Linked *list){
	printf("Output: ");
	Node *node = list->head;
	//node->next = NULL;	
	while(node != NULL){
		//printf("%li ", *(node->data));
		if(node == list->tail){
			printf("%li ", node->data );
			break;
		}
		printf("%li ", node->data );
		node = node->next;
	}
	printf("\n");
}


