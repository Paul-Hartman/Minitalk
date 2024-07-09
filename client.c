/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@strudent.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:47:40 by phartman          #+#    #+#             */
/*   Updated: 2024/07/10 00:08:13 by phartman         ###   ########.fr       */
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

void send_binary_as_signal(int pid, unsigned char *binary)
{
	int	i;

	i = 0;
	while(binary[i])
	{
		if (binary[i] == '0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(100000);
	}

}


int	main(int argc, char const *argv[])
{
	int pid;
	const char *msg;
	int result;
	char *binary;

	if (argc != 3)
	{
		ft_printf("wrogn number of args\n");
		return 1;
	}
	pid = ft_atoi(argv[1]);
	msg = argv[2];

	while(msg)
	{	
		binary = char_to_binary(*msg);
		send_binary_as_signal(pid, binary);
		msg++;
		free(binary);
	}
	return (0);
}
