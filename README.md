# Minitalk

Minitalk est un projet du cursus 42 qui consiste à implémenter une communication entre deux processus Unix en utilisant uniquement les signaux (`SIGUSR1` et `SIGUSR2`).

## Description

- **Serveur** : Attend les signaux envoyés par le client. À la réception, il reconstruit les caractères envoyés et affiche le message.
- **Client** : Envoie un message au serveur, caractère par caractère, bit par bit, via des signaux Unix.

## Installation

```bash
git clone https://github.com/sbr93z/minitalk.git
cd minitalk
make
```

Utilisation
```bash
Lancer le serveur :

./server

Puis, depuis un autre terminal, envoyer un message avec le client :

./client <PID> "Votre message ici"
```
Exemple :
```bash
./server
./client 4242 "Hello, World!"
```
Fichiers

includes/minitalk.h : Header principal du projet.

src/server.c : Gère la réception des signaux et affiche le message.

src/client.c : Envoie les signaux pour transmettre le message.

libft/ : Ma bibliothèque personnelle (libft incluse avec ft_printf et get_next_line).

Makefile : Fichier pour compiler et nettoyer le projet.

Commandes Makefile
```bash
make : Compile les programmes.

make clean : Supprime les fichiers objets.

make fclean : Supprime les fichiers objets et les exécutables.

make re : fclean puis make.
```
Fonctionnement

SIGUSR1 = bit à 1

SIGUSR2 = bit à 0

Chaque caractère est reconstruit bit par bit sur le serveur.
