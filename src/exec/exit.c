#include "../../inc/minishell.h"

//comment for real test
//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <string.h>
//#####################

//int	exit_code;

long long	ft_atoll(const char	*str)
{
	int		i;
	long long	sign;
	long long	tot;

	i = 0;
	sign = 1;
	tot = 0;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		tot = tot * 10 + (str[i] - '0');
		i++;
	}
	return (tot * sign);
}

int	invalid_exit_arg(char *arg)
{
	(void)arg;
	write(2, "exit : numeric argument required\n", 34);
	return (0);
}

int	is_exit_arg_valid(char *arg)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(arg);					//ft_strlen
	if (arg[i] != '-' && (arg[i] < '0' || arg[i] > '9'))
		return (invalid_exit_arg(arg));
	if ((arg[i] == '-' && size > 20) || (arg[i] != '-' && size > 19))
		return (invalid_exit_arg(arg));
	while (arg[++i])
	{
		if (arg[i] <  '0' || arg[i] > '9')
			return (invalid_exit_arg(arg));
	}
	return (1);
}

int	get_formated_status(char *arg)
{
	long long	formated_status;

	if (is_exit_arg_valid(arg) == 0)
		return (2);
	formated_status = ft_atoll(arg);
	if (formated_status < 0)
		formated_status = 256 - ((-formated_status) % 256);
	else
		formated_status %= 256;
	return ((int)formated_status);

}

int	ft_exit(int ac, char **av)
{
	int	status;

	status = 2;
	if (ac == 1)
		exit(exit_code);
	if (ac > 2)
	{
		write(2, "Too many arguments\n", 20);
		return (1);
	}
	status = get_formated_status(av[1]);
	printf("exit_status = %d\n", status);
	exit(status);
	return (0);
}

/*int	main(int ac, char **av)
{
	int test;
	exit_code = 127;
	test = ft_exit(ac, av);
	printf("[-%d-]\n", test);
	return (0);
}*/
