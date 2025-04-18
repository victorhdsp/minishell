#include "../../__test/utils.h"
#include <criterion/criterion.h>
#include "traitement.h"

void suite_setup_traitement(void) {
    char		*env[] = {"A=victor", "B=renato", NULL};
	t_system	new_sys;

	new_sys.name = "test";
	new_sys.last_exit_status = 0;
	new_sys.env = env;
	get_system(&new_sys);
}

// Tests for functions in quote.c
Test(quote, test_quote_traitement) {
    char *input = strdup("\"Hello, World!\"");
    char *expected = "Hello, World!";
    char **breaked = word_breaker(input);
    t_lexer_item *lexed = lexer(breaked);
    quote_traitement(lexed);

    cr_assert_str_eq(lexed[0].value, expected, "Expected '%s' but got '%s'", expected, lexed[0].value);

    free(input);
    free(lexed[0].value);
}

Test(quote, test_quote_traitement_no_quotes) {
    char *input = strdup("NoQuotesHere");
    char *expected = "NoQuotesHere";
    char **breaked = word_breaker(input);
    t_lexer_item *lexed = lexer(breaked);
    quote_traitement(lexed);

    cr_assert_str_eq(lexed[0].value, expected, "Expected '%s' but got '%s'", expected, lexed[0].value);

    free(input);
    free(lexed[0].value);
}

// Tests for functions in variable.c
Test(variable, test_variable_traitement, .init=suite_setup_traitement) {
    char *input = strdup("Hello, $A!");
    char *expected = "victor!";
    char **breaked = word_breaker(input);
    t_lexer_item *lexed = lexer(breaked);
    variable_traitement(lexed);

    cr_assert_str_eq(lexed[1].value, expected, "Expected '%s' but got '%s'", expected, lexed[1].value);

    free(input);
    free(lexed[1].value);   
}

Test(variable, test_variable_traitement_no_variable, .init=suite_setup_traitement) {
    char *input = strdup("Hello, World!");
    char *expected = "Hello,";
    char **breaked = word_breaker(input);
    t_lexer_item *lexed = lexer(breaked);
    variable_traitement(lexed);

    cr_assert_str_eq(lexed[0].value, expected, "Expected '%s' but got '%s'", expected, lexed[0].value);

    free(input);
    free(lexed[0].value);
}

Test(variable, test_variable_traitement_multiple_variables, .init=suite_setup_traitement) {
    char *input = strdup("$A@$B");
    char *expected = "victor@renato"; 
    char **breaked = word_breaker(input);
    t_lexer_item *lexed = lexer(breaked);
    variable_traitement(lexed);

    cr_assert_str_eq(lexed[0].value, expected, "Expected '%s' but got '%s'", expected, lexed[0].value);

    free(input);
    free(lexed[1].value);
}