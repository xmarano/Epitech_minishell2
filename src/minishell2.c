/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell2-leo.gregori
** File description:
** minishell2.c
*/
#include "minishell1.h"
#include "my.h"

static void redirection_right(S_t *s)
{
    return;
}

int minishell2(S_t *s)
{
    if (my_strcmp(s->arr[1], ">") == 0) {
        redirection_right(s);
        return 1;
        }
    if (my_strcmp(s->arr[1], "<") == 0) {
        my_printf("\x1b[38;5;208m" "<\n" "\x1b[0m");
        return 1;
        }
    return 0;
}
