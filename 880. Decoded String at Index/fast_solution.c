#include <string.h>

int multiply_string(char *s, long int *len, int mult, long int *k)
{
    int i = 1;

    while (i < mult)
    {
        memcpy(s + i * *len, s, *len);
        i++;
    }
    *len *= mult;
    return 0;
}

long int get_size(char  *s, long int k)
{
    int i = 0;
    long int needed_size = 0;
    int mult = 0;

    while (needed_size < k)
    {
        if (isalpha(s[i]))
            needed_size += 1;
        if (isdigit(s[i]))
        {
            mult = s[i] - '0';
            if (needed_size * mult > k)
            {
                mult = 1;
                while (needed_size * mult < k)
                    mult++;
                k -= needed_size * (mult - 1);
                needed_size = 0;
                i = -1;
            }
            needed_size *= mult;
        }
        i++;
    }
    s[i] = '\0';
    return k;
}

char *decodeAtIndex(char * s, int k){
    long int len = 0;
    int i = 0;

    if (!s)
        return NULL;
    k = get_size(s, k);
    i = 0;
    char *result_str = (char *)malloc(sizeof(char) * k);
    if (result_str == NULL)
        return NULL;
    memset(result_str, 0, k);
    while (s[i])
    {
        if (isalpha(s[i]))
        {
            result_str[len] = s[i];
            len++;
        }
        if (isdigit(s[i]))
            multiply_string(result_str, &len, s[i] - '0', &k);
        if (len >= k)
            break;
        i++;
    }
    char *r = malloc(sizeof(char) * 2);
    r[0] = result_str[k - 1];
    r[1] = '\0';
    free(result_str);
    return r;
}