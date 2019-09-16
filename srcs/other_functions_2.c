/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:48:27 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/16 13:00:12 by sschmele         ###   ########.fr       */
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

/*
**Sorry for that. That is because of norm. I cry when do such things.
*/

short			quatations_indication(char c, short flag)
{
	if (c == '"' && flag == 0)
		flag = 1;
	else if ((c == '"' || c == '\'') && flag != 0)
		flag = 0;
	else if (c == '\'' && flag == 0)
		flag = 2;
	return (flag);
}
