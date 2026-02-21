#ifndef PARSER_H
#define PARSER_H

enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,           // |
    TOKEN_REDIR_IN,       // <
    TOKEN_REDIR_OUT,      // >
    TOKEN_REDIR_APPEND,   // >>
    TOKEN_HEREDOC,        // <<
    TOKEN_AND,            // &&
    TOKEN_OR,             // ||
    TOKEN_EOF
};

typedef struct s_token
{
    enum e_token_type   type;
    char                *value;
    struct s_token      *next;
}   t_token;


enum e_token_type  get_operator_type(char *str);
int is_operator(char c);
int get_operator_len(char *str);
int is_whitespace(char c);
int is_word_char(char c);

#endif