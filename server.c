/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 14:40:38 by tdehne            #+#    #+#             */
/*   Updated: 2022/10/03 19:23:55 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// static void handle_sig(int sig)
// {
// 	static int				counter;
// 	static unsigned char	c;
// 	int						bin;

// 	bin = 0;
// 	if (sig == SIGUSR1)
// 		bin = ++bin << counter;
// 	c |= bin;
// 	if(++counter == 7)
// 	{
// 		ft_putchar_fd(c, 1);
// 		counter = 0;
// 		c = 0;
// 	}
// }

static void	decode_msg(int sig, siginfo_t *info, void *context)
{
	static int				counter = 0;
	static unsigned char	c = 0;
	int						bin;

	bin = 0;
	if (sig == SIGUSR1)
		bin = (1 << counter);
	//printf("before %d\t", c);
	fprintf(stderr, "before %d\t", c);
	c |= bin;
	fprintf(stderr, "after %d counter %d\t", c, counter);
	//printf("after %d\n", c);
	counter++;
	if(counter == 7)
	{
		if (!c)
		{
			kill(info->si_pid, SIGUSR2);
			c = 0;
			counter = 0;
			return ;
		}
		printf("%d\t", c);
		ft_putchar_fd(c, 1);
		fprintf(stderr, "\n");
		counter = 0;
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int main(void)
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
