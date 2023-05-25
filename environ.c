#include "main.h"

/**
 * _myenv - This returns string array copy of env
 * @info: This is a structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: This is a string array copy of the environment variables
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - This gets the value of an environ variable
 * @info: This is a structure containing potential arguments. Used to maintain
 * @name: This is a env var name
 * Return: This is the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)

	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}

	return (NULL);
}

/**
 * _unsetenv - This removes env variable
 * @info: This is structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: This is 1 on delete, always 0 otherwise
 */

int _unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}

/**
 * _setenv - Initialize new env variable,
 *           or modify an existing one
 * @info_struct: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: Always 0
 */
void _setenv(info_t *info_struct)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * populate_env_list - This initialize new env variable,
 *           or modify an existing one
 * @info: This is a structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: This is always 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
