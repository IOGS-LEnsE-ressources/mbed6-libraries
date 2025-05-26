# Keil uVision, MBED-OS et Nucléo

Ce document présente comment installer et utiliser **Keil uVision** (version 5.41) avec le système d'exploitation **mbed-os** (version 6.17) dans le cadre de la salle de Travaux Pratiques d'Interfaçage Numérique et de ProTIS à l'*Institut d'Optique Graduate School*.

*Document rédigé par Julien VILLEMEJANE - LEnsE*

## Installation de Keil uVision

Télécharger la version **5.41** de **MDK-ARM** depuis le site de *Keil* : [https://www.keil.com/](https://www.keil.com/)

Installer la version 5.41 dans le répertoire **`C:\Keil_v5\`**.

### Packages à installer

Au premier lancement de l'application **Keil uVision**, l'outil de gestion des packages **Pack Installer** s'ouvre. Sinon, vous pouvez vous rendre sur cet outil en cliquant sur l'icône **Pack Installer**.

Dans la zone de droite, cliquer sur l'onglet `Boards` et rechercher la carte Nucléo L476RG. Sélectionner le composant installé sur la carte : *STM32L476RGTx*. 

Une fois sélectionnée, choisir l'installation des packages (en cliquant sur *Install* :

- Keil::NUCLEO-L476RG_BSP
- Keil::STM32L4xx_DFP
- Keil::STM32NUCLEO_BSP

*Ces paramètres doivent être adaptés en cas d'utilisation de cartes Nucléo différentes ou de composants STM32 différents.*

### Licence Community-MDK6

Dans **Keil uVision**, aller dans `File > License Management...` et sélectionner l'onblet `User-Based License`.

Cliquer sur `Activate / Deactive...` pour ouvrir le gestionnaire de licence *Arm License Management Utility*.

Cliquer sur `License Server...` et entrer *https://mdk-preview.keil.arm.com* comme serveur de licence. Cliquer sur `Query`. Selectionner `Keil MDK Community...` et appuyer sur `Activate`.


Plus d'information à l'adresse suivante : [https://www.keil.arm.com/mdk-community/](https://www.keil.arm.com/mdk-community/)


## Clonage du dépôt mbed-os

Le dépôt GitHub de **mbed-os** se trouve à l'adresse suivante : [https://github.com/ARMmbed/](https://github.com/ARMmbed/)

Depuis le répertoire **`C:\Keil_v5\`**, cloner le dépôt à l'aide de la commande :

``git clone https://github.com/ARMmbed/mbed-os.git``

Si vous n'avez pas le logiciel Git, il est possible de se rendre sur la page suivante : [https://github.com/ARMmbed/](https://github.com/ARMmbed/) et de télécharger le code (Code - bouton vert - puis Download Zip). Il faut ensuite décompresser le document archivé dans le répertoire **`C:\Keil_v5\`**.

**Attention**, dans la version 6.17, il faut commenter la ligne 141 (`mbed_error_initialize();`) du fichier `/platform/source/mbed_sdk_boot.c` (fonction introuvable...)


## Projet de base

### Téléchargement

Un projet de base, réalisé avec MBED-Cli, est disponible dans le répertoire suivant (dépôt Git) : 

Une version archivée est disponible au téléchargement ici : [https://lense.institutoptique.fr/ressources/mbed/hello-L476RG.zip](https://lense.institutoptique.fr/ressources/mbed/hello-L476RG.zip)

Décompresser l'archive dans un répertoire de votre ordinateur.

### Utilisation

Ce projet de base est prévu pour fonctionner avec des cartes **Nucléo L476RG** et le système d'exploitation **Mbed-OS** (version 6.14 et supérieure).

Double-cliquer sur le fichier `hello-l476rg.uvprojx`. *(Vous pourrez renommer ce fichier par la suite.)*

L'application **Keil uVision** se lance.

Un fichier `main.cpp` est déjà présent dans le projet. Il est basé sur l'exemple *blinky-baremetal* de *mbed-os*.

Structure de base du programme mbed-os :

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

### Ajout de bibliothèques

Dossier `libs`

