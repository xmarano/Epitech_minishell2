/*
** EPITECH PROJECT, 2023
** my_strcmp
** File description:
** Infos
*/

int my_strcmp(const char *s1, const char *s2)
{
    int result = 0;
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            result = s1[i] - s2[i];
            break;
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0')
        return 0;
    else
        return result;
}
