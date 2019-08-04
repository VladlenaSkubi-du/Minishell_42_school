/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:40:20 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/04 18:01:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void     check_command(char *s)
{
    if (ft_strchri(s, ';') != -1)
        ft_putendl("THERE IS IT ;");
    if (ft_strcmp(s, "cd\n") == 0)
        ft_putendl("cd");
    else if (ft_strcmp(s, "echo\n") == 0)
        ft_putendl("echo");
    else if (ft_strcmp(s, "exit\n") == 0)
        cmd_exit();
    else
        ft_putendl("OTHER");
}

static void     handle_sigint(int sig)
{
    ft_putchar('\n');
    ft_putstr("$> "); //correct
}

static void     check_signal(void)
{
    signal(SIGINT, handle_sigint);
}

static void     command_line(void)
{
    char        command[BUF_SIZE + 1];
    int         bytes_read;

    while (1)
    {
        check_signal();
        ft_putstr("$> "); //correct
 
        bytes_read = read(STDIN_FILENO, command, BUF_SIZE);
        if (command[bytes_read - 1] == '\n')
            check_command(command);
        if (bytes_read == 0)
            cmd_exit();
        ft_bzero(command, BUF_SIZE + 1);
    }
}

int             main(void)
{
    command_line();
    return (0);
}