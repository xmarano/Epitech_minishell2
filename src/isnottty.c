/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell1-leo.gregori
** File description:
** isnottty.c
*/
#include "minishell1.h"
#include "my.h"

static int shell_command2(char **argv, char **env, S_t *s)
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

static void check_basic2(S_t *s)
{
    if (my_strcmp(s->input, "exit") == 0)
        exit(0);
}

static void input_to_arr2(S_t *s, char **env)
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

int echo_command(char **argv, char **env, S_t *s)
{
    DIR *dir;

    input_to_arr2(s, env);
    if (my_strcmp(s->arr[0], "setenv") == 0
    || my_strcmp(s->arr[0], "unsetenv") == 0
    || my_strcmp(s->arr[0], "cd") == 0)
        return check_setenv_cd(argv, env, s);
    check_basic2(s);
    s->str = malloc(my_strlen(s->arr[0]) * sizeof(char));
    dir = opendir(s->arr[0]);
    if (dir != NULL) {
        my_printf("%s: Permission denied.\n", s->arr[0]);
        return 0;
    }
    shell_command2(argv, env, s);
    return 0;
}

static int check_if_is_dir(char **argv, char **env, S_t *s)
{
    struct stat info;

    stat(s->input, &info);
    if (S_ISDIR(info.st_mode) && s->input[0] == '.' && s->input[1] == '/') {
        my_printf("%s: Permission denied.\n", s->input);
        return 1;
    }
    return 0;
}

static int cat_slash_before(S_t *s)
{
    s->execute = malloc(10 * sizeof(char *));
    s->execute[0] = malloc(my_strlen(s->input) + 2 * sizeof(char));
    s->execute[0] = my_strcat(s->execute[0], "./");
    s->execute[0] = my_strcat(s->execute[0], s->input);
    return 0;
}

static int error_architecture(char **env, S_t *s)
{
    execve(s->execute[0], s->execute, env);
    if (errno == 8) {
        my_printf("%s: "ARCHI, s->input);
        exit(3);
    }
    return 0;
}

int execute2(char **argv, char **env, S_t *s)
{
    int fork_info = fork();
    int status;

    if (fork_info == 0) {
        cat_slash_before(s);
        if (check_if_is_dir(argv, env, s) == 1)
            return 0;
        error_architecture(env, s);
    } else {
        wait(&status);
        if (WEXITSTATUS(status) == 3)
            exit(1);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            my_printf("Segmentation fault\n");
            return 0;
        }
    }
    return 1;
}

static int update_env(char **argv, char **env, S_t *s)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (env[i][0] == 'P' && env[i][1] == 'A' &&
        env[i][2] == 'T' && env[i][3] == 'H') {
            path_to_bin(s, env, i);
            return 0;
        }
    }
    return 1;
}

int isnottty(char **argv, char **env, S_t *s)
{
    size_t input_size = 0;

    s->input = malloc(input_size);
    while (getline(&s->input, &input_size, stdin) != -1) {
        if (update_env(argv, env, s) == 1)
            s->arr_path[0] = NULL;
        error_handling_backslash(s);
        if (s->nb == my_strlen(s->input))
            return 0;
        remove_n(s);
        error_handling2(s);
        if (s->nb != 0) {
            my_printf("%s: Command not found.\n", s->arr[0]);
            return 2;
        }
        if (execute2(argv, env, s) == 0)
            return 0;
        echo_command(argv, env, s);
    }
    return 0;
}
