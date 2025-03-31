#include "export.h"

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

void order(t_my_env *my_env)
{
    t_my_env *tmp;
    t_my_env *ordered_head;
    t_my_env *new_node;
    char **env_arr;
    int index;

    index = 0;
    if (!my_env)
        return;
    env_arr = get_env_arr(my_env);
    ordered_head = ft_lstnew_env(env_arr[index]);
    my_env = my_env->next;
    index++;
    while (my_env)
    {
        new_node = ft_lstnew_env(env_arr[index]);
        if (ft_strcmp(new_node->key, ordered_head->key) < 0)
        {
            new_node->next = ordered_head;
            ordered_head = new_node;
        }
        else 
        {
            tmp = ordered_head;
            
            while (tmp->next && ft_strcmp(tmp->next->key, new_node->key) < 0)
                tmp = tmp->next;
            new_node->next = tmp->next;
            tmp->next = new_node;
        }
        index++;
        my_env = my_env->next;
    }
    print_lst(ordered_head);
    ft_clean_arr(env_arr);
    ft_lstclear_env(&ordered_head);
}



/*PRINT:

RENATO

export: declare -x RENATO
env: n aparece

REN=

export: declare -x REN=""
env: REN=

export: sem = n aparece nem = nem ""
        com = aparece ""

env: sem = nao aparece
    com = aparece o =
*/


int check_valid_name(char *word)
{
    int index;

    index = 1;
    if (!word)
        return (0);
    if (word[0] != '_' && !ft_isalpha(word[0]))
    {
            printf("export: '%s': not a valid identifier", word);
            return (0);
    }
    while (word[index] != '\0')
    {
        if (word[index] != '_' && word[index] != '=' && !ft_isalnum(word[index]))
        {
            printf("export: '%s': not a valid identifier", word);
            return (0);
        }
        index++;
    }
    return (1);
}

int check_overwriting(t_my_env *my_env, char *word)
{
    char    *value;
    char    *key;
    
    value = ft_strchr(word, '=');
    key = ft_calloc(value - word + 1, sizeof(char));
	key = ft_memmove(key, word, value - word);    
    while (my_env)
    {
        if (my_env && ft_strncmp(my_env->key, key, value - word) == 0)
        {
            free(my_env->value);
            my_env->value = ft_strdup(value + 1);
            free(key);
            return (0);
        }
        my_env = my_env->next;
    }
    free(key);
    return (1);
}

int ft_export(t_my_env **my_env, char *word)
{
    t_my_env *new_node;

    if (!word)
        order(*my_env);
    if (!check_valid_name(word))
        return (0);
    if (check_overwriting(*my_env, word))
    {
        new_node = ft_lstnew_env(word);
        ft_lstadd_back_env(&(*my_env), new_node);
        //ft_lstclear_env(&new_node);
    }
    return (0);
}
