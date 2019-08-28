/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:41:23 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/28 19:34:21 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>     //DELETE
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "ft_printf.h"

# define BUF_SIZE       1024
# define MAX            5
# define PROMPT         3
# define FLAG_NL        0x1 //next line
# define FLAG_SCMD      0x2 //several commands
# define FLAG_ESC       0x4 //there was '\033'
# define FLAG_OSQBRK    0x8 //there was an open square bracket '['
# define FLAG_A         0x10

//char                **g_envn;
struct termios          g_backup_tty;

/*
**The list of working functions - file main.c
*/

void                    set_noncanonical_input(void);
void                    reset_canonical_input(void);

/*
**The list of working functions - file prompt_readline.c
*/

void                    display_prompt(void);
int                     readline(void);

/*
**The list of working functions - file commands_check.c
*/

int                     check_command(char **cmd);

/*
**The list of builtins we have to implement: echo, cd, setenv, unsetenv, env, exit
*/

void                    cmd_exit(char *cmd);

/*
**Other functions used - the file other_functions.c
*/
void                    *ft_xmalloc(size_t size);
void                    *ft_realloc(void *subj, int len_subj, int len_needed);
void                    get_terminal_width(unsigned int *term);

#endif
