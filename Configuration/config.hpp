/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:00:51 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/28 17:13:30 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <set>
# include <map>
# include <vector>
# include <fstream>
# include <sstream>

# include "ServerConfig.hpp"
# include "RouteConfig.hpp"

class	Config {
	public:
		Config(int ac, char **av);
		
		// Methods
		
		bool		hasExtension(std::string filename, std::string extension);
		bool		isDirective(std::string token);
		bool		indentLevel(std::string line, size_t level);
		bool		isCommentLine(std::string line);
		
		void		parseServerConfig();
		void		parseDirective(ServerConfig serverConfig, std::vector <std::string> tokens);
		
		void		parseRouteConfig(ServerConfig serverConfig, std::string route);
		
		
		// Setters

		void								addPort(int port);
		void								addServer(int port, ServerConfig serverConfig);
		
		// Getters

		std::set	<int>					getPorts();
		std::map 	<int, ServerConfig>		getServers();
	
	private:
		std::ifstream						configFile;
		std::string							line;
		
		std::set 	<std::string>			directives;
		
		std::set	<int>					usedPorts;
		std::map	<int, ServerConfig>		serverConfigs;
};
