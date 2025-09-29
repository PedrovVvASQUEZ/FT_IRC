/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:41:21 by pgrellie          #+#    #+#             */
/*   Updated: 2025/09/17 18:41:22 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Clients.hpp"

//==================== Contructors N Destructor ===================//

Clients::Clients(void) : _cfd(-1), _cstate(DISCONNECTED)
{
	return ;
}

Clients::Clients(int fd, const std::string &hostname) : _cfd(fd), _hostname(hostname), _cstate(DISCONNECTED)
{
	return ;
}

Clients::Clients(const Clients &rhs) : _cfd(rhs._cfd), _hostname(rhs._hostname),
										_nickname(rhs._nickname), _username(rhs._username),
										_realname(rhs._realname), _cstate(rhs._cstate),
										_buffer(rhs._buffer)
{
	return ;
}

Clients::~Clients(void)
{
	if (_cfd != -1 && _cstate != DISCONNECTED)
		disconnect();
}

//============= Surcharges d'operateur ===========//

Clients	&Clients::operator=(const Clients &rhs)
{
	if (this != &rhs)
	{
		_cfd = rhs._cfd;
		_nickname = rhs._nickname;
		_username = rhs._username;
		_realname = rhs._realname;
		_hostname = rhs._hostname;
		_cstate = rhs._cstate;
		_buffer = rhs._buffer;
	}
	return (*this);
}

//==================== Getters N Setters ===================//



//==================== Méthodes privées setup ===================//



//==================== Méthodes publiques principales ===================//

