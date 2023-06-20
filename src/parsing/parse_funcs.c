/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:31 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/20 15:48:25 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Counts the number of words for `split_words`
 */
static int	num_words(char *str)
{
	int				n;
	int				cont;
	int				index;
	enum e_quotes	flag;

	flag = NONE;
	n = 0;
	cont = 0;
	index = 0;
	while (str[n])
	{
		flag = check_flag(str, n);
		if (str[n] != ' ' || flag != NONE)
			index = 0;
		if ((str[n] == ' ' && flag == NONE && index == 0)
			|| (!str[n + 1] && str[n] != ' '))
		{
			cont++;
			index = 1;
		}
		n++;
	}
	return (cont);
}

/**
 * Receives a command as in input. It separates the different words
 * of the command. The command itself and it's parameters.
*/
char	**split_words(char *str)
{
	int				i;
	int				aux;
	int				index;
	int				j;
	enum e_quotes	flag;
	char			**arr;

	i = 0;
	aux = 0;
	index = 0;
	j = 0;
	arr = ft_calloc(num_words(str) + 1, sizeof(char *));
	while (str[i])
	{
		flag = check_flag(str, i);
		if (!str[i + 1] && str[i] != ' ')
			arr[j] = ft_substr(str, aux, i - aux + 1);
		if (str[i] == ' ' && flag == NONE && index == 0)
		{
			arr[j] = ft_substr(str, aux, i - aux);
			aux = i;
			j++;
			index = 1;
		}
		if (str[i] != ' ' || flag != NONE)
			index = 0;
		if (str[i] == ' ' && index == 1)
			aux = i;
		i++;
	}
	free(str);
	return (arr);
}
