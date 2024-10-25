/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:21:09 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/24 19:32:11 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"
# include "ServerConfig.hpp"

Config::Config(int ac, char **av) {
	if (ac > 2)
		exit(1); // TODO: Throw proper exception
	if (ac == 2)
		if (hasExtension(av[1], ".conf"))
			configFile.open(av[1]);
			// TODO: Catch open failure exception
		// TODO: Bad file exception
	else
		configFile.open("webserv.conf"); // Open default config
		// TODO: Catch failure exception
	
	// Specify Directives Set
	directives.insert("listen");
	directives.insert("server_name");
	directives.insert("error_page");
	directives.insert("allow");
	directives.insert("redirect");
	directives.insert("root");
	directives.insert("autoindex");
	directives.insert("index");
	
	// TODO: parseConfigFile();
}

Config::~Config() {
	if (configFile.is_open())
		configFile.close();
}

//	PUBLIC METHODS

bool	Config::hasExtension(std::string filename, std::string extension) {
	size_t	filenameLenght = filename.length();
	size_t	extensionLenght = extension.length();
	return (filename.substr(filenameLenght - extensionLenght) == extension);
}

bool	Config::isDirective(std::string token) {
	return (directives.find(token) != directives.end());
}

// void	Config::parseConfigFile() {
// 	;
// > Read line by line
// > Tokenize each string separated by either space or tab
//// > Have a min and max expected tokens per given directive ?
// > Populate the configs from the parsing
// }

// SETTERS

void							Config::addPort(int port) {
	if (usedPorts.find(port) != usedPorts.end())
		; // throw exception: Port Already Used
	usedPorts.insert(port);
}

void							Config::addServer(int port, ServerConfig srv) {
	serverConfigs[port] = srv; // Send port to constructor ? srv(port)
}

// GETTERS

std::set <int>					Config::getPorts() {
	return (usedPorts);
}

std::map <int, ServerConfig>	Config::getServers() {
	return (serverConfigs);
}
