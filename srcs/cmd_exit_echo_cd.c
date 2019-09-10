/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit_echo_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:29:35 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/10 20:21:14 by sschmele         ###   ########.fr       */
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
**ECHO_E - '-e' flag - enable interpretation of backslash escapes; - not a POSIX standard
**ECHO_EE - '-E' flag - disable interpretation of backslash escapes (default); - not a POSIX standard
**also --help - --help display this help and exit;
*/

void        cmd_echo(char *cmd, int len, int flag)
{
    char    *ptr;
    int     i;
    
    i = 5;
    flag = 0;
    //ft_putendl(cmd + i);
    while (i < len)
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
    cmd_echo_output(cmd, len, &flag, i);
    (flag & ECHO_N) ? 0 : ft_putchar('\n');
}

void        cmd_echo_output(char *cmd, int len, int *flag, int i)
{
    //ft_putendl(cmd + i);
    while (i < len)
    {
        if (cmd[i] == '"')
        {
            *flag = (*flag & ECHO_OQUT) ? *flag ^ ECHO_OQUT : *flag | ECHO_OQUT;
            i++;
        }
        if ((*flag & ECHO_OQUT) && (*flag & ECHO_E) && cmd[i] == '\\')
        {
            i++;
            if (cmd[i] == 'a')
            {
                write(STDOUT_FILENO, "\a", 1);
                i++;
            }
            else if (cmd[i] == 'b')
            {
                write(STDOUT_FILENO, "\b", 1);
                i++;
            }
            else if (cmd[i] == 'c')
            {
                *flag |= ECHO_N;
                break ;
            }
            else if (cmd[i] == 'f')
            {
                write(STDOUT_FILENO, "\f", 1);
                i++;
            }
            else if (cmd[i] == 'n')
            {
                write(STDOUT_FILENO, "\n", 1);
                i++;
            }
            else if (cmd[i] == 'r')
            {
                write(STDOUT_FILENO, "\r", 1);
                i++;
            }
            else if (cmd[i] == 't')
            {
                write(STDOUT_FILENO, "\t", 1);
                i++;
            }
            else if (cmd[i] == 'v')
            {
                write(STDOUT_FILENO, "\v", 1);
                i++;
            }
            else if (cmd[i] == '"' && i + 1 < len)
            {
                write(STDOUT_FILENO, "\"", 1);
                i++;
            }
            if (ft_strncmp(cmd + i, "033", 3) == 0
                || ft_strncmp(cmd + i, "x1b", 3) == 0)
            {
                write(STDOUT_FILENO, "\033", 1);
                i += 3;
            }
        }
        i += (cmd[i] == '\\' && !(*flag & ECHO_OQUT)) ? 1 : 0;
        if (cmd[i] != '"' && cmd[i] != '\\')
        {
            write(STDOUT_FILENO, &cmd[i], 1);
            i++;
        }
    }
    if ((*flag & ECHO_OQUT) && i >= len)
        write(STDOUT_FILENO, ">Close the brackets", 20);
}

void        cmd_cd(char *cmd, int flag)
{
    ft_putendl(cmd);
}