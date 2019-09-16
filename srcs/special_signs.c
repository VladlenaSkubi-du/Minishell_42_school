/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_signs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:40:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/16 12:58:58 by sschmele         ###   ########.fr       */
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

char			*special_tilda_processing(char *cmd, int *len)
{
	short		flag;
	t_signs		s;
	static int	a;

	flag = 0;
	s.flag = 0;
	while (cmd[a])
	{
		if (cmd[a] == '"' || cmd[a] == '\'')
		{
			flag = quatations_indication(cmd[a], flag);
			a++;
		}
		if (cmd[a] == '~' && flag == 0)
		{
			s.i = a;
			cmd = cmd_line_modification(cmd, len, s);
			free(s.main);
			return (cmd);
		}
		(!(cmd[a] == '\'' || cmd[a] == '"')) ? a++ : 0;
	}
	return (cmd);
}

/*
**@s consists of:
**s.i - counter in the full cmd-line (f.e. "echo $$ aaa",
**if s.i = 3, cmd[s.i] = 'o');
**s.j - is counter in the environ - counter of lines;
**s.word - counter of the word needed: $HOME will be 5, $PWD will be 4;
**s.flag - is for cmd_line_modification-function to know from which case
**information comes: 0 - there is tilda, 1 - there is $$ (pid),
**2 - name found in environ, 3 - name is not found in environ;
**s.tmp - just for any case;
**s.main - what we need to add to the cmd-line: in case of "flag == 3"
**will be equal to NULL.
*/

char			*special_dollar_processing_1(char *cmd, int *len, int i)
{
	t_signs		s;

	s.word = 1;
	if (((s.main = ft_strchr(cmd + i, '$')) == NULL)
		|| (s.main != NULL && (s.main[1] == '\0' || s.main[1] == ' ')))
		return (cmd);
	s.i = s.main - cmd - i;
	while (signs_indication(cmd[s.i + s.word]) == 0 && cmd[s.i + s.word])
		s.word++;
	if (s.word == 1 && cmd[s.i + s.word] == '$')
	{
		s.flag = 1;
		s.main = ft_itoa((int)getpid());
		cmd = cmd_line_modification(cmd, len, s);
		free(s.main);
		return (cmd);
	}
	return (cmd = special_dollar_processing_2(cmd, len, s));
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
	free(s.main);
	return (cmd);
}

char			*cmd_line_modification(char *cmd, int *len, t_signs s)
{
	char		*cmd_end;
	int			len_full;
	extern char	**environ;

	if (s.flag == 1)
		cmd_end = ft_strdup(cmd + s.i + s.word + 1);
	else if (s.flag == 2 || s.flag == 3)
		cmd_end = ft_strdup(cmd + s.i + s.word);
	else if (s.flag == 0)
	{
		s.j = 0;
		while (ft_strncmp(environ[s.j], "HOME", 4) != 0)
			s.j++;
		s.main = ft_strdup(&environ[s.j][5]);
		cmd_end = ft_strdup(cmd + s.i + s.word);
	}
	len_full = ft_strlen(cmd_end) + s.i + ft_strlen(s.main);
	ft_bzero(cmd + s.i, *len - s.i);
	cmd = (len_full + 1 > *len) ? ft_realloc(cmd, *len, len_full + 1) : cmd;
	(s.main != NULL) ? ft_strcat(cmd, s.main) : 0;
	ft_strcat(cmd, ((s.flag == 3 && cmd_end[0] == ' ') ?
		&cmd_end[1] : cmd_end));
	free(cmd_end);
	*len = len_full;
	return (cmd);
}
