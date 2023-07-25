#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * addNode - Adds a new node to the end of the linked list
 * @head_ref: A pointer to the head node of the list
 * @new_data: The data to store in the new node in the list
 */
void addNode(Node **head_ref, char *new_data)
{
	Node *new_node = (Node *) malloc(sizeof(Node));
	new_node->data = new_data;
	new_node->next = NULL;

	Node *last = *head_ref;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	while (last->next != NULL)
	{
		last = last->next;
	}

	last->next = new_node;
	return;
}

/**
 * buildPathLinkedList - Builds a linked list of directories in the PATH
 * environment variable.
 *
 * Return: A pointer to the head node of the list.
 */
Node *buildPathLinkedList(void)
{
	Node *head = NULL;

	char *path = getenv("PATH");
	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		addNode(&head, dir);
		dir = strtok(NULL, ":");
	}

	return (head);
}
