/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:50:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/13 21:05:37 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			check_command(char *cmd, int len)
{
	int			i;
	int			flag;
	int			tmp;

	i = 0;
	flag = 0;
	while (cmd[i] == ' ')
		i++;
	if ((tmp = special_signs_check(cmd + i, len)) == -1)
		write(STDERR_FILENO, "Readline call: minishell is too baby for that\n", 47);
	else
	{
		cmd = special_signs_processing(cmd, &len, i);
		(ft_strncmp(cmd + i, "exit", 4) == 0) ? cmd_exit(cmd) : 0;
		(ft_strncmp(cmd + i, "echo", 4) == 0) ? cmd_echo(cmd + i, len - i, flag++) : 0;
		// (ft_strncmp(cmd + i, "cd", 2) == 0) ? cmd_cd(cmd + i, flag++) : 0;
		// (ft_strncmp(cmd + i, "env", 3) == 0) ? cmd_env(cmd + i, flag++) : 0;
		// (ft_strncmp(cmd + i, "setenv", 6) == 0) ? cmd_setenv(cmd + i, flag++) : 0;
		// (ft_strncmp(cmd + i, "unsetenv", 8) == 0) ? cmd_unsetenv(cmd + i, flag++) : 0;
		//(flag == 0) ? search_command(cmd + i) : 0;
	}
}

void			search_command(char *cmd)
{

}
