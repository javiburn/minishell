/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:39:49 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/20 17:04:07 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	exec_one_builtin(t_command *input, t_files *files, char **env)
{
	if (input->redi != NULL
		&& input->redi->type != 4)
		files = create_files(input, files);
	if (files->read->content)
		files->fd[0][0] = read_infile(files->read, files->fd);
	if (files->write->content)
	{
		files->fd[1][0] = open(files->write->content, O_WRONLY);
		dup2(files->fd[1][0], STDOUT_FILENO);
		close(files->fd[1][0]);
	}
	exec_cmd(input, files, env);
}