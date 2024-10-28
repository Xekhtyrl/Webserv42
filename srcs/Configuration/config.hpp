/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:00:51 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/24 19:27:27 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <set>
# include <map>
# include <fstream>

class	ServerConfig;
class	Config {
	public:
		Config(int ac, char **av);
		~Config();
		
		// Public Methods
		bool	hasExtension(std::string filename, std::string extension);
		bool	isDirective(std::string token);
		
		// Setters

		void								addPort(int port);
		void								addServer(int port, ServerConfig);
		
		// Getters

		std::set	<int>					getPorts();
		std::map 	<int, ServerConfig>		getServers();
	
	private:
		std::set 	<std::string>			directives;
		std::ifstream						configFile;
		std::set	<int>					usedPorts;
		std::map	<int, ServerConfig>		serverConfigs;
};
