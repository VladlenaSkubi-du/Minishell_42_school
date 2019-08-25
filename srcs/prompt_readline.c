/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:39:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/25 19:32:05 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int      after_nextline(char *cmd, int signal)
{
    // if (signal = NEXTLINE && cmd[0] == ':' && cmd[1] == ' ')
    // {
    //     ft_putchar('\n');
    //     return (1);
    // } 
    return (0);
}

static int      before_nextline(char *cmd, char c)
{
    int         signal;
    
    // if (c == 3 || c == 10 || c == 13)
    // {
    //     ft_putchar('\n');
    //     return (1);
    // }
    if (c == 4)
        cmd_exit(cmd);
    else if (c == ';')
        signal = SEVERAL;
    else if (c == '#' || c == ':')
        signal = NEXTLINE;
    return (signal);
}

int            readline(void)
{
    char        *cmd;
    int         max;
    char        c;
    int         i;
    int         signal;

    max = 50;
    cmd = (char*)ft_xmalloc(max);
    i = -1;
    while (c != '\n')
    {
        read(STDIN_FILENO, &c, 1);
        if (c == 3 || c == 10 || c == 13)
        {
            ft_putchar('\n');
            return (1);
        }
        else
            signal = before_nextline(cmd, c);
        write(STDOUT_FILENO, &c, 1);
        if (i >= max - 1)
        {
            cmd = ft_realloc(cmd, max, max * 2);
            max *= 2;
        }
        cmd[++i] = c;
    }
    // if (signal == NEXTLINE && cmd[0] == ':' && cmd[1] == ' ')
    // {
    //     ft_putchar('\n');
    //     return (1);
    // }
    // after_nextline(cmd, signal);
    return (0);
}

void            display_prompt(void)
{
    ft_putstr("$> ");
}
