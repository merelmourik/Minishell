/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:52:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/06 14:32:10 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "shell.h"
#include "./libft/libft.h"
#include "errno.h"
#include <unistd.h>
#include <string.h>

t_node *cd(t_node *node)
{
	char *path;

	node = node->next;
	if (!node)
		return (node);
	path = node->data;
	if (chdir(path))
	{
		ft_printf("Error: %s\n", strerror(errno));
		errno = 0;
	}
	while (node && node->command != SEMICOLON)
		node = node->next;
	return (node);
}
