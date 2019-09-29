/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:50:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/29 15:51:16 by sschmele         ###   ########.fr       */
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

char				*check_command(char *cmd, int len)
{
	int				i;
	int				tmp;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	if ((tmp = special_signs_check(cmd + i)) == -1)
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

void				builtin_minishell(char *cmd, int i, int len)
{
	int				flag;

	flag = 0;
	(ft_strncmp(cmd + i, "exit", 4) == 0) ? cmd_exit(cmd) : 0;
	(ft_strncmp(cmd + i, "echo", 4) == 0) ?
		cmd_echo(cmd + i, len - i, flag++) : 0;
	(ft_strncmp(cmd + i, "cd", 2) == 0) ? cmd_cd(cmd + i, flag++) : 0;
	(ft_strncmp(cmd + i, "env", 3) == 0) ? cmd_env(flag++) : 0;
	(ft_strncmp(cmd + i, "setenv", 6) == 0) ? cmd_setenv(cmd + i, flag++) : 0;
	(ft_strncmp(cmd + i, "unsetenv", 8) == 0) ?
		cmd_unsetenv(cmd + i, flag++) : 0;
	(flag == 0) ? search_command(cmd + i) : 0;
}

void				search_command(char *cmd)
{
	extern char		**environ;
	t_signs			s;

	s.j = 0;
	s.i = -1;
	while (environ[s.j] && ft_strncmp(environ[s.j], "PATH=", 5) != 0)
		s.j++;
	if ((environ[s.j] == NULL || environ[s.j][5] == '\0') &&
		(!(cmd[0] == '/' || cmd[0] == '.')))
	{
		command_error(cmd, 0);
		return ;
	}
	prepare_for_check(cmd, s);
}

void				prepare_for_check(char *cmd, t_signs s)
{
	extern char		**environ;
	char			**dirpath;
	char			**cmd_components;

	dirpath = (environ[s.j] != NULL) ?
		ft_strsplit(&environ[s.j][5], ':') : NULL;
	cmd_components = ft_strsplit(cmd, ' ');
	if ((cmd_components[0][0] == '/' || cmd_components[0][0] == '.')
		&& check_cmd_name(cmd_components) <= 0)
	{
		ft_arrdel(dirpath);
		ft_arrdel(cmd_components);
		return ;
	}
	while (dirpath[++s.i])
		if (find_cmd_in_path(dirpath[s.i], cmd_components) == 0)
			break ;
	if (dirpath[s.i] == NULL)
		command_error(cmd_components[0], 0);
	ft_arrdel(dirpath);
	ft_arrdel(cmd_components);
}

int					command_error(char *cmd, int fl)
{
	ft_putstr("minishell: ");
	write(STDERR_FILENO, cmd, ft_strchrlen(cmd, ' '));
	if (fl == 0)
		ft_putendl_fd(": Command not found.", 2);
	else if (fl == 1)
		ft_putendl_fd(": No such file or directory found.", 2);
	else if (fl == 2)
		ft_putendl_fd(": Is a directory.", 2);
	else if (fl == 3)
		ft_putendl_fd(": Is not a regular file.", 2);
	else if (fl == 4)
		ft_putendl_fd(": Permission denied.", 2);
	return (-1);
}
