/**********************************************************************
Program: Problem 673 on UVA Online Judge
Author: Yorgo A. Kennos
Date: 2/27/2019
Time spent: 1 hour
Purpose: The purpose of this program is to keep track of delimiters by pushing any left delimiters onto the stack,
		 when a right delimiter character is read it compares it to the top of the stack. If they are of the same type
		 then the item is popped off. Will return Yes if string is empty or delimiters match up, will return No otherwise.
		 This is a useful program to practicing an implementation of Stacks as well as testing whether a mathematic expression
		 per say has appropriate () [] {} etc.
***********************************************************************/


#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node {
	char data;
	char top;
	Node* next;
};


/*function prototypes*/
void push(Node**, char);
void pop(Node**);
char top(Node**);
void print(Node*);
void destroy(Node**);
int isempty(Node**);
void delimiter_check(int);
void clear_keyboard_buffer();


int main(int argc, char* argv[]) {
	int n;

	scanf("%d", &n);
	clear_keyboard_buffer();

	delimiter_check(n);

	return 0;

}
void delimiter_check(int n) {

	Node* head = NULL;
	char c;
	int i;


	for (i = 0; i < n; i++) {
		Node* head = NULL;
		scanf("%c", &c);

		if (c == '\n') {
			push(&head, c);
		}

		while (c != '\n') {

			/*if character is a left delimiter*/
			if ( c == '{' || c == '[' || c == '(' ) {

				/*push onto the stack*/

				/*printf("Pushed onto the stack\n");*/
				push(&head, c);
				/*printf("Current Top: %c\n", top(&head));*/
			}

			/*if character is a right delimiter and the top of stack is a left
			  delimiter of the same type call pop*/
			if (c == '}' || c == ']' || c == ')') {

				if (c == '}' && top(&head) == '{') {
					/*printf("Popping stack\n");*/
					pop(&head);
				}
				else if (c == ']' && top(&head) == '[') {
					/*printf("Popping stack\n");*/
					pop(&head);
				}
				else if (c == '>' && top(&head) == '<') {
					/*printf("Popping stack\n");*/
					pop(&head);
				}
				else if (c == ')' && top(&head) == '(') {
					/*printf("Popping stack\n");*/
					pop(&head);
				}
				
				else {
					push(&head, c);
				}
				

			}
			scanf("%c", &c);

		}
		
		if (isempty(&head)) {
			printf("Yes\n");
		}
		
		else if (isempty(&head) == 0 && top(&head) == '\n') {
			printf("Yes\n");
		}
		
		else {
			printf("No\n");
		}
	}

	destroy(&head);
}

void push(Node** pHead, char item) {
	Node* temp;

	/*when the linked list is empty*/
	if (*pHead == NULL) {
		*pHead = (Node*)malloc(sizeof(Node));
		(*pHead)->data = item;
		(*pHead)->next = NULL;
	}

	/*when not empty*/
	else {
		temp = *pHead;

		/*traverse the linked list until we get to the last node that points to NULL*/
		while (temp->next != NULL) {
			temp = temp->next;
		}

		/*now that we are at the final Node*/
		temp->next = (Node*)malloc(sizeof(Node));
		temp->next->data = item;
		temp->next->next = NULL;

	}

}
/*will remove the last node in the linked list that points to NULL or return nothing if the list is empty*/
void pop(Node** pHead) {
	Node* temp;

	/*if the linked list is empty cannot pop*/
	if (*pHead == NULL) {
		return;
	}

	/*if the linked list only has one node*/
	if ((*pHead)->next == NULL) {
		temp = *pHead;
		free(temp);
		(*pHead)->next = NULL;
		*pHead = NULL;
		return;
	}


	/*when the linked list is not empty*/
	else {
		temp = *pHead;

		/*travel to the second to last node*/
		while (temp->next->next != NULL) {
			temp = temp->next;
		}

		/*remove final node and set the previous node->next to NULL*/
		free(temp->next);
		temp->next = NULL;
	}

}

/*returns the end of the linked list (The most recently pushed item)*/
char top(Node** pHead) {

	Node* temp;

	/*if the linked list is empty them return ~*/
	if (*pHead == NULL) {
		return '~';
	}

	else {
		temp = *pHead;

		while (temp->next != NULL) {
			temp = temp->next;
		}

		return (temp->data);

	}

}
/*prints out the linked list starting from the first node that Head points to*/
void print(Node* head) {

	if (head == NULL) {
		printf("Stack is Empty!\n");
		return;
	}

	while (head != NULL) {
		printf("[  %c  ]\n", head->data);
		head = head->next;
	}

}

/*destroys and frees every node in the linked list*/
void destroy(Node** pHead) {
	Node* temp;

	/*if linked list has NO nodes*/
	if (*pHead == NULL) {
		return;
	}

	/*if linked list has more than one node*/
	if ((*pHead)->next != NULL) {
		while (*pHead != NULL) {
			temp = *pHead;
			*pHead = (*pHead)->next;
			free(temp);
		}
	}

	/*if linked list only has 1 node*/
	if ((*pHead)->next == NULL) {
		*pHead = NULL;
	}

}

int isempty(Node** pHead) {
	if (*pHead == NULL) {
		return 1;
	}
	else {
		return 0;
	}


}

void clear_keyboard_buffer() {
	char ch;

	scanf("%c", &ch);

	while (ch != '\n') {
		scanf("%c", &ch);
	}
}
