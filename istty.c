/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell1-leo.gregori
** File description:
** istty.c
*/
#include "minishell1.h"
#include "my.h"

void shell_command(char **argv, char **env, S_t *s)
{
    int fork_info = fork();

    if (fork_info == 0) {
        for (int i = 0; s->arr_execve[i] != NULL; i++) {
            free(s->arr[0]);
            s->arr[0] = malloc(my_strlen(s->arr_execve[i]) * sizeof(char));
            s->arr[0] = s->arr_execve[i];
            execve(s->arr[0], s->arr, env);
        }
        if (s->input[0] != '.' && s->input[0] != '/')
            my_printf("%s: Command not found.\n", s->input);
        exit(0);
    } else {
        wait(NULL);
    }
}

static void check_basic(S_t *s)
{
    if (my_strcmp(s->input, "exit") == 0)
        exit(0);
}

void input_to_arr(S_t *s, char **env)
{
    s->arr = malloc(50 * sizeof(char *));
    s->arr = str_to_word_array(s->input);
    s->arr_execve = malloc(100 * sizeof(char *));
    for (int i = 0; s->arr_path[i] != NULL; i++) {
        s->arr_execve[i] = malloc(my_strlen(s->arr_path[i])
        + my_strlen(s->arr[0]) * sizeof(char));
        s->arr_execve[i] = my_strcat(s->arr_execve[i], s->arr_path[i]);
        s->arr_execve[i] = my_strcat(s->arr_execve[i], s->arr[0]);
    }
    return;
}

void execute(char **argv, char **env, S_t *s)
{
    int pid_fork = fork();

    if (pid_fork == 0) {
        s->execute = malloc(10 * sizeof(char *));
        s->execute[0] = malloc(my_strlen(s->input) + 2 * sizeof(char));
        s->execute[0] = my_strcat(s->execute[0], "./");
        s->execute[0] = my_strcat(s->execute[0], s->input);
        execve(s->execute[0], s->execute, env);
        return;
    } else {
        wait(NULL);
    }
}

static void error_handling(S_t *s)
{
    s->nb = 0;
    s->nb2 = 0;
    for (int i = 0; s->input[i] != '\0'; i++) {
        if (s->input[i] == ' ' || s->input[i] == '\t' || s->input[i] == '\n')
            s->nb++;
    }
    for (int i = 0; s->input[i] != '\0'; i++) {
        if (s->input[i] < 0 || s->input[i] > 127)
            s->nb2++;
    }
}

static void program(char **argv, char **env, S_t *s)
{
    int n = 0;

    for (int i = 0; s->input[i] != '\0'; i++)
        n = i;
    s->input[n] = '\0';
    if (s->nb2 != 0) {
        my_printf("%s: Command not found.\n", s->input);
    } else {
        execute(argv, env, s);
        input_to_arr(s, env);
        check_basic(s);
        shell_command(argv, env, s);
    }
}

void istty(char **argv, char **env, S_t *s)
{
    size_t input_size = 0;

    while (1) {
        my_printf("\x1b[38;5;208m" "➤  " "\x1b[36m" "~ " "\x1b[0m");
        s->input = malloc(input_size);
        getline(&s->input, &input_size, stdin);
        error_handling(s);
        if (s->nb != my_strlen(s->input))
            program(argv, env, s);
    }
    return;
}
