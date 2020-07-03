/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/07/03 15:09:44 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"

static void		sort_list(t_env **export_list)
{
	t_env	*ptr;
	t_env	*next;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		ptr = *export_list;
		next = ptr->next;
		while (ptr && ptr->next)
		{
			if (compare_data(ptr->data, next->data))
			{
				ptr->next = next->next;
				next->next = *export_list;
				*export_list = next;
				swap = 1;
			}
			ptr = ptr->next;
			if (ptr)
				next = ptr->next;
		}
	}
}

void			check_existence_env(char *str, t_env **list)
{
	int		len;
	t_env	*ptr;
	t_env	*previous;

	ptr = *list;
	len = check_equal_sign(str);
	if (len == -1)
		return ;
	previous = NULL;
	while (ptr)
	{
		if (!compare(str, ptr->data, len))
		{
			remove_node(&ptr, &previous, list);
			break ;
		}
		previous = ptr;
		ptr = ptr->next;
	}
	return ;
}

static int		check_existence_exp(char *input, t_env **head)
{
	t_env	*ptr;
	t_env	*previous;

	ptr = *head;
	previous = NULL;
	while (ptr)
	{
		if (compare_exp(input, ptr->data) == 1)
		{
			remove_node(&ptr, &previous, head);
			return (0);
		}
		if (compare_exp(input, ptr->data) == 2)
			return (-1);
		previous = ptr;
		ptr = ptr->next;
	}
	return (0);
}

static t_node	*extend_lists(t_node *node, t_lists **list)
{
	int		i;
	char	*temp;

	while (node->next != NULL && node->type != SYMBOL && node->type != REDIR)
	{
		node = node->next;
		temp = ft_strdup(node->data);
		i = check_existence_exp(node->data, &(*list)->export_list);
		check_input(node);
		if (check_equal_sign(node->data) > 0)
		{
			if (node->next != NULL)
			{
				free(temp);
				temp = ft_strjoin(node->data, node->next->data);
				node = node->next;
			}
			check_existence_env(temp, &(*list)->env_list);
			add_env_node(&(*list)->env_list, temp);
		}
		if (i != -1)
			add_export_node(&(*list)->export_list, temp);
		free(temp);
	}
	return (node->next);
}

t_node			*export_cmd(t_node *node, t_lists **list)
{
	t_env *head;

	if (node->next != NULL && node->type != SYMBOL && node->type != REDIR)
		return (extend_lists(node, list));
	sort_list(&(*list)->export_list);
	head = (*list)->export_list;
	while ((*list)->export_list)
	{
		ft_printf("declare -x %s\n", (*list)->export_list->data);
		(*list)->export_list = (*list)->export_list->next;
	}
	(*list)->export_list = head;
	node = node->next;
	return (node);
}