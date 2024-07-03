/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:47:40 by phartman          #+#    #+#             */
/*   Updated: 2024/07/03 19:28:53 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


unsigned char	*char_to_binary(char c)
{
	int i;
	int j;
	int k;
	unsigned char* bin;
	bin = malloc(sizeof(unsigned char) * 9);
	if (!bin)
		return (NULL);
	i = 7;
	j = 0;
	while (i >= 0)
	{
		k = (c >> i) & 1;
		bin[j] = '0' + k;
		
		j++;
		i--;
	}
	bin[j]	= '\0';
	return (bin);
}

void signal_handler(int signum)
{
	ft_printf("signal received: %d\n", signum);
}

int	main(int argc, char const *argv[])
{
	int pid;
	const char *msg;
	int result;

	struct sigaction action;

	pid = getpid();
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);

	result = sigaction(SIGUSR1, &action, NULL);
	printf("result: %d\n", result);
	if (argc != 3)
	{
		msg = argv[0];
		ft_printf("%s\n", char_to_binary('O'));
		
	}
	kill(pid, SIGUSR1);

	
	//pid = ft_atoi(argv[1]);
	//msg = argv[2];
	return (0);
}
