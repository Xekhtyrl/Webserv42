/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RouteConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:17:11 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/28 17:35:11 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RouteConfig.hpp"

RouteConfig::RouteConfig() {
	for (size_t i = 0; i < sizeof(methods)/sizeof(methods[0]); i++)
		methods[i] = false;
	redirect = "";
	root = "";
	autoindex = false;
	index = "";
	upload = "";
}

// SETTERS

void	RouteConfig::allowMethod(int method) {
	methods[method] = true;
}

void	RouteConfig::setRedirect(std::string redirect) {
	this->redirect = redirect;
}

void	RouteConfig::setRoot(std::string root) {
	this->root = root;
}

void	RouteConfig::setAutodindex(bool state) {
	autoindex = state;
}

void	RouteConfig::setIndex(std::string index) {
	this->index = index;
}

void	RouteConfig::setUpload(std::string upload) {
	this->upload = upload;
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

std::string		RouteConfig::getUpload() {
	return (upload);
}

// Overloaded Operator

bool			RouteConfig::operator[](int RULE) {
	switch (RULE) {
		case GET:
		case POST:
		case DELETE:	return	(isMethodAllowed(RULE));
		case REDIRECT: 	return	(!getRedirect().empty());
		case ROOT: 		return	(!getRoot().empty());
		case AUTOINDEX: return	(hasAutoindex());
		case INDEX: 	return	(!getIndex().empty());
		case UPLOAD:	return	(!getUpload().empty());
		default:
			throw std::invalid_argument("Invalid RULE");
	}
}
