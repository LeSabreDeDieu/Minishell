# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:19:20 by gcaptari          #+#    #+#              #
#    Updated: 2024/10/04 16:56:52 by sgabsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

# Directories
SRC_SUBDIR			=	ast command command/builtins env readline token utils
SRCDIR				=	./src
INCDIR				=	./include
LIBDIR				=	./lib
OBJDIR				=	obj

# Sources
#AST
SRC_AST_DIR 		=	ast
SRC_AST_FILES		=	create_ast.c \
						create_ast_value.c \
						create_ast_value_utils.c \
						exec_ast.c \
						utils.c \
						free_ast.c \
						free_ast.c
SRC_AST				=	$(addprefix $(SRC_AST_DIR)/, $(SRC_AST_FILES))

#ENV
SRC_ENV_DIR 		=	env
SRC_ENV_FILES		=	env_factory.c \
						env.c		\
						parser.c	\
						utils.c		\
						test.c
SRC_ENV				=	$(addprefix $(SRC_ENV_DIR)/, $(SRC_ENV_FILES))

#TOKEN
SRC_TOKEN_DIR 		=	token
SRC_TOKEN_FILES		=	tokenise_and_or.c \
						tokenise_quote.c \
						tokenise_subshell.c \
						tokenise.c \
						tokens.c \
						totokenise.c \
						utils.c	\
						utils2.c \
						valid_token.c
SRC_TOKEN			=	$(addprefix $(SRC_TOKEN_DIR)/, $(SRC_TOKEN_FILES))

#UTILS
SRC_UTILS_DIR 		=	utils
SRC_UTILS_FILES		=	error.c \
						free.c \
						history.c \
						free_children.c	\
						len.c \
						minishell_utils.c
SRC_UTILS			=	$(addprefix $(SRC_UTILS_DIR)/, $(SRC_UTILS_FILES))

#COMMAND
SRC_COMMAND_DIR 	=	command
SRC_COMMAND_FILES	=	command.c \
						here_doc.c \
						wait.c     \
						utils.c \
						prepare/close_all_redir.c \
						prepare/dup_all_redir.c \
						prepare/open_all_redirection.c \
						prepare/safe_dup_all_redir.c \
						prepare/standard_fd.c \
						exec/exec_subshell.c \
						exec/exec_simple.c \
						exec/pipe/pipe.c \
						exec/pipe/utils.c \
						builtins/echo.c	\
						builtins/export.c \
						builtins/unset.c \
						builtins/env.c	\
						builtins/cd.c	\
						builtins/exit.c
SRC_COMMAND			=	$(addprefix $(SRC_COMMAND_DIR)/, $(SRC_COMMAND_FILES))

#READ_LINE
SRC_READ_LINE_DIR 	=	readline
SRC_READ_LINE_FILES	=	get_line.c
SRC_READ_LINE		=	$(addprefix $(SRC_READ_LINE_DIR)/, $(SRC_READ_LINE_FILES))

#Expension
SRC_EXPENSION_DIR 	=	expension
SRC_EXPENSION_FILES	=	expend/expend.c \
						expend/expend_variable.c \
						expend/expend_wildcard.c \
						expend/expend_wildcard_utils.c \
						expend/split_args.c \
						dequoting.c \
						utils.c	\
						utils2.c
SRC_EXPENSION		=	$(addprefix $(SRC_EXPENSION_DIR)/, $(SRC_EXPENSION_FILES))

#DLIST
SRC_DLIST_DIR 		=	dlist
SRC_DLIST_FILES		=	dlist.c \
						dlist_utils.c
SRC_DLIST			=	$(addprefix $(SRC_DLIST_DIR)/, $(SRC_DLIST_FILES))

# Files

#SIGNAL
SRC_SIGNAL_DIR 		=	signal
SRC_SIGNAL_FILES	=	signal.c
SRC_SIGNAL			=	$(addprefix $(SRC_SIGNAL_DIR)/, $(SRC_SIGNAL_FILES))

#$(SRC_AST)
#$(SRC_COMMAND)
SRC_FILES			= $(SRC_AST) \
					  $(SRC_ENV) \
					  $(SRC_COMMAND) \
					  $(SRC_TOKEN) \
					  $(SRC_UTILS) \
					  $(SRC_READ_LINE) \
					  $(SRC_EXPENSION) \
					  $(SRC_SIGNAL) \
					  $(SRC_DLIST) \
					  test/print.c \
					  minishell.c

SRC					=	$(addprefix $(SRCDIR)/, $(SRC_FILES))

# Objects
OBJ_SUBDIRS			=	$(SRC_SUBDIR:%=$(OBJDIR)/%)
OBJ					=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEP					=	$(OBJ:.o=.d)

# Libraries
LIBFT_DIR 			=	$(LIBDIR)/libft
LIBFT 				=	$(LIBFT_DIR)/libft.a

# Output
NAME				=	minishell

# Compiler
CC					=	cc
CFLAGS				=	-MMD -g3 -Wall -Wextra -Wshadow -Wunused #-Werror

OPTIONS				=	-I $(INCDIR) -I $(LIBFT_DIR)/includes
LFLAGS				=	-L $(LIBFT_DIR) -lft -lreadline -lcurses

# Progress bar
COUNT				=	1
TOTAL_FILES			=	$(shell find $(SRCDIR) -type f -name "*.c" | wc -l)

# Colors
RED					=	\033[0;31m
GREEN				=	\033[0;32m
YELLOW				=	\033[0;33m
NC					=	\033[0m
KL					=	\033[K

#################
##  TARGETS    ##
#################

all: check

compile: pre_comp $(LIBFT) $(NAME)

check:
	@if [ -f "$(NAME)" ] && [ -z "$(shell find $(SRCDIR) -type f -name "*.c" -newer $(NAME) 2>/dev/null)" ] && [ -z "$(shell find $(SRCDIR) -type f -name "*.h" -newer $(NAME) 2>/dev/null)" ]; then \
		echo "$(YELLOW)********* Rien à faire - Tout est à jour *********$(NC)"; \
	else \
		make -s compile; \
	fi

pre_comp:
	@echo "$(YELLOW)********* Début de la compilation du programme $(NAME) *********$(NC)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ $(OPTIONS) $(LFLAGS) -o $@
	@echo -e "\r$(GREEN)********* Compilation terminée avec succès! *********$(NC)$(KL)"
	@echo "$(GREEN)********* L'executable $(NAME) a été créée. *********$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OPTIONS) -c $< -o $@
	@printf "$(NC)\rCompiling files: [%-50s] %3d%% (%d/%d) %s$(KL)" \
		"$(shell printf '=%.0s' $$(seq 1 $$(($(COUNT) * 50 / $(TOTAL_FILES)))))" \
		$$(($(COUNT) * 100 / $(TOTAL_FILES))) \
		$(COUNT) \
		$(TOTAL_FILES) \
		$<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

$(LIBFT):
	@make -sC $(LIBFT_DIR)

clean:
	@rm -rf $(OBJDIR)
	@rm -f norm.log
	@make -sC $(LIBFT_DIR) clean
	@echo "$(YELLOW)********* Suppression des fichiers objets *********$(NC)"

fclean: clean
	@make -sC $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(RED)********* Suppression de l'executable $(NAME) *********$(NC)"

re: fclean compile

norminette:
	@echo "$(YELLOW)********* Exécution de norminette *********$(NC)"
	@norminette src/ include/ > norm.log | grep -B 1 -e "Error" || echo "Tous les fichiers ont passé le check norminette !"

.PHONY: check compile all clean fclean re norminette
-include $(DEP)
