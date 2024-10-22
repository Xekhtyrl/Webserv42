/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:00:51 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/22 16:39:33 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <map>

enum	Methods { GET, POST, DELETE }; 

// namespace conf {

class	Route {
	public:
		;
	private:
		bool							methods[3];
		std::string						redirect;
		std::string						root;
		bool							autoindex;
		std::string						index;
//		[WIP] Execute CGI based on certain file extension (for example .php) and make it work with POST and GET methods.
//		[WIP] Make the route able to accept uploaded files and configure where they should be saved.
};

class Server {
	public:
		;
	private:
		int								port;
		std::string						host;
		std::map<int, std::string>		error_pages; // error_pages[CODE]
		size_t							client_max_body_size;
		std::map<std::string, Route>	routes;		 // routes[PATH]
};

class	Config {
	public:
		;
	private:
		std::map<int, Server>			servers;	 // servers[PORT]
};

// }
