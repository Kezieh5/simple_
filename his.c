#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
    char *dir = _getenv(info, "HIME=");
    if (!dir)
        return NULL;
    
    size_t buf_size = _strlen(dir) + _strlen(HIST_FILE) + 2;
    char *buf = malloc(buf_size);
    if (!buf)
        return NULL;
    
    snprintf(buf, buf_size, "%s/%s", dir, HIST_FILE);
    free(dir);
    
    return buf;
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return -1;

    size_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return -1;
    
    list_t *node = info->history;
    while (node)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
        node = node->next;
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);
    
    return 1;
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: history on success, 0 otherwise
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;

    size_t fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return 0;
    
    struct stat st;
    if (fstat(fd, &st) == -1)
        return close(fd), 0;
    
    size_t fsize = st.st_size;
    char *buf = malloc(fsize + 1);
    if (!buf)
        return close(fd), 0;
    
    ssize_t rdlen = read(fd, buf, fsize);
    close(fd);
    if (rdlen == -1)
        return free(buf), 0;
    
    buf[rdlen] = '\0';
    int linecount = 0;
    char *line = strtok(buf, "\n");
    while (line)
    {
        build_history_list(info, line, linecount++);
        line = strtok(NULL, "\n");
    }
    free(buf);
    
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&info->history, 0);
    renumber_history(info);
    
    return info->histcount;
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: parameter struct
 * @buf: buffer
 * @linecount: the history line count, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = add_node_end(&info->history, buf, linecount);
    if (!info->history)
        info->history = node;
    
    return 0;
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: parameter struct
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
    int n = 0;
    for (list_t *node = info->history; node != NULL; node = node->next) {
        node->num = n++;
    }
    info->histcount = n;
    return n;
}
