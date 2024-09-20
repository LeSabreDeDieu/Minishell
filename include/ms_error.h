/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:48:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/20 09:51:44 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# define HERE_DOC_EOF_ERROR "avertissement : « here-document » à la ligne 10 \
délimité par la fin du fichier (au lieu de « EOF »)"

void	error_message(char *message);

#endif