/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:49:53 by sschmele          #+#    #+#             */
/*   Updated: 2019/09/23 17:38:02 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*temp;

	if (!s1)
		return ((char*)s1);
	len = ft_strlen(s1);
	if (!(temp = (char*)malloc((len + 1) * sizeof(*s1))))
	{
		free(temp);
		return (NULL);
	}
	while (*s1 != '\0')
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	*temp = '\0';
	return (temp -= len);
}
