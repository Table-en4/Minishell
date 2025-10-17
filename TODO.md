## TODO
Non-exhaustive list of everything that needs to be done or repaired.

### minishell:

> AND (`&&`) and OR (`||`) logic combination.</br>
> Currently
> ```
> /home/user/Documents/minishell> true && false || true || true && echo SUCCESS
> /home/user/Documents/minishell>
> ```
> Target
> ```
> bash-5.1$ true && false || true || true && echo SUCCESS
> SUCCESS
> bash-5.1$
> ```

### minibox:

> #### Expand values ​​between each command execution.</br>
> Currently
> ```
> /home/user/Documents/minishell> unset DUMMY
> /home/user/Documents/minishell> export DUMMY=dummy && echo $DUMMY
>
> /home/user/Documents/minishell>
> ```
> Target
> ```
> bash-5.1$ unset DUMMY
> bash-5.1$ export DUMMY=dummy && echo $DUMMY
> dummy
> bash-5.1$
> ```

> #### Expand the values ​​on each file descriptor.</br>
> Currently
> ```
> /home/user/Documents/minishell> export DUMMY=dummy
> /home/user/Documents/minishell> cat << EOF
> heredoc> $DUMMY
> heredoc> EOF
> $DUMMY
> /home/user/Documents/minishell> cat << 'EOF'
> heredoc> $DUMMY
> heredoc> EOF
> $DUMMY
> /home/user/Documents/minishell>
> ```
> Target
> ```
> bash-5.1$ export DUMMY=dummy
> bash-5.1$ cat << EOF
> > $DUMMY
> > EOF
> dummy
> bash-5.1$ cat << 'EOF'
> > $DUMMY
> > EOF
> $DUMMY
> bash-5.1$
> ```
