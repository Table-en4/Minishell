# Minibox (submodule for Minishell)

This library provides a minimal shell lexing and parsing toolkit.<br/>
Minibox only supports the following operators:<br/>
- `|` Pipe
- `&&`, `||` Logical AND, OR
- `>`, `<`, `>>`, `<<` Redirection (Explicit file descriptors are not supported.)
- `'`, `"` Quotes (Unclosed quotes are not supported.)
- `(`, `)` Parenthesis

## Functions
#### `ft_build_minibox();`
Initializes a `t_minibox` structure by performing input processing, lexing, and parsing on the provided command string `str`.
```c
Protoype: int ft_build_minibox(t_minibox *minibox, const char *str);
Returns: 0 on success.
         -1 if minibox is NULL.
         >0 on a specific error.
```
#### `ft_convert_lexing_to_argv();`
Convert a lexing linked list into a NULL-terminated array of strings, similar to `argv`, which is suitable for use with `execve`.
```c
Protoype: char	**ft_convert_lexing_to_argv(const t_minilexing *lexing);
Returns: NULL-terminated array of strings on success.
         NULL on failure.
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
#### `t_miniparsing`
```c
typedef struct s_miniparsing
{
	t_minitype				type;
	t_minilexing			*lexing;
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
    MINITOKEN_SQUOTE,
    MINITOKEN_DQUOTE,
    MINITOKEN_REDOUT,
    MINITOKEN_REDIN,
    MINITOKEN_LPAREN,
    MINITOKEN_RPAREN,
    MINITOKEN_PIPE,
    MINITOKEN_TEXT,
    MINITOKEN_SIZE
}   t_minitoken;
```
#### `t_minitype`
```c
typedef enum e_minitype
{
    MINITYPE_CMD,
    MINITYPE_AND,
    MINITYPE_OR,
    MINITYPE_PIPE,
    MINITYPE_REDIN,
    MINITYPE_REDOUT,
    MINITYPE_REDAPP,
    MINITYPE_HEREDOC,
    MINITYPE_SUBSHELL,
    MINITYPE_SIZE
}   t_minitype;
```
#### `t_minicode`
```c
typedef enum e_minicode
{
    MINICODE_NONE,
    MINICODE_ERRNO,
    MINICODE_INPUT_NULL,
    MINICODE_UNCLOSED_QUOTES,
    MINICODE_UNDEFINED,
    MINICODE_SIZE
}   t_minicode;
```
## Errors
|ID  |Code                        |Message                                 |
|----|----------------------------|----------------------------------------|
|0   |`MINICODE_NONE`             |No error.                               |
|1   |`MINICODE_ERRNO`            |A system error occurred (see errno).    |
|2   |`MINICODE_INPUT_NULL`       |Input Error: Null or blank input.       |
|3   |`MINICODE_UNCLOSED_QUOTES`  |Lexing Error: Unclosed quotes.          |
|4   |`MINICODE_UNDEFINED`        |Unknown or undefined error.             |
## Minishell
This library was originally developed as a submodule for the minishell project from 42 school.<br/>
You can find the main repository here: [Minishell](https://github.com/Table-en4/Minishell) by [Table-en4](https://github.com/Table-en4).
