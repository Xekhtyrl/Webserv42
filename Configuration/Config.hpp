/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:51:42 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/29 18:51:45 by alexphil         ###   ########.fr       */
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
		bool		isRule(std::string token);
		bool		indentLevel(size_t level);
		bool		isCommentLine(std::string line);
		
		void		processDirective(int port, std::vector <std::string> tokens);
		void		processRule(int port, std::string route, std::vector <std::string> tokens);	
		
		// Setters

		void		addPort(int port);
		void		addServer(int port, ServerConfig serverConfig);
		
		// Getters

		std::set	<int>					getPorts();
		std::map 	<int, ServerConfig>		getServers();
	
	private:
		std::ifstream						configFile;
		std::string							line;
		
		std::set 	<std::string>			directives;
		std::set 	<std::string>			rules;
		
		std::set	<int>					usedPorts;
		std::map	<int, ServerConfig>		serverConfigs;
};
