/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_readline_changes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 13:38:26 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/01 18:29:36 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char        *str_add_symbol(char *cmd, char add, unsigned int *all)
{
    char            *new;
    int             i;
    
    i = all[3] - PROMPT;
    all[7] = ft_strlen(cmd) + 1 + 1;
    new = (all[7] > all[0]) ? (char*)ft_xmalloc((all[0] = all[0] *
        (all[7] / all[0] + 1))) : (char*)ft_xmalloc(all[0]);
    // ft_putnbr(all[0]);
    // ft_putchar('\n');
    if (!(cmd[i] >= ' ' && cmd[i] <= '~'))
    {
        ft_strcpy(new, cmd); //add to the end of the string
        if (cmd[i - 1] == '\0') //counter is among '\0'
        {
            while (i > 0 && new[i - 1] == '\0')
                i--;
            all[3] = i + PROMPT;
        }
    }
    if (cmd[i] != '\0') //add to some part of the string
    {
        ft_strncpy(new, cmd, i);
        ft_strcpy(new + i + 1, cmd + i);
    }
    new[i] = add;
    all[3]++;
    all[2]++;
    free(cmd);
    return (new);
}

char        *str_del_symbol(char *arr, unsigned int *all)
{
    char            *new;
    unsigned int    full_len;
    
    full_len = ft_strlen(arr) + 1;
    //printf("\n%d - %d\n", full_len, len);
    if (arr[all[3]] == '\0') //"where" is a '\0'
        return(arr);
    new = (full_len - 1 == all[0] / 2) ? ft_xmalloc((all[0] = all[0] / 2)) :
        ft_xmalloc(all[0]);
    new = ft_strncpy(new, arr, all[3]);
    if (arr[all[3] + 1] == '\0') //del from the end of the string
        new[all[3]] = ' ';
    else
        new = ft_strcpy(new + all[3], arr + all[3] + 1); //del from some part of the string
    all[2]--;
    free(arr);
    return (new);
}