/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell1-leo.gregori
** File description:
** minishell1.h
*/
#include "my.h"
#ifndef MINISHELL1_H
    #define MINISHELL1_H
    #define ARCHI "Exec format error. Wrong Architecture.\n"

typedef struct S {
    char *input;
    char **arr;
    char **arr_path;
    char **arr_execve;
    char **execute;
    int nb;
    int nb2;
    char **env2;
    int last;
    char *new_line;
    char **env_copy;
    int env_2_modify;
    char *str;
} S_t;

int minishell2(S_t *s);
void remove_n(S_t *s);
void error_handling2(S_t *s);
void error_handling_backslash(S_t *s);
int do_cd(char **argv, char **env, S_t *s);
void path_to_bin(S_t *s, char **env, int i);
void istty(char **argv, char **env, S_t *s);
int isnottty(char **argv, char **env, S_t *s);
int check_setenv_cd(char **argv, char **env, S_t *s);
void old_chdir_func(char **env, char *old_chdir, int pwd_0, int nb);
#endif
