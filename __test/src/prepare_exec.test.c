#include "../utils.h"
#include "../../src/exec/exec.h"
#include "../../src/minishell.h"

void suite_setup_ambient(void) {
    redirect_stderr();
}

void suite_teardown(void) {
}

// Test case: Redirect output to a file
Test(exec_command, test_redirect_output_to_file) {
    char      *filename = "/usr/src/app/__test/local/tmp/test_output.txt";
    t_lexer_item    input[] = {
		{.value = ">", .type = type_outfile, .fn = fn_output},
		{.value = filename, .type = type_word, .fn = fn_null},
		{.value = NULL}
	};
    t_sentence *sentence = create_pipes((t_lexer_item *)input);
    prepare_redirects(sentence);
    int result = access(filename, F_OK);
    cr_assert(result == 0);
    remove(filename);
}

// Test case: Redirect input from a file
Test(exec_command, test_redirect_input_from_file)
{
    char *filename = "/usr/src/app/__test/local/tmp/test_input.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "test input", 10);
    t_lexer_item input[] = {
        {.value = "<", .type = type_infile, .fn = fn_input},
        {.value = filename, .type = type_word, .fn = fn_null},
        {.value = NULL}
    };
    t_sentence *sentence = create_pipes((t_lexer_item *)input);
    prepare_redirects(sentence);
    int result = access(filename, F_OK);
    cr_assert(result == 0);
    remove(filename);
}

// Test case: Invalid file descriptor
Test(exec_command, test_invalid_file_descriptor, .init=suite_setup_ambient, .fini=suite_teardown, .exit_code = 1)
{
    char *filename = "/usr/src/app/__test/local/tmp/test_invalid_fd.txt";
    t_lexer_item input[] = {
        {.value = "<", .type = type_infile, .fn = fn_input},
        {.value = filename, .type = type_word, .fn = fn_null},
        {.value = NULL}
    };
    t_sentence *sentence = create_pipes((t_lexer_item *)input);
    prepare_redirects(sentence);
}


// Test case: Invalid file path
Test(exec_command, test_invalid_file_path, .init=suite_setup_ambient, .fini=suite_teardown, .exit_code = 1)
{
    char *filename = "/invalid/path";
    t_lexer_item input[] = {
        {.value = "<", .type = type_infile, .fn = fn_input},
        {.value = filename, .type = type_word, .fn = fn_null},
        {.value = NULL}
    };
    t_sentence *sentence = create_pipes((t_lexer_item *)input);
    prepare_redirects(sentence);
}

// Test case: Redirect append to a file
Test(exec_command, test_redirect_append_to_file) {
    char      *filename = "/usr/src/app/__test/local/tmp/test_append.txt";
    t_lexer_item    input[] = {
		{.value = ">>", .type = type_outfile, .fn = fn_append},
		{.value = filename, .type = type_word, .fn = fn_null},
		{.value = NULL}
	};
    t_sentence *sentence = create_pipes((t_lexer_item *)input);
    prepare_redirects(sentence);
    int result = access(filename, F_OK);
    cr_assert(result == 0);
    remove(filename);
}

// Test case: Redirect output to a file with invalid path
Test(exec_command, test_redirect_output_to_invalid_file, .init=suite_setup_ambient, .fini=suite_teardown, .exit_code = 1) {
    char      *filename = "/invalid/path/test_output.txt";
    t_lexer_item    input[] = {
        {.value = ">", .type = type_outfile, .fn = fn_output},
        {.value = filename, .type = type_word, .fn = fn_null},
        {.value = NULL}
    };
    t_sentence *sentence = create_pipes((t_lexer_item *)input);
    prepare_redirects(sentence);
    int result = access(filename, F_OK);
    cr_assert(result == -1);
}

// Test case: Redirect input from a file with invalid path
Test(exec_command, test_redirect_input_from_invalid_file, .init=suite_setup_ambient, .fini=suite_teardown, .exit_code = 1) {
    char *filename = "/invalid/path/test_input.txt";
    t_lexer_item input[] = {
        {.value = "<", .type = type_infile, .fn = fn_input},
        {.value = filename, .type = type_word, .fn = fn_null},
        {.value = NULL}
    };
    t_sentence *sentence = create_pipes((t_lexer_item *)input);
    prepare_redirects(sentence);
    int result = access(filename, F_OK);
    cr_assert(result == -1);
}

// Test case: Create HEREDOC file
Test(exec_command, test_create_heredoc_file) {
    char *filename = "/usr/src/app/__test/local/heredoc/heredoc_1";
    char *heredoc_content = "test heredoc content\n";
    char *heredoc_delimiter = "EOF";
    t_lexer_item input[] = {
        {.value = "<<", .type = type_infile, .fn = fn_heredoc},
        {.value = heredoc_delimiter, .type = type_word, .fn = fn_null},
        {.value = NULL}
    };
    t_sentence *sentence = create_pipes((t_lexer_item *)input);
    int fd = fork();
    if (fd == 0)
    {
        prepare_redirects(sentence);
        exit(0);
    }
    write(0, heredoc_content, strlen(heredoc_content));
    write(0, heredoc_delimiter, strlen(heredoc_delimiter));
    usleep(100);
    int result = access(filename, F_OK);
    cr_assert(result == 0, "File not created");
    remove(filename);
}