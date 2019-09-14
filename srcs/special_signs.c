/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_signs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:40:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/14 23:00:45 by sschmele         ###   ########.fr       */
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

char			*special_tilda_processing(char *cmd, int *len, int i)
{
	extern char	**environ;
	short		flag;
	t_signs		s;

	flag = 0;
	s.flag = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			flag = (cmd[i] == '"' && flag == 0) ? 1 : flag;
			flag = (cmd[i] == '"' && flag == 1) ? 0 : flag;
			flag = (cmd[i] == '\'' && flag == 0) ? 2 : flag;
			flag = (cmd[i] == '\'' && flag == 2) ? 0 : flag;
		}
		if (!(cmd[i] == '~' && flag == 0) || cmd[i] != '~')
			i++;
		else
		{
			s.main = ft_strdup("HOME");
			cmd = cmd_line_modification(cmd, len, s);
			free(s.main);
			return (cmd);
		}
	}
	return (cmd);
}

/*
**@tmp[4] where: tmp[0] = counter of symbols in the word before the separator;
**tmp[1] = counter of the position in the line;
**tmp[2] = flag, from which function we come to the cmd_line_modification-function;
**tmp[3] = just working integer;
*/

char			*special_dollar_processing_1(char *cmd, int *len, int i)
{
	t_signs		s;

	s.word = 1;
	if (((s.main = ft_strchr(cmd + i, '$')) == NULL)
		|| (s.main != NULL && s.main[1] == '\0'))
		return (cmd);
	s.i = s.main - cmd - i;
	while (signs_indication(cmd[s.i + s.word]) == 0 && cmd[s.i + s.word])
		s.word++;
	if (s.word == 1 && cmd[s.i + s.word] == '$')
	{
		s.flag = 1;
		s.main = ft_strdup(ft_itoa((int)getpid()));
		cmd = cmd_line_modification(cmd, len, s);
		free(s.main);
		return (cmd);
	}
	return (special_dollar_processing_2(cmd, len, s));
}

char			*special_dollar_processing_2(char *cmd, int *len, t_signs s)
{
	extern char	**environ;

	s.j = -1;
	while (environ[++s.j])
		if (ft_strncmp(environ[s.j], cmd + s.i + 1, s.word - 1) == 0
				&& environ[s.j][s.word - 1] == '=')
			break ;
	if (environ[s.j] != NULL)
	{
		s.flag = 2;
		s.main = ft_strdup(environ[s.j] + s.word);
	}
	else
	{
		s.flag = 3;
		s.main = NULL;
	}
	cmd = cmd_line_modification(cmd, len, s);
	printf("CMD - %s\n", cmd);
	(s.main != NULL) ? free(s.main) : 0;
	return (cmd);
}

char			*cmd_line_modification(char *cmd, int *len, t_signs s)
{
	char		*cmd_end;
	int			len_full;

	if (s.flag == 0 || s.flag == 1)
		cmd_end = ft_strdup(cmd + s.i + s.word + 1);
	else if (s.flag == 2 || s.flag == 3)
		cmd_end = ft_strdup(cmd + s.i + s.word);
	ft_bzero(cmd + s.i, *len - s.i);
	len_full = ft_strlen(cmd_end) + s.i + ft_strlen(s.main);
	cmd = (len_full + 1 > *len) ? ft_realloc(cmd, *len, len_full + 1) : cmd;
	(s.main != NULL) ? ft_strcat(cmd, s.main) : 0;
	ft_strcat(cmd, ((s.flag == 3 && cmd_end[0] == ' ') ? &cmd_end[1] : cmd_end));
	printf("CMD AFTER - %s\n", cmd);
	free(cmd_end);
	*len = len_full;
	return (cmd);
}
