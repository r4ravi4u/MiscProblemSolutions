#include "Functions.h"

void linkedlist()
{
	struct Node1 *head = NULL, *head1 = NULL;
	int i = 0, a[arrSize] = { 1, -2, 3, 4, 2, 102, 7, 8, 9, 10 };

	int b[arrSize] = { 0, -1, 101, 6, 2, 46, 2, 8, 10, 11 };

	int k = 3;

	for (i = 0; i < arrSize; i++)
	{
		insertList(&head, a[i]);
		insertList(&head1, b[i]);
	}
		

	printList(head);
	printList(head1);

	struct Node1 *head3 = findIntersection(head, head1);

/*	for (i = 0; i < arrSize; i++)
	{
		printf("Enter a no. to be inserted : ");
		scanf_s("%d", &a[i]);
		insertList(&head, a[i]);
	}

	printf("\n\n Enter a number to delete : ");
	scanf_s("%d", &i);*/

//	deleteList(&head, i);

//	reverseList(&head);

//	printf("\n\n After Reverse : \n\n");

//	head = reverse(head, k);

//	printList(head);

	return;

}

bool visited_node(struct Node1 visited[], int N, struct Node1 *node)
{
	int i = 0;
	while (visited[i].next && N < 300)
	{
		if (visited[i++].next == node)
			return true;
	}
	return false;
}

void removeTheLoop(Node1 *node)
{
	if (!node)
		return;

	struct Node1 visited[300] = { { INT_MAX, NULL } };
	int i = 0;
	visited[i].data = node->data;
	visited[i].next = node;
	while (node->next)
	{
		if (!visited_node(visited, 300, node->next))	//if not viisted then only it will set the value
		{
			visited[++i].next = node->next;
			visited[++i].data = node->data;
		}
		else
		{
			node->next = NULL;
		}
		node = node->next;
	}
}

struct Node1* findIntersection(struct Node1* head1, struct Node1* head2)
{
	//Traverse head1 list and store it into hash table of size 100. Since range of integers is very large.
	//We will check data of the node, prepare a key (hash table index) based on value of the node and then store the address of that node directly into hash table
	//For collision resolution, rather than searching for next index, we will make a linked list at that index itself

	if (!head1 || !head2)
		return;	//No intersection

	struct Node_L *hash_table[100] = { NULL };

	while (head1)	//to traverse head1 list and insertion to hash map
	{
		int index = (head1->data) % 100;	//hash function, but here is a problem for negative integers
		if (index < 0)
			index = abs(index);

		//insert addresses in a form of stack, so as to get quick access and quick removal
		//Node will contain address of a node of linked list(data), next pointer 
		struct Node_L *temp;
		temp = (Node_L *)malloc(sizeof(Node_L));

		if (temp == NULL)
			return; //mem full

		temp->data = head1;

		temp->next = hash_table[index]; //making a stack as a linked list
		hash_table[index] = temp;

		temp = NULL;

		head1 = head1->next;
	}
	//hash table created

	// now time to traverse list2 and check value in hash map accordingly

	struct Node1 *head3 = NULL;

	while (head2)
	{
		int index = (head2->data) % 100;
		if (index < 0)
			index = abs(index);

		struct Node_L *temp = hash_table[index];

		if (!temp)	//element not found
		{
			head2 = head2->next;
			continue;
		}

		if (temp->data->data == head2->data) //search for data in list
		{
			insertList(&head3, head2->data);
			hash_table[index] = temp->next;
		}
			
		
		else
		{
			while (temp->next)
			{
				if (temp->next->data->data == head2->data)
				{
					insertList(&head3, head2->data);
					temp->next = temp->next->next;
					break;
				}
				temp = temp->next;
			}
		}
		head2 = head2->next;
	}
	return head3;
}

void insertList(struct Node1** head, int data)	//will create link list in sorted order only
{
	struct Node1 *temp, *temp1;

	temp1 = (struct Node1*)malloc(sizeof(struct Node1)); //new Node to insert

	if (!temp1)	//mem full
		return;

	temp1->data = data;

	if (!(*head) || (*head)->data >= data) //element insert at head
	{
		temp1->next = *head;
		*head = temp1;

		temp = temp1 = NULL;
		return;
	}

	temp = *head;

	while (temp->next && temp->next->data < data)
		temp = temp->next;

	temp1->next = temp->next;
	temp->next = temp1;
	temp = temp1 = NULL;

	return;

}

struct Node1 *reverse(struct Node1 *head, int k)
{
	struct Node1* curr = head;	//backup is required as we are passing original head to recursive function
	struct Node1* next = NULL;
	struct Node1* prev = NULL;
	int count = 0;

	/*reverse first k nodes of the linked list */
	while (curr && count++ < k)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	if (next)
		head->next = reverse(next, k);

	/* prev is new head of the input list */
	head = prev;
	return head;
}

void deleteList(struct Node1** head, int data)
{
	struct Node1 *temp = NULL;
	temp = *head;
	
	if (!temp)	//list empty
		return;

	if (temp->data == data) //if first node i.e. head data to be deleted
	{
		*head = temp->next;
		free(temp);
		return;
	}

	while (temp->next) //traverse list till NULL;
	{
		if (temp->next->data == data)
		{
			struct Node1 *temp1 = temp->next;
			temp->next = temp1->next;
			free(temp1);
			temp = temp1 = NULL;
			return;
		}
		temp = temp->next;
	}

	temp = NULL;
	printf("\nElement not found !!\n\n");
	return;

}

void reverseList(struct Node1 **head)
{
	struct Node1 *prev, *next;	//1 for link building, 1 for next upcoming Node handling

	prev = NULL;

	while (*head)
	{
		next = (*head)->next;
		(*head)->next = prev;
		prev = (*head);
		(*head) = next;
	}
	*head = prev;
	return;

}

void printList(struct Node1* head)
{
	if (!head)
	{
		printf("\n\n");
		return;
	}
		

	printf("%d -> ",head->data);
	printList(head->next);

	
}



