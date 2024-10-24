/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:39:55 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/24 17:14:52 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"
# include "Server.hpp"
# include "Route.hpp"

int	main(int ac, char **av) {
	
	Config config(ac, av);
	
	std::map<int, Server> srvrs;
	srvrs = config.getServers();
	
	Server srv = srvrs[42];

	if (srv["/campus"][INDEX])
		std::string	indexFile = srv["/campus"].getIndex();
	if (srv["/42"][REDIRECT])
		std::string redirectAddr = srv["/42"].getRedirect();;
	if (srv[404])
		std::string notFoundFile = srv.getErrorPage(404);
}
