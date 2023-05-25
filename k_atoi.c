#include "main.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);

}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
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
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{


		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * reverse_string - reverses a string
 * @s: the string to be reversed
 */
void reverse_string(char *s)
{
	if (s == NULL)
		return;

	int i, j;
	char temp;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

/**
 * itoa - converts an integer to a string
 * @num: the integer to be converted
 * @str: the destination string
 * @base: the base for conversion
 *
 * Return: pointer to the resulting string
 */
char *itoa(int num, char *str, int base)
{
	if (str == NULL)
		return NULL;

	int i = 0;
	int is_negative = 0;

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	if (num < 0 && base == 10)
	{
		is_negative = 1;
		num = -num;
	}

	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	if (is_negative)
		str[i++] = '-';

	str[i] = '\0';

	reverse_string(str);

	return str;
}
