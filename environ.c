#include "main.h"

/**
 * get_environ - returns string array copy of env
 * @info_struct: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: String array copy of the environment variables
 */
char **get_environ(info_c *info_struct)
{
    if (!info_struct->environ || info_struct->env_changed)
    {
        if (info_struct->environ)
            free_list(info_struct->environ);  // Free the previous environment variables list
        info_struct->environ = list_co_strings(info_struct->env);
        info_struct->env_changed = 0;
    }

    return (info_struct->environ);
}

/**
 * _unsetenv - Remove env variable
 * @info_struct: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * @name: the string env variable property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_c *info_struct, const char *name)
{
    list_c **node = &(info_struct->env);
    size_t i = 0;
    char *p;
    if (!node || !name)
        return (0);
    while (*node)
    {
        p = starts_with((*node)->str, name);
        if (p && *p == '=')
        {
            info_struct->env_changed = delete_node_at_idx(node, i);
            i = 0;
            continue;
        }
        node = &((*node)->next);
        i++;
    }
    return (info_struct->env_changed);
}

/**
 * _setenv - Initialize new env variable,
 *           or modify an existing one
 * @info_struct: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * @name: the string env variable property
 * @value: the string env variable value
 * Return: Always 0
 */
void _setenv(info_c *info_struct, char *name, char *value)
{
    char *buf = NULL;
    list_c *node;
    char *p;
    if (!name || !value)
        return;
    buf = malloc(_strlen(name) + _strlen(value) + 2);
    if (!buf)
        return;
    _strcpy(buf, name);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info_struct->env;
    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info_struct->env_changed = 1;
            return;
        }
        node = node->next;
    }
    add_node_end(&(info_struct->env), buf, 0);
    free(buf);
    info_struct->env_changed = 1;
}
