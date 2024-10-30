/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:51:17 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/29 18:51:19 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>

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
	directives.insert("error_page");
	directives.insert("client_max_body_size");
	
	rules.insert("allow");
	rules.insert("redirect");
	rules.insert("root");
	rules.insert("autoindex");
	rules.insert("index");
	rules.insert("upload");
	
	int			port	= -1;
	std::string	route	= "";
	bool		inSrv	= false;
	bool		inRoute = false;

	while (std::getline(configFile, line)) {

		if (line[0] == '\n' || isCommentLine(line) || line.empty()) // Doesn't handle all "empty" lines yet
			continue;
		
		std::istringstream			stream(line);
		std::string					token;
		std::vector <std::string>	tokens;
		
		while (stream >> token)
			tokens.push_back(token);
			
		if (indentLevel(0) && tokens[0] == "server" && tokens.size() == 1) {
			port	= -1;
			inSrv	= true;
			inRoute = false;
			continue;
		}
		else if (indentLevel(1) && inSrv && !inRoute && tokens[0] == "listen" && tokens.size() == 2) {
			std::istringstream	stream(tokens[1]);
			stream >> port;
			if (usedPorts.find(port) != usedPorts.end()) {
				std::cout << "Port already used!\n";	
				exit(1); // Trying to setup the same port multiple times
			}
			addPort(port);
			serverConfigs[port].setPort(port);
			continue;
		}
		else if (indentLevel(1) && inSrv && !inRoute && isDirective(tokens[0]) && port > 0) {
			processDirective(port, tokens);
			continue;
		}
		else if (indentLevel(1) && inSrv && tokens[0] == "location" && tokens.size() == 2 && port > 0) {
			inRoute = true;
			route = tokens[1];
			continue;
		}
		else if (indentLevel(2) && inSrv && inRoute && isRule(tokens[0]) && port > 0) {
			processRule(port, route, tokens);
			continue;
		}
		else {
			std::cout << "Stx error, exiting main parsing loop\n";
			exit(1);
		}
	}
	if (usedPorts.size() != serverConfigs.size()) {
		exit(1); // bad port config
	}
}

//	METHODS

void	Config::processDirective(int port, std::vector <std::string> tokens) {
	
	std::string			directive = tokens[0];
	std::istringstream	stream(tokens[1]);
	
	if (tokens.size() != 2 && (directive == "error_page" && tokens.size() != 3)) {
		std::cout << "processDirective bad tokens nbr\n";
		exit(1); // Bad directive stx
	}
	if (directive == "server_name") {	
		serverConfigs[port].setHost(tokens[1]);
	}
	else if (directive == "error_page") {
		int	code;
		if (stream >> code && stream.eof()) { // Make isPath and isDir utils methods to check tokens[2] ?
			serverConfigs[port].addErrorPage(code, tokens[2]);
		} else {
			exit(1); // error with provided code
		}
	}
	else if (directive == "client_max_body_size") {
		size_t		size;
		std::string	suffix;
		if (stream >> size >> suffix && suffix == "M" && stream.eof())
			serverConfigs[port].setClientMaxBodySize(size * 1024);
		else {
			std::cout << "Issue with client max body size\n";
			exit(1); // throw error
		}
	}
	else {
		std::cout << "processDirective bad stx\n";
		exit(1); // throw error bad directive syntax
	}
}

void	Config::processRule(int port, std::string route, std::vector <std::string> tokens) {
	std::string	rule = tokens[0];
	
	if (tokens.size() != 2) {
		std::cout << "Bad size!\n";	
		exit(1); // Bad rule syntax for given rule;
	}

	std::cout << rule << " called within " << route << " for " << port << "\n";

	if (rule == "allow") {
		if (tokens[1] == "GET") {
			serverConfigs[port][route].allowMethod(GET);
			std::cout << "Adding GET method in " << route << "\n";
			if (serverConfigs[port][route][GET])
				std::cout << "Should print if GET is allowed\n";	
		}
		else if (tokens[1] == "POST")
			serverConfigs[port][route].allowMethod(POST);
		else if (tokens[1] == "DELETE")
			serverConfigs[port][route].allowMethod(DELETE);
		else
			exit(1); // throw error
	}
	else if (rule == "redirect")
		serverConfigs[port][route].setRedirect(tokens[1]);
	else if (rule == "root")
		serverConfigs[port][route].setRoot(tokens[1]);
	else if (rule == "autoindex") {
		if (tokens[1] == "on")
			serverConfigs[port][route].setAutoindex(true);
		else if (tokens[1] == "off")
			serverConfigs[port][route].setAutoindex(false);
		else
			exit(1); // throw proper error
	}
	else if (rule == "index")
		serverConfigs[port][route].setIndex(tokens[1]);
	else if (rule == "upload")
		serverConfigs[port][route].setUpload(tokens[1]);
}

bool	Config::hasExtension(std::string filename, std::string extension) {
	size_t	filenameLength = filename.length();
	size_t	extensionLength = extension.length();
	return (filename.substr(filenameLength - extensionLength) == extension);
}

bool	Config::isDirective(std::string token) {
	return (directives.find(token) != directives.end());
}

bool	Config::isRule(std::string token) {
	return (rules.find(token) != directives.end());
}

bool	Config::indentLevel(size_t level) {
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
