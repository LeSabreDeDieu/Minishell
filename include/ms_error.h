/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:48:50 by sgabsi            #+#    #+#             */
/*   Updated: 2024/09/25 09:18:47 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

// Error messages
# define NO_SUCH_FILE_OR_DIRECTORY "No such file or directory"
# define COMMAND_NOT_FOUND "Command not found"
# define PERMISSION_DENIED "Permission denied"
# define IS_A_DIRECTORY "Is a directory"
# define TOO_MANY_ARGUMENTS "Too many arguments"
# define NOT_A_DIRECTORY "Not a directory"
# define NOT_AN_IDENTIFIER "Not an identifier"
# define NUMERIC_ARGUMENT_REQUIRED "Numeric argument required"
# define TOO_FEW_ARGUMENTS "Too few arguments"
# define INVALID_OPTION "Invalid option"
# define INVALID_ARGUMENT "Invalid argument"
# define AMBIGUOUS_REDIRECT "Ambiguous redirect"
# define NO_SUCH_FILE "No such file"
# define BAD_FILE_DESCRIPTOR "Bad file descriptor"
# define SYNTAX_ERROR "Syntax error"
# define SYNTAX_ERROR_NEAR "Syntax error near unexpected token"
# define SYNTAX_ERROR_NEAR_PIPE "Syntax error near unexpected token `|'"
# define SYNTAX_ERROR_NEAR_AND_IF "Syntax error near unexpected token `&&'"
# define SYNTAX_ERROR_NEAR_OR_IF "Syntax error near unexpected token `||'"

# define HERE_DOC_EOF_ERROR "avertissement : « here-document » à la dernière \
ligne délimité par la fin du fichier (au lieu de « EOF »)"

# define HOME_NOT_SET "<<HOME>> not set"
# define OLDPWD_NOT_SET "« OLDPWD » not set"

void	error_message(char *message);
void	error_message_with_arg(char *message, char *arg);
void	error_message_command(char *command, char *error);
void	error_message_command_with_arg(char *command, char *arg, char *error);

#endif