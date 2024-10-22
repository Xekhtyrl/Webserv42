/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:41:17 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/22 19:43:46 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <map>

class	Route;

class	Server {
	public:
		Server();

		void			setHost(std::string name);
		void			addErrorPage(int code, std::string file);
		void			setClientMaxBodySize(size_t size);
		void			addRoute(std::string route);		
		
		std::string		getHost();
		std::string		getErrorPage(int code);
		size_t			getClientMaxBodySize();
		Route			getRoute(std::string route);
		
	private:
		std::string						host;
		std::map <int, std::string>		errorPages;
		size_t							clientMaxBodySize;
		std::map <std::string, Route>	routes;
};
