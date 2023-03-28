/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:11:16 by saltysushi        #+#    #+#             */
/*   Updated: 2023/03/28 18:11:36 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	do_builtin(t_tree *cmdtree, int *redr_fds, t_list **vars_lst)
{
	int			i;
	int			j;
	int			in;
	int			out;
	static char	*pwd;

	if (!pwd)
		pwd = getcwd(0, 500);
	if (redr_fds)
	{
		in = dup(0);
		out = dup(1);
		if (dup2(redr_fds[0], 0) < 0 || dup2(redr_fds[1], 1) < 0)
			return (perror("dup2"), exit(errno), 1);
	}
	i = 0;
	while (cmdtree->arg && cmdtree->arg[i])
	{
		j = 0;
		while (cmdtree->arg[i][j])
		{
			if (cmdtree->arg[i][j] == '$')
				expand2(cmdtree, i, &j, vars_lst);
			else
				j++;
		}
		expand(cmdtree, i);
		i++;
	}
	if (!ft_strncmp(cmdtree->arg[0], "echo", 5))
		return (do_echo(cmdtree), (dup2(in, 0), dup2(out, 1)), 1);
	if (!ft_strncmp(cmdtree->arg[0], "exit", 5))
		return (do_exit(cmdtree->arg[1], count_args(cmdtree)), (dup2(in, 0),
				dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "cd", 3))
		return (do_cd(cmdtree, pwd), (dup2(in, 0), dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "pwd", 4))
		return (do_pwd(pwd), (dup2(in, 0), dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "env", 4))
		return (do_env(cmdtree, vars_lst), (dup2(in, 0), dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "export", 7))
		return (do_export(cmdtree, vars_lst), (dup2(in, 0), dup2(out, 1)), 1);
	else if (!ft_strncmp(cmdtree->arg[0], "unset", 6))
		return (do_unset(cmdtree, vars_lst), (dup2(in, 0), dup2(out, 1)), 1);
	else
	{
		return ((dup2(in, 0), dup2(out, 1)), 0);
	}
}
