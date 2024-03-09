#include "minishell.h"
#include "parsing.h"

int is_in_quotes(char *line, size_t *i, char quote)
{
    size_t  j;

    j = *i + 1;
    while (line[j] && line[j] != quote)
        j++;
    if (!line[j])
        return (EXIT_FAILURE);
    *i = j;
    return (EXIT_SUCCESS);
}

char    check_redirection(char *line, size_t *i, char c)
{
    size_t  j;

    j = *i;
    if (line[j] != c)
        return ('\0');
    while (line[j] && line[j] == c)
        j++;
    if (j - *i > 2)
        return (c);
    if (line[j] == '\0')
        return ('\n');
    return ('\0');
}

char    have_invalid_token(char *line)
{
    const char  *invalid_token = ";\\";
    char        c;
    size_t  i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            c = line[i];
            if (is_in_quotes(line, &i, c) == EXIT_FAILURE)
                return (c);
        }
        c = check_redirection(line, &i, '>');
        if (c)
            return (c);
        c = check_redirection(line, &i, '<');
        if (c)
            return (c);
        if (strchr(invalid_token, line[i]))
            return (line[i]);
        i++;
    }
    return ('\0');
}

