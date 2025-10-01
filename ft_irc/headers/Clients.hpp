/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:11:13 by pgrellie          #+#    #+#             */
/*   Updated: 2025/10/01 18:45:16 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTS_HPP
# define CLIENTS_HPP

# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>

enum	ClientState
{
	DISCONNECTED,
	CONNECTED,
	AUTHENTIFICATED
};

class	Clients
{
	private:
		int			_cfd;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;
		std::string	_hostname;
		ClientState	_cstate;
		std::string	_buffer;

	public:
		Clients(void);
		Clients(int fd, const std::string& hostname);
		Clients(const Clients &rhs);
		~Clients(void);

		Clients& operator=(const Clients &rhs);

		// Getters
		int					getFd(void) const;
		const std::string&	getNickname(void) const;
		const std::string&	getUsername(void) const;
		const std::string&	getRealname(void) const;
		const std::string&	getHostname(void) const;
		ClientState			getState(void) const;
		const std::string&	getBuffer(void) const;
		std::string&		getBuffer(void);

		// Setters
		void	setNickname(const std::string &nickname);
		void	setUsername(const std::string &username);
		void	setRealname(const std::string &realname);
		void	setState(ClientState state);
		void	appendToBuffer(const std::string &data);
		void	clearBuffer(void);

		bool		messageComplete(void) const;
		std::string	extractMessage(void);
		void		eraseFromBuffer(size_t pos);

		bool	isAuthenticated(void) const;
		bool	isConnected(void) const;
		void	disconnect(void);
};

#endif

// Oui et avec les modifications necessaire concerner les nouvelles fonctions et des fonctions a modifier de part la nouvelle nature des variables privees. Les modifications toujours dans le chat