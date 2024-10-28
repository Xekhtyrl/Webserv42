/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:21:09 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/28 17:56:52 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"
# include "ServerConfig.hpp"

Config::Config(int ac, char **av) {
	if (ac > 2)
		exit(1); // TODO: Throw proper error/exception
	else if (ac == 2) {
		if (hasExtension(av[1], ".conf"))
			configFile.open(av[1]);
			// TODO: Catch open failure exception
		// TODO: Not a .conf file exception
	} else
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
	
	std::getline(configFile, line);
	
	// REFACTOR WITH SINGLE FUNC ?
	// int port;
	// std::string route;
	// Read line by line and update as it goes
	// Using srv[port].whatever and srv[port][route].whatever()
	// with dedicated processDirective and processRule subfunctions
	
	while (true) {
		if (line[0] == '\n' || isCommentLine(line) || line.empty()) {
			std::getline(configFile, line);
			continue;
		}
		std::istringstream	stream(line);
    	std::string 		word;
		stream >> word;
		if (indentLevel(line, 0) && word == "server")
			parseServerConfig();
		else
			exit(1); // Synthax error, first bloc level keyword must be a server bloc
		std::getline(configFile, line);
	}
}

//	METHODS

bool	Config::hasExtension(std::string filename, std::string extension) {
	size_t	filenameLength = filename.length();
	size_t	extensionLength = extension.length();
	return (filename.substr(filenameLength - extensionLength) == extension);
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

bool	Config::isCommentLine(std::string line) {
	size_t	it = 0;
	while (it < line.length() && isspace(line[it]))
		++it;
	return (it < line.length() && line[it] == '#');
}

void	Config::parseServerConfig() {
	ServerConfig	srv;
	while (true) {
		if (line[0] == '\n' || isCommentLine(line) || line.empty()) {
			std::getline(configFile, line);
			continue;
		}
		else if (indentLevel(line, 1) == false)
			return;
		std::istringstream			stream(line);
		std::string					token;
		std::vector <std::string>	tokens;
		while (stream >> token)
			tokens.push_back(token);
		if (tokens.size() != 2 || (tokens[0] == "error_page" && tokens.size() != 3))
			exit(1); // Throw Wrong number of parameters
		else if (tokens[0] == "location")
			parseRouteConfig(srv, tokens[1]);
		else if (isDirective(tokens[0]))
			parseDirective(srv, tokens);
		std::getline(configFile, line);
	}
	addPort(srv.getPort());
	addServer(srv.getPort(), srv);
}

void	Config::parseRouteConfig(ServerConfig srv, std::string route) {
	while (true) {
		if (line[0] == '\n' || isCommentLine(line) || line.empty()) {
			std::getline(configFile, line);
			continue;
		}
		if (indentLevel(line, 2) == false)
			return;
		std::istringstream			stream(line);
		std::string					token;
		std::vector <std::string>	tokens;
		while (stream >> token)
			tokens.push_back(token);
		if (tokens.size() != 2)
			exit(1); // Throw Wrong number of parameters
		if (tokens[0] == "allow") {
			if (tokens[1] == "GET")
				srv[route].allowMethod(GET);
			else if (tokens[1] == "POST")
				srv[route].allowMethod(POST);
			else if (tokens[1] == "DELETE")
				srv[route].allowMethod(DELETE);
			else
				exit(1); // throw error
		}
		else if (tokens[0] == "redirect")
			srv[route].setRedirect(tokens[1]);
		else if (tokens[0] == "root")
			srv[route].setRoot(tokens[1]);
		else if (tokens[0] == "autodindex") {
			if (tokens[1] == "on")
				srv[route].setAutodindex(true);
			else if (tokens[1] == "off")
				srv[route].setAutodindex(false);
			else
				exit(1); // throw proper error
		}
		else if (tokens[0] == "index")
			srv[route].setIndex(tokens[1]);
		else if (tokens[0] == "upload")
			srv[route].setUpload(tokens[1]);
	}
}

void	Config::parseDirective(ServerConfig srv, std::vector <std::string> tokens) {
	std::string			directive = tokens[0];
	std::istringstream	stream(tokens[1]);

	if (directive == "listen") {
		int	port;
		if (stream >> port && stream.eof() && port >= 0 && port <= 65535)
			srv.setPort(port);
		else
			exit(1); // throw error 
	}
	else if (directive == "server_name")
		srv.setHost(tokens[1]);
	else if (directive == "error_page") {
		int	code;
		if (stream >> code && stream.eof()) // Check if within expected error ranges ?
			srv.addErrorPage(code, tokens[2]);
	}
	else if (directive == "client_max_body_size") {
		size_t	size;
		char	suffix;
		if (stream >> size >> suffix && suffix == 'M' && stream.eof())
			srv.setClientMaxBodySize(size * 1024);
		else
			exit(1); // throw error
	}
	else
		exit(1); // throw error
}

// SETTERS

void							Config::addPort(int port) {
	if (usedPorts.find(port) != usedPorts.end())
		exit(1); // throw exception: Port Already Used
	usedPorts.insert(port);
}

void							Config::addServer(int port, ServerConfig srv) {
	serverConfigs[port] = srv;
}

// GETTERS

std::set <int>					Config::getPorts() {
	return (usedPorts);
}

std::map <int, ServerConfig>	Config::getServers() {
	return (serverConfigs);
}
