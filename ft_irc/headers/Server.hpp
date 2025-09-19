/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:10:58 by pgrellie          #+#    #+#             */
/*   Updated: 2025/09/19 18:06:59 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

// Includes essentiels pour un serveur simple
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <iostream>
# include <string>
# include <cstring>
# include <cstdlib>

class Server
{
	private:
		// Configuration de base
		int				_port;
		std::string		_password;
		int				_server_fd;
		int				_client_fd;
		struct sockaddr_in	_server_addr;

		// Méthodes privées - étapes de setup
		void	_createSocket();
		void	_bindSocket();
		void	_listenSocket();

	public:
		// Constructeurs / Destructeur
		Server(void);
		Server(int port, const std::string &password);
		Server(const Server &rhs);
		~Server(void);

		// Sucharges d'operateur
		Server	&operator=(const Server &rhs);

		// Getters de base
		int		getPort() const;
		std::string	getPassword() const;

		// Méthodes principales - version simple
		void	start();		// Setup complet du serveur
		void	acceptClient();	// Accept UNE connexion
		void	handleMessage();	// Lit et traite UN message
		void	sendMessage(const std::string& message);	// Envoie UN message
		void	stop();			// Ferme les connexions
		
};

#endif

