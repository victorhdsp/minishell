#include "../../__test/utils.h"
#include "./env.h"

// teste funcs

int	ft_count_arr_size(char **arr)
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
		index++;
	return (index);
}

// Chamada da função get_env sem argumentos
Test(get_env, functions_with_no_args)
{
	char		*env[] = {NULL};
	t_my_env	*ret;
	t_my_env	*expected;

	expected = NULL;
	ret = get_env(env);
	cr_assert(ret == expected, "valor de retorno diferente");
}

// Chamada da função get_env com env mockada
Test(get_env, functions_with_env)
{
	char		*env[] = {"GDMSESSION=ubuntu", "DISPLAY=:0", "SHLVL=1",
				"OLDPWD=/home/rpassos-", "MAIL=rpassos-@student.42.rio"};
	t_my_env	*my_env;
	int			ret;
	int			expected;

	my_env = get_env(env);
	ret = ft_lstsize_env(my_env);
	expected = ft_count_arr_size(env);
	cr_assert(ret == expected, "elementos incompatíveis");
}

// Chamada da função get_env_arr
Test(get_env_arr, functions_with_myenv)
{
	char		*env[] = {"GDMSESSION=ubuntu", "DISPLAY=:0", "SHLVL=1",
				"OLDPWD=/home/rpassos-", "MAIL=rpassos-@student.42.rio"};
	t_my_env	*my_env;
	char		**my_env_arr;
	int			ret;
	int			expected;

	my_env = get_env(env);
	my_env_arr = get_env_arr(my_env);
	ret = ft_lstsize_env(my_env);
	expected = ft_count_arr_size(my_env_arr);
	cr_assert(ret == expected, "elementos incompatíveis");
}
