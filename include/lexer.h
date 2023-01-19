/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:32:19 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/19 09:15:02 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	AND	= 1 << 0,
	OR = 1 << 1,
	PIPE = 1 << 2,
	REDR_O = 1 << 3,
	REDR_I = 1 << 4,
	HERE_DOC = 1 << 5,
	APPEND = 1 << 6,
	QUOTE = 1 << 7,
	DQUOTE = 1 << 8,
	OPENPAR = 1 << 9,
	CLOSEPAR = 1 << 10,
	VAR = 1 << 11,
	WORD = 1 << 12,
	WHITE_SPC = 1 << 13
}t_type;

typedef struct s_tkns
{
	char	*val;
	t_type	type;
	int		len;
	int		stat;
	t_tkns	*next;
	t_tkns	*prev;
}	t_tkns;

#endif
