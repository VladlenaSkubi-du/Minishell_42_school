/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:40:20 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/25 18:51:27 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**'T' means terminal
*/

static void         error(char c)
{
    if (c == 'T')
        ft_putendl("Stdin is not terminal. The program is finished");
    exit(1);
}

/*
**After the program is finished terminal should be set to canonical input.
*/

void                reset_canonical_input(void)
{
    tcsetattr (STDIN_FILENO, TCSANOW, &g_backup_tty);
}

/*
**Here we change the canonical input to non-canonical, not to react on
**combinations: ^C, ^Z, ^Q, ^S as default. After the program finished terminal
**should be set to canonical input.
*/

void                set_noncanonical_input(void)
{
    struct termios  tty;

    if (!isatty(0))
        error('T');
    tcgetattr (STDIN_FILENO, &tty);
    g_backup_tty = tty;
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tty);
}

int                 main(int argc, char **argv, char **envp)
{
    int             ret;
    
    set_noncanonical_input();
    while (1)
    {
        display_prompt();
        if (readline() == 1)
            continue;
    }
    reset_canonical_input();
    return (0);
}