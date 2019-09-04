/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit_echo_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:29:35 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/04 19:18:48 by sschmele         ###   ########.fr       */
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
    cmd_echo_output(cmd, len, flag, i);
    (flag & ECHO_N) ? 0 : ft_putchar('\n');
}

void        cmd_echo_output(char *cmd, int len, int flag, int i)
{
    char    *ptr;
    char    c[2];
    
    //ft_putendl(cmd + i);
    while (i < len)
    {
        if (cmd[i] == '"')
        {
            flag = (flag & ECHO_OQUT) ? flag ^ ECHO_OQUT : flag | ECHO_OQUT;
            i++;
        }
        if (flag & ECHO_OQUT)
        {
            if (cmd[i] == '\\' && (flag & ECHO_E))
            {
                if (cmd[i + 1] == '\\' || (cmd[i + 1] >= 'a' && cmd[i + 1] <= 'c')
                || cmd[i + 1] == 'e' || cmd[i + 1] == 'f' || cmd[i + 1] == 'n'
                || cmd[i + 1] == 'r' || cmd[i + 1] == 't' || cmd[i + 1] == 'v'
                || cmd[i + 1] == 'E')
                {
                    c[0] = '\\';
                    c[1] = cmd[i];
                    write(STDOUT_FILENO, &c, 1);
                    i++;
                }
                else if (ft_strncmp(cmd + i + 1, "033", 3) == 0)
                {
                    write(STDOUT_FILENO, "\033", 1);
                    i += 3;
                }
                else
                {
                    write(STDOUT_FILENO, &cmd[i], 1);
                    write(STDOUT_FILENO, &cmd[i + 1], 1);
                    i++;
                }
            }
            else if (cmd[i] == '\\' && (flag & ECHO_EE))
                write(STDOUT_FILENO, &cmd[i], 1);
        }
        else
        {
            (cmd[i] == '\\') ? i++ : 0;
            write(STDOUT_FILENO, &cmd[i], 1);
        }
        i++;
    }
    // (ptr = ft_strchr(cmd, '"')) ? flag |= ECHO_OQUT : 0;
    // if (ft_strrchr(ptr + 1, '"') && (flag & ECHO_EE))
    //     write(STDOUT_FILENO, ptr + 1, ft_strlen(ptr + 1) - 1);
}

void        cmd_cd(char *cmd, int flag)
{
    ft_putendl(cmd);
}