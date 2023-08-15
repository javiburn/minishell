/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:22:26 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 17:56:11 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Deletes all heredoc temp files
*/
void	there_doc(void)
{
	char	*file_name;
	int		i;
	char	*nbr;

	i = 0;
	while (i < 100000)
	{
		nbr = ft_itoa(i);
		file_name = ft_strjoin("/tmp/.heredoc_", nbr);
		free(nbr);
		if (!access(file_name, F_OK))
			unlink(file_name);
		else
			i = -2;
		free(file_name);
		i++;
		if (i == -1)
			break ;
	}
}

/**
 * Creates the temp files that heredoc needs to function. /tmp/.heredoc_*
*/
static char	*create_file(char *str)
{
	char	*file_name;
	int		fd;
	int		i;
	char	*nbr;

	i = 0;
	while (i < 100000)
	{
		nbr = ft_itoa(i);
		file_name = ft_strjoin("/tmp/.heredoc_", nbr);
		free(nbr);
		if (access(file_name, F_OK))
			break ;
		free(file_name);
		i++;
	}
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	write(fd, str, ft_strlen(str));
	close(fd);
	return (file_name);
}

char	*heredoc(char *key_word)
{
	char	*input;
	char	*str;
	char	*change;
	char	*aux;

	signal(SIGINT, SIG_IGN);
	str = ft_calloc(1, 1);
	while (1)
	{
		ft_printf("\033[0;34m→ heredoc\033[0m:\033[0;33m%s\033[0m$ ", key_word);
		input = get_next_line(STDIN_FILENO);
		change = ft_strtrim(input, "\n");
		if (change == NULL || ft_strcmp(change, key_word) == 0)
		{
			(free(change), free(input));
			break ;
		}
		aux = str;
		str = ft_strjoin(str, input);
		(free(aux), free(change), free(input));
	}
	aux = str;
	str = create_file(str);
	(free(aux), signal(SIGINT, signal_handler));
	return (str);
}
