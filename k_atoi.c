#include "main.h"
#include <stdio.h>

/**
 * interactive - This returns true if shell is interactive mode
 * @info: This is a struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This is to check if character is a delimeter
 * @c: This is the char to check
 *
 * @delim: This is the delimeter string
 * Return: 1 if true, 0 if false
 */

int is_delim(char c, char delim)
{
	return (c == delim);
}

/**
 * _isalpha - This checks for alphabetic character
 * @c: This is the character to input
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - This converts a string to an integer
 * @s: This is the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
