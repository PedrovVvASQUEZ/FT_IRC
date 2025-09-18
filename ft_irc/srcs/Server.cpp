/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:41:53 by pgrellie          #+#    #+#             */
/*   Updated: 2025/09/17 18:41:54 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//==================== Contructors N Destructor ===================//

Server::Server(void) : _port(0), _password(""), _server_fd(-1)
{
	std::memset(&_server_addr, 0, sizeof(_server_addr));
	return ;
}

Server::Server(int port, const std::string &password) : _port(port), _password(password), _server_fd(-1)
{
	std::memset(&_server_addr, 0, sizeof(_server_addr));
	return ;
}

Server::Server(const Server &rhs) : _port(rhs._port), _password(rhs._password), _server_fd(rhs._server_fd)
{
	std::memset(&_server_addr, 0, sizeof(_server_addr));
	return ;
}

Server::~Server(void)
{
	return ;
}
//=============== Operators Overload Member Functions =============//

Server	&Server::operator=(const Server &rhs)
{
	if (&rhs != this)
	{
		stop();
		for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			delete (*it);
		}
		for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		{
			delete (it->second);
		}
		_clients.clear();
		_channels.clear();
		_poll_fds.clear();
		_port = rhs._port;
		_password = rhs._password;
		_server_fd = rhs._server_fd;
		_server_addr = rhs._server_addr;
	}
	return (*this);
}

//======================= Member functions ========================//
