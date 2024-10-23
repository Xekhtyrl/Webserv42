/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:41:17 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/23 21:40:14 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <map>

class	Route;

class	Server {
	public:
		Server();

		// Setters

		void			setHost(std::string name);
		void			addErrorPage(int code, std::string file);
		void			setClientMaxBodySize(size_t size);
		void			addRoute(std::string route);		
		
		// Getters

		std::string		getHost();
		std::string		getErrorPage(int code);
		size_t			getClientMaxBodySize();
		Route			getRoute(std::string route);

		// Overloaded Operators

		bool			operator[](int code);
		Route			operator[](std::string route);
		
	private:
		// int								port; // Needed with map ?
		std::string						host;
		std::map <int, std::string>		errorPages;
		size_t							clientMaxBodySize;
		std::map <std::string, Route>	routes;
};
