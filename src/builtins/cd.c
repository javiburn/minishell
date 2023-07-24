/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:33:09 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/24 16:54:32 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bi_cd(t_command *com, char **env, int num)
{
	char	path[PATH_MAX];
	t_list	*args;
	char	*home;
	char	*pwd;
	int		len;

	args = com->args;
	pwd = getcwd(path, sizeof(path));
	if (!args)
	{
		home = create_vars("HOME", env);
		chdir(home);
		free(home);
	}
	else if (access(args->content, F_OK) == 0)
		chdir(args->content);
	else if (args && ft_strncmp(args->content, "..", 2) == 0)
	{
		len = ft_strlen(ft_strrchr(pwd, '/'));
		(free(pwd), pwd = NULL);
		pwd = ft_substr(pwd, 0, ft_strlen(pwd) - len);
		chdir(pwd);
		if (ft_strlen(args->content) == 2)
			return ;
	}
	char * aux = ft_strjoin(pwd, "/");
	pwd = ft_strjoin(aux, args->content);
	if (access(pwd, F_OK) == 0)
	{
		chdir(pwd);
		free(aux);
		free(pwd);
	}
	else
		ft_perror("cd");
	if (num != 0)
		exit(EXIT_SUCCESS);
}

/* int	main(int argc, char **argv, char **env)
{
	t_command	*test = malloc(sizeof(t_command));

	ft_lstadd_new(&test->args, "../../include");
	bi_cd(test, env);
	return (0);
} */
