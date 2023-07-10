/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:27:28 by jsarabia          #+#    #+#             */
/*   Updated: 2023/07/10 17:36:51 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static void	change_dir(char **arr, char **env)
{
	char	*pwd;
	char	*buf;
	char	*home;
	int		len;
	char	path[PATH_MAX];

	buf = NULL;
	pwd = NULL;
	if (!arr[1])
	{
		home = create_vars("HOME", env);
		chdir(home);
		free(home);
		free(arr);
		return ;
	}
	if (access(arr[1], F_OK) == 0)
	{
		chdir(arr[1]);
		free(arr);
		return ;
	}
	buf = getcwd(path, sizeof(path));
	if (ft_strncmp(arr[1], "..", 2) == 0)
	{
		len = ft_strlen(ft_strrchr(buf, '/'));
		pwd = ft_substr(buf, 0, ft_strlen(buf) - len);
		chdir(pwd);
		free(pwd);
		if (ft_strlen(arr[1]) == 2)
			return ;
	}
	if (!pwd)
	{
		pwd = ft_strjoin(buf, "/");
		buf = ft_strjoin(pwd, arr[1]);
		if (access(buf, F_OK) == 0)
		{
			chdir(buf);
			free(pwd);
			free(buf);
		}
		else
			perror("cd");
	}
	free(arr);
	free(pwd);
	free(buf);
}

static char	*check_param(char *argv)
{
	char	*str;
	char	**aux;

	aux = ft_split(argv, ' ');
	if (!aux)
	{
		str = ft_substr(argv, 0, ft_strlen(argv));
		free_matrix(aux);
		return (str);
	}
	str = ft_substr(aux[0], 0, ft_strlen(aux[0]));
	free_matrix(aux);
	return (str);
}

static char	*find_command(char *argv, char **paths)
{
	char	*str;
	char	*temp;
	char	*aux;

	argv = check_param(argv);
	if (access(argv, F_OK) == 0)
		return (argv);
	while (*paths != NULL)
	{
		aux = ft_strjoin(*paths, "/");
		temp = ft_strjoin(aux, argv);
		if (access(temp, F_OK) == 0)
		{
			str = ft_substr(temp, 0, ft_strlen(temp));
			free(temp);
			free(aux);
			free(argv);
			return (str);
		}
		paths++;
		free(temp);
		free(aux);
	}
	free(argv);
	return (NULL);
}

static void	execute_one(char **comms, char **paths, char **env)
{
	char	**arr;
	char	*name;
	int		id;

	// TODO: Check for built-in commands
	name = find_command(comms[0], paths);
	if (!name)
	{
		perror("command");
		return ;
	}
	arr = create_arrays(comms, name);
	if (ft_strncmp(comms[0], "cd", 2) == 0)
	{
		free(name);
		return (change_dir(arr, env));
	}
	id = fork();
	if (id == 0)
	{
		execve(name, arr, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(id, NULL, 0);
	free_matrix(arr);
	free(name);
} */

void	handle_file(char *filename, int flag)
{
	if (flag == 1 || flag == 3)
		open(filename, O_CREAT, 0644);
	else if (flag == 0)
	{
		if (access(filename, R_OK) != 0)
			exit(EXIT_FAILURE);			// TODO: hacer que esto funcione bien
	}
}

char	*create_files(t_command *input)
{
	int		index;
	char	*filename;

	index = 0;
	while (input->redi)
	{
		if (input->redi->type == 0 || input->redi->type == 1)
			filename = ft_substr(input->redi->content, 1,
					ft_strlen(input->redi->content) - 1);
		else if (input->redi->type == 2 || input->redi->type == 3)
			filename = ft_substr(input->redi->content, 2,
					ft_strlen(input->redi->content) - 2);
		if (!filename || input->redi->type == 4)
			exit(EXIT_FAILURE); // TODO: Fix this shit
		handle_file(filename, input->redi->type);
		free(filename);
		if (input->redi->next)
			input->redi = input->redi->next;
		else
			break ;
	}
	return (input->redi->content);
}

void	print_commands(t_command *input, char **paths, char **env)
{
	t_redi	*aux;

	aux = input->redi;
	((void)paths, (void)env);
	if (input->comm)
	{
		printf("command: %s\n", input->comm);
		//execute_one(&input->comm, paths, env);
	}
	while (aux)
	{
		printf("redi: %s\n", (char *)aux->content);
		printf("  -> type: %d\n", (int)aux->type);
		aux = aux->next;
	}
	while (input->args)
	{
		printf("args: %s\n", (char *)input->args->content);
		input->args = input->args->next;
	}
}

void	execute_final(t_command *input, char **paths, char **env)
{
	((void)paths, (void)env);
	if (input->redi && input->redi->type != 4)
		create_files(input);
}

