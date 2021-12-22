Rev 1.0
Dans ce dossier il n'y a que le dossier Speeduino et le fichier du dossier reference pour le INI

Speeduino + L298N + Trottle Body VAG VR5 170cv
Video du test
https://www.instagram.com/p/CWWm2S4oEU1/

Test ok 
-La pedale electronique et le papillon motorisé trottle body on été ajouté au projet Speeduino.
-le l298N chauffe trop il va cramer
-le ADC de la pedal est du TB et mapper 0 100 ce qui est trop faible. Le papillon tremble un peu.
-le code n'utilise pas l'algorhitm des PID mais fonctionne pas mal.

Reste a faire
-le code est dans le ino sensor, il faudrait l'isolé avec un ino et un heder.
-rajourté les 2 pédales electronique et fair une moyenne et creer les DTC en cas de probleme
-ajouté le ralenti
-Ajouré les commande PID 
-créer l'interface tuner studio pour le ralenti et les PID.
-Créer une map de Patillon motorisé KFWDKMSN X=Rpm Y=Kg/heure Z= % d'ouverture (map invese KLAF linearisation MAF)
-Créer une protection de fermeture du papillon en cas de mode dégradé
-créer une protection de fermeture du papillon en cas d'AFR pauvre 
-Créer un régulateur de viter & un limiteur de vitesse 
	Recuperer les infos can du module pour les boutton du regulateur de vitesse et vitesse vehicule 