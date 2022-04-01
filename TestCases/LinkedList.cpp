#include <iostream>



using namespace std;


struct Node /* Node has an integer data and a pointer to the next node*/
{
	int data;
	struct Node *next;
};


//We can push a new node onto the front of the list by making the head the next node
void push(struct Node** head, int node_data){
	struct Node* newNode = new Node;

	newNode->data = node_data;
	newNode->next = (*head);
	(*head) = newNode;
}


//We can insert a node after a certain previous node by switching next pointers
void insertAfter(struct Node* prev_node, int node_data){
	if (prev_node == NULL){
		cout << "Previous node cannot be NULL" << endl;
		return;
	}

	struct Node* newNode = new Node;
	newNode->data = node_data;
	newNode->next = prev_node->next;

	prev_node->next = newNode;
}


//We can add a node to the end once we find the NULL pointer 
void append(struct Node** head, int node_data){

	struct Node* newNode = new Node;
	struct Node *last = *head;
	newNode->data = node_data;
	newNode->next = NULL;

	if (*head == NULL){
		*head = newNode;
		return;
	}

	while (last->next != NULL){
		last = last->next;
	}

	last->next = newNode;
	return;
}


void DisplayList(struct Node *node){		// Display the contents of the linked list
	while (node != NULL){
		cout << node->data << "-->";
		node = node->next;
	}

	if (node == NULL){
		cout << "Empty List" << endl;
	}
}



int main(){


	struct Node* head = NULL;

	append(&head, 10);
	push(&head, 20);

	push(&head,30);
	append(&head, 40);

	insertAfter(head->next, 50);

	cout << "Final List: " << endl;
	DisplayList(head);

	return 0;
}