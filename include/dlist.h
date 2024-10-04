/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:29 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/04 16:49:03 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H

# include "libft.h"
# include <unistd.h>

typedef struct s_dlist
{
	char			*str;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

t_dlist				*new_dlist(char *str);
int					dlist_len(t_dlist *dlist);
void				add_dlist(t_dlist **dlist, t_dlist *new_dlist);
void				free_dlist(t_dlist **dlist);
t_dlist				*dlist_last(t_dlist *dlist);
char				**dlist_to_argv(t_dlist **dlist);

#endif