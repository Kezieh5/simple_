#include "shell1.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
    int len = 1;
    if (num < 0) {
        len++;
        num = -num;
    }
    while (num >= 10) {
        len++;
        num /= 10;
    }
    return len;
}
/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
    static char str[12]; /*max length of int as string is 11*/
    int len = num_len(num);
    int digit = num % 10;

    if (num < 0) {
        str[0] = '-';
        num = -num;
        len++;
    }
    if (num == 0) {
        str[len - 1] = '0';
        str[len] = '\0';
        return str;
    }
    str[len - 1] = digit + '0';
    str[len] = '\0';
    _itoa(num / 10);
    return str;
}
/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *error_2_exit(char **args);
        char *error_2_syntax(char **args);
        char *error_2_cd(char **args);
	char* error_126(char** args);
	char* error_127(char** args);
	char* error_1(char** args);
	char* error_env(char** args);


	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
