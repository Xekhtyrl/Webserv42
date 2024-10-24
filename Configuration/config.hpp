/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:00:51 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/24 18:03:28 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <vector>
# include <map>
# include <fstream>

class	ServerConfig;
	
class	Config {
	public:
		Config(int ac, char **av);
		~Config();
		
		// Parsing Methods
		
		bool	hasExtension(std::string filename, std::string extension);
		
		// Getters

		std::vector<int>				getPorts();
		std::map <int, ServerConfig>	getServers();
	
	private:
		std::ifstream					configFile;
		std::vector<int>				usedPorts;
		std::map <int, ServerConfig>	serverConfigs;
};
