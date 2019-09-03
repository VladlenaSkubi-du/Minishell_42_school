/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit_echo_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:29:35 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/03 19:31:15 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        cmd_exit(char *cmd)
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
**ECHO_EE - '-E' flag - disable interpretation of backslash escapes (default);
**also --help - --help display this help and exit;
*/

void        cmd_echo(char *cmd, char **envp, int flag)
{
    char    *ptr;
    int     i;
    
    i = 5;
    flag = 0;
    while (cmd[i] != '\0' && cmd[i] != '\n')
    {
        if (cmd[i] == '-')
        {
            while (cmd[++i] != ' ' && cmd[i] != '\0')
            {
                (cmd[i] == 'n') ? flag |= ECHO_N : 0;
                (cmd[i] == 'e') ? flag |= ECHO_E : 0;
                (cmd[i] == 'E' && !(flag & ECHO_E)) ? flag |= ECHO_EE : 0;
            }
        }
        (cmd[i] == ' ') ? i++ : 0;
        if ((cmd[i] > ' ' && cmd[i] <= '~') && cmd[i] != '-')
            break ;
    }
    (!(flag & ECHO_E)) ? flag |= ECHO_EE : 0;
    cmd_echo_output(cmd + i, flag);
    (flag & ECHO_N) ? 0 : ft_putchar('\n');
}

void        cmd_echo_output(char *cmd, int flag)
{
    ft_putstr(cmd + i);
    (ptr = ft_strchr(cmd, '"')) ? flag |= ECHO_OQUT : 0;
    // if (ft_strrchr(ptr + 1, '"') && (flag & ECHO_EE))
    //     write(STDOUT_FILENO, ptr + 1, ft_strlen(ptr + 1) - 1);
}

void        cmd_cd(char *cmd, char **envp, int flag)
{
    ft_putendl(cmd);
}