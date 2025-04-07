#include "env_management.h"

void print_lst(t_my_env *ordered_head)
{
    while (ordered_head)
    {
        printf("declare -x %s", ordered_head->key);
        if (ordered_head->equal && *ordered_head->equal)
        {
            printf("=\"%s\"", ordered_head->value);
            
        }
        printf("\n");
        ordered_head = ordered_head->next;
    }
}

int ft_unset(t_my_env **my_env, char **word)
{
    t_my_env *current;
    t_my_env *prev;
    
    if (!word)
        return (0);
    current = *my_env;
    prev = NULL;
    while (current)
    {
        if (ft_strcmp(current->key, word) == 0)
        {
            if (prev == NULL)
                *my_env = current->next;
            else
                prev->next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return (0);
        }
        prev = current;
        current = current->next;
    }
    return (0);
}

