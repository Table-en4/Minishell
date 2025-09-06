# Minibox (submodule for Minishell)

This library provides a minimal shell lexing and parsing toolkit.<br/>
Minibox only supports the following operators:<br/>
- `&&`, `||` Logical AND, OR
- `|` Pipe
- `>`, `<`, `>>`, `<<` Redirection (Explicit file descriptors are not supported.)
- `(`, `)` Parenthesis
- `'`, `"` Quotes (Unclosed quotes are not supported.)

## Functions
#### `ft_build_minibox();`
Initializes a `t_minibox` structure by performing input processing, lexing, and parsing on the provided command string `str`.
```c
Protoype: int ft_build_minibox(t_minibox *minibox, const char *str);
Returns: 0 on success.
         -1 if minibox is NULL.
         >0 on a specific error.
```
#### `ft_destroy_minibox();`
Frees all dynamically allocated memory within the `t_minibox` structure.<br/>
The user is responsible for freeing the `t_minibox` struct itself.
```c
Protoype: void ft_destroy_minibox(t_minibox *minibox);
```
#### `ft_display_minibox();`
Prints the contents of the `t_minibox` structure, to the standard output.
```c
Protoype: void ft_display_minibox(const t_minibox *minibox);
```
## Structures
#### `t_minibox`
```c
typedef struct s_minibox
{
    t_miniinput     *input;
    t_minilexing    *lexing;
    t_miniparsing   *parsing;
    t_minierror     error;
}   t_minibox;
```
#### `t_miniinput`
```c
typedef struct s_miniinput
{
	char	*value;
	size_t	length;
}	t_miniinput;
```
#### `t_minilexing`
```c
typedef struct s_minilexing
{
	t_minitoken			token;
	char				*value;
	size_t				length;
	struct s_minilexing	*next;
	struct s_minilexing	*prev;
}	t_minilexing;
```
#### `t_minifd`
```c
typedef struct s_minifd
{
	t_minitype		redir;
	char			*file;
	int				fd;
	struct s_minifd	*next;
	struct s_minifd	*prev;
}	t_minifd;
```
#### `t_miniparsing`
```c
typedef struct s_miniparsing
{
	t_minitype				type;
	t_minifd				*fds;
	size_t					argc;
	char					**argv;
	struct s_miniparsing	*subshell;
	struct s_miniparsing	*left;
	struct s_miniparsing	*right;
}	t_miniparsing;
```
#### `t_minierror`
```c
typedef struct s_minierror
{
	t_minicode	code;
	char		msg[MINIMSG_SIZE];
}	t_minierror;
```
## Enumerations
#### `t_minitoken`
```c
typedef enum e_minitoken
{
	MINITOKEN_REDAPP,
	MINITOKEN_HEREDOC,
	MINITOKEN_AND,
	MINITOKEN_OR,
	MINITOKEN_PIPE,
	MINITOKEN_REDOUT,
	MINITOKEN_REDIN,
	MINITOKEN_LPAREN,
	MINITOKEN_RPAREN,
	MINITOKEN_DQUOTE,
	MINITOKEN_SQUOTE,
	MINITOKEN_UQUOTE,
	MINITOKEN_WSPACE,
	MINITOKEN_SIZE
}   t_minitoken;
```
#### `t_minitype`
```c
typedef enum e_minitype
{
	MINITYPE_AND,
	MINITYPE_OR,
	MINITYPE_PIPE,
	MINITYPE_CMD,
	MINITYPE_SUBSHELL,
	MINITYPE_REDAPP,
	MINITYPE_HEREDOC,
	MINITYPE_REDOUT,
	MINITYPE_REDIN,
	MINITYPE_SIZE
}   t_minitype;
```
#### `MINIMSG_SIZE`
```c
# define MINIMSG_SIZE 256
```
#### `t_minicode`
```c
typedef enum e_minicode
{
	MINICODE_NONE,
	MINICODE_ERRNO,
	MINICODE_INPUT_NULL,
	MINICODE_INPUT_BLANK,
	MINICODE_UNCLOSED_QUOTES,
	MINICODE_UNCLOSED_PARENTHESIS,
	MINICODE_UNDEFINED,
	MINICODE_SIZE
}   t_minicode;
```
## Errors
|ID  |Code                            |Message                                 |
|----|--------------------------------|----------------------------------------|
|0   |`MINICODE_NONE`                 |No error.                               |
|1   |`MINICODE_ERRNO`                |System error (see errno).               |
|2   |`MINICODE_INPUT_NULL`           |Null input.                             |
|3   |`MINICODE_INPUT_BLANK`          |Blank input.                            |
|4   |`MINICODE_UNCLOSED_QUOTES`      |Unclosed quotes.                        |
|5   |`MINICODE_UNCLOSED_PARENTHESIS` |Unclosed parenthesis.                   |
|6   |`MINICODE_UNDEFINED`            |Unknown or undefined error.             |
## Minishell
This library was originally developed as a submodule for the minishell project from 42 school.<br/>
You can find the main repository here: [Minishell](https://github.com/Table-en4/Minishell) by [Table-en4](https://github.com/Table-en4).
