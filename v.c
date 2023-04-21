#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parater struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	switch (buf[k])
	{
	case '|':
		if (buf[k + 1] == '|')
		{
			buf[k] = 0;
			k++;
			info->cmd_buf_type = CMD_OR;
			break;
		}
		return (0);
	case '&':
		if (buf[k + 1] == '&')
		{
			buf[k] = 0;
			k++;
			info->cmd_buf_type = CMD_AND;
			break;
		}
		return (0);
	case ';':
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
		break;
	default:
		return (0);
	}

	*p = k;
	return (1);
}
/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t b, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[b] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[b] = 0;
			k = len;
		}
	}
	*p = k;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int h;
	list_t *node;
	char *p;

	for (h = 0; h < 10; h++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	char *number = convert_number(info->status, 10, 0);
	char *pid = convert_number(getpid(), 10, 0);

	for (int i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] == '$')
		{
			if (!_strcmp(info->argv[i], "$?"))
				replace_string(&info->argv[i], _strdup(number));
			else if (!_strcmp(info->argv[i], "$$"))
				replace_string(&info->argv[i], _strdup(pid));
			else
			{
				list_t *node = node_starts_with(info->env, &info->argv[i][1], '=');
				if (node)
					replace_string(&info->argv[i], _strdup(_strchr(node->str, '=') + 1));
				else
					replace_string(&info->argv[i], _strdup(""));
			}
		}
	}

	free(number);
	free(pid);

	return (1);
}
/**
 * replace_string - replaces string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
void replace_string(char **old, char *new)
{
	if (new == NULL)
		return;

	free(*old);
	*old = new;
}
