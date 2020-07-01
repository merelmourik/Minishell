/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 14:08:49 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/19 13:30:51 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_node		*env(t_node *node, t_env *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->data);
		env_list = env_list->next;
	}
	while (node && node->type != SYMBOL) 
	{
		node = node->next;
	}
	return (node);
}
