#include "Functions.h"

void queue()
{
	struct Node2 *head = NULL, *tail = NULL;

	deq(&head, &tail);

	enq(&head, &tail, "B.D. Gupta");
	enq(&head, &tail, "Santosh");
	enq(&head, &tail, "Ravi");

	deq(&head, &tail);
	
	printq(head, tail);

	enq(&head, &tail, "Sakshi");
	enq(&head, &tail, "Parini");

	deq(&head, &tail);

	printq(head, tail);
}

void deq(struct Node2 **head, struct Node2 **tail)	//delete from head end
{
	struct Node2 *temp;

	if (!(*head))	//empty list
	{
		printf("\nList is empty !!\n\n");
		return;
	}

	temp = *head;
	if (*head == *tail)
		*tail = temp->next;
	*head = temp->next;
	free(temp);


}

void printq(struct Node2 *head, struct Node2 *tail)
{
	if (!head || !tail)	//empty list
		return;

	printf("\n\n");
	while (tail != head)
	{
		printf("%s -> ", head->data);
		head = head->next;
	}

	printf("%s", head->data);
}

void enq(struct Node2 **head, struct Node2 **tail, char *data)	//insert from tail end
{
	struct Node2 *temp;
	temp = (struct Node2*)malloc(sizeof(struct Node2));

	if (!temp) //mem full
		return;

	//temp->data = (char *)malloc(strlen(data)*sizeof(char));
	temp->data = data;
	temp->next = NULL;

	if (!(*head) && !(*tail)) //1st element insertion
	{
		*head = *tail = temp;
		temp = NULL;
		return;
	}

	(*tail)->next = temp;
	*tail = temp;
	temp = NULL;

}


