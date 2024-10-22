/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:41:23 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/22 19:44:58 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>

enum	Methods { GET, POST, DELETE }; 

class	Route {
	public:
		Route();
		
		void			allowMethod(int method);
		void			setRedirect(std::string redirect);
		void			setRoot(std::string root);
		void			setAutoindex(bool state);
		void			setIndex(std::string index);

		bool			isMethodAllowed(int method);
		std::string		hasRedirect();
		std::string 	hasRoot();
		bool			hasAutoindex();
		std::string		hasIndex();		
		
	private:
		bool			methods[3];
		std::string		redirect;
		std::string		root;
		bool			autoindex;
		std::string		index;
};

//	[WIP] Execute CGI based on certain file extension (for example .php) and make it work with POST and GET methods.
//	[WIP] Make the route able to accept uploaded files and configure where they should be saved.