#include "main.h"

/**
 * _myexit - This exits the shell
 * @info: This structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: The exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int _myexit(info_t *info)
{
	int exit_c;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_c = _erratoi(info->argv[1]);
		if (exit_c == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - The changes the current directory of the process
 * @info: This structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */

int _mycd(info_t *info)
{
	char *k, *m, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!k)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!m)
			chdir_ret = /* TODO: what should this be? */
				chdir((m = _getenv(info, "PWD=")) ? m : "/");
		else
			chdir_ret = chdir(m);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(k);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - The changes the current directory of the process
 * @info: The Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */

int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
