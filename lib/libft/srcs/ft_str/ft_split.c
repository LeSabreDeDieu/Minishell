/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:32:04 by sgabsi            #+#    #+#             */
/*   Updated: 2023/11/16 13:08:10 by sgabsi           ###   ########.fr       */
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
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (*s && *s != c)
		word[i++] = *s++;
	word[i] = '\0';
	*len = i;
	return (word);
}

static void	ft_clear(char **tab, int indice)
{
	int	i;

	i = 0;
	while (i <= indice)
	{
		tab[i] = NULL;
		free(tab[i]);
	}
}

static char	**ft_fill(const char *s, char c, char **result, size_t *word_len)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i++] = extract_word(s, c, word_len);
			if (!result[i - 1])
			{
				ft_clear(result, i - 1);
				free(result);
				return (NULL);
			}
			s += *word_len;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;
	size_t	word_len;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	result = ft_fill(s, c, result, &word_len);
	return (result);
}
