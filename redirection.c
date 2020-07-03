/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/03 11:31:03 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include <string.h>
#include "parser.h"

int			count_redirections(t_node *cmd_list)
{
	t_node	*temp;

	temp = cmd_list;
	while (temp)
	{
		if (temp->type == REDIR)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static int	open_file(t_node *cmd_list)
{
	if (cmd_list->command == ARROW_RIGHT)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_TRUNC, 0644));
	if (cmd_list->command == ARROW_DOUBLE)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (0);			//error van maken
}

void		fd_error(void)
{
	ft_printf("Error: %s\n", strerror(errno));
	errno = 0;
}

static void	redirect(t_node *cmd_list, int *fd_in, int *fd_out)
{
	if (cmd_list->command == ARROW_LEFT)
	{
		if (*fd_in)
			close(*fd_in);
		if (!(*fd_in = open(cmd_list->next->data, O_RDONLY)))
			fd_error();
	}
	else
	{
		if (*fd_out)
			close(*fd_out);
		if (!(*fd_out = open_file(cmd_list)))
			fd_error();
	}
	return ;
}

void		redirection(t_node *cmd_list)
{
	int		fd_out;
	int		fd_in;

	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->type == REDIR)
			redirect(cmd_list, &fd_in, &fd_out);
		cmd_list = cmd_list->next;
	}
	if (fd_in)
		dup2(fd_in, 0);
	if (fd_out)
		dup2(fd_out, 1);
}

//als je dup2 en close protect, geeft hij een error melding
//dit doe ik met if(fd), blijkbaar werkt dat niet goed
//hoe kan je dit dan wel protecten, ook op andere plaatsen
//in de code naar kijken.