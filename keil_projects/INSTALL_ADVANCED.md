# Keil uVision, MBED-OS et Nucléo

Ce document présente comment installer et utiliser **Keil uVision** (version 5.41) avec le système d'exploitation **mbed-os** (version 6.17) dans le cadre de la salle de Travaux Pratiques d'Interfaçage Numérique et de ProTIS à l'*Institut d'Optique Graduate School*.

*Document rédigé par Julien VILLEMEJANE - LEnsE*

## Installation de Keil uVision

Télécharger la version **5.41** de **MDK-ARM** depuis le site de *Keil* : [https://www.keil.com/](https://www.keil.com/)

Installer la version 5.41 dans le répertoire **`C:\Keil_v5\`**.



## Clonage du dépôt mbed-os

Le dépôt GitHub de **mbed-os** se trouve à l'adresse suivante : [https://github.com/ARMmbed/](https://github.com/ARMmbed/)

Depuis le répertoire **`C:\Keil_v5\`**, cloner le dépôt à l'aide de la commande :

``git clone https://github.com/ARMmbed/mbed-os.git``

**Attention**, dans la version 6.17, il faut commenter la ligne 141 (`mbed_error_initialize();`) du fichier `/platform/source/mbed_sdk_boot.c` (fonction introuvable...)


## Utilisation de MBED-Cli

Afin de créer un projet propre pour une cible particulière, basé sur **mbed-os**, nous allons nous intéresser à l'application *mbed-cli* fourni par *ARM*. Cette application permet de créer de nouveau projet mbed pour des cartes Nucléo en particulier (d'autres plateformes sont également disponible).

### Installation de MBED-CLI

Il existe un package pour Python (version 3 de Python) qui s'installe à l'aide de la commande suivante : 

``pip install mbed-cli``

**Attention** D'autres packages sont indispensables au bon fonctionnement de *mbed-cli*. (liste à venir)

### Création d'un nouveau projet

Naviguer jusqu'au répertoire souhaité.

Dans un terminal, exécuter la commande suivante (pour créer un projet nommé *hello-mdk* :

``mbed new hello-mdk``

Cette commande crée un projet incluant la dernière version de *mbed-os* (téléchargement un peu long...).

### Ajout d'une cible

Naviguer dans le répertoire nouvellement créé du projet (*hello-mdk* dans l'exemple précédent).

Exécuter la commande suivante pour associer une cible à votre projet (ici Nucleo L476RG) :

``mbed target -m NUCLEO_L476RG``

### Export du projet vers Keil

Afin de créer les fichiers spécifiques à Keil, exécuter la commande suivante :

``mbed export -i uvision5 -m K64F``

## Adaptation du projet


Il est possible de conserver cette version pour l'utilisation du projet **Keil uVision**, mais cela ajoute à chaque projet environ 1Go de bibliothèque *mbed-os*.

Avec quelques modifications du projet créé, il est possible de se baser sur une version mutualisée de *mbed-os* (par exemple celle contenue dans le répertoire **`C:\Keil_v5\mbed-os\`**

Vous allez pouvoir créer un projet de référence réutilisable.

Supprimer le répertoire *mbed-os* du projet de référence (ici *hello-mdk*). Vous pouvez aussi supprimer les répertoires `.git`, `__pycache__` et les fichiers `GettingStarted.html` et `mbed_settings.py`.

### Modification du fichier *.uvprojx

Afin que votre projet Keil soit lié à la version de *mbed-os* déjà pré-installée, il faut modifier le fichier `nom_projet.uvprojx` du répertoire du projet à l'aide d'un éditeur de texte (type *Notepad* ou *Notepad++*).

Remplacer toutes les occurrences de **`./mbed-os/`** par **`C:/Keil_v5/mbed-os/`** et sauvegarder le fichier `nom_projet.uvprojx`.

Remplacer également toutes les occurrences de **`;mbed-os`** par **`;C:/Keil_v5/mbed-os`**

### Lancement de Keil uVision

Lancer à présent **Keil uVision** en double-cliquant sur le fichier `nom_projet.uvprojx`.

*Attention* Certaines options de compilation peuvent être supprimées pour accélérer la compilation…

*Liste ??*

Vous pouvez alors ajouter un fichier `main.cpp` au projet (dans un répertoire déjà existant - celui portant le nom du projet - ou un nouveau répertoire).

Dans ce fichier `main.cpp`, saisir la structure de base d'un programme mbed-os :

```
#include "mbed.h" 

DigitalOut led(LED1); 


int main(){ 

	while (1) { 
		led = !led; 
		thread_sleep_for(50); 
	} 
}
```

### Compilation

Avant de compiler le projet, vous pouvez modifier le fichier **`mbed_app.json`** de la manière suivante : 

```json
{
    "requires": ["bare-metal"],
    "target_overrides": {
        "*": {
            "platform.stdio-baud-rate": 9600,
            "platform.minimal-printf-enable-floating-point": false,
            "platform.stdio-minimal-console-only": true
        }
    }
}
```


