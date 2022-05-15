# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorfanu <lorfanu@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 14:59:38 by lorfanu           #+#    #+#              #
#    Updated: 2022/04/04 14:31:10 by lorfanu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CNAME = client
SNAME = server

SRV = server.c
CLT = client.c
UTILS = ft_utils.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(CNAME) $(SNAME)

$(CNAME): $(CLT) $(UTILS)
		$(CC) $(CFLAGS) $(CLT) $(UTILS) -o client

$(SNAME): $(SRV) $(UTILS)
		$(CC) $(CFLAGS) $(SRV) $(UTILS) -o server

clean:
	rm -f server client

fclean:
	rm -f server client utils

re: fclean all

mandatory: $(CNAME) $(SNAME)

bonus: mandatory

m: mandatory

b: bonus

.PHONY: re clean fclean all mandatory m bonus b
 