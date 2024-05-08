/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:28:50 by josfelip          #+#    #+#             */
/*   Updated: 2024/05/08 11:57:15 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_H
# define DICTIONARY_H

# include "../lib/includes/libft.h"

typedef struct	s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}				t_dict;

t_dict	*ft_dictnew(char **var);
t_dict	*ft_dictlast(t_dict *dict);
t_dict	*ft_dictsort(t_dict *dict);
void	ft_dictadd_back(t_dict **dict, t_dict *new_entry);
void	ft_dict_insert(t_dict **dict, char **var);
void	ft_dict_print(t_dict *dict);
int		ft_dict_update(t_dict *dict, char **var);
size_t	ft_max(size_t a, size_t b);

#endif