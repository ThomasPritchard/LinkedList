// An unrolled LinkedList in C. 
// Utilising cache-hits to speed up overall performance. 

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int numOfElements;
	int elements[4];

	struct node* next;
}node;

typedef struct list {
	node* head;
}list;

int append(list* l, int data);
int print(list* l, int size);
int destroy(list* l);

int main() {
	// Allocate memory to create the list. 
	list* l = (list*) malloc(sizeof(list));
	if(l == NULL){
		printf("Allocation of list incomplete");
		return 0;
	}
	l->head = NULL; // Set the head of the list to NULL. 

	int size = 1000000;
	
	for(int i = 0; i < size ; i++){
		append(l, i+1); // Adding items 1 to 10. 
	}
	
	print(l, size); // Print out all items in the list. 
	
	destroy(l); // free all data. 

	return 0; 
}

int append(list* l, int data){
	
	// Check if list is empty. 
	if(l->head == NULL){ // Only working with the head. 
		l->head = (node*) malloc(sizeof(node));
		if(l->head == NULL){
			printf("Allocation of head node is incomplete");
			return -1;
		}
		l->head->numOfElements = 0; // Initialise our first index. 
		l->head->elements[l->head->numOfElements] = data; // Add the data to the first index in the array. 
		l->head->numOfElements += 1; // Incrementing to the next index. 
		l->head->next = NULL; // Prepare the next node. 
		return 0;
	}

	node* current = l->head; // Setting the current node to the head.

	if(current->numOfElements != 4){ // If array is non-empty within the head. 
		current->elements[current->numOfElements] = data;
		current->numOfElements += 1;
		return 0;
	}

	while(current->next != NULL && current->next->numOfElements == 4){ //If node array is full, traverse to the next node.  
		current = current->next;
	}

	if(current->next != NULL && current->next->numOfElements != 4){
		current->next->elements[current->next->numOfElements] = data; // Append the element
		current->next->numOfElements += 1;
		return 0;
	}
	
	// Allocate memory for the new node. Make sure to check if malloc has been successful. 
	current->next = (node*) malloc(sizeof(node));
	if(current->next == NULL){
		printf("Allocation of node is incomplete");
		return -1;
	}
	current->next->numOfElements = 0;
	current->next->elements[current->next->numOfElements] = data; // Set the first element within the new node. 
	current->next->numOfElements += 1;
	current->next->next = NULL;

	return 0;
}

int print(list* l, int size){
	node* current = l->head;
	// Printing the current item in the list. 
	while(current != NULL && size > 0){
		for(int i = 0; i < 4; i++){
			if(size > 0) printf("%d -> ", current->elements[i]);
			size--;
		}
		current = current->next; // Then traverse along the list.
	}
	printf("End of list. \n");
	return 0; // When the current is null, end the print by returning 0.
}

int destroy(list* l){
	// Release all of the data.
	node* current = l->head;
	while(current != NULL){ // Traverse the list and free each node.
		node* temp = current->next; // Use a temp node as the next node in order to switch to the next one after the current has been freed. 
		free(current);
		current = temp;
	}
	free(l); // Free'ing the whole list after all of the nodes were successfully freed
	
	return 0;
}