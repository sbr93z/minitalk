/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:22:10 by sferrad           #+#    #+#             */
/*   Updated: 2025/01/29 19:01:12 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile sig_atomic_t	g_signal_received = 0;

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_signal_received = 1;
}

static void	handle_error(void)
{
	ft_printf("ERROR");
	exit(0);
}

int	ft_send_char(char c, pid_t serv_pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_signal_received = 0;
		if ((c >> i & 1) && kill(serv_pid, SIGUSR2) == -1)
			handle_error();
		else if (!(c >> i & 1) && kill(serv_pid, SIGUSR1) == -1)
			handle_error();
		while (!g_signal_received)
			pause();
		i--;
	}
	return (1);
}

pid_t	init_pid(int ac, char **av)
{
	pid_t	serv_pid;

	if (ac != 3)
	{
		ft_printf("Error : Arguments\n");
		exit(0);
	}
	serv_pid = ft_atoi(av[1]);
	if (serv_pid <= 0)
	{
		ft_printf("Error : PID\n");
		exit(0);
	}
	return (serv_pid);
}

int	main(int ac, char **av)
{
	int		i;
	pid_t	serv_pid;

	signal(SIGUSR1, signal_handler);
	i = 0;
	serv_pid = init_pid(ac, av);
	while (av[2][i])
	{
		if (!ft_send_char(av[2][i], serv_pid))
			return (0);
		i++;
	}
	ft_send_char('\0', serv_pid);
	return (0);
}
