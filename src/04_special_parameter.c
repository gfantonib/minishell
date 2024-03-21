/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_special_parameter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:03:33 by josfelip          #+#    #+#             */
/*   Updated: 2024/03/14 15:03:35 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/minishell.h"

void	mini_special_parameter(t_mini *mini)
{
	int		i;
	char	**token;
	char	*tmp;

	i = 0;
	token = mini->split_cmd_line;
	while (token[i])
	{
		if (token[i][0] == '$')
		{
			if (token[i][1])
			{
				tmp = mini_expand(token[i][1], mini);
				free(token[i]);
				token[i] = tmp; 
			}
		}
		i++;
	}
}

char	*mini_expand(char c, t_mini *mini)
{
	char	*expansion;

	expansion = NULL;
	if (c == '?')
		expansion = ft_itoa(mini->status);
	return (expansion);
}

int		ft_get_exit_status(int exit_status)
{
	return ((exit_status & 0xff00) >> 8);
}