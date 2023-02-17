/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:27:09 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/17 12:00:57 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

int		do_logops(t_tree *cmdtree, int	*redr_fds, int limn);
int		*rslv_redr(t_tree *redr, int *redr_fds, int limn, int cmd);
char	*is_vld_exc(char *path);
void	executor(t_tree *cmdtree);
void	pipe_close(int *pipefd, int limn);

#endif
