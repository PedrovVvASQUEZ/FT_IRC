/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:17:45 by pgrellie          #+#    #+#             */
/*   Updated: 2025/09/17 17:29:02 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int ac, char **av)
{
	
	return (0);
}

// socket : crée un point de communication réseau (socket).

// close : ferme un descripteur de fichier (socket ou fichier).

// setsockopt : configure des options sur un socket (ex : réutilisation d’adresse).

// getsockname : récupère l’adresse locale d’un socket.

// getprotobyname : obtient des informations sur un protocole réseau (ex : "tcp").

// gethostbyname : résout un nom d’hôte en adresse IP (obsolète, remplacé par getaddrinfo).

// getaddrinfo : résout un nom d’hôte/service en adresses utilisables par socket.

// freeaddrinfo : libère la mémoire allouée par getaddrinfo.

// bind : associe un socket à une adresse locale (IP/port).

// connect : connecte un socket à une adresse distante.

// listen : met un socket en mode écoute (serveur).

// accept : accepte une connexion entrante sur un socket en écoute.

// htons, htonl : convertit des entiers (16/32 bits) de l’ordre hôte à l’ordre réseau.

// ntohs, ntohl : convertit des entiers de l’ordre réseau à l’ordre hôte.

// inet_addr : convertit une adresse IPv4 en chaîne en entier (obsolète).

// inet_ntoa : convertit une adresse IPv4 en entier en chaîne.

// send : envoie des données sur un socket.

// recv : reçoit des données sur un socket.

// signal, sigaction : gère les signaux (ex : interruption, arrêt).

// lseek : déplace le curseur de lecture/écriture dans un fichier.

// fstat : obtient des informations sur un fichier via son descripteur.

// fcntl : manipule des descripteurs de fichiers (ex : mode non bloquant).

// poll : surveille plusieurs descripteurs pour voir s’ils sont prêts (lecture/écriture).