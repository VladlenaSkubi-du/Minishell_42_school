/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:50:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/14 22:36:11 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			check_command(char *cmd, int len)
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
		return ;
	}
	while (1)
	{
		tmp = len;
		cmd = special_dollar_processing_1(cmd, &len, i);
		cmd = special_tilda_processing(cmd, &len, i);
		if (tmp == len)
			break ;
	}
	build_in_minishell(cmd, i, len);
}

void			build_in_minishell(char *cmd, int i, int len)
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
