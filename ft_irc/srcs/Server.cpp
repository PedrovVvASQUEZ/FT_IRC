/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:41:53 by pgrellie          #+#    #+#             */
/*   Updated: 2025/09/19 17:57:29 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//==================== Contructors N Destructor ===================//

Server::Server(void) : _port(0), _password("Password"), _server_fd(-1), _client_fd(-1){}

Server::Server(int port, const std::string &password) : _port(port), _password(password), _server_fd(-1), _client_fd(-1)
{
	std::memset(&_server_addr, 0, sizeof(_server_addr));
	std::cout << "Server created on port " << _port << std::endl;
}
// Constructeur de copie - recrée un nouveau serveur
Server::Server(const Server &rhs) : _port(rhs._port), _password(rhs._password), _server_fd(-1), _client_fd(-1)
{
	std::memset(&_server_addr, 0, sizeof(_server_addr));
	// On ne copie PAS les file descriptors - chaque serveur doit avoir les siens
	std::cout << "Server copied (port " << _port << ")" << std::endl;
}

Server::~Server(void)
{
	stop();
	std::cout << "Server destroyed" << std::endl;
}

//============= Surcharges d'operateur ===========//

Server	&Server::operator=(const Server &rhs)
{
	if (&rhs != this)
	{
		// Fermer les anciennes connexions avant de copier
		stop();
		
		// Copier seulement la configuration, pas les file descriptors
		_port = rhs._port;
		_password = rhs._password;
		_server_fd = -1;  // Reset - il faudra redémarrer le serveur
		_client_fd = -1;  // Reset
		std::memset(&_server_addr, 0, sizeof(_server_addr));
	}
	return (*this);
}

//==================== Getters ===================//

int	Server::getPort() const
{
	return (_port);
}

std::string	Server::getPassword() const
{
	return (_password);
}

//==================== Méthodes privées setup ===================//

void	Server::_createSocket()
{
	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "Server FD: " << _server_fd << std::endl;
	if (_server_fd == -1)
	{
		std::cerr << "Error: Failed to create socket" << std::endl;
		exit(1);
	}
	
	// Option pour réutiliser l'adresse
	int opt = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Error: Failed to set socket options" << std::endl;
		close(_server_fd);
		exit(1);
	}
	std::cout << "Socket created successfully" << std::endl;
}

void	Server::_bindSocket()
{
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_addr.s_addr = INADDR_ANY; // Écoute sur toutes les interfaces
	_server_addr.sin_port = htons(_port);
	
	if (bind(_server_fd, (struct sockaddr*)&_server_addr, sizeof(_server_addr)) < 0)
	{
		std::cerr << "Error: Failed to bind socket to port " << _port << std::endl;
		close(_server_fd);
		exit(1);
	}
	std::cout << "Socket bound to port " << _port << std::endl;
}

void	Server::_listenSocket()
{
	if (listen(_server_fd, 5) < 0) // Max 5 connexions en attente
	{
		std::cerr << "Error: Failed to listen on socket" << std::endl;
		close(_server_fd);
		exit(1);
	}
	std::cout << "Server listening on port " << _port << std::endl;
}

//==================== Méthodes publiques principales ===================//

void	Server::start()
{
	std::cout << "Starting IRC server..." << std::endl;
	_createSocket();
	_bindSocket();
	_listenSocket();
	std::cout << "Server ready! Waiting for connections..." << std::endl;
}

void	Server::acceptClient()
{
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	
	_client_fd = accept(_server_fd, (struct sockaddr*)&client_addr, &client_len);
	std::cout << "Client FD: " << _client_fd << std::endl;
	if (_client_fd < 0)
	{
		std::cerr << "Error: Failed to accept client connection" << std::endl;
		return;
	}
	std::cout << "Client connected! File descriptor: " << _client_fd << std::endl;
}

void	Server::handleMessage()
{
	char buffer[512];
	std::memset(buffer, 0, 512);
	
	ssize_t bytes_received = recv(_client_fd, buffer, 511, 0);
	if (bytes_received <= 0)
	{
		std::cout << "Client disconnected" << std::endl;
		close(_client_fd);
		_client_fd = -1;
		return;
	}
	
	std::string message(buffer);
	std::cout << "Received: " << message << std::endl;
	
	// Echo simple - renvoie le message reçu
	sendMessage("ECHO: " + message);
}

void	Server::sendMessage(const std::string& message)
{
	if (_client_fd == -1)
	{
		std::cerr << "No client connected" << std::endl;
		return;
	}
	
	std::string full_message = message + "\r\n";
	ssize_t bytes_sent = send(_client_fd, full_message.c_str(), full_message.length(), 0);
	if (bytes_sent < 0)
	{
		std::cerr << "Error: Failed to send message" << std::endl;
		return;
	}
	std::cout << "Sent: " << message << std::endl;
}

void	Server::stop()
{
	if (_client_fd != -1)
	{
		close(_client_fd);
		_client_fd = -1;
	}
	if (_server_fd != -1)
	{
		close(_server_fd);
		_server_fd = -1;
	}
	std::cout << "Server stopped" << std::endl;
}

