#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;

	struct node* next;
}node;

typedef struct list {
	node* head;
}list;

int append(list* l, int data);
int print(list* l);
int destroy(list* l);

int main() {
	// Allocate memory to create the list. 
	list* l = (list*) malloc(sizeof(list));
	if(l == NULL){
		printf("Allocation of list incomplete");
		return 0;
	}
	l->head = NULL; // Set the head of the list to NULL. 
	
	for(int i = 0; i < 10 ; i++){
		append(l, i+1); // Adding items 1 to 10. 
	}
	
	print(l); // Print out all items in the list. 
	
	destroy(l); // free all data. 

	return 0; 
}

int append(list* l, int data){
	
	// Check if list is empty. 
	if(l->head == NULL){
		printf("current is null \n");
		l->head = (node*) malloc(sizeof(node));
		if(l->head == NULL){
			printf("Allocation of head node is incomplete");
			return -1;
		}
		l->head->data = data;
		printf("Successfully added first number %d \n", l->head->data);
		l->head->next = NULL;
		return 0;
	}

	node* current = l->head; // Create a node.
	while(current->next != NULL){
		current = current->next;
		printf("Current is not null \n");
	}
	
	// Allocate memory for the new node. Make sure to check if malloc has been successful. 
	current->next = (node*) malloc(sizeof(node));
	if(current->next == NULL){
		printf("Allocation of node is incomplete");
		return -1;
	}
	
	current->next->data = data; // Append the element
	current->next->next = NULL;
	printf("Successfully added number %d \n", data);
	return 0;
}

int print(list* l){
	node* current = l->head;
	// Printing the current item in the list. 
	while(current != NULL){
		printf("%d -> ", current->data);
		current = current->next; // Then traverse along the list.
	}
	printf("End of list \n");
	return 0; // When the current is null, end the print by returning 0.
}

int destroy(list* l){
	// Release all of the data.
	node* current = l->head;
	while(current != NULL){ // Traverse the list and free each node.
		node* temp = current->next; // Use a temp node as the next node in order to switch to the next one after the current has been freed. 
		free(current);
		printf("Node has been freed\n");
		current = temp;
	}
	free(l); // Free'ing the whole list after all of the nodes were successfully freed
	
	return 0;
}

