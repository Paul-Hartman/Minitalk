/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:47:40 by phartman          #+#    #+#             */
/*   Updated: 2024/07/03 17:04:31 by phartman         ###   ########.fr       */
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

int	main(int argc, char const *argv[])
{
	//int pid;
	//char *msg;

	if (argc != 3)
	{
		ft_printf("write %s\n", argv[0]);
		ft_printf("%s\n", char_to_binary('O'));
		
	}
	//pid = ft_atoi(argv[1]);
	//msg = argv[2];
	return (0);
}
