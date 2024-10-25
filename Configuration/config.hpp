/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:00:51 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/25 20:09:59 by alexphil         ###   ########.fr       */
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
		~Config();
		
		// Methods
		
		bool		hasExtension(std::string filename, std::string extension);
		void		processTokens(std::vector <std::string> tokens);
		bool		isDirective(std::string token);
		bool		indentLevel(std::string line, size_t level);
		void		parseServerConfig();
		void		parseRouteConfig(ServerConfig serverConfig, std::string route);
		void		parseDirective(std::vector <std::string> tokens);
		bool		isCommentLine(std::string line);
		
		// Setters

		void								addPort(int port);
		void								addServer(int port, ServerConfig serverConfig);
		
		// Getters

		std::set	<int>					getPorts();
		std::map 	<int, ServerConfig>		getServers();
	
	private:
		std::ifstream						configFile;
		std::set 	<std::string>			directives;
		std::set	<int>					usedPorts;
		std::map	<int, ServerConfig>		serverConfigs;
};
