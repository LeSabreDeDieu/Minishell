/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:32:04 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/02 14:51:52 by gcaptari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*extract_word(const char *s, char c, size_t *len)
{
	char	*word;
	char	*m;

	m = (char *)s;
	while (*m && *m != c)
		m++;
	*len = m - s;
	word = ft_substr(s, 0, *len);
	return (word);
}

static void	ft_clear(char **tab, size_t indice)
{
	size_t	i;

	i = -1;
	while (++i <= indice)
		(free(tab[i]), tab[i] = NULL);
}

static char	**ft_fill(const char *s, char c, char **result)
{
	char	**move;
	size_t	word_len;

	move = result;
	while (*s)
	{
		if (*s != c)
		{
			*move = extract_word(s, c, &word_len);
			if (!*move)
				return (ft_clear(result, move - result), free(result), NULL);
			move++;
			s += word_len;
		}
		else
			s++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)ft_calloc((word_count + 1), sizeof(char *));
	if (!result)
		return (NULL);
	result = ft_fill(s, c, result);
	return (result);
}
