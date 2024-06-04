//Testing pleas

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct Node {
int data;
struct Node* next;
struct Node* prev;
};

int length;
struct Node* head;

struct Node* create_node(int x){
	
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	assert(new_node != NULL);
	new_node->data = x;
	new_node->prev = NULL;
	new_node->next = NULL;
	length++;
	return new_node;
}


void insert_at_head(int x){
struct Node* new_node = create_node(x);

	if (head == NULL) {
	head = new_node;
	}
	else {
	head->prev = new_node;
	new_node->next = head;
	head = new_node;
	}
}

void print_forward(){

if(head == NULL){
printf("List was empty, can't print print_forward\n");
return;
}

struct Node* temp;
temp = head; 
printf("Printing forwards values are = ");
while(temp != NULL){
printf("%d, ", temp->data);
temp = temp->next;
}
printf("\n");
}

void print_reverse(){

	if(head == NULL){
	printf("List was empty can't print_reverse \n");
	return;
	}

	struct Node* temp = head; 
	while(temp->next != NULL){
	temp = temp->next;
	}

	printf("Printing backwards values are = ");
	while(temp != NULL){
	printf("%d, ", temp->data);
	temp = temp->prev; 
	}
	printf("\n");
}

	void insert_at_tail(int x){
	struct Node* new_node = create_node(x);
	struct Node* temp = head;
	if (head == NULL){
	head = new_node;
	} 
	else {
	while(temp->next != NULL) {
	temp = temp->next;
	}
	temp->next = new_node;
	new_node->prev = temp;
	}

	}

	void destroy_node(int index){
	struct Node* temp = head; 

	if(head == NULL){
	printf("List was empty, can't destroy_node \n");
	return;
	}
		if (length < index) {
		printf("Index out of bounds \n");
		return;
		}
		//-1 because we start at head
		for(int i = 0 ; i < index-1 ; i++){
		temp = temp->next;

		}
		

		// remove the head
		if (temp->prev == NULL) {
		head = temp->next;
		temp->next->prev = NULL;
		free(temp);
		return;
		}

		//remove the tail
		if (temp->next == NULL) {
		temp->prev->next = NULL;
		free(temp);
		return;
		}

		// any other node
		temp->prev->next=temp->next;
		temp->next->prev = temp->prev;
		
		free(temp);
	}

	void destroy_specific_value(int x){
	struct Node* temp = head;

	while((temp != NULL)){

		if (temp->data == x){

		// remove the head
		if (temp->prev == NULL) {
		head = temp->next;
		temp->next->prev = NULL;
		free(temp);
		return;
		}

		//remove the tail
		if (temp->next == NULL) {
		temp->prev->next = NULL;
		free(temp);
		return;
		}

		// any other node
		temp->prev->next=temp->next;
		temp->next->prev = temp->prev;
		
		free(temp);
		return;
			}
		temp = temp->next;
	
		}
		printf("The value didn't exist in the linked list \n");
	
	}

	int get_length(struct Node* temp){

		int result = 0; 
		if (head == NULL){
		return result;
		}
		result++;
		while(temp != NULL){
		result++;
		temp = temp->next;
		}
		return result;

	}



int main(){
	head = NULL;
	length = 0;
	printf(" Testing please \n");

	for (int i = 0 ; i < 10 ; i++) {
	insert_at_head(i);
	}
	print_forward();
	//insert_at_tail(-1);
	//destroy_node(0);
	//destroy_node(9);
	//destroy_node(0);
	destroy_specific_value(0);
	//destroy_specific_value(9);
	printf("The length of the linked list is %d \n ", get_length(head) );
	print_forward();
	//print_reverse();

	exit(EXIT_SUCCESS);
}