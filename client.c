/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 07:15:50 by tdehne            #+#    #+#             */
/*   Updated: 2022/10/11 20:46:18 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	void	received(int sig)
{
	static int	received_sig;

	if (sig == SIGUSR1)
		++received_sig;
	else
	{
		ft_putnbr_fd(received_sig, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static	void	send_msg(int pid, char *str)
{
	char	c;
	int		counter;

	while (*str)
	{
		c = *str;
		counter = 8;
		while (counter--)
		{
			if (c & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			c = c >> 1;
			usleep(40);
		}
		str++;
	}
	c = 8;
	while (c--)
	{
		kill(pid, SIGUSR2);
		usleep(40);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc == 3)
	{
		ft_putstr_fd("Sent    : ", 1);
		ft_putnbr_fd(ft_strlen(argv[2]), 1);
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("Received: ", 1);
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = &received;
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
		send_msg(ft_atoi(argv[1]), argv[2]);
		while (1)
			pause();
	}
	return (0);
}
