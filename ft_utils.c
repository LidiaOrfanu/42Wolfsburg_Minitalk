/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorfanu <lorfanu@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:57:10 by lorfanu           #+#    #+#             */
/*   Updated: 2022/03/28 15:32:30 by lorfanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(char *nptr)
{
	int	result;
	int	aux;
	int	sign;

	result = 0;
	aux = 0;
	sign = 1;
	while ((*nptr != '\0') && ((*nptr == ' ') || (*nptr == '	')
			|| (*nptr == '\n')
			|| (*nptr == '\v') || (*nptr == '\f') || (*nptr == '\r')))
		nptr++;
	if (*nptr == '-')
	{
		nptr++;
		sign = -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9' && *nptr != '\0')
	{
		aux = *nptr - '0';
		result = result * 10 + aux;
		nptr++;
	}
	return (result * sign);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = (-1) * nb;
		write(fd, "-", 1);
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
