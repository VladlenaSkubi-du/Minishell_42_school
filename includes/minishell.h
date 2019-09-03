/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:41:23 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/03 13:23:45 by sschmele         ###   ########.fr       */
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

# define MAX            5
# define PROMPT         3
# define FLAG_NL        0x1 //next line
# define FLAG_SCMD      0x2 //several commands
# define FLAG_ESC       0x4 //there was '\033'
# define FLAG_OSQBRK    0x8 //there was an open square bracket '['

char                    **g_envn;
struct termios          g_backup_tty;

/*
**The list of working functions - file main.c
*/

void                    set_noncanonical_input(void);
void                    reset_canonical_input(void);
void                    display_prompt(void);
void                    save_environment(int argc, char **argv, char **envp);

/*
**The list of working functions - file readline.c
*/

int                     readline(void);
char                    *delete_symbol(char *cmd, unsigned int *all);
void                    esc_leftright(char c, char *cmd, unsigned int *all);
char                    *printable_parce(char c, char *cmd, unsigned int *all);
int                     nl_signals(char c, char *cmd, unsigned int *all);

/*
**The list of working functions - file cmd_readline_changes.c
*/

char                    *str_add_symbol(char *arr, char add, unsigned int *all);
char                    *str_del_symbol(char *arr, unsigned int *all);
char                    *help_str_change(char *cmd, char *swap,
                            int point, char add);

/*
**The list of working functions - file commands_check.c
*/

void                    check_command(char *cmd);

/*
**The list of builtins we have to implement: echo, cd, setenv, unsetenv, env,
**exit
*/

void                    cmd_exit(char *cmd);

/*
**Other functions used - the file other_functions.c
*/
void                    *ft_xmalloc(size_t size);
void                    *ft_realloc(void *subj, int len_subj, int len_needed);
void                    get_terminal_width(unsigned int *term);
void                    init_all(unsigned int *all);

#endif
