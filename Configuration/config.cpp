/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:00:53 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/23 21:33:26 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"

Config::Config(int ac, char **av) {
	if (ac > 2)
		exit(1); // Throw proper exception
	if (ac == 2)
		if (hasExtension(av[1], ".conf"))
			configFile.open(av[1]);
			// Catch open failure exception
		// Bad file exception
	else
		configFile.open("webserv.conf"); // Open default config
		// Catch failure exception
	parseConfigFile();
}

Config::~Config() {
	if (configFile.is_open())
		configFile.close();
}

//	Parsing Methods

bool	Config::hasExtension(std::string filename, std::string extension) {
	size_t	filenameLenght = filename.length();
	size_t	extensionLenght = extension.length();
	return (filename.substr(filenameLenght - extensionLenght) == extension);
}

void	parseConfigFile() {
	; // [WIP]
}

// Getters

std::vector<int>		Config::getPorts() {
	return (ports);
}

std::map <int, Server>	Config::getServers() {
	return (servers);
}

