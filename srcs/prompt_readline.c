/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:39:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/27 16:53:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	    get_terminal_width(int *term)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
    term[0] = sz.ws_col;
    term[1] = sz.ws_row;
}

int            readline(void)
{
    char        *cmd;
    int         max;
    unsigned char        c;
    int         i;
    int         sig;
    static int  term[2];

    max = 50;
    cmd = (char*)ft_xmalloc(max);
    i = -1;
    sig = 0;
    get_terminal_width(term);
    while (c != '\n')
    {
        read(STDIN_FILENO, &c, 1);
        if (ft_isprint(c) && !(sig & FLAG_ESC))
        {
            i++;
            write(STDOUT_FILENO, &c, 1);
            (c == ';') ? sig |= FLAG_SCMD : 0;
            (c == '#' || c == ':') ? sig |= FLAG_NL : 0;
            if (i >= max - 1)
            {
                cmd = ft_realloc(cmd, max, max * 2);
                max *= 2;
            }
            cmd[i] = c;
        }
        // if (ft_isprint(c) && !(sig & FLAG_ESC))
        //     term[2]++;
        
        //reaction for signals
        if (c == 3 || c == 10 || c == 13)
        {
            ft_putchar('\n');
            return (1);
        }
        (c == 4 && !cmd[0]) ? cmd_exit(cmd) : 0;
        
        //switches
        (c == '\033') ? sig |= FLAG_ESC : 0;
        (c == 91 && (sig & FLAG_ESC)) ? sig |= FLAG_OSQBRK : 0;
        if (c == 68 && (sig & FLAG_ESC) && (sig & FLAG_OSQBRK))
        {
            // if (term[2] > 0)
            // {
            //     write(STDOUT_FILENO, "\033[D", 3);
            //     term[2]--;
            // }
            if (i >= 0)
            {
                write(STDOUT_FILENO, "\033[D", 3);
                i--;
            }
        }
        else if (c == 67 && (sig & FLAG_ESC) && (sig & FLAG_OSQBRK))
        {
            write(STDOUT_FILENO, "\033[C", 3);
            i++;
            //term[2]++;
        }

        //delete
        if (c == 127)
        {
            if (i >= 0)
            {
                write(STDOUT_FILENO, "\033[D \033[D", 7);
                // write(STDOUT_FILENO, " ", 1);
                // write(STDOUT_FILENO, "\033[D", 3);
                (i >= 0) ? cmd[i] = '\0' : 0;
                i--;
            }
            // if (term[2] > 0)
            // {
            //     write(STDOUT_FILENO, "\033[D \033[D", 7);
            //     // write(STDOUT_FILENO, " ", 1);
            //     // write(STDOUT_FILENO, "\033[D", 3);
            //     (i >= 0) ? cmd[i] = '\0' : 0;
            //     i--;
            //     term[2]--;
            // }
        }
            
        // if (ft_isprint(c) && !(sig & FLAG_ESC))
        // {
        //     i++;
        //     write(STDOUT_FILENO, &c, 1);
        //     (c == ';') ? sig |= FLAG_SCMD : 0;
        //     (c == '#' || c == ':') ? sig |= FLAG_NL : 0;
        //     if (i >= max - 1)
        //     {
        //         cmd = ft_realloc(cmd, max, max * 2);
        //         max *= 2;
        //     }
        //     cmd[i] = c;
        // }
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
