/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:41:23 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/10 20:20:15 by sschmele         ###   ########.fr       */
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
# define FLAG_NL        0x1
# define FLAG_SCMD      0x2
# define FLAG_ESC       0x4
# define FLAG_OSQBRK    0x8
# define ECHO_N         0x10
# define ECHO_E         0x20
# define ECHO_EE        0x40
# define ECHO_OQUT      0x80
# define ECHO_SLASH     0x100

char                    **g_envn;
struct termios          g_backup_tty;

/*
**The list of working functions - file main.c
*/

void                    set_noncanonical_input(void);
void                    reset_canonical_input(void);
void                    display_prompt(void);
void                    save_environment(void);

/*
**The list of working functions - file readline.c
*/

int                     readline();
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
void                    help_nl_signal(unsigned int *all);

/*
**The list of working functions - file commands_check.c
*/

void                    check_command(char *cmd);
void                    search_command(char *cmd);

/*
**The list of builtins we have to implement: echo, cd, setenv, unsetenv, env,
**exit - file cmd_exit_echo_cd.c and cmd_env_set_unset.c
*/

void                    cmd_exit(char *cmd);
void                    cmd_echo(char *cmd, int len, int flag);
void                    cmd_echo_output(char *cmd, int len, int *flag, int shift);
void                    cmd_cd(char *cmd, int flag);
void                    cmd_env(char *cmd, int flag);
void                    cmd_setenv(char *cmd, int flag);
void                    cmd_unsetenv(char *cmd, int flag);

/*
**Other functions used - the file other_functions.c
*/
void                    *ft_xmalloc(size_t size);
void                    *ft_realloc(void *subj, int len_subj, int len_needed);
void                    get_terminal_width(unsigned int *term);
void                    init_all(unsigned int *all);

#endif
