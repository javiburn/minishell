/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:39:49 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/26 17:51:12 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_one_builtin(t_command *input, t_files *files, char **env)
{
	if (input->redi != NULL
		&& input->redi->type != 4)
		files = create_files(input, files);
	if (files->read->content)
		read_infile(files->read);
	if (files->write->content)
		write_outfile(files->write);
	exec_cmd(input, files, env, 0);
}
