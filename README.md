# Richard Seul

Test préliminaire...

## Instalation

- Installer [Arduino](https://www.arduino.cc/en/Main/Software)
- Installer [node.js](https://nodejs.org/en/) (version 8.x LTS)
- Télécharger ou clôner le présent dépôt
- Déplacer tout le contenu du sous-dossier `richard_seul/libraries` à l'intérieur du dossier `libraries` d'Arduino (qui devrait se situer dans `Mes documents`)
- Connecter le contrôleur, ouvrir le sketch `richard_seul/richard_test/richard_test.ino` avec Arduino, le configurer sur le bon port série – **en profiter pour noter le nom du port (par exemple : COM11) car il sera utile par la suite !** – puis transférer le sketch sur le contrôleur
- Éditer le script `richard_seul/test.js` et remplacer `COM3` par le bon nom du port (récupéré plus haut) à la ligne 4 (`let board = new SerialPort('COM3'...`)
- A partir du terminal, exécuter la commande : 

	`npm install --global --production windows-build-tools` 

	> Voir [ici](https://github.com/felixrieseberg/windows-build-tools) pour plus de détails, il se peut que le terminal doive être lancé en mode administrateur...

- Toujours avec le terminal, aller dans le dossier `richard_seul` du projet et exécuter la commande :

	`npm install`
	
- Puis exécuter la commande :

	`node test`
	
- Suivre les instructions et voir ce qui se passe...

