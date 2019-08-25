/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:41:23 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/25 19:32:05 by sschmele         ###   ########.fr       */
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
#include <termios.h>

# include "libft.h"
# include "ft_printf.h"

# define BUF_SIZE       1024
# define NEXTLINE       1
# define SEVERAL        2

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

#endif
