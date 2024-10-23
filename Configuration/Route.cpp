/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:17:11 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/23 21:36:32 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Route.hpp"

Route::Route() {
	for (int i = 0; i < sizeof(methods)/sizeof(methods[0]); i++)
		methods[i] = false;
	redirect = "";
	root = "";
	autoindex = false;
	index = "";
}

// SETTERS

void	Route::allowMethod(int method) {
	methods[method] = true;
}

void	Route::setRedirect(std::string redirect) {
	this->redirect = redirect;
}

void	Route::setRoot(std::string root) {
	this->root = root;
}

void	Route::setAutoindex(bool state) {
	autoindex = state;
}

void	Route::setIndex(std::string index) {
	this->index = index;
}

// GETTERS

bool			Route::isMethodAllowed(int method) {
	return (methods[method]);
}

std::string		Route::getRedirect() {
	return (redirect);
}

std::string 	Route::getRoot() {
	return (root);
}

bool			Route::hasAutoindex() {
	return (autoindex);
}

std::string		Route::getIndex() {
	return (index);
}

// Overloaded Operator

bool			Route::operator[](int RULE) {
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
