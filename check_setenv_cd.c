/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell1-leo.gregori
** File description:
** check_setenv_cd.c
*/
#include "minishell1.h"
#include "my.h"

static void add_setenv(char **env, S_t *s)
{
    for (int i = 0; env[i] != NULL; i++)
        s->last = i;
    s->new_line = malloc(my_strlen(s->arr[1] + 1 * sizeof(char)));
    s->new_line = my_strcat(s->new_line, s->arr[1]);
    s->new_line = my_strcat(s->new_line, "=");
    if (s->arr[2] != NULL)
        s->new_line = my_strcat(s->new_line, s->arr[2]);
    env[s->last + 1] = s->new_line;
    env[s->last + 2] = NULL;
}

static int check_if_already_exist_and_modify(char **env, S_t *s, int j)
{
    int check = 0;

    for (int k = 0; s->arr[1][k] != '\0'; k++) {
        if (s->arr[1][k] != env[j][k])
            break;
        if (env[j][k + 1] == '=' && s->arr[1][k + 1] == '\0') {
            s->env_2_modify = j;
            check = 1;
        }
    }
    if (check == 1) {
        env[s->env_2_modify] = s->arr[1];
        env[s->env_2_modify] = my_strcat(env[s->env_2_modify], "=");
        if (s->arr[2] != NULL)
            env[s->env_2_modify] = my_strcat(env[s->env_2_modify], s->arr[2]);
        return 1;
    }
    return 0;
}

static int setenv_error_modify_add(char **argv, char **env, S_t *s)
{
    if (s->arr[1][0] < 65 || s->arr[1][0] > 90 && s->arr[1][0] < 97
    || s->arr[1][0] > 122) {
        write(2, "setenv: Variable name must begin with a letter.\n", 49);
        return 1;
    }
    for (int i = 1; s->arr[1][i] != '\0'; i++) {
        if (s->arr[1][i] > 9 && s->arr[1][i] < 65 || s->arr[1][i] > 90
        && s->arr[1][i] < 97 || s->arr[1][i] > 122) {
            write(2, "setenv: Variable name must contain ", 36);
            write(2, "alphanumeric characters.\n", 26);
            return 1;
        }
    }
    for (int j = 0; env[j] != NULL; j++) {
        if (check_if_already_exist_and_modify(env, s, j) == 1)
            return 0;
    }
    add_setenv(env, s);
    return 0;
}

int do_setenv(char **argv, char **env, S_t *s)
{
    int nb_args = 0;

    for (int i = 0; s->arr[i] != NULL; i++)
        nb_args = i;
    if (nb_args == 0) {
        for (int i = 0; env[i] != NULL; i++)
            my_printf("%s\n", env[i]);
        return 0;
    }
    if (nb_args > 2) {
        write(2, "setenv: Too many arguments.\n", 29);
        return 1;
    }
    if (setenv_error_modify_add(argv, env, s) == 1)
        return 1;
    return 0;
}

static void unsetenv_replace(char **env, S_t *s)
{
    int nb_env = 0;

    for (int i = 0; env[i + 1] != NULL; i++) {
        my_printf("\x1b[38;5;208m" "boo\n" "\x1b[0m");
        if (env[i][0] == '\0') {
            env[i] = env[i + 1];
            env[i + 1] = "\0";
        }
        nb_env = i + 1;
    }
    env[nb_env] = NULL;
}

static void env_modify(char **env, S_t *s, int i, int j)
{
    while (env[j + 1] != NULL) {
        env[j] = my_strcpy(env[j], env[j + 1]);
        j++;
    }
    env[j] = NULL;
}

static int unsetenv_modify(char **env, S_t *s, int i, int j)
{
    for (int k = 0; s->arr[i][k] != '\0'; k++) {
        if (s->arr[i][k] != env[j][k])
            return 0;
        if (s->arr[i][k + 1] == '\0' && env[j][k + 1] == '=')
            return 1;
    }
    return 0;
}

void do_unsetenv2(char **env, S_t *s, int i, int j)
{
    if (unsetenv_modify(env, s, i, j) == 1) {
        env_modify(env, s, i, j);
        return;
    }
}

int do_unsetenv(char **argv, char **env, S_t *s)
{
    int nb_args = 0;

    for (int i = 0; s->arr[i] != NULL; i++)
        nb_args = i;
    if (nb_args == 0) {
        write(2, "unsetenv: Too few arguments.\n", 30);
        return 1;
    }
    for (int i = 1; s->arr[i] != NULL; i++) {
        for (int j = 0; env[j] != NULL; j++) {
            do_unsetenv2(env, s, i, j);
        }
    }
    return 0;
}

int check_setenv_cd(char **argv, char **env, S_t *s)
{
    if (my_strcmp(s->arr[0], "setenv") == 0)
        return do_setenv(argv, env, s);
    if (my_strcmp(s->arr[0], "unsetenv") == 0)
        return do_unsetenv(argv, env, s);
    if (my_strcmp(s->arr[0], "cd") == 0)
        return do_cd(argv, env, s);
    return 0;
}
