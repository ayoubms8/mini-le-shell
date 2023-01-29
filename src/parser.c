/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:16:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/01/29 17:41:47 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	no_delims(t_tkns *tkns, int delim, int stop)
{
	int	subsh;

	subsh = tkns->sbsh;
	while (tkns)
	{
		if (!subsh && tkns->sbsh)
		{
			tkns = tkns->next;
			continue ;
		}
		if (tkns->type & stop)
			return (1);
		if (tkns->type & delim)
			return (0);
		tkns = tkns->next;
	}
	return (1);
}

t_tree	*giv_tree(t_tkns *tkns)
{
	t_tree	*treenode;
	int		error;

	error = 0;
	while (tkns->type & WHITE_SPC)
		tkns = tkns->next;
	treenode = logops(tkns, &error);
	if (error)
	{
		if (error == 2)
			printf("Syntax Error\n");
		else if (error == 1)
			printf("Allocation Error\n");
		return (freetree(treenode), freelst(&tkns), NULL);
	}
	return (treenode);
}

t_tree	*logops(t_tkns *tkns, int *error)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int		subsh;

	if (no_delims(tkns, AND | OR, 0))
		return (lqados(tkns, error));
	treenode = ft_calloc(1, sizeof(t_tree));
	if (!treenode)
		return (*error = 1, treenode);
	tmp = tkns;
	subsh = tmp->sbsh;
	while (tmp && !(subsh && !tmp->sbsh))
	{
		if (!subsh && tmp->sbsh)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type & (AND | OR))
		{
			if (!tmp->prev || !tmp->next || (tkns->type & (AND | OR)))
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = lqados(tkns, error);
			if (*error)
				return (treenode);
			while (tmp->next && tmp->next->type & WHITE_SPC)
				tmp = tmp->next;
			if (!tmp->next)
				return (*error = 2, treenode);
			treenode->limn = logops(tmp->next, error);
			if (*error)
				return (treenode);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}

t_tree	*lqados(t_tkns *tkns, int *error)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int		subsh;

	tmp = tkns;
	if (no_delims(tkns, PIPE, AND | OR))
		return (cmdlst(tkns, error));
	treenode = ft_calloc(1, sizeof(t_tree));
	if (!treenode)
		return (*error = 1, treenode);
	subsh = tmp->sbsh;
	while (tmp && !(tmp->type & (AND | OR)) && !(subsh && !tmp->sbsh))
	{
		if (!subsh && tmp->sbsh)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type & PIPE)
		{
			if (!tmp->prev || !tmp->next || (tkns->type & PIPE))
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = cmdlst(tkns, error);
			if (*error)
				return (treenode);
			while (tmp->next && tmp->next->type & WHITE_SPC)
				tmp = tmp->next;
			if (!tmp->next)
				return (*error = 2, treenode);
			treenode->limn = lqados(tmp->next, error);
			if (*error)
				return (treenode);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}
