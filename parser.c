#include "parser.h"
#include "minishell.h"

static t_token *new_token(enum e_token_type type, char *value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = ft_strdup(value);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
    token->next = NULL;
    return (token);
}

static  void add_token(t_token **head, t_token *new_token)
{
    t_token *current;

    if (!head || !new_token)
        return ;
    if (*head == NULL)
    {
        *head = new_token;
        return ;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

static int skip_whitespace(char *line, int i)
{
    while (line[i] && is_whitespace(line[i]))
        i++;
    return (i);
}

static char *extract_word(char *line, int *i)
{
    char    *word;
    int     start;
    int     len;
    int     j;

    start = *i;
    len = 0;
    j = start;
    
    while (line[j] && !is_whitespace(line[j]) && !is_operator(line[j]))
    {
        if (line[j] == '\\' && line[j + 1])
        {
            j += 2;
            len += 2;
        }
        else if (line[j] == '\'' || line[j] == '"')
        {
            char quote = line[j];
            j++;
            len++;
            while (line[j] && line[j] != quote)
            {
                if (line[j] == '\\' && line[j + 1] && quote == '"')
                    j += 2;
                else
                    j++;
                len++;
            }
            if (line[j] == quote)
            {
                j++;
                len++;
            }
        }
        else
        {
            j++;
            len++;
        }
    }
    
    word = (char *)malloc(len + 1);
    if (!word)
        return (NULL);
    ft_strncpy(word, line + start, len);
    word[len] = '\0';
    *i = j;
    
    return (word);
}

t_token *tokenize(char *line)
{
    t_token     *tokens;
    char        *word;
    int         i;
    int         operator_len;
    enum e_token_type operator_type;

    tokens = NULL;
    i = 0;
    
    while (line[i])
    {
        i = skip_whitespace(line, i);
        if (!line[i])
            break;
        
        if (is_operator(line[i]))
        {
            operator_len = get_operator_len(line + i);
            operator_type = get_operator_type(line + i);
            
            word = (char *)malloc(operator_len + 1);
            if (!word)
                return (tokens); 
            ft_strncpy(word, line + i, operator_len);
            word[operator_len] = '\0';
            
            add_token(&tokens, new_token(operator_type, word));
            free(word);
            i += operator_len;
        }
        else
        {
            word = extract_word_advanced(line, &i);
            if (word)
            {
                add_token(&tokens, new_token(TOKEN_WORD, word));
                free(word);
            }
        }
    }
    
    add_token(&tokens, new_token(TOKEN_EOF, ""));
    
    return (tokens);
}