# Richard Seul Test

Test préliminaire...

## Instalation

1. Installer [Arduino](https://www.arduino.cc/en/Main/Software)
1. Installer [node.js](https://nodejs.org/en/) (version 8.x LTS)
1. Télécharger ou clôner le présent dépôt
1. Déplacer tout le contenu du sous-dossier `richard_seul_test/libraries` à l'intérieur du dossier `libraries` d'Arduino (qui devrait se situer dans `Mes documents`)
1. Connecter le contrôleur, ouvrir le sketch `richard_seul_test/richard_test/richard_test.ino` avec Arduino puis le configurer sur le bon port série – _en profiter pour noter le nom du port (par exemple : COM11) car il sera utile par la suite !_
1. Modifier le sketch pour renseigner le bon _pin_ sur lequel doit être connecté l'un des vérins, à la ligne 35 (`int pinVerin = 5;`)
1. Transférer le sketch sur le contrôleur
1. Éditer le script `richard_seul_test/test.js` et remplacer `COM3` par le bon nom du port (récupéré plus haut) à la ligne 4 (`let board = new SerialPort('COM3'...`)
1. A partir du terminal, exécuter la commande : `npm install --global --production windows-build-tools` _(voir [ici](https://github.com/felixrieseberg/windows-build-tools) pour plus de détails, il se peut que le terminal doive être lancé en mode administrateur...)_
1. Toujours avec le terminal, aller dans le dossier `richard_seul_test` et exécuter la commande : `npm install`
1. Puis exécuter la commande :	`node test`
1. Suivre les instructions et voir ce qui se passe...

## TODO

- Tester la méthode `Omni.setCarMove(speedMMPS, rad, omega)` qui devrait être celle sur laquelle repose l'essentiel des déplacements, en mappant les paramètres `speedMMPS`, `rad` et `omega` avec le vecteur `xz` fourni par l'application archivée dans https://github.com/LePhasme/richard_seul_tracker. 
