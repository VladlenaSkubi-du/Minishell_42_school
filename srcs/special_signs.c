/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_signs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:40:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/12 17:15:49 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			special_signs(char *cmd, int len)
{
	int		i;
	int		count_qu;
	int		count_ap;
	int		count_br;

	i = 0;
	count_qu = 0;
	count_br = 0;
	count_ap = 0;
	while (i < len)
	{
		if (cmd[i] == '\\' && ft_isprint(cmd[i + 1]))
			i += 2;
		else if (cmd[i] == '\\' && ft_isprint(cmd[i + 1]) == 0)
			return (1);
		(cmd[i] == '\"') ? count_qu++ : 0;
		(cmd[i] == '\'') ? count_ap++ : 0;
		(cmd[i] == '(') ? count_br++ : 0;
		(cmd[i] == ')') ? count_br-- : 0;
		i++;
	}
	if (count_br != 0 || (count_qu % 2 && count_ap % 2))
		return (1);
	return (0);
}
