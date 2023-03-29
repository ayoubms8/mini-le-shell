/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:47:17 by saltysushi        #+#    #+#             */
/*   Updated: 2023/03/29 00:31:16 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

void	swap_args(t_tree *cmdtree, int i, int num, int args_num)
{
	char	*tmp;
	int		n;

	n = num - i - 2;
	while (i < num - 1)
	{
		tmp = cmdtree->arg[i + 1];
		cmdtree->arg[i + 1] = cmdtree->arg[args_num - n];
		cmdtree->arg[args_num - n] = tmp;
		args_num++;
		i++;
	}
}

void	expand3(t_tree *cmdtree, int i)
{
	DIR				*d;
	struct dirent	*fil;
	int				num;
	int				args_num;

	args_num = count_args(cmdtree);
	num = args_num;
	d = opendir(".");
	if (!ft_strncmp(cmdtree->arg[i], "*", 2))
	{
		cmdtree->arg = reallocate(cmdtree->arg, sizeof(char *) * args_num,
				(count_dir() + args_num) * sizeof(char *));
		if (!cmdtree->arg)
		{
			// handle allocation error
			return ;
		}
		if (d)
		{
			fil = readdir(d);
			free(cmdtree->arg[i]);
			cmdtree->arg[i] = ft_strdup(fil->d_name);
			while (fil)
			{
				fil = readdir(d);
				if (fil && ft_strncmp(fil->d_name, ".", 1))
				{
					cmdtree->arg[args_num] = ft_strdup(fil->d_name);
					if (!cmdtree->arg[args_num++])
					{
						// handle allocation error
						break ;
					}
				}
			}
			swap_args(cmdtree, i, num, args_num - 1);
			closedir(d);
		}
	}
}

void	*reallocate(void *ptr, int oldsize, int size)
{
	void	*newptr;

	newptr = ft_calloc(1, size);
	if (!newptr)
		return (NULL);
	newptr = ft_memcpy(newptr, ptr, oldsize);
	free(ptr);
	return (newptr);
}


int	count_dir(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				num;

	d = opendir(".");
	num = 0;
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			if (ft_strncmp(dir->d_name, ".", 1))
				num++;
			dir = readdir(d);
		}
		closedir(d);
	}
	return (num);
}

int	count_args(t_tree *cmdtree)
{
	int	i;

	i = 0;
	while (cmdtree->arg && cmdtree->arg[i])
		i++;
	return (i);
}
