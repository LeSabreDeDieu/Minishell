/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:18:07 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/17 16:34:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expension.h"

static size_t	get_nb_words(char *str)
{
	char	*tmp;
	char	*tmp2;
	size_t	nb_words;

	tmp = str;
	nb_words = 1;
	while (*tmp)
	{
		tmp2 = (char *)find_space(tmp);
		if (tmp2 == NULL)
			break ;
		nb_words++;
		tmp = tmp2 + 1;
	}
	return (nb_words);
}

static char	*check_value(char *value, char *search)
{
	if (search == NULL)
		return (ft_strdup(value));
	return (ft_substr(value, 0, search - value));
}

char	**ft_split_not_in_quote(char *str)
{
	char	**split;
	char	*tmp;
	char	*tmp2;
	size_t	nb_words;
	size_t	i;

	if (str == NULL)
		return (NULL);
	nb_words = get_nb_words(str);
	split = ft_calloc((nb_words + 1), sizeof(char *));
	if (split == NULL)
		return (NULL);
	tmp = str;
	i = 0;
	while (*tmp && i < nb_words)
	{
		tmp2 = (char *)find_space(tmp);
		split[i] = check_value(tmp, tmp2);
		if (split[i] == NULL)
			return (free_str_tab(split), NULL);
		if (tmp2 != NULL)
			tmp = tmp2 + 1;
		i++;
	}
	return (split);
}
