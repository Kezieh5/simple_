#include "shell1.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **args)
{
      char *error, *hist_str;
        int len, n;
	char *name = "my_program";
	int hist = 0;


        hist_str = _itoa(hist);
        if (!hist_str)
                return (NULL);

        len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
        error = malloc(sizeof(char) * (len + 1));
        if (!error)
        {
                free(hist_str);
                return (NULL);
        }

        n = snprintf(error, len + 1, "%s: %s: %s: Unable to add/remove from environment\n", name, hist_str, args[0]);
        if (n < 0 || n > len)
        {
                free(hist_str);
                free(error);
                return NULL;
        }

        free(hist_str);
        return (error);
}
/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **args)
{
	char *error;
	int len;
	char *name = "my_program";


	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}
/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **args)
{
    int errnum = atoi(args[0]);
    char *error;
    char *name = "my_program";
    int hist = 0;

    if (errnum < 0 || errnum > 255)
        return NULL;

    error = malloc(sizeof(char) * 50);
    if (!error)
        return NULL;

    sprintf(error, "%s: %d: exit: Illegal number: %s\n", name, hist, args[0]);

    return error;
}
/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_cd(char **args)
{
	char *error, *hist_str;
	int len;
	char *name = "my_program";
	int hist = 0;
	

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}
/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **args)
{
    char *error;
    int len;
    char *name = "my_program";
    int hist = 0;

    len = snprintf(NULL, 0, "%s: %d: Syntax error: \"%s\" unexpected\n", name, hist, args[0]) + 1;
    error = malloc(len);
    if (!error)
    {
        return NULL;
    }

    snprintf(error, len, "%s: %d: Syntax error: \"%s\" unexpected\n", name, hist, args[0]);

    return error;
}
