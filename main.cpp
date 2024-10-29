/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:39:55 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/29 16:41:05 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"
# include "ServerConfig.hpp"
# include "RouteConfig.hpp"

int	main(int ac, char **av) {
	
	Config config(ac, av);
	
	std::map<int, ServerConfig> srvConfs = config.getServers();
	
	ServerConfig srvConf = srvConf[42];

	if (srvConf["/campus"][INDEX])
		std::string	indexFile = srvConf["/campus"].getIndex();
	if (srvConf["/42"][REDIRECT])
		std::string redirectAddr = srvConf["/42"].getRedirect();;
	if (srvConf[404])
		std::string notFoundFile = srvConf.getErrorPage(404);
}
