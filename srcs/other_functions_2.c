/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:48:27 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/14 17:45:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_bzero_int(int *arr, int len)
{
	int			i;

	i = -1;
	while (++i < len)
		arr[i] = 0;
}

int				signs_indication(char c)
{
	if (c == ' ' || c == '#' || c == '%' || c == '!' ||
		c == '@' || c == '"' || c == '\\' || c == '^' ||
		c == '*' || c == '(' || c == ')' || c == '=' ||
		c == '/' || c == '.' || c == '\'' || c == ':' ||
		c == '-' || c == '$')
		return (1);
	return (0);
}

void			ft_arrdel(char **arr)
{
	int			i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
