/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:39:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/26 18:48:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int            readline(void)
{
    char        *cmd;
    char        escape[4];
    int         max;
    unsigned char        c;
    int         i;
    int         signal;

    max = 50;
    cmd = (char*)ft_xmalloc(max);
    i = -1;
    while (c != '\n')
    {
        read(STDIN_FILENO, &c, 1);

        //reaction for signals
        if (c == 3 || c == 10 || c == 13)
        {
            ft_putchar('\n');
            return (1);
        }
        else if (c == 4)
            cmd_exit(cmd);
        
        //switches
        if (c == '\033' || c == 91)
        {
            //ft_putendl("HERE");
            signal = LEFRIG;
        }
        // if (c == 91 && escape[0])
        // {
        //     ft_putendl("HERE1");
        //     escape[1] = c;
        // }
        if (c == 68 && signal == LEFRIG)
        {
            //ft_putendl("HERE2");
            write(STDOUT_FILENO, &'\h', 1);
        }
            

        if (ft_isprint(c) && signal != LEFRIG)
        {
            write(STDOUT_FILENO, &c, 1);
            if (c == ';')
                signal = SEVERAL;
            else if (c == '#' || c == ':')
                signal = NEXTLINE;
            if (i >= max - 1)
            {
                cmd = ft_realloc(cmd, max, max * 2);
                max *= 2;
            }
            cmd[++i] = c;
        }
        //ft_putendl("OUT");
    }

    // if (signal = NEXTLINE && cmd[0] == ':' && cmd[1] == ' ')
    // {
    //     ft_putchar('\n');
    //     return (1);
    // } 
    return (0);
}

void            display_prompt(void)
{
    ft_putstr("$> ");
}
