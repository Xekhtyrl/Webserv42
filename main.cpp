/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:39:55 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/30 13:24:38 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>

# include "Config.hpp"
# include "ServerConfig.hpp"
# include "RouteConfig.hpp"

int	main(int ac, char **av) {
	
	Config config(ac, av);
	
	std::map<int, ServerConfig> srvConfs = config.getServers();
	
	std::cout << std::boolalpha << "\n";
	
	std::cout << srvConfs[42].getHost() << ":";
	std::cout << srvConfs[42].getPort() << "\n\n";
	
	std::cout << srvConfs[42].getErrorPage(403) << "\n";
	std::cout << srvConfs[42].getErrorPage(404) << "\n";
	
	std::cout << srvConfs[42].getClientMaxBodySize() << "\n";
	
	std::cout << srvConfs[42]["/methods"].isMethodAllowed(GET) << "\n";
	std::cout << srvConfs[42]["/methods"].isMethodAllowed(POST) << "\n";
	std::cout << srvConfs[42]["/methods"].isMethodAllowed(DELETE) << "\n";
	
	std::cout << srvConfs[42]["/42"].getRedirect() << "\n";
	
	std::cout << srvConfs[42]["/pictures"].getRoot() << "\n";

	std::cout << srvConfs[42]["/cloud"].hasAutoindex() << "\n";

	std::cout << srvConfs[42]["/index"].getIndex() << "\n";

	std::cout << srvConfs[42]["/sendfeetpics"].getUpload() << "\n\n";

	std::cout << srvConfs[19].getHost() << ":";
	std::cout << srvConfs[19].getPort() << "\n\n";

	std::cout << srvConfs[80].getHost() << ":";
	std::cout << srvConfs[80].getPort() << "\n\n";

	return (0);
}
