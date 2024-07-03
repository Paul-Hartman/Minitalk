/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/03 17:54:44 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main(int argc, char const *argv[])
{
	int pid;
	if(argc != 1)
	{
		ft_printf("write %s\n", argv[0]);
		return 1;
	}
	pid = getpid();
	ft_printf("pid: %d\n", pid);
	return 0;
}
