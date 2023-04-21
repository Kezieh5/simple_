/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if frees, otherwise 0
 */
int bfree(void **ptr)
{
    int result = 0;

    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
        result = 1;
    }

    return result;
}
