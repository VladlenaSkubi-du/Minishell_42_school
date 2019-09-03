/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:50:11 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/03 16:20:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void            check_command(char *cmd, char **envp)
{
    int         i;
    int         flag;
    
    i = 0;
    flag = 0;
    // ft_putstr("CHECK");
    // ft_putendl(cmd);
    while (cmd[i] == ' ')
        i++;
    (ft_strncmp(cmd + i, "exit", 4) == 0) ? cmd_exit(cmd) : 0;
    (ft_strncmp(cmd + i, "echo", 4) == 0) ? cmd_echo(cmd + i, envp, flag++) : 0;
    (ft_strncmp(cmd + i, "cd", 2) == 0) ? cmd_cd(cmd + i, envp, flag++) : 0;
    (ft_strncmp(cmd + i, "env", 3) == 0) ? cmd_env(cmd + i, envp, flag++) : 0;
    (ft_strncmp(cmd + i, "setenv", 6) == 0) ? cmd_setenv(cmd + i, envp, flag++) : 0;
    (ft_strncmp(cmd + i, "unsetenv", 8) == 0) ? cmd_unsetenv(cmd + i, envp, flag++) : 0;
    (flag == 0) ? search_command(cmd + i, envp) : 0;
}

void            search_command(char *cmd, char **envp)
{
    
}