/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:09:14 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/03 16:13:21 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include "../include/dictionary.h"

void	unit_print_array_list(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->commands[i])
	{
		debug_print_parse_list(&mini->commands[i]);
		printf("\n");	
		i++;
	}
}


void	unit_cmd_selection(t_token *token_lst, t_mini *mini)
{
	char	*cmd;
	t_token	*arg;

	cmd = token_lst->token;
	arg = token_lst->next;
	if (!ft_strncmp(cmd, "export", 6))
		mini->status = mini_export(arg, &mini->env_list);
	else if (!ft_strncmp(cmd, "echo", 4))
		mini->status = mini_echo(arg);
}

void	unit_cmd_router(t_mini *mini)
{
	int i;

	i = -1;
	while (mini->commands[++i])
		unit_cmd_selection(mini->commands[i], mini);
}

int main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;
	t_token *arg;
	int		i;

	mini.env_list = NULL;
	mini.status = 0;
	mini_getenv(&mini);
	i = 0;
	while (++i < argc)
	{
		mini_init(&mini);
		mini.cmd_line = argv[i];
		mini_tokenizer(&mini);
		mini_parser(&mini);
		mini_expansion(&mini);
		unit_cmd_router(&mini);
	}
	ft_free_trashman(ft_get_mem_address());
	return (mini.status);
}
