#include "export.h"

char	**ft_clean_arr(char **result)
{
	int	index;

	index = 0;
	while (result && result[index])
	{
		free(result[index]);
		index++;
	}
	free(result);
	result = NULL;
    return(result);
}

void	ft_lstclear_env(t_my_env **lst)
{
	t_my_env	*current;

	current = *lst;
	while (*lst)
	{
		current = *lst;
        free(current->key);
		if (current->value)
            free(current->value);
		*lst = current->next;
		free(current);
	}
    *lst = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

t_my_env	*ft_lstlast_env(t_my_env *lst)
{
	t_my_env	*current;

	current = lst;
	if (current)
		while (current->next)
			current = current->next;
	return (current);
}

void	ft_lstadd_back_env(t_my_env **lst, t_my_env *new)
{
	t_my_env	*current;

	if (*lst)
	{
		current = ft_lstlast_env(*lst);
		current->next = new;
	}
	else
		*lst = new;
}
