/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorfanu <lorfanu@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:20:58 by lorfanu           #+#    #+#             */
/*   Updated: 2022/04/04 15:04:42 by lorfanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

/*
** This function is a helper for the process_and_confirm function
** Is being called when a signal is received and verifies the bit:
** if the signal received is a 0 or a 1 and returns 0 / 1
*/

int	check_bit(int sig)
{
	int	i;

	i = 0;
	if (sig == SIGUSR1)
		return (i);
	if (sig == SIGUSR2)
		return (i + 1);
	else
		exit(EXIT_FAILURE);
}

/*
** This fction is called every time the server receives a signal from client:
** SIGUSR1 (which represents a 0) or SIGUSR2 (which represents a 1)
** By getting these signals from client, server is able to process and
** recreate the message (receiving it bit by bit: 0, 1), using bitwise ops.
** This function is also sending back a signal to the client when 1 byte
** has been received (after displaying it to the output) and re-setting
** c to 0.
** After receiveing the '\0', the confirmation is sent to the client
** and then the server is getting ready to receive another message
** from another client by re-setting the client_pid to 0.
** The signal sent in this case is SIGUSR2 -> which is catched by the 
** client (function receipt_confirmation)
*/

static void	process_and_confirm(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	c += (check_bit(sig) << i);
	if (++i == 8)
	{
		i = 0;
		if (c == '\0')
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			ft_putchar_fd('\n', 1);
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
}

/*
** Main function of the server
**
** Starts by setting up the fction that will receive the signals from the client:
** sigaction() - is used instead of signal in order to be able to use the param
** 'info->si_pid' (needed to get the pid of the sender: client).
** Once setting up is done, the function getpid() is used:
** to output its pid (the server pid) - which we use later
** The function enters in an infinite loop waiting for signals from the client
*/

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = &process_and_confirm;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
