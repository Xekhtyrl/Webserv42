/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:16:46 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/23 21:40:04 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "Route.hpp"

Server::Server() {
	host = "localhost";
	clientMaxBodySize = 1024 * 1024; // 1MB
}

// SETTERS

void	Server::setHost(std::string name) {
	host = name;
}

void	Server::addErrorPage(int code, std::string file) {
	errorPages[code] = file;
}

void	Server::setClientMaxBodySize(size_t size) {
	clientMaxBodySize = size;
}

void	Server::addRoute(std::string route) {
	routes[route] = Route();
}

// GETTERS

std::string		Server::getHost() {
	return (host);
}

std::string		Server::getErrorPage(int code) {
	return (errorPages[code]);
}

size_t			Server::getClientMaxBodySize() {
	return (clientMaxBodySize);
}

Route			Server::getRoute(std::string route) {
	return (routes[route]);
}

// OVERLOADED OPERATOR

bool		Server::operator[](int code) {
	return (!getErrorPage(code).empty());
}

Route	Server::operator[](std::string route) {
	return (getRoute(route));
}
