/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:10:58 by pgrellie          #+#    #+#             */
/*   Updated: 2025/09/17 18:10:59 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

// Includes système pour les sockets et fonctions réseau
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>

// Includes C++
# include <cstring>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <algorithm>
# include <sstream>

// Forward declarations
class Client;
class Channel;

class Server
{
	private:
		// Configuration du serveur
		int				_port;
		std::string		_password;
		int				_server_fd;
		struct sockaddr_in	_server_addr; //Structure qui stocke l'adresse IP et le port du serveur
		
		// Gestion des clients et channels
		std::vector<Client*>			_clients;
		std::map<std::string, Channel*>	_channels;
		
		// Pour poll()
		std::vector<struct pollfd>		_poll_fds; //Structure pour la fonction poll() qui gère les événements I/O multiples
		
		// Méthodes privées - setup
		void	_createSocket();
		void	_bindSocket();
		void	_listenSocket();
		void	_setupServer();
		
		// Méthodes privées - gestion clients
		void	_acceptNewClient();
		void	_handleClientData(int client_fd);
		void	_removeClient(int client_fd);
		Client*	_getClientByFd(int fd);
		
		// Méthodes privées - parsing et commandes
		void	_processMessage(Client* client, const std::string& message);
		std::vector<std::string> _parseMessage(const std::string& message);
		
	public:
		// Constructeurs / Destructeur
		Server(void);
		Server(int port, const std::string &password);
		Server(const Server& other);
		Server& operator=(const Server& other);
		~Server(void);
		
		// Méthodes principales
		void	start();
		void	run();
		void	stop();
		
		// Getters
		int			getPort() const;
		std::string	getPassword() const;
		int			getServerFd() const;
		
		// Gestion des clients
		void	addClient(Client* client);
		void	removeClient(Client* client);
		Client*	getClientByNickname(const std::string& nickname);
		std::vector<Client*>& getClients();
		
		// Gestion des channels
		void	addChannel(Channel* channel);
		void	removeChannel(const std::string& name);
		Channel* getChannel(const std::string& name);
		Channel* createChannel(const std::string& name, Client* creator);
		std::map<std::string, Channel*>& getChannels();
		
		// Méthodes utilitaires
		void	broadcastToChannel(const std::string& channel_name, const std::string& message, Client* sender = NULL);
		void	sendToClient(Client* client, const std::string& message);
		bool	isValidNickname(const std::string& nickname);
		bool	isNicknameInUse(const std::string& nickname);
};

#endif

