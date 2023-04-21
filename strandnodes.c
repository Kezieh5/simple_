#include "shell.h"

/**
 * list_len - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		len++;
		head = head->next;
	}

	return (len);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	size_t len = list_len(head);
	char **strs = NULL;
	char **strs_copy = NULL;

	if (!head || !len)
		return (NULL);

	strs = malloc(sizeof(char *) * (len + 1));
	if (!strs)
		return (NULL);

	for (size_t p = 0; head != NULL; p++, head = head->next)
	{
		strs[p] = _strdup(head->str);
		if (!strs[p])
		{
			for (size_t l = 0; l < p; l++)
				free(strs[l]);
			free(strs);
			return (NULL);
		}
	}

	strs[len] = NULL;
	strs_copy = strs;

	return (strs_copy);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		len++;
	}

	return (len);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *head, char *prefix, char c)
{
    list_t *node = head;

    while (node)
    {
        if (starts_with(node->str, prefix))
        {
            if (c == -1 || node->str[_strlen(prefix)] == c)
                return (node);
        }
        node = node->next;
    }

    return (NULL);
}
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t p = 0;

	while (head)
	{
		if (head == node)
			return (p);
		head = head->next;
		p++;
	}
	return (-1);
}
