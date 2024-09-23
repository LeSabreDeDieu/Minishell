#include "libft.h" // Inclure la libft.h

char	*ft_str_sub(const char *str, size_t start, size_t end)
{
	if (start >= end || start >= ft_strlen(str))
		return (NULL);
	return (ft_substr(str, start, end - start));
}

unsigned char	ft_str_equals(const char *haystack, const char *needle)
{
	size_t	length_needle;

	length_needle = ft_strlen(needle);
	if (length_needle > ft_strlen(haystack))
		return (0);
	return (ft_strncmp(haystack, needle, length_needle) == 0);
}

size_t	ft_str_contents(const char *haystack, const char *needle)
{
	size_t	contents;

	contents = 0;
	if (ft_str_equals(haystack, needle))
		contents++;
	return (contents);
}

static char	*ft_str_replace_fill(char *new_str, const char *replace,
		size_t *origin, size_t *i)
{
	ft_memcpy(&new_str[*origin], replace, ft_strlen(replace));
	*i += ft_strlen(replace) - 1;
	*origin += ft_strlen(replace) - 1;
	return (new_str);
}

char	*ft_str_replace(const char *search, const char *replace,
		const char *str)
{
	char	*new_str;
	char	*tmp;
	size_t	i;
	size_t	origin;
	size_t	count_search;

	count_search = ft_str_contents(str, search);
	new_str = ft_calloc((ft_strlen(str) - (ft_strlen(search)
					* count_search) + (ft_strlen(replace) * count_search) + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	origin = 0;
	while (i < ft_strlen(str))
	{
		tmp = ft_str_sub(str, i, i + ft_strlen(search));
		if (tmp == NULL || ft_str_equals(tmp, search) == 0)
		{
			free(tmp);
			new_str[origin++] = str[i++];
		}
		else
		{
			free(tmp);
			new_str = ft_str_replace_fill(new_str, replace, &origin, &i);
		}
	}
	return (new_str);
}
