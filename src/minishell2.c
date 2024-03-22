/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell2-leo.gregori
** File description:
** minishell2.c
*/
#include "minishell1.h"
#include "my.h"

static int error_shell2(S_t *s)
{
    DIR *dir;

    for (int i = 0; s->arr[i] != NULL; i++) {
        if (my_strcmp(s->arr[i], ">") == 0 || my_strcmp(s->arr[i], ">>") == 0)
            s->pipe = i;
    }
    if (my_strcmp(s->arr[s->pipe], ">") == 0 && s->arr[s->pipe + 1] == NULL) {
        my_printf("Missing name for redirect.\n");
        return 1;
    }
    dir = opendir(s->arr[s->pipe + 1]);
    if (dir != NULL) {
        my_printf("%s: Is a directory.\n", s->arr[s->pipe + 1]);
        return 1;
    }
    return 0;
}

static int command_test(S_t *s, char **env)
{
    int fork_info = fork();
    int status;

    s->str = my_strcat(s->str, s->arr[0]);
    if (fork_info == 0) {
        for (int i = 0; s->arr_execve[i] != NULL; i++) {
            free(s->arr[0]);
            s->arr[0] = malloc(my_strlen(s->arr_execve[i]) * sizeof(char));
            s->arr[0] = s->arr_execve[i];
            execve(s->arr[0], s->arr, env);
        }
        my_printf("%s: Command not found.\n", s->str);
        exit(2);
    } else {
        wait(&status);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return 0;
    }
}

static void redirection_right(S_t *s, char **env)
{
    int file;
    char *command = s->arr[0];
    int a = my_strcmp(s->arr[s->pipe], ">");

    my_printf("variable a = (%d)\n", a);
    if (a == 0) {
        my_printf("(%s)\n", s->arr[s->pipe + 1]);
        file = open(s->arr[s->pipe + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    } else if (my_strcmp(s->arr[s->pipe], ">>") == 0)
        file = open(s->arr[s->pipe + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    dup2(file, STDOUT_FILENO);
    s->arr[s->pipe] = NULL;
    command_test(s, env);
    close(file);
    return;
}

int minishell2(S_t *s, char **env)
{
    s->pipe = 0;
    if (error_shell2(s) == 1)
        return 1;
    if (my_strcmp(s->arr[s->pipe], ">") == 0
    || my_strcmp(s->arr[s->pipe], ">>") == 0) {
        redirection_right(s, env);
        return 1;
    }
    if (my_strcmp(s->arr[s->pipe], "<") == 0) {
        my_printf("\x1b[38;5;208m" "<\n" "\x1b[0m");
        return 1;
    }
    return 0;
}
