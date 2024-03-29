#include "shell.h"

/**
 * _history - displays the history list, one command by line, starting at 0.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter structre
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, l;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	l = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = l;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter structre
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _alias(info_t *info)
{
	int q = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (q = 1; info->argv[q]; q++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[q]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
