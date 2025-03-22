#include <readline/readline.h>
#include <readline/history.h>

int     main(void)
{
    char    *result;

    result = readline("test2: ");
    printf("O resultado foi: %s\n", result);
    return (1);
}
