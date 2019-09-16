/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:50:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/16 17:10:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Before commands as strings go to other functions to function, we check if
**there are '~' or '\', '"', '$', '\'', '{', '}', '(', ')', '[', ']'. In case of
** '~' or '$' the command-line is changed.
**@i - is counter in cmd-line;
**@tmp - working value, two times reused;
*/

char			*check_command(char *cmd, int len)
{
	int			i;
	int			tmp;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	if ((tmp = special_signs_check(cmd + i, len)) == -1)
	{
		write(STDERR_FILENO,
			"Readline call: minishell is too baby for that\n", 47);
		return (cmd);
	}
	while (1)
	{
		tmp = len;
		cmd = special_dollar_processing_1(cmd, &len, i);
		cmd = special_tilda_processing(cmd, &len);
		if (tmp == len)
			break ;
	}
	builtin_minishell(cmd, i, len);
	return (cmd);
}

/*
**@flag - is used to count, if we entered one of build-in finctions. If
**not, we go further to search the commands in $PATH
*/

void			builtin_minishell(char *cmd, int i, int len)
{
	int			flag;

	flag = 0;
	(ft_strncmp(cmd + i, "exit", 4) == 0) ? cmd_exit(cmd) : 0;
	(ft_strncmp(cmd + i, "echo", 4) == 0) ?
		cmd_echo(cmd + i, len - i, flag++) : 0;
	(ft_strncmp(cmd + i, "cd", 2) == 0) ? cmd_cd(cmd + i, flag++) : 0;
	(ft_strncmp(cmd + i, "env", 3) == 0) ? cmd_env(cmd + i, flag++) : 0;
	(ft_strncmp(cmd + i, "setenv", 6) == 0) ? cmd_setenv(cmd + i, flag++) : 0;
	(ft_strncmp(cmd + i, "unsetenv", 8) == 0) ?
		cmd_unsetenv(cmd + i, flag++) : 0;
	(flag == 0) ? search_command(cmd + i) : 0;
}

void			search_command(char *cmd)
{
	ft_putendl("DO PROCESSING");
}
