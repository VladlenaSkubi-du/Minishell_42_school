/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:39:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/27 18:33:44 by sschmele         ###   ########.fr       */
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

static int     some_signals(char c, char *cmd, int *all)
{
    if (c == 3 || c == 10 || c == 13)
    {
        ft_putchar('\n');
        return (1);
    }
    (c == 4 && !cmd[0]) ? cmd_exit(cmd) : 0;
    return (0);
}

static char     *printable_parce(char c, int *all, char *cmd)
{
    all[3]++;
    write(STDOUT_FILENO, &c, 1);
    (c == ';') ? all[1] |= FLAG_SCMD : 0;
    (c == '#' || c == ':') ? all[1] |= FLAG_NL : 0;
    if (all[2] >= all[0] - 1)
    {
        cmd = ft_realloc(cmd, all[0], all[0] * 2);
        //cmd = realloc(cmd, all[0] * 2);
        all[0] *= 2;
    }
    cmd[all[2]++] = c;
    return (cmd);
}

/*
**The structure all consists of:
**all[0] = maximal command string size;
**all[1] = signal-flags;
**all[2] = counter of the cursor: how much in input and deleted -
**printable symbols in fact;
**all[3] = counter of the cursor: to input or delete
**in the final command-string;
**all[4] = terminal width;
**all[5] = terminal rows number;
*/

int            readline(void)
{
    char                *cmd;
    int                 all[6];
    unsigned char       c;

    all[0] = MAX;
    cmd = (char*)ft_xmalloc(all[0]);
    all[1] = 0;
    all[2] = 0;
    all[3] = 0;
    get_terminal_width(&all[4]);

    while (c != '\n')
    {
        read(STDIN_FILENO, &c, 1);
        if (c == 3 || c == 4 || c == 10 || c == 13)
            return (some_signals(c, cmd, all));
        if (ft_isprint(c) && !(all[1] & FLAG_ESC))
        {
            cmd = printable_parce(c, all, cmd);
            // ft_putchar('\n');
            // ft_putendl(cmd);
            // all[3]++;
            // write(STDOUT_FILENO, &c, 1);
            // (c == ';') ? all[1] |= FLAG_SCMD : 0;
            // (c == '#' || c == ':') ? all[1] |= FLAG_NL : 0;
            // if (all[2] >= all[0] - 1)
            // {
            //     cmd = ft_realloc(cmd, all[0], all[0] * 2);
            //     all[0] *= 2;
            // }
            // cmd[all[2]++] = c;
        }
       
        //switches
        (c == '\033') ? all[1] |= FLAG_ESC : 0;
        (c == 91 && (all[1] & FLAG_ESC)) ? all[1] |= FLAG_OSQBRK : 0;
        if (c == 68 && (all[1] & FLAG_ESC) && (all[1] & FLAG_OSQBRK))
        {
            if (all[3] >= 0)
            {
                write(STDOUT_FILENO, "\033[D", 3);
                all[3]--;
            }
        }
        else if (c == 67 && (all[1] & FLAG_ESC) && (all[1] & FLAG_OSQBRK))
        {
            write(STDOUT_FILENO, "\033[C", 3);
            all[3]++;
        }

        //delete
        if (c == 127 && all[2] > 0)
        {
            all[3]--;
            write(STDOUT_FILENO, "\033[D \033[D", 7);
            (all[2] > 0) ? cmd[all[2]] = '\0' : 0;
            all[2]--;
        }
       
        // read(STDIN_FILENO, &c, 1);
        // if (ft_isprint(c) && !(sig & FLAG_ESC))
        // {
        //     all[2]++;
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
        
        // //reaction for signals
        // if (c == 3 || c == 10 || c == 13)
        // {
        //     ft_putchar('\n');
        //     return (1);
        // }
        // (c == 4 && !cmd[0]) ? cmd_exit(cmd) : 0;
        
        // //switches
        // (c == '\033') ? sig |= FLAG_ESC : 0;
        // (c == 91 && (sig & FLAG_ESC)) ? sig |= FLAG_OSQBRK : 0;
        // if (c == 68 && (sig & FLAG_ESC) && (sig & FLAG_OSQBRK))
        // {
        //     if (i >= 0)
        //     {
        //         write(STDOUT_FILENO, "\033[D", 3);
        //         i--;
        //     }
        // }
        // else if (c == 67 && (sig & FLAG_ESC) && (sig & FLAG_OSQBRK))
        // {
        //     write(STDOUT_FILENO, "\033[C", 3);
        //     i++;
        // }

        // //delete
        // if (c == 127)
        // {
        //     if (i >= 0)
        //     {
        //         write(STDOUT_FILENO, "\033[D \033[D", 7);
        //         (i >= 0) ? cmd[i] = '\0' : 0;
        //         i--;
        //     }
        // }
    }
    return (0);
}

void            display_prompt(void)
{
    ft_putstr("$> ");
}
