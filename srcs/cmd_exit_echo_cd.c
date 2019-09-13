/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit_echo_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:29:35 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/13 21:03:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cmd_exit(char *cmd)
{
	ft_putendl("exit");
	reset_canonical_input();
	free(cmd);
	exit(1);
}

/*
**Flags here:
**ECHO_N - '-n' flag - do not output the trailing newline;
**ECHO_E - '-e' flag - enable interpretation of backslash escapes;
**- not a POSIX standard
**ECHO_EE - '-E' flag - disable interpretation of backslash escapes
**(default); - not a POSIX standard
*/

void			cmd_echo(char *cmd, int len, int flag)
{
	int			i;
	int			tmp;

	flag = 0;
	i = cmd_echo_flags(cmd, len, &flag, 5);
	(!(flag & ECHO_E)) ? flag |= ECHO_EE : 0;
	cmd_echo_output(cmd, len, flag, i);
}

int				cmd_echo_flags(char *cmd, int len, int *flag, int i)
{
	while (i < len)
	{
		if (cmd[i] == '-')
		{
			if (!(cmd[i + 1] == 'n' || cmd[i + 1] == 'e' || cmd[i + 1] == 'E'))
				return (i);
			while (cmd[++i] != ' ' && cmd[i] != '\0')
			{
				(cmd[i] == 'n')	? *flag |= ECHO_N : 0;
				(cmd[i] == 'e') ? *flag |= ECHO_E : 0;
				(cmd[i] == 'E' && !(*flag & ECHO_E)) ? *flag |= ECHO_EE : 0;
			}
		}
		(cmd[i] == ' ') ? i++ : 0;
		if ((cmd[i] > ' ' && cmd[i] <= '~') && cmd[i] != '-')
			return (i);
	}
	return (i);
}

void			cmd_echo_output(char *cmd, int len, int flag, int i)
{
	while (i < len)
	{
		(cmd[i] == '"') ? (flag = (flag & ECHO_OQUT) ?
			flag ^ ECHO_OQUT : flag | ECHO_OQUT) : 0;
		if (cmd[i] == '\\' && (flag & ECHO_OQUT) &&
			(flag & ECHO_E) && cmd[i + 1] == 'c')
		{
			flag |= ECHO_N;
			break ;
		}
		else if (cmd[i] == '\\' && (flag & ECHO_OQUT))
		{
			(flag & ECHO_E) ? i = cmd_echo_escape(cmd, ++i) : 0;
			(flag & ECHO_EE) ? write(STDOUT_FILENO, &cmd[i++], 1) : 0;
			continue ;
		}
		else if (cmd[i] == '\\' && (cmd[i + 1] == '\\'
			|| cmd[i + 1] == '\"'))
			write(STDOUT_FILENO, &cmd[++i], 1);
		(ft_isprint(cmd[i]) && (cmd[i] != '"' && cmd[i] != '\\')) ?
			write(STDOUT_FILENO, &cmd[i++], 1) : i++;
	}
	(flag & ECHO_N) ? 0 : ft_putchar('\n');
}

int				cmd_echo_escape(char *cmd, int i)
{
	if (ft_strncmp(cmd + i, "033", 3) == 0
		|| ft_strncmp(cmd + i, "x1b", 3) == 0)
	{
		write(STDOUT_FILENO, "\033", 1);
		return (i + 3);
	}
	if (cmd[i] == 'a')
		write(STDOUT_FILENO, "\a", 1);
	else if (cmd[i] == 'b')
		write(STDOUT_FILENO, "\b", 1);
	else if (cmd[i] == 'f')
		write(STDOUT_FILENO, "\f", 1);
	else if (cmd[i] == 'n')
		write(STDOUT_FILENO, "\n", 1);
	else if (cmd[i] == 'r')
		write(STDOUT_FILENO, "\r", 1);
	else if (cmd[i] == 't')
		write(STDOUT_FILENO, "\t", 1);
	else if (cmd[i] == 'v')
		write(STDOUT_FILENO, "\v", 1);
	else if (cmd[i] == 'e')
		write(STDOUT_FILENO, "\033", 1);
	return (++i);
}

void		cmd_cd(char *cmd, int flag)
{
	ft_putendl(cmd);
}
