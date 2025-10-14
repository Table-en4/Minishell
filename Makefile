CC_FLAGS = -Wall -Wextra -Werror -g
MK_FLAGS = --silent
MAKEFLAGS += $(MK_FLAGS)

NAME = minishell
LBFT = Libft/libft.a
MINIBOX = minibox/minibox.a
MINIBOX_SRCS = $(addprefix $(dir $(MINIBOX)), $(shell $(MAKE) $(MK_FLAGS) -C $(dir $(MINIBOX)) get-srcs))

SRCS = srcs/main.c \
	   srcs/builtins/ft_echo.c \
	   srcs/builtins/ft_cd.c \
	   srcs/builtins/env_init.c \
	   srcs/builtins/env_node.c \
	   srcs/builtins/env_utils.c \
	   srcs/exec_builtin.c \
	   srcs/builtins/ft_export.c \
	   srcs/builtins/ft_env.c \
	   srcs/builtins/env_to_tab.c \
	   srcs/builtins/ft_unset.c \
	   srcs/builtins/ft_pwd.c \
	   srcs/builtins/ft_exit.c \
	   srcs/pipex/here_doc.c \
	   srcs/pipex/exec_and.c \
	   srcs/pipex/exec_command.c \
	   srcs/pipex/exec_pipe.c \
	   srcs/pipex/exec_subshell.c \
	   srcs/pipex/pipex_utils.c \
	   srcs/signals_setup.c \
	   srcs/pipex/read_ast.c \
	   srcs/pipex/exec_or.c \
	   srcs/pipex/redirection.c \
	   srcs/pipex/excute_minibox.c \
	   srcs/signal.c \
	   srcs/tokenizeing.c \
	   srcs/pipex/redirection_utils.c \
	   srcs/builtins/utilis.c \
	   srcs/pipex/apply_redirections.c \
	   srcs/pipex/run_command.c \
	   srcs/exec_extern.c
INCS = incs/ \
	   Libft/incs/
OBJS = $(patsubst srcs/%.c, objs/%.o, $(SRCS))
DEPS = $(patsubst objs/%.o, deps/%.d, $(OBJS))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LBFT) $(MINIBOX)
	cc $(CC_FLAGS) -o $@ $(OBJS) $(MINIBOX) $(LBFT) -lreadline
	$(info [MAKE $(NAME)] $@ built successfully.)

objs/%.o: srcs/%.c
	mkdir -p $(sort $(dir $@) $(dir $(patsubst objs/%.o, deps/%.d, $@)))
	cc $(CC_FLAGS) -MMD -MP -MF $(patsubst objs/%.o, deps/%.d, $@) $(addprefix -I, $(INCS)) -o $@ -c $<
	$(info [MAKE $(NAME)] $(addprefix $*, .c) compiled successfully.)

$(LBFT):
	$(MAKE) $(MK_FLAGS) -C $(dir $@) 1> /dev/null
	$(info [MAKE $(NAME)] $(dir $@) compiled successfully.)

$(MINIBOX): $(MINIBOX_SRCS)
	$(MAKE) -C $(dir $@)

clean:
	rm -rf $(sort $(dir $(OBJS)) $(dir $(DEPS)))
	$(MAKE) $(MK_FLAGS) -C $(dir $(LBFT)) $@ 1> /dev/null
	$(MAKE) $(MK_FLAGS) -C $(dir $(MINIBOX)) $@
	$(info [MAKE $(NAME)] $(NAME) cleaned successfully.)

fclean: clean
	$(MAKE) $(MK_FLAGS) -C $(dir $(MINIBOX)) $@ 1> /dev/null
	rm -rf $(NAME) $(LBFT) $(MINIBOX)

re: fclean all

-include $(DEPS)
