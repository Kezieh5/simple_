#include "shell1.h"

char *error_126(char **args);
char *error_127(char **args);
/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **args)
{
    char *error;
    char *name = "my_program";
    int hist = 0;
    int len;

    len = snprintf(NULL, 0, "%s: %d: %s: Permission denied\n", name, hist, args[0]) + 1;
    error = malloc(len * sizeof(char));
    if (!error)
    {
        return (NULL);
    }

    snprintf(error, len, "%s: %d: %s: Permission denied\n", name, hist, args[0]);

    return (error);
}
/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int hist = 0;
	char *name = "my_program";
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
