/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:39:55 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/22 18:08:12 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"
# include "Server.hpp"
# include "Route.hpp"

int	main(int ac, char **av) {
	Config	config;

	if (ac > 2)
		exit (1);
	else if (ac == 2)
		config.parse(av[1]);
	else
		config.parse("webserv.conf");	
}
