/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell1-leo.gregori
** File description:
** isnottty2.c
*/
#include "minishell1.h"
#include "my.h"

void error_handling_backslash(S_t *s)
{
    s->nb = 0;
    for (int i = 0; s->input[i] != '\0'; i++) {
        if (s->input[i] == ' ' || s->input[i] == '\t' || s->input[i] == '\n')
            s->nb++;
    }
}

void error_handling2(S_t *s)
{
    s->nb = 0;
    for (int i = 0; s->input[i] != '\0'; i++) {
        if (s->input[i] < 0 || s->input[i] > 127)
            s->nb++;
    }
}

void remove_n(S_t *s)
{
    int n = 0;

    for (int i = 0; s->input[i] != '\0'; i++)
        n = i;
    if (s->input[n] == '\n')
        s->input[n] = '\0';
}

void old_chdir_func(char **env, char *old_chdir, int pwd_0, int nb)
{
    for (int i = 0; env[nb][i + 4] != '\0'; i++) {
        old_chdir[i] = env[nb][i + 4];
        pwd_0 = i;
    }
    old_chdir[pwd_0 + 1] = '\0';
}
