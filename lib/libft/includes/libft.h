/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:48:24 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/24 11:17:56 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file libft.h
 * @brief Header file for the libft library.
 *
 * This file contains the declarations of various functions and structures
 * provided by the libft library.
 */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

// BUFFER_SIZE FOR GET_NEXT_LINE
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// STRUCT FOR BONUS
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

struct				s_bypass_trim
{
	size_t			len_start;
	size_t			len_end;
	size_t			real_len;
};

// MANDATORY
/**
 * @file libft.h

	* @brief This file contains the declarations of various string
	and memory manipulation functions.
 */

/**

	* @brief Returns a pointer to the first occurrence of the character
	'c' in the string 'str'.
 * @param str The string to search in.
 * @param c The character to search for.
 * @return A pointer to the first occurrence of 'c' in 'str',
	or NULL if 'c' is not found.
 */
char				*ft_strchr(const char *str, int c);

/**

	* @brief Returns a pointer to the last occurrence of the character
	'c' in the string 'str'.
 * @param str The string to search in.
 * @param c The character to search for.
 * @return A pointer to the last occurrence of 'c' in 'str',
	or NULL if 'c' is not found.
 */
char				*ft_strrchr(const char *str, int c);

/**

	* @brief Locates the first occurrence of the string 'needle' in the
	string 'haystack' within the first 'len' characters.
 * @param haystack The string to search in.
 * @param needle The string to search for.
 * @param len The maximum number of characters to search.
 * @return A pointer to the first occurrence of 'needle' in 'haystack',
	or NULL if 'needle' is not found.
 */
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

/**

	* @brief Locates the first occurrence of the string 'needle' in the
	string 'haystack'.
 * @param haystack The string to search in.
 * @param needle The string to search for.
 * @return A pointer to the first occurrence of 'needle' in 'haystack',
	or NULL if 'needle' is not found.
 */
char				*ft_strstr(const char *haystack, const char *needle);

/**
 * @brief Allocates and returns a substring of the string 's'.
 * @param s The string to create the substring from.
 * @param start The starting index of the substring in 's'.
 * @param len The maximum length of the substring.
 * @return The substring of 's', or NULL if the allocation fails.
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Concatenates two strings 's1' and 's2' and returns the result.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The concatenated string, or NULL if the allocation fails.
 */
char				*ft_strjoin(char const *s1, char const *s2);

/**

	* @brief Trims the characters specified in 'set' from the beginning
	and end of the string 's1'.
 * @param s1 The string to trim.
 * @param set The set of characters to trim.
 * @return The trimmed string, or NULL if the allocation fails.
 */
char				*ft_strtrim(char const *s1, char const *set);

/**

	* @brief Applies the function 'f' to each character of the
	string 's' to create a new string.
 * @param s The string to iterate over.
 * @param f The function to apply to each character.
 * @return The new string created by applying 'f' to each character,
	or NULL if the allocation fails.
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**

	* @brief Splits the string 's' using the character 'c' as
	a delimiter and returns an array of strings.
 * @param s The string to split.
 * @param c The delimiter character.
 * @return An array of strings resulting from the split,
	or NULL if the allocation fails.
 */
char				**ft_split(char const *s, char c);

/**
 * @brief Converts an integer 'n' to a string representation.
 * @param n The integer to convert.
 * @return The string representation of 'n', or NULL if the allocation fails.
 */
char				*ft_itoa(int n);

/**
 * @brief Converts a string 'str' to an integer.
 * @param str The string to convert.
 * @return The converted integer value.
 */
int					ft_atoi(const char *str);

/**
 * @brief Checks if the given character 'c' is alphanumeric.
 * @param c The character to check.
 * @return 1 if 'c' is alphanumeric, 0 otherwise.
 */
int					ft_isalnum(int c);

/**
 * @brief Checks if the given character 'c' is alphabetic.
 * @param c The character to check.
 * @return 1 if 'c' is alphabetic, 0 otherwise.
 */
int					ft_isalpha(int c);

/**
 * @brief Checks if the given character 'c' is a printable ASCII character.
 * @param c The character to check.
 * @return 1 if 'c' is a printable ASCII character, 0 otherwise.
 */
int					ft_isascii(int c);

/**
 * @brief Checks if the given character 'c' is a digit.
 * @param c The character to check.
 * @return 1 if 'c' is a digit, 0 otherwise.
 */
int					ft_isdigit(int c);

/**
 * @brief Checks if the given character 'c' is a space character.
 * @param c The character to check.
 * @return 1 if 'c' is a space character, 0 otherwise.
 */
int					ft_isspace(int c);

/**
 * @brief Checks if the given character 'c' is a printable character.
 * @param c The character to check.
 * @return 1 if 'c' is a printable character, 0 otherwise.
 */
int					ft_isprint(int c);

/**
 * @brief Converts the given character 'c' to uppercase.
 * @param c The character to convert.
 * @return The uppercase representation of 'c',
	or 'c' if 'c' is not a lowercase letter.
 */
int					ft_toupper(int c);

/**
 * @brief Converts the given character 'c' to lowercase.
 * @param c The character to convert.
 * @return The lowercase representation of 'c',
	or 'c' if 'c' is not an uppercase letter.
 */
int					ft_tolower(int c);

/**
 * @brief Compares the first 'n' bytes of memory areas 's1' and 's2'.
 * @param s1 The first memory area.
 * @param s2 The second memory area.
 * @param n The number of bytes to compare.
 * @return An integer less than, equal to,
	or greater than zero if 's1' is found, respectively, to be less than,
	to match, or be greater than 's2'.
 */
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Compares the first 'n' characters of strings 's1' and 's2'.
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The number of characters to compare.
 * @return An integer less than, equal to,
	or greater than zero if 's1' is found, respectively, to be less than,
	to match, or be greater than 's2'.
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Copies up to 'size' characters from the string 'src' to 'dest'.
 * @param dest The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.

	* @return The total length of the string that would have been
	copied if 'size' was large enough.
 */
size_t				ft_strlcpy(char *dest, const char *src, size_t size);

/**
 * @brief Appends the string 'src' to the end of 'dest'.
 * @param dest The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.

	* @return The total length of the string that would have been
	created if 'size' was large enough.
 */
size_t				ft_strlcat(char *dest, const char *src, size_t size);

/**
 * @brief Calculates the length of the string 'str',
	excluding the terminating null byte.
 * @param str The string to calculate the length of.
 * @return The length of the string.
 */
size_t				ft_strlen(const char *str);

/**
 * @brief Sets the first 'n' bytes of the memory area 's' to the value 'c'.
 * @param s The memory area to setchar	*ft_strstr(const char *haystack,
		const char *needle)
.
 * @param c The value to set.
 * @param n The number of bytes to set.
 * @return A pointer to the memory area 's'.
 */
void				*ft_memset(void *s, int c, size_t n);

/**

	* @brief Locates the first occurrence of the character 'c'
	in the memory area 's'.
 * @param s The memory area to search in.
 * @param c The character to search for.
 * @param n The number of bytes to search.
 * @return A pointer to the first occurrence of 'c' in 's',
	or NULL if 'c' is not found.
 */
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Copies 'n' bytes from the memory area 'src' to the memory area 'dest'.
 * @param dest The destination memory area.
 * @param src The source memory area.
 * @param n The number of bytes to copy.
 * @return A pointer to the destination memory area 'dest'.
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copies 'n' bytes from the memory area 'src' to the memory area 'dest',
	even if the memory areas overlap.
 * @param dest The destination memory area.
 * @param src The source memory area.
 * @param n The number of bytes to copy.
 * @return A pointer to the destination memory area 'dest'.
 */
void				*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Sets the first 'n' bytes of the memory area 's' to zero.
 * @param s The memory area to set.
 * @param n The number of bytes to set.
 */
void				ft_bzero(void *s, size_t n);

/**
 * @brief Applies the function 'f' to each character of the string 's'.
 * @param s The string to iterate over.
 * @param f The function to apply to each character.
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**

	* @brief Allocates memory for an array of 'count' elements of
	'size' bytes each and returns a pointer to the allocated memory.
 * @param count The number of elements to allocate.
 * @param size The size of each element.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void				*ft_calloc(size_t count, size_t size);

/**

	* @brief Duplicates the string 's1' and returns a pointer to
	the duplicated string.
 * @param s1 The string to duplicate.
 * @return A pointer to the duplicated string, or NULL if the allocation fails.
 */
char				*ft_strdup(const char *s1);

/**
 * @brief Writes the character 'c' to the file descriptor 'fd'.
 * @param c The character to write.
 * @param fd The file descriptor.
 */
void				ft_putchar_fd(char c, int fd);

/**
 * @brief Writes the string 's' to the file descriptor 'fd'.
 * @param s The string to write.
 * @param fd The file descriptor.
 */
int					ft_putstr_fd(char *s, int fd);

/**

	* @brief Writes the string 's' followed by a newline character
	to the file descriptor 'fd'.
 * @param s The string to write.
 * @param fd The file descriptor.
 */
void				ft_putendl_fd(char *s, int fd);

/**
 * @brief Writes the integer 'n' to the file descriptor 'fd'.
 * @param n The integer to write.
 * @param fd The file descriptor.
 */
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief Creates a new node with the specified content.
 *
 * @param content The content to be stored in the new node.
 * @return A pointer to the newly created node.
 */
t_list				*ft_lstnew(void *content);

/**
 * @brief Returns a pointer to the last node in the list.
 *
 * @param lst The list.
 * @return A pointer to the last node in the list.
 */
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief Applies the function f to each node of the list and creates a new list
 * resulting from the successive applications of f.
 *
 * @param lst The list.
 * @param f The function to apply to each node.
 * @param del The function used to delete the content of a node.
 * @return The new list.
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**
 * @brief Adds a new node to the beginning of the list.
 *
 * @param lst A pointer to the pointer to the first node of the list.
 * @param new The new node to add.
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Adds a new node to the end of the list.
 *
 * @param lst A pointer to the pointer to the first node of the list.
 * @param new The new node to add.
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Deletes a node from the list.
 *
 * @param lst The node to delete.
 * @param del The function used to delete the content of the node.
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Deletes all nodes of the list.
 *
 * @param lst A pointer to the pointer to the first node of the list.
 * @param del The function used to delete the content of a node.
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Applies the function f to each node of the list.
 *
 * @param lst The list.
 * @param f The function to apply to each node.
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Returns the number of nodes in the list.
 *
 * @param lst The list.
 * @return The number of nodes in the list.
 */
int					ft_lstsize(t_list *lst);

/**
 * @brief Reads a line from a file descriptor.
 *
 * @param fd The file descriptor.
 * @return The line read from the file descriptor.
 */
char				*get_next_line(int fd);

/**
 * @brief Concatenates two strings, allocating memory for the result.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The concatenated string.
 */
char				*ft_strjoin_gnl(char *s1, char const *s2);

/**
 * @brief Replaces the first occurrences of 'old_sub' in 'str' with 'new_sub'.
 * @param str The string to search in.
 * @param old_sub The substring to replace.
 * @param new_sub The substring to replace with.
 * @return The new string with all occurrences of 'old_sub' replaced with
 * 'new_sub'.
 * or NULL if the allocation fails.
 */
char				*ft_str_replace(char *str, char *old_sub, char *new_sub);

/**
 * @brief Duplicates the first 'n' characters of the string 's1'.
 * @param s1 The string to duplicate.
 * @param n The number of characters to duplicate.
 * @return A pointer to the duplicated string, or NULL if the allocation fails.
 */
char				*ft_strndup(const char *s1, size_t n);

/**
 * @brief Writes formatted output to the standard output.
 * @param format The format string.
 * @return The number of characters printed, or a negative value
 * if an error occurs.
 * @note The format string can contain format specifiers that begin
 * with a percent sign (%).
 * Each format specifier starts with a percent sign (%) and ends with
 * a conversion specifier.
 * The conversion specifier is a character that specifies the type
 *  of conversion to be applied.
 * The format specifiers supported by this function are:
 * - %c: Character
 * - %s: String
 * - %d: Signed decimal integer
 * - %i: Signed decimal integer
 * - %u: Unsigned decimal integer
 * - %x: Unsigned hexadecimal integer (lowercase)
 * - %X: Unsigned hexadecimal integer (uppercase)
 * - %p: Pointer
 * - %%: Percent sign
 */
int					ft_printf(const char *format, ...);

int					ft_printstr(char *str);
int					ft_printnbr(int n);
int					ft_printpourcent(void);
int					ft_print_hex(unsigned int num, const char format);
int					ft_print_ptr(void *ptr);
int					ft_print_unsigned(unsigned int n);

#endif
