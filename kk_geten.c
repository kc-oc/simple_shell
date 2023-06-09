#include "main.h"

/**
 * get_environ - This returns the string array copy of our environ
 * @info: This is structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenvm - This remove an environment variable
 * @info: This is the structure containing potential arguments.
 * Used to maintain constant function prototype.
 *
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 *
 */

int _unsetenvm(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			return 1;
		}
		node = node->next;
		i++;
	}
	return 0;
}

/**
 * _setenvm - This is an initialize a new environment variable
 * or modify an existing one
 * @info: This is a structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: This is the string env var property
 * @value: This is the string env var value
 *
 * Return: Always 0
 */
int _setenvm(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return 1;

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return 0;
		}
		node = node->next;
}
	if (add_node_end(&(info->env), buf, 0) == NULL)
	{
		free(buf);
		return 1;
	}
	free(buf);
	info->env_changed = 1;
	return 0;
}
