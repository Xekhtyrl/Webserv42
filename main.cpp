/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:39:55 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/24 17:38:36 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"
# include "ServerConfig.hpp"
# include "RouteConfig.hpp"

int	main(int ac, char **av) {
	
	Config conf(ac, av);
	
	std::map<int, ServerConfig> srvrsConf;
	srvrsConf = conf.getServers();
	
	ServerConfig srvConf = srvrsConf[42];

	if (srvConf["/campus"][INDEX])
		std::string	indexFile = srvConf["/campus"].getIndex();
	if (srvConf["/42"][REDIRECT])
		std::string redirectAddr = srvConf["/42"].getRedirect();;
	if (srvConf[404])
		std::string notFoundFile = srvConf.getErrorPage(404);
}
