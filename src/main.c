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

int do_cd(char **argv, char **env, S_t *s)
{
    if (s->arr[2] != NULL) {
        my_printf("cd: string not in pwd: %s\n", s->arr[1]);
        return 1;
    }
    my_printf("%s: Not a directory.\n", s->arr[1]);
    return 1;
}
