/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RouteConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:17:11 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/24 18:04:45 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RouteConfig.hpp"

RouteConfig::RouteConfig() {
	for (int i = 0; i < sizeof(methods)/sizeof(methods[0]); i++)
		methods[i] = false;
	redirect = "";
	root = "";
	autoindex = false;
	index = "";
}

// SETTERS

void	RouteConfig::allowMethod(int method) {
	methods[method] = true;
}

void	RouteConfig::setRedirect(std::string redirect) {
	redirect = redirect;
}

void	RouteConfig::setRoot(std::string root) {
	root = root;
}

void	RouteConfig::setAutoindex(bool state) {
	autoindex = state;
}

void	RouteConfig::setIndex(std::string index) {
	index = index;
}

// GETTERS

bool			RouteConfig::isMethodAllowed(int method) {
	return (methods[method]);
}

std::string		RouteConfig::getRedirect() {
	return (redirect);
}

std::string 	RouteConfig::getRoot() {
	return (root);
}

bool			RouteConfig::hasAutoindex() {
	return (autoindex);
}

std::string		RouteConfig::getIndex() {
	return (index);
}

// Overloaded Operator

bool			RouteConfig::operator[](int RULE) {
	switch (RULE) {
		case GET:
		case POST:
		case DELETE:	return (isMethodAllowed(RULE));
		case REDIRECT: 	return (!getRedirect().empty());
		case ROOT: 		return (!getRoot().empty());
		case AUTOINDEX: return (hasAutoindex());
		case INDEX: 	return (!getIndex().empty());
	}
}
