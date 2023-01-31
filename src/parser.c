/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:16:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/01/31 11:49:49 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	no_delims(t_tkns *tkns, int delim, int stop)
{
	while (tkns) //quote dquote problem still here
	{
		if (tkns->type & OPAR)
		{
			while (tkns && !(tkns->type & CPAR))
			{
				if (tkns->type & OPAR)
					while (!(tkns->type & CPAR))
						tkns = tkns->next;
				tkns = tkns->next;
			}
		}
		if (tkns && tkns->type & stop)
			return (1);
		if (tkns && tkns->type & delim && !tkns->stat)
			return (0);
		if (tkns)
			tkns = tkns->next;
	}
	return (1);
}

t_tree	*giv_tree(t_tkns *tkns, int *error)
{
	t_tree	*treenode;
	int	subsh;

	subsh = tkns->sbsh;
	while (tkns && tkns->type & WHITE_SPC )
		tkns = tkns->next;
	treenode = logops(tkns, error);
	if (*error && !subsh)
	{
		if (*error == 2)
			printf("Syntax Error\n");
		else if (*error == 1)
			printf("Allocation Error\n");
		return (freetree(treenode), freelst(&tkns), NULL);
	}
	return (treenode);
}

t_tree	*logops(t_tkns *tkns, int *error)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int	subsh;

	if (no_delims(tkns, AND | OR, 0))
		return (lqados(tkns, error));
	treenode = ft_calloc(1, sizeof(t_tree));
	if (!treenode)
		return (*error = 1, treenode);
	tmp = tkns;
	subsh = tmp->sbsh;
	while (tmp && !(tkns->type & CPAR))//quote dquote problem still here
	{
		if (tmp->type & OPAR)
			while (!(tmp->type & CPAR))
				tmp = tmp->next;
		if (tmp->type & (AND | OR))
		{
			if (!tmp->prev || !tmp->next || (tkns->type & (AND | OR)))
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = lqados(tkns, error);
			if (*error)
				return (treenode);
			while (tmp->next && (tmp->next->type & WHITE_SPC || (subsh && tmp->next->type & CPAR)))
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
	while (tmp && !(tmp->type & (AND | OR)) && !(tmp->type & CPAR)) //quote dquote problem still here
	{
		if (tmp->type & OPAR && !(tmp->stat & (IN_DQUOTE | IN_QUOTE)))
			while (!(tmp->type & CPAR))
				tmp = tmp->next;
		if (tmp->type & PIPE)
		{
			if (!tmp->prev || !tmp->next || (tkns->type & PIPE))
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = cmdlst(tkns, error);
			if (*error)
				return (treenode);
			while (tmp->next && (tmp->next->type & WHITE_SPC || (subsh && tmp->next->type & CPAR)))
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

