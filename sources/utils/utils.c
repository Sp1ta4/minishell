/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:16:10 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/03 12:16:44 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	free_ptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

char	*ft_str_char_join(char const *s1, char const *s2, char c)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!res)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		++i;
	}
	res[i++] = c;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		++i;
		++j;
	}
	res[i] = '\0';
	return (res);
}