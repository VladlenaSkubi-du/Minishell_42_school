/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:40:20 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/03 13:18:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**After the program is finished terminal should be set to canonical input,
**otherwise terminal won't work properly.
*/

void                reset_canonical_input(void)
{
    tcsetattr (STDIN_FILENO, TCSANOW, &g_backup_tty);
}

void                display_prompt(void)
{
    ft_putstr("$> ");
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
    {
        ft_putendl("Stdin is not terminal. The program is finished");
        exit(1);
    }
    tcgetattr (STDIN_FILENO, &tty);
    g_backup_tty = tty;
    tty.c_lflag &= ~(ICANON | ECHO | ISIG);
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tty);
}

void                save_environment(int argc, char **argv, char **envp)
{
    int             i;
    
    i = 0;
    (void)argc;
    (void)argv;
    g_envn = (char**)ft_xmalloc(28 * sizeof(char*) + 1);
    g_envn[29] = NULL;
    while (envp[i])
    {
        g_envn[i] = (char*)ft_xmalloc(ft_strlen(envp[i]) + 1);
        g_envn[i] = ft_strcpy(g_envn[i], envp[i]);
        i++;
    }
}

/*
**If we get 1 return from the fuction readline, that means
**user put '\n' and wants to input another command.
*/

int                 main(int argc, char **argv, char **envp)
{
    save_environment(argc, argv, envp);
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