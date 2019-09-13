/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_signs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:40:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/13 21:05:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				special_signs_check(char *cmd, int len)
{
	int			i;
	int			count[3];

	i = -1;
	ft_bzero_int(count, 3);
	while (cmd[++i])
	{
		if (cmd[i] == '\\' && ft_isprint(cmd[i + 1]))
			i += 2;
		else if (cmd[i] == '\\' && ft_isprint(cmd[i + 1]) == 0)
			return (-1);
		(cmd[i] == '\"') ? count[1]++ : 0;
		(cmd[i] == '\'') ? count[2]++ : 0;
		(cmd[i] == '(') ? count[0]++ : 0;
		(cmd[i] == ')') ? count[0]-- : 0;
	}
	if (count[0] != 0 || (count[1] % 2 && !count[2] % 2 && !count[2]) ||
		(!count[1] % 2 && count[2] % 2 && !count[1]) ||
		(count[1] % 2 && count[2] % 2 && count[2] && count[1]))
		return (-1);
	return (0);
}

char			*special_signs_processing(char *cmd, int *len, int i)
{
	extern char	**environ;
	char		*cmd_end;
	int			j;
	int			tmp;
	int			len_full;

	j = -1;
	tmp = 0;
	if ((cmd_end = ft_strchr(cmd + i, '$')) == NULL)
		return (cmd);
	i = cmd_end - cmd - i;
	while (cmd[i + tmp] != ' ' && cmd[i + tmp])
		tmp++;
	while (environ[++j])
		if (ft_strncmp(environ[j], cmd + i + 1, tmp - 1) == 0)
			break ;
	if (environ[j] != NULL)
	{
		cmd_end = ft_strdup(cmd + i + tmp);
		len_full = ft_strlen(environ[j] + tmp + 1) + ft_strlen(cmd_end) + i;
		ft_bzero(cmd + i, *len - i);
		if (len_full + 1 > *len)
			cmd = ft_realloc(cmd, *len, len_full + 1);
		ft_strcat(cmd, environ[j] + tmp + 1);
		ft_strcat(cmd, cmd_end);
		free(cmd_end);
		*len = len_full;
	}
	return (cmd);
}

