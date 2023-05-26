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

	if (info->argv[1])  /* If there is an exit arguement */
	{ 
		print_error(info, "exit: ");
	
		return 1;
	}
	free_info(info, 1);
	exit (EXIT_SUCCESS);
}

/**
 * _mycd - Changes the current directory of the process
 * @info: The info_t structure
 * Return: 0 on success, 1 on failure
 */
int _mycd(info_t *info)
{
	char *dir = info->argv[1];
	char *pwd = _getenv(info, "PWD");

	if (!dir)
	{
		dir = _getenv(info, "HOME");
		if (!dir)
		{
			fprintf(stderr, "cd: No home directory found\n");
			return 1;
		}
	}

	if (_strcmp(dir, "-") == 0)
	{
		char *oldpwd = _getenv(info, "OLDPWD");
		if (!oldpwd)
		{
			fprintf(stderr, "cd: No previous directory found\n");
			return 1;
		}
		dir = oldpwd;
		printf("%s\n", dir);
	}

	int chdir_ret = chdir(dir);
	if (chdir_ret == -1)
	{
		perror("cd");
		return 1;
	}

	char buffer[PATH_MAX];
	char *cwd = getcwd(buffer, PATH_MAX);
	if (!cwd)
	{
		perror("getcwd");
		return 1;
	}

	_setenvm(info, "OLDPWD", pwd);
	_setenvm(info, "PWD", cwd);

	return 0;
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
