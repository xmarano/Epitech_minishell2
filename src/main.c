/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell1-leo.gregori
** File description:
** main.c
*/
#include "minishell1.h"
#include "my.h"

void path_to_bin(S_t *s, char **env, int i)
{
    char *path = NULL;
    int j = 0;

    for (int a = 0; env[a] != NULL; a++)
        j = a;
    s->env2 = malloc(j * sizeof(char *));
    for (int a = 0; env[a] != NULL; a++) {
        s->env2[a] = malloc(my_strlen(env[a]) * sizeof(char));
        s->env2[a] = my_strcat(s->env2[a], env[a]);
    }
    j = 0;
    s->arr_path = malloc(100 * sizeof(char *));
    path = strtok(s->env2[i] + 5, ":");
    while (path != NULL) {
        s->arr_path[j] = malloc(my_strlen(path) * sizeof(char));
        s->arr_path[j] = path;
        s->arr_path[j] = my_strcat(s->arr_path[j], "/");
        path = strtok(NULL, ":");
        j++;
    }
}

int shell(char **argv, char **env)
{
    S_t s;

    for (int i = 0; env[i] != NULL; i++) {
        if (env[i][0] == 'P' && env[i][1] == 'A' &&
        env[i][2] == 'T' && env[i][3] == 'H')
            path_to_bin(&s, env, i);
    }
    if (isatty(0)) {
        istty(argv, env, &s);
    } else {
        return isnottty(argv, env, &s);
    }
    free(s.input);
    return 0;
}

int main(int argc, char **argv, char **env)
{
    if (argc != 1)
        return 84;
    return shell(argv, env);
}

static void cd_alone(char **env, char *str)
{
    int nb = 0;
    int i = 0;

    for (; env[nb] != NULL; nb++) {
        if (my_strncmp(env[nb], "HOME=", 5) == 0)
            break;
    }
    str = malloc(my_strlen(env[nb]) * sizeof(char));
    for (; env[nb][i + 5] != '\0'; i++)
        str[i] = env[nb][i + 5];
    str[i] = '\0';
    i = 0;
    for (; env[nb] != NULL; nb++) {
        if (my_strncmp(env[nb], "PWD=", 4) == 0)
            break;
    }
    for (; str[i] != '\0'; i++)
        env[nb][i + 4] = str[i];
    env[nb][i + 4] = '\0';
    chdir(str);
}

static int cd_dir_to_env(char **env, S_t *s, char *str)
{
    DIR *dir;
    int nb = 0;

    dir = opendir(str);
    if (dir == NULL)
        return 1;
    closedir(dir);
    for (; env[nb] != NULL; nb++) {
        if (my_strncmp(env[nb], "PWD=", 4) == 0)
            break;
    }
    if (str[0] != '.') {
        env[nb] = my_strcat(env[nb], "/");
        env[nb] = my_strcat(env[nb], str);
    }
    return 0;
}

static int cd_dir_check(S_t *s, char *str, int *i)
{
    if (s->arr[1][0] == '.' && s->arr[1][1] == '/') {
        if (s->arr[1][2] == '\0') {
            str = my_strcpy(str, ".");
            *i = 1;
            return 0;
        }
        for (; s->arr[1][(*i) + 2] != '\0'; (*i)++) {
            str[(*i)] = s->arr[1][(*i) + 2];
        }
        return 0;
    }
    return 1;
}

static int cd_dir(char **env, S_t *s)
{
    int i = 0;
    char *str = malloc(my_strlen(s->arr[1]) * sizeof(char));

    if (cd_dir_check(s, str, &i) == 1) {
        for (; s->arr[1][i] != '\0'; i++)
            str[i] = s->arr[1][i];
    }
    str[i] = '\0';
    if (cd_dir_to_env(env, s, str) == 1) {
        chdir(str);
        return 1;
    }
    chdir(str);
    return 0;
}

static int cd_old_to_new(char **env, S_t *s)
{
    char *pwd;
    int nb = 0;
    int pwd_0;
    char *old_chdir;

    for (; env[nb] != NULL; nb++) {
        if (my_strncmp(env[nb], "PWD=", 4) == 0)
            break;
    }
    pwd = malloc((my_strlen(env[nb]) + 1) * sizeof(char));
    for (int i = 0; env[nb + 1][i + 3] != '\0'; i++) {
        pwd[i] = env[nb + 1][i + 3];
        pwd_0 = i + 3;
    }
    pwd[pwd_0 + 1] = '\0';
    env[nb] = pwd;
    old_chdir = malloc(my_strlen(env[nb]) * sizeof(char));
    old_chdir_func(env, old_chdir, pwd_0, nb);
    chdir(old_chdir);
    return 0;
}

static int cd_file(S_t *s)
{
    int a;

    a = open(s->arr[1], O_RDONLY);
    if (a == -1) {
        my_printf("%s: No such file or directory.\n", s->arr[1]);
        return 0;
    }
    my_printf("%s: Not a directory.\n", s->arr[1]);
    close(a);
    return 0;
}

int do_cd(char **argv, char **env, S_t *s)
{
    char *str;

    if (s->arr[2] != NULL) {
        my_printf("cd: string not in pwd: %s\n", s->arr[1]);
        return 1;
    }
    if (s->arr[1] == NULL) {
        cd_alone(env, str);
        return 0;
    }
    if (cd_dir(env, s) == 0)
        return 0;
    if (s->arr[1][0] == '-' && cd_old_to_new(env, s) == 0)
        return 0;
    cd_file(s);
    return 1;
}
