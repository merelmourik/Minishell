/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 11:40:54 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/03 14:23:52 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../lexer.h"
# include "libft/libft.h"

char	*check_spec_char(const char *str, int c);
char	*cpy_str(char *str, const char *s, int start, int s_len);
char	*ft_substr_lexer(char const *s, unsigned int start, size_t len);

int		add_export_node(t_env **head, char *export_var);
int		add_env_node(t_env **head, char *env_var);
int		check_equal_sign(const char *str);
int		compare_data(const char *str1, const char *str2);
int		compare_exp(const char *input, const char *in_list);
int		get_len(char *str);
int		input_check(char c, char *str1);
int		populate_node(char *cmd, t_node *node);

t_node	*check_input(t_node *node);
t_node	*free_on_error(char *cmd, t_node *cmd_list);

size_t	ft_strlen_lexer(const char *str);

void	add_to_back_env(t_env **head, t_env *node);
void	continue_populating(char *cmd, t_node *node);
void	extend_env_list(char *str, t_env **env_list);
void	free_cmdlist(t_node **head);
void	free_envlist(t_env **head);
void	set_info(int command, int type, t_node *node);

#endif