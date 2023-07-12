/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:22:26 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/12 11:59:18 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*create_file(char *str)
{
	char	*file_name;
	int		fd;
	int		i;
	char	*nbr;

	i = 0;
	while (i < 10000)
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

	str = "\0";
	while (1)
	{
		ft_printf("-> heredoc:%s $ ", key_word);
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break ;
		change = ft_strtrim(input, "\n");
		if (ft_strncmp(key_word, change, ft_strlen(change)) == 0)
			break ;
		str = ft_strjoin(str, input);
		free(change);
		free(input);
	}
	free(input);
	str = create_file(str);
	return (str);
}

int	main(int argc, char **argv)
{
	printf("%s", heredoc("yes"));
	return (0);
}
