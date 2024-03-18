/*
** EPITECH PROJECT, 2023
** my_strncmp
** File description:
** Infos
*/
#include "../src/my.h"

int my_strncmp(const char *str1, const char *str2, size_t n)
{
    while (n && *str1 && *str2) {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
        n--;
    }
    if (n == 0)
        return 0;
    else
        return (*str1 - *str2);
}
