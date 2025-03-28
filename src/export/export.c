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
        if (ft_strcmp(new_node->key, ordered_head->key) < 0) // verifica se new_node vem antes do head
        {
            new_node->next = ordered_head;
            ordered_head = new_node;
        }
        //if (ft_strcmp(new_node->key, ordered_head->key) == 0)
          //  continue;
        else 
        {
            tmp = ordered_head;
            // aqui ele percorre a tmp até achar a posição correta - se não tiver mais tmp->next o nó entra no final. se ele for menor que o tmp->next entra no meio deles.
            while (tmp->next && ft_strcmp(tmp->next->key, new_node->key) < 0)
                tmp = tmp->next;
            new_node->next = tmp->next;
            tmp->next = new_node;
        }
        index++;
       // ft_lstclear_env(&new_node);
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

/*int find_equal(char *word)
{
    int index;

    index = 0;
    while(word[index] != '\0')
    {
        if (word[index] == '=')
            return (index); //RETORNA A POSIÇÃO QUE ACHOU O =
        index++;
    }
    return (0);
}*/

/*int check_valid_name(char *word)
{
    
}*/

/*int check_doubles(t_my_env *lst, char *key)
{
    int equal_pos;

    equal_pos = find_equal(key);
    if (equal_pos == 0)
        equal_pos = ft_strlen(key);
    while (lst)
    {
        if (ft_strncmp(lst->expanded, key, equal_pos) == 0)
            return (1);
        lst = lst->next;
    }
    return (0);

}*/

int ft_export(t_my_env *my_env, char *word)
{
    if (!word)
        order(my_env);

    /*if (!find_equal(word))
    {
        if (!check_valid_name(word) && check_doubles(env_data.export_lst, word));
            //error();
        new_node = lst_new(word);
        ft_lstadd_back(env_data.export_lst, new_node);
    }
    if (!check_valid_name(word) && check_doubles(env_data.env_lst, word));
            //error();
    new_node = lst_new(word);
    ft_lstadd_back(env_data.env_lst, new_node);*/
    
    return (0);


}
