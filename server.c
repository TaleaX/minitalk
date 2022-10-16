/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 14:40:38 by tdehne            #+#    #+#             */
/*   Updated: 2022/10/11 20:41:04 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	decode_msg(int sig, siginfo_t *info, void *context)
{
	static int				counter = 0;
	static unsigned char	c = 0;
	int						bin;

	if (context)
		;
	bin = 0;
	if (sig == SIGUSR1)
		bin = (1 << counter);
	c |= bin;
	counter++;
	if (counter == 8)
	{
		if (!c)
		{
			kill(info->si_pid, SIGUSR2);
			c = 0;
			counter = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		counter = 0;
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = decode_msg;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}
