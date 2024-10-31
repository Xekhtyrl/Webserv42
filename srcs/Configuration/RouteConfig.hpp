/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RouteConfig.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:41:23 by alexphil          #+#    #+#             */
/*   Updated: 2024/10/31 19:40:28 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>

enum	Rules { GET, POST, DELETE, REDIRECT, ROOT, AUTOINDEX, INDEX, UPLOAD };

class	RouteConfig {
	public:
		RouteConfig();
		
		// Setters

		void			allowMethod(int method);
		void			setRedirect(std::string redirect);
		void			setRoot(std::string root);
		void			setAutoindex(bool state);
		void			setIndex(std::string index);
		void			setUpload(std::string upload);

		// Getters

		bool			isMethodAllowed(int method);
		std::string		getRedirect();
		std::string 	getRoot();
		bool			hasAutoindex();
		std::string		getIndex();
		std::string		getUpload();
		
		// Operator
		
		bool			operator[](int RULE);
		
	private:
		bool			methods[3];
		std::string		redirect; //exclusive >> GET
		std::string		root; //non exclusif  >> GET
		bool			autoindex;
		std::string		index; //non exclusif >> GET
		std::string		upload; //non exclusif >> ALL aLLOWD?
};
