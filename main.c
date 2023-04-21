#include "shell.h"

/**
 * Frees memory used by the data structure.
 *
 * @param datash Pointer to the data structure.
 */
void free_data_structure(data_shell *datash)
{
	unsigned int v;

	for (v = 0; datash->_environ[v]; v++)
	{
		free(datash->_environ[v]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * Initializes the data structure.
 *
 * @param datash Pointer to the data structure.
 * @param av Argument vector.
 */
void initialize_data_structure(data_shell *datash, char **av)
{
	unsigned int z;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (z = 0; environ[z]; z++)
		;

	datash->_environ = malloc(sizeof(char *) * (z + 1));

	for (z = 0; environ[z]; z++)
	{
		datash->_environ[z] = _strdup(environ[z]);
	}

	datash->_environ[z] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * Entry point of the program.
 *
 * @param ac Argument count.
 * @param av Argument vector.
 *
 * @return 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	initialize_data_structure(&datash, av);
	shell_loop(&datash);
	free_data_structure(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
