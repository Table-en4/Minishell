CC_FLAGS =  -g3 -MMD -MP
MK_FLAGS = --silent
MAKEFLAGS += $(MK_FLAGS)

NAME = minishell.a
LBFT = Libft/libft.a

SRCS = srcs/main.c srcs/builtins/ft_echo.c srcs/builtins/ft_cd.c \
	srcs/builtins/env_init.c srcs/builtins/env_node.c srcs/builtins/env_utils.c \
	srcs/exec_builtin.c

INCS = incs Libft/incs

OBJS = $(patsubst srcs/%.c, objs/%.o, $(SRCS))
DEPS = $(patsubst objs/%.o, deps/%.d, $(OBJS))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LBFT)
	cc $(CC_FLAGS) -o $@ $^ -lreadline 
	$(info [MAKE] $@ built successfully.)

objs/%.o: srcs/%.c
	mkdir -p $(sort $(dir $@) $(dir $(patsubst objs/%.o, deps/%.d, $@)))
	cc $(CC_FLAGS) -MF $(patsubst objs/%.o, deps/%.d, $@) $(addprefix -I, $(INCS)) -o $@ -c $<
	$(info [MAKE] $(addprefix $*, .c) compiled successfully.)

$(LBFT):
	$(MAKE) $(MK_FLAGS) -C $(dir $@) 1> /dev/null
	$(info [MAKE] $(dir $@) compiled successfully.)

clean:
	rm -rf $(sort $(dir $(OBJS)) $(dir $(DEPS)))
	$(MAKE) $(MK_FLAGS) -C $(dir $(LBFT)) $@ 1> /dev/null
	$(info [MAKE] $(NAME) cleaned successfully.)

fclean: clean
	rm -rf $(NAME) $(LBFT)

re: fclean all

-include $(DEPS)