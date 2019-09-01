/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:39:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/01 18:29:34 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int     nl_exit_signals(char c, char *cmd, unsigned int *all)
{
    if (c == 3 || c == 10 || c == 13 || c == '\n')
    {
        ft_putchar('\n');
        ft_putendl(cmd);
        ft_putnbr(all[2]);
        ft_putchar('-');
        ft_putnbr(all[3]);
        ft_putchar('\n');
        if (all[4])
        {
            while (all[3] != all[2])
            {
                write(STDOUT_FILENO, "\033[C", 3);
                all[3]++;
            }
        }
        free(cmd);
        //ft_putchar('\n');
        return (1);
    }
    (c == 4 && !cmd[0]) ? cmd_exit(cmd) : 0;
    return (0);
}

static char     *printable_parce(char c, char *cmd, unsigned int *all)
{
    if (all[2] == PROMPT && all[3] != all[2])
    {
        while (all[2] != all[3])
        {
            cmd[all[2] - PROMPT] = ' ';
            all[2]++;
        }
    }
    // else if (all[2] > PROMPT && all[3] != all[2])
    // {
    //     if (ft_strlen(cmd) >= all[0] - 1)
    //     {
    //         cmd = ft_realloc(cmd, all[0], all[0] * 2);
    //         all[0] *= 2;
    //     }
    // }
    ++all[3];
    write(STDOUT_FILENO, &c, 1);
    (c == ';') ? all[1] |= FLAG_SCMD : 0;
    (c == '#' || c == ':') ? all[1] |= FLAG_NL : 0;
    cmd = str_add_symbol(cmd, c, all);
    return (cmd);
}

static void     esc_leftright(char c, char *cmd, unsigned int *all)
{
    all[4] = (all[3] >= all[5]) ? all[3] / all[5] : 0;
    
    (c == 91 && (all[1] & FLAG_ESC)) ? all[1] |= FLAG_OSQBRK : 0;
    if (c == 68 && (all[1] & FLAG_ESC) && (all[1] & FLAG_OSQBRK) && all[3] > PROMPT)
    {
        all[3]--;           
        write(STDOUT_FILENO, "\033[D", 3);
    }
    else if (c == 67 && (all[1] & FLAG_ESC) && (all[1] & FLAG_OSQBRK) && all[3] < all[5] - 1)
    {
        if (all[4])
        {
            write(STDOUT_FILENO, "\f", 1);
        }
        all[3]++;
        write(STDOUT_FILENO, "\033[C", 3);
    }
    //printf("%d\n", all[4]);
    //return (cmd);
}

/*
**The structure all consists of:
**all[0] = maximal command string size;
**all[1] = signal-flags;
**all[2] = counter of the cursor: how much in input and deleted -
**printable symbols in fact;
**all[3] = counter of the cursor: to input or delete
**in the final command-string;
**all[4] = nb of strings printed;
**all[5] = terminal width;
**all[6] = terminal rows number;
**all[7] = usable in different functions;
*/

static void             init_all(unsigned int *all)
{
    all[0] = MAX;
    all[1] = 0;
    all[2] = PROMPT;
    all[3] = PROMPT;
    all[4] = 0;
    get_terminal_width(&all[5]);
    all[7] = 0;
    //printf("%d - %d - %d - %d - %d - %d\n", all[0], all[1], all[2], all[3], all[4], all[5]);
}

int            readline(void)
{
    char                *cmd;
    unsigned int        all[8];
    unsigned char       c;

    init_all(all);
    cmd = (char*)ft_xmalloc(all[0]);
    while (1)
    {
        read(STDIN_FILENO, &c, 1);
        if (c == 3 || c == 4 || c == 10 || c == 13 || c == '\n')
            return (nl_exit_signals(c, cmd, all));
        if (ft_isprint(c) && !(all[1] & FLAG_ESC))
            cmd = printable_parce(c, cmd, all);
        (c == '\033') ? all[1] |= FLAG_ESC : 0; //turn on the flag_esc
        (all[1] & FLAG_ESC) ? esc_leftright(c, cmd, all) : 0;
        ((c == 'D' || c == 'C') && (all[1] & FLAG_ESC)) ? all[1] ^= FLAG_ESC : 0; //turn off the flag_esc

        // //delete
        // if (c == 127 && all[2] > 0)
        // {
        //     all[3]--;
        //     write(STDOUT_FILENO, "\033[D \033[D", 7);
        //     (all[2] > 0) ? cmd[all[2]] = '\0' : 0;
        //     all[2]--;
        // }
    }
    free(cmd);
    return (0);
}