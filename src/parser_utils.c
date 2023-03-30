/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:43:50 by mnadir            #+#    #+#             */
/*   Updated: 2023/03/30 21:44:01 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <string.h>

void	freelst(t_tkns **lst)
{
	t_tkns	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		(*lst) = tmp;
	}
}

int	count_arg(t_tkns *tkn)
{
	int	cnt;
	int	delim;

	delim = PIPE | AND | OR | HERE_DOC | APPEND | REDR_O | REDR_I;
	cnt = 0;
	while (tkn && !(tkn->type & delim))
	{
		if (tkn->type & (VAR | WORD))
			cnt++;
		tkn = tkn->next;
	}
	return (cnt);
}

char	**get_arg(t_tkns *tkn, int *error)
{
	char	**arg;
	int		delim;
	int		i;
	int		cnt;

	delim = PIPE | AND | OR | HERE_DOC | APPEND | REDR_O | REDR_I;
	cnt = count_arg(tkn);
	if (!cnt)
		return (NULL);
	arg = ft_calloc(cnt + 2, sizeof(*arg));
	if (!arg)
		return (*error = 1, NULL);
	i = 0;
	while (tkn && !(tkn->type & delim) && i < cnt + 1)
	{
		if (tkn->type & (VAR | WORD))
		{
			arg[i] = ft_strndup(tkn->val, tkn->len);
			if (!arg[i])
				return (*error = 1, NULL);
			while (tkn && !(tkn->type & WHITE_SPC) && tkn->next && tkn->next->type & (QUOTE | DQUOTE))
			{
				tkn = tkn->next->next;
				while (tkn && (tkn->stat & (IN_QUOTE | IN_DQUOTE)
						|| tkn->type & (VAR | WORD | QUOTE | DQUOTE)))
				{
					ft_strlcat(arg[i], tkn->val, tkn->len
						+ ft_strlen(arg[i]) + 1);
					tkn = tkn->next;
				}
			}
			while (tkn && !(tkn->type & WHITE_SPC) && tkn->next && tkn->next->type & (VAR | WORD))
			{
				tkn = tkn->next;
				ft_strlcat(arg[i], tkn->val, tkn->len + ft_strlen(arg[i]) + 1);
			}
			i++;
		}
		if (tkn)
			tkn = tkn->next;
	}
	return (arg[i] = NULL, arg);
}

int	no_delims(t_tkns *tkns, int delim, int stop)
{
	while (tkns && (!(tkns->type & CPAR) || (tkns->type & CPAR && tkns->stat)))
	{
		if (tkns && tkns->type & OPAR)
		{
			skip_pars(&tkns);
			continue ;
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
