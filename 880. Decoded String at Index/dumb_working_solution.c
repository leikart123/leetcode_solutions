#include <string.h>
#include <stdint.h>
/*
You are given an encoded string s. To decode the string to a tape, the encoded string is read one character at a time and the following steps are taken:
If the character read is a letter, that letter is written onto the tape.
If the character read is a digit d, the entire current tape is repeatedly written d - 1 more times in total.
Given an integer k, return the kth letter (1-indexed) in the decoded string.
Example 1:
Input: s = "leet2code3", k = 10
Output: "o"
Explanation: The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".

Example 2:
Input: s = "ha22", k = 5
Output: "h"
Explanation: The decoded string is "hahahaha".
The 5th letter is "h".

Example 3:
Input: s = "a2345678999999999999999", k = 1
Output: "a"
Explanation: The decoded string is "a" repeated 8301530446056247680 times.
The 1st letter is "a".
 
Constraints:
2 <= s.length <= 100
s consists of lowercase English letters and digits 2 through 9.
s starts with a letter.
1 <= k <= 109
It is guaranteed that k is less than or equal to the length of the decoded string.
The decoded string is guaranteed to have less than 263 letters.
*/
/* идея была как всегда использовать первое попавшееся решение
но оказалось, что полностью строку декодить нельзя, очевидно
не декодить тоже вроде как нельзя
если декодить, то среди 45 тесткейсов, которые подаются, можно попасть в лимит по памяти, который в задаче неявно задан
в итоге я решил сначала пройтись по строке
и посчитать, на какой из цифр, умножающих строку, можно закончить
потом попытался немного улучшить решение, понял, что последний раз можно уже и не умножать полностью, тк 
это все будут повторы уже существующей строки
стал в случае, если при умножении получается больше символов, чем k - уменьшать k так, чтобы k становилось 
индексом в уже существующей строке.
Решение прошло, но использовало в последнем кейса 250мб памяти и выполнялось 60мс
Думал что бы такого сделать, интуитивно пришел к решению обнулять цикл, подсчитывающий размер и К заново, после уменьшения К
Почему? не знаю, почувствовал что надо
результат в fast_solution - выполнялось 0мс и 7мб заняло
*/
int multiply_string(char *s, long int *len, int mult, long int *k)
{
    int i = 1;
    if (*len * mult > *k)
    {
        int mult = 1;
        while (*len * mult < *k)
            mult++;
        *k -= *len * (mult - 1);
        return 0;
    }
    while (i < mult)
    {
        memcpy(s + i * *len, s, *len);
        i++;
    }
    *len *= mult;
    return 0;
}

char *decodeAtIndex(char * s, int k){
    long int len = 0;
    long int k2 = k;

    if (!s)
        return NULL;
    int i = 0;
    long int needed_index = 0;
    int mult = 0;
    while (needed_index < k2)
    {
        if (isalpha(s[i]))
            needed_index += 1;
        if (isdigit(s[i]))
        {
            mult = s[i] - '0';
            if (needed_index * mult > k2)
            {
                mult = 1;
                while (needed_index * mult < k2)
                    mult++;
                k2 -= needed_index * (mult - 1);
                break;
            }
            needed_index *= mult;
        }
        i++;
    }
    s[i] = '\0';
    i = 0;
    char *result_str = (char *)malloc(sizeof(char) * k2);
    if (result_str == NULL)
        return NULL;
    memset(result_str, 0, k2);
    while (s[i])
    {
        if (isalpha(s[i]))
        {
            result_str[len] = s[i];
            len++;
        }
        if (isdigit(s[i]))
            multiply_string(result_str, &len, s[i] - '0', &k2);
        if (len >= k2)
            break;
        i++;
    }
    char *r = malloc(2);
    r[0] = result_str[k2 - 1];
    r[1] = '\0';
    free(result_str);
    return r;
}