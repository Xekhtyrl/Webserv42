/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:17:11 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/22 19:42:41 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Route.hpp"

Route::Route() {
	for (int i = 0; i < 3; i++)
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

std::string		Route::hasRedirect() {
	return (redirect);
}

std::string 	Route::hasRoot() {
	return (root);
}

bool			Route::hasAutoindex() {
	return (autoindex);
}

std::string		Route::hasIndex() {
	return (index);
}
