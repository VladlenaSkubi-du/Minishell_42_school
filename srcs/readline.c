/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 11:39:51 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/02 20:46:50 by sschmele         ###   ########.fr       */
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

/*
**Here we print and add a printable symble to the command-line.
*/

static char     *printable_parce(char c, char *cmd, unsigned int *all)
{
    if (all[2] == PROMPT && all[3] != all[2])
    {
        while (all[2] != all[3])
            cmd = str_add_symbol(cmd, ' ', all);
    }
    (all[2] <= all[3]) ? write(STDOUT_FILENO, &c, 1) : 0;
    cmd = str_add_symbol(cmd, c, all);
    (c == ';') ? all[1] |= FLAG_SCMD : 0;
    (c == '#' || c == ':') ? all[1] |= FLAG_NL : 0;
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
}

static char     *delete_symbol(char *cmd, unsigned int *all)
{
    all[3]--;
    write(STDOUT_FILENO, "\033[D \033[D", 7);
    cmd = str_del_symbol(cmd, all);
    // (all[2] > 0) ? cmd[all[2]] = '\0' : 0;
    // all[2]--;
    return (cmd);
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
        (c == '\033') ? all[1] |= FLAG_ESC : 0;
        (all[1] & FLAG_ESC) ? esc_leftright(c, cmd, all) : 0;
        ((c == 'D' || c == 'C') && (all[1] & FLAG_ESC)) ? all[1] ^= FLAG_ESC : 0;
        (c == 127 && all[2] > 0 && all[3] > PROMPT) ? cmd = delete_symbol(cmd, all) : 0;


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