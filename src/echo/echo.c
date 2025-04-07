#include "echo.h"

int check_consecutive_n(char *word)
{
    int index;

    index = 1;
    while (word[index] != '\0')
    {
        if (word[index] != 'n')
            return (0);
        index++;
    }
    return (1);
}
int check_no_args(char *ret, char *data)
{
    if (!data)
    {
        ret = ft_strjoin(ret, "\n");
        printf("\n");
        return (0);
    }
    return (1);
}

int check_args(char **ret, char **data, int *flag_beginning, int *index, int *flag_check)
{
    if (!ft_strncmp(data[*index], "-n", 2) && !*flag_beginning)
    {
        while (data[*index] && !ft_strncmp(data[*index], "-n", 2))
        {
            if (!check_consecutive_n(data[*index])) //achou algo diferente de n
            {
                *ret = ft_strjoin(*ret, data[*index]);
                *ret = ft_strjoin(*ret, " ");
                printf("%s ", data[*index]); 
                (*index)++;
                break;
            }
            (*index)++;
            *flag_check = 1;
        }
    }
    *flag_beginning = 1;
    if (!data[*index])
        return (0);
    *ret = ft_strjoin(*ret, data[*index]);
    printf("%s", data[*index]);
    return (1);
}

char *ft_echo(int ac, char **data)
{
    int index;
    int flag_check;
    int flag_not_at_beginning;
    char *ret;

    ret = (char *)malloc(sizeof(char) * 1000);
    ret[0] = '\0';
    
    index = 1;
    flag_check = 0;
    flag_not_at_beginning = 0;
    //if (!check_no_args(ret, data[index]))
    //    return (0);
    while (data[index] != NULL)
    {
        if (!check_args(&ret, data, &flag_not_at_beginning, &index, &flag_check))
            break;
        if (index != ac - 1)
        {
            ret = ft_strjoin(ret, " ");
            printf(" ");
        }
        index++;
    }
    if (!flag_check)
    {
        ret = ft_strjoin(ret, "\n");
        printf("\n");
    }
    return (ret);
}
