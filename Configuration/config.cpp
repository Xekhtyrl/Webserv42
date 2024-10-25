/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:21:09 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/25 20:11:19 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"
# include "ServerConfig.hpp"

Config::Config(int ac, char **av) {
	if (ac > 2)
		exit(1); // TODO: Throw proper error/exception
	if (ac == 2)
		if (hasExtension(av[1], ".conf"))
			configFile.open(av[1]);
			// TODO: Catch open failure exception
		// TODO: Not a .conf file exception
	else
		configFile.open("webserv.conf"); // Open default config
		// TODO: Catch failure exception
	
	directives.insert("listen");
	directives.insert("server_name");
	directives.insert("error");
	directives.insert("client_max_body_size");
	directives.insert("allow");
	directives.insert("redirect");
	directives.insert("root");
	directives.insert("autoindex");
	directives.insert("index");
	directives.insert("upload");
	
	std::string				line;
	while (std::getline(configFile, line)) {
		if (line[0] == '\n' || isCommentLine(line))
			continue;
		std::istringstream	stream(line);
    	std::string 		word;
		stream >> word;
		if (indentLevel(line, 0) && word == "server")
			parseServerConfig();
		else
			exit(1); // Synthax error, first bloc level keyword must be a server bloc
	}
	configFile.close();
}

Config::~Config() {
	if (configFile.is_open())
		configFile.close();
}

//	METHODS

bool	Config::hasExtension(std::string filename, std::string extension) {
	size_t	filenameLenght = filename.length();
	size_t	extensionLenght = extension.length();
	return (filename.substr(filenameLenght - extensionLenght) == extension);
}

bool	Config::isDirective(std::string token) {
	return (directives.find(token) != directives.end());
}

bool	Config::indentLevel(std::string line, size_t level) {
	size_t	indent = 0;
	while (line[indent] == '\t')
		++indent;
	return (indent == level);
}

bool	isCommentLine(std::string line) {
	size_t	it = 0;
	while (it < line.length() && isspace(line[it]))
		++it;
	return (it <line.length() && line[it] == '#');
}

void	Config::parseServerConfig() {
	ServerConfig	srv;
	std::string		line;
	while (std::getline(configFile, line)) {
		if (line[0] == '\n' || isCommentLine(line))
			continue;
		else if (indentLevel(line, 0))
			return;
		std::istringstream			stream(line);
		std::string					token;
		std::vector <std::string>	tokens;
		while (stream >> token)
			tokens.push_back(token);
		if (tokens.size() != 2 || ( tokens[0] == "error_page" && tokens.size() != 3))
			exit(1); // Wrong number of parameters
		else if (indentLevel(line, 1) && isDirective(tokens[0]) && tokens[0] != "location")
			parseDirective(tokens);
		else if (indentLevel(line, 1) && tokens[0] == "location")
			parseRouteConfig(srv, tokens[1]);
		else
			exit(1); // Error in the syntax
	}
	addPort(srv.getPort());
	addServer(srv.getPort(), srv);
}

void	Config::parseRouteConfig(ServerConfig srv, std::string route) {
	; // [WIP]
}

// void	Config::processTokens(std::vector <std::string> tokens) {
// 	;
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
