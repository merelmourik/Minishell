/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 15:03:35 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/12 11:18:17 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node	*echo(t_node *node)
{
	int flag;

	flag = 0;
	g_exitcode = 0;
	node = node->next;
	if (node && node->command == N)
	{
		flag = 1;
		node = node->next;
	}
	while (node && node->type != SYMBOL && node->type != REDIR)
	{
		ft_printf("%s", node->data);
		if (node->next && node->next->type != SYMBOL && \
			node->next->type != REDIR)
			ft_printf(" ");
		node = node->next;
	}
	if (!flag)
		ft_printf("\n");
	return (node);
}
