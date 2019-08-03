/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:40:20 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/03 21:02:03 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define BUF_SIZE 1024

static void check_command(char *s)
{
    if (ft_strchri(s, ';') != -1)
        ft_putendl("THERE IS IT ;");
    if (ft_strcmp(s, "cd\n") == 0)
        ft_putendl("cd");
    else if (ft_strcmp(s, "echo\n") == 0)
        ft_putendl("echo");
    else if (ft_strcmp(s, "exit\n") == 0)
    {
        ft_putendl("exit");
        exit (1);
    }
    else
        ft_putendl("OTHER");
}

int         main(void)
{
    int     ret;
    char    command[BUF_SIZE + 1];

    while (1)
    {
        ft_putstr("$> ");
        ret = read(0, command, BUF_SIZE);
        if (command[ret - 1] == '\n')
            check_command(command);
        if (ret == 0 || command[ret - 1] == '\0')
        {
            ft_putendl("exit");
            exit(1);
        }
        ft_bzero(command, BUF_SIZE + 1);
    }
    // pid_t   process;

    // process = fork();
    //     printf("Original program,  pid=%d\n",  getpid());
    //     if (process == 0) 
    //     {
    //         printf("In child process,  pid=%d,  ppid=%d\n", 
    //             getpid(),  getppid());
    //     }
    //     else
    //     {
    //         printf("In parent,  pid=%d,  fork returned=%d\n", 
    //                 getpid(),  process);
    //     }
    //     ft_printf("Hi\n");
    // if (process < 0)
    // {
    //     ft_printf("No new process\n");
    // }
    // else if (process == 0)
    // {
    //     ft_printf("\nI am child-process\n");
    //     ft_printf("My PID: %d\n", getpid());
    //     ft_printf("My parent PID: %d\n", getppid());
    // }
    // else
    // {
    //     ft_printf("\nI am parent-process\n");
    //     ft_printf("My PID: %d\n", getpid());
    //     ft_printf("My child PID=%d\n", process);
    // }
    exit(0);
}