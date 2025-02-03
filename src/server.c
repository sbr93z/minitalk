/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:22:13 by sferrad           #+#    #+#             */
/*   Updated: 2025/01/29 18:55:01 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	free_data(t_data *data)
{
	if (data->str)
	{
		free(data->str);
		data->str = NULL;
	}
	data->count = 0;
	data->bits = 0;
	data->pos = 0;
	data->msg_size = 0;
	data->capacity = 64;
	data->str = malloc(sizeof(char) * data->capacity);
	if (!data->str)
		exit(1);
}

void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(1);
	(*data)->capacity = 64;
	(*data)->count = 0;
	(*data)->bits = 0;
	(*data)->pos = 0;
	(*data)->msg_size = 0;
	(*data)->str = malloc(sizeof(char) * (*data)->capacity);
	if (!(*data)->str)
		exit(1);
}

void	handle_realloc(t_data *data)
{
	char	*new_str;
	int		i;

	i = 0;
	if (data->capacity == 0)
		data->capacity = 64;
	else
		data->capacity *= 2;
	new_str = malloc(sizeof(char) * data->capacity);
	if (!new_str)
		return ;
	if (!data->str)
	{
		data->str = new_str;
		return ;
	}
	while (i < data->msg_size)
	{
		new_str[i] = data->str[i];
		i++;
	}
	free(data->str);
	data->str = new_str;
}

void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	static t_data	*data;

	(void)context;
	if (!data)
		init_data(&data);
	if (signum == SIGUSR2)
		data->bits = ((data->bits << 1) | 1);
	else
		data->bits = ((data->bits << 1));
	data->count++;
	if (data->count == 8)
	{
		if ((data->msg_size + 1) > data->capacity)
			handle_realloc(data);
		data->str[data->pos++] = data->bits;
		data->msg_size++;
		data->count = 0;
		if (data->bits == '\0')
		{
			ft_printf("%s\n", data->str);
			free_data(data);
		}
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)ac;
	(void)av;
	sa.sa_sigaction = handle_sigint;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID = %d\n", getpid());
	while (1)
		pause();
	return (0);
}
