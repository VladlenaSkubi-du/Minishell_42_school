/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_signs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:40:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/29 18:49:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**@count[3] exists because of the norm and consists of:
**count[0] - for brackets;
**count[1] - for double quatations;
**count[2] - for single quatations.
*/

int				special_signs_check(char *cmd)
{
	int			i;
	int			count[3];

	i = -1;
	ft_bzero_int(count, 3);
	while (cmd[++i])
	{
		if (cmd[i] == '\\' && cmd[i + 1] && ft_isprint(cmd[i + 1]))
		{
			i += 1;
			continue ;
		}
		else if (cmd[i] == '\\' && ft_isprint(cmd[i + 1]) == 0)
			return (-1);
		(cmd[i] == '\"') ? count[1]++ : 0;
		(cmd[i] == '\'') ? count[2]++ : 0;
		(cmd[i] == '(' || cmd[i] == '{') ? count[0]++ : 0;
		(cmd[i] == ')' || cmd[i] == '}') ? count[0]-- : 0;
	}
	if (count[0] != 0 || (count[1] % 2 && !count[2] % 2 && !count[2]) ||
		(!count[1] % 2 && count[2] % 2 && !count[1]) ||
		(count[1] % 2 && count[2] % 2 && count[2] && count[1]))
		return (-1);
	return (0);
}

/*
**@s exists because of the norm and consists of (used here):
**s.i - counter in the full cmd-line (f.e. "echo $$ aaa",
**if s.i = 3, cmd[s.i] = 'o');
**s.j - is counter in the environ - counter of lines;
**s.w - counter of the word needed: $HOME will be 5, $PWD will be 4;
**s.fl - is for cmd_line_modification-function to know from which case
**information comes: 0 - there is tilda, 1 - there is $$ (pid),
**2 - name found in environ, 3 - name is not found in environ;
**s.tmp - just for any case;
**s.main - what we need to add to the cmd-line: in case of "flag == 3"
**will be equal to NULL.
*/

char			*special_tilda_processing(char *cmd, int *len)
{
	short		flag;
	t_signs		s;

	flag = 0;
	s.fl = 0;
	s.i = 0;
	s.w = 1;
	while (cmd[s.i])
	{
		if (cmd[s.i] == '"' || cmd[s.i] == '\'')
		{
			flag = quatations_indication(cmd[s.i], flag);
			s.i++;
		}
		if (cmd[s.i] == '~' && flag == 0)
		{
			cmd = cmd_line_modification(cmd, len, s);
			return (cmd);
		}
		(!(cmd[s.i] == '\'' || cmd[s.i] == '"') && cmd[s.i]) ? s.i++ : 0;
	}
	return (cmd);
}

char			*special_dollar_processing_1(char *cmd, int *len, int i)
{
	t_signs		s;

	s.w = 1;
	if (((s.main = ft_strchr(cmd + i, '$')) == NULL)
		|| (s.main != NULL && (s.main[1] == '\0' || s.main[1] == ' ')))
		return (cmd);
	s.i = s.main - cmd - i;
	while (signs_indication(cmd[s.i + s.w]) == 0 && cmd[s.i + s.w])
		s.w++;
	if (s.w == 1 && cmd[s.i + s.w] == '$')
	{
		s.fl = 1;
		s.main = ft_itoa((int)getpid());
		cmd = cmd_line_modification(cmd, len, s);
		return (cmd);
	}
	cmd = special_dollar_processing_2(cmd, len, s);
	return (cmd);
}

char			*special_dollar_processing_2(char *cmd, int *len,
					t_signs s)
{
	extern char	**environ;

	s.j = -1;
	while (environ[++s.j])
		if (ft_strncmp(environ[s.j], cmd + s.i + 1, s.w - 1) == 0
				&& environ[s.j][s.w - 1] == '=')
			break ;
	if (environ[s.j] != NULL)
	{
		s.fl = 2;
		s.main = ft_strdup(environ[s.j] + s.w);
	}
	else
	{
		s.fl = 3;
		s.main = NULL;
	}
	cmd = cmd_line_modification(cmd, len, s);
	return (cmd);
}

char			*cmd_line_modification(char *c, int *len,
					t_signs s)
{
	char		*cmd_e;
	extern char	**environ;

	if ((cmd_e = NULL) && s.fl == 1)
		cmd_e = (c[s.i + s.w]) ? ft_strdup(c + s.i + s.w + 1) : NULL;
	else if (s.fl == 2 || s.fl == 3)
		cmd_e = (c[s.i + s.w]) ? ft_strdup(c + s.i + s.w) : NULL;
	else if ((s.j = 0) == 0 && s.fl == 0)
	{
		while (environ[s.j] && !(ft_strncmp(environ[s.j], "HOME", 4) == 0
			&& environ[s.j][4] == '='))
			s.j++;
		if (environ[s.j] == NULL)
		{
			ft_putendl_fd("minishell: HOME not set.", 2);
			*len = 0;
			return (c);
		}
		cmd_e = (c[s.i + s.w]) ? ft_strdup(c + s.i + s.w) : NULL;
		s.main = ft_strdup(&environ[s.j][5]);
	}
	s.w = ft_strlen(cmd_e) + s.i + ft_strlen(s.main);
	c = cmd_line_modification_2(c, cmd_e, len, s);
	*len = s.w;
	return (c);
}
