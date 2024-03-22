/*
** EPITECH PROJECT, 2024
** B-PSU-200-MAR-2-1-minishell1-leo.gregori
** File description:
** my.h
*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>
#ifndef MY_H
    #define MY_H
int my_put_nbr(int nb);
int my_atoi(char *str);
char my_putchar(char c);
int my_strlen(char const *str);
int my_putstr(char const *str);
int my_put_nbr_recursive(int nb);
char *my_strdup(char const *src);
char **str_to_word_array(char *str);
int my_printf(const char *format, ...);
char *my_strcpy(char *dest, char const *src);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_strcmp2(const char *s1, const char *s2);
char *my_strncpy(char *dest, char const *src, int n);
int my_strncmp(const char *str1, const char *str2, size_t n);
#endif
