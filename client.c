/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorfanu <lorfanu@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:20:52 by lorfanu           #+#    #+#             */
/*   Updated: 2022/04/04 15:07:45 by lorfanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

/*
** This function is the signal handler for signal()
** As long as the signal that was caught is SIGUSR1
** the received variable is increased
** When the server is signaling that has received the '\0' (with SIGUSR2)
** the "received" confirmation will be displayed and the program is
** succesfully ending with exit.
*/

static void	receipt_confirmation(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else if (sig == SIGUSR2)
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

/*
** Helper function for send_message that handles the null
** character - is sending 8 times the SIGUSR1 (0) signal
*/

static void	ft_handle_null(int bit, int pid)
{
	bit = 0;
	while (bit <= 7)
	{
		kill (pid, SIGUSR1);
		bit++;
		usleep(100);
	}
}

/*
** This fction takes as parameters:
** the pid of the server 
** *str being the message passed in the command line by the user
** While the function hasn't reached the '\0', every single character
** is being processed with the function send_signals (bit by bit)
** SIGUSR2 is it's a 1, and SIGUSR1 if it's a 0
** Then with the helper function (handle_null), 8 SIGUSR1 are being sent to
** the server (null character in binary = 00000000)
** usleep: suspends the execution for microsecond intervals
**
*/

static void	send_message(int pid, char *str)
{
	int	i;
	int	bit;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		bit = 0;
		while (bit <= 7)
		{
			if (str[i] >> bit & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			bit++;
			usleep(100);
		}
		i++;
	}
	ft_handle_null(bit, pid);
}

/*
** Main function for the client
** argc - argument counter
** argv - command line parameters given to client by user
** correct format: ./client <pid> <message>
** First it checks if the command line parameters given by the user are correct
** if the pid has an incorrect format or one parameter is missing:
** it displays the error message and the program exits with EXIT_FAILURE
** If the param. are correct, the programm is displaying the number of the
** bits that have been sent and displays 'Received'
** The program continues running and prepares itself to receive either
** SIGUSR1 (as long as the character received by the server is != '\0')
** SIGUSR2 (when the end of the string has been reached, by receiving
** this, the client is being acknowledged that all the bytes have been received)
** When a signal is received -> the receipt_confirmation function is being called
** once the signals are received
** After setting the signal() functions, using the fction send_message the client
** is starting to send the string one bit at a time
** After sending the first bit & making the first contact with the server
** the client enters and infinite loop of pause(), waiting for SIGUSR signals 
** from the server.
**/

int	main(int argc, char **argv)
{
	if (argc != 3 || (ft_atoi(argv[1]) < 1))
	{
		write(1, "Ntz ntz ntz, please give me a correct input.", 45);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, receipt_confirmation);
	signal(SIGUSR2, receipt_confirmation);
	send_message(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
