#include "main.h"

/**
 * check_env - This checks if the typed variable is an env variable
 *
 * @h: The head of linked list
 * @in:The input string
 * @data: The data structure
 * Return: no return
 */
void check_env(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->commandBufferType == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->commandBufferType == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * check_vars - This check if the typed variable is $$ or $?
 *
 * @h: The head of the linked list
 * @in: The input string
 * @st: The last status of the Shell
 * @data: The data structure
 * Return: no return
 */
int check_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replaced_input - This replaces string into variables
 *
 * @head: The head of the linked list
 * @input: Ths is ainput string
 * @new_input: This is a new input string (replaced)
 * @nlen: This is a new length
 * Return: The replaced string
 */
int replaced_input(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
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
 * rep_var - This is used to calls functions to replace string into vars
 *
 * @input: This is a input string
 * @datash: This is a data structure
 * Return: replaced string
 */
int rep_var(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->commandBufferType = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->commandBufferType = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->commandBufferType = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
