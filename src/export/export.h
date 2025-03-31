#ifndef EXPORT_H
# define EXPORT_H

# include "../../include/libft/libft.h"
# include "../env/env.h"
# include <stdio.h>
# include <stdlib.h>

char	**ft_clean_arr(char **result);
void	ft_lstclear_env(t_my_env **lst);
int		ft_export(t_my_env **my_env, char *word);
int		ft_strcmp(char *s1, char *s2);


#endif