/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:39:31 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/20 09:40:01 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	return (c == '\n' || c == '\r' || c == '\f' \
			|| c == '\t' || c == '\v' || c == ' ');
}