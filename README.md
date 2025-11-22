# Description

Go One Game est un projet de manette à une main. Ce repo contient les fichiers et ressources utiles pour réaliser une manette Go One Game.

# Aperçu des fichiers

- `conception3D` : dossier contenant les fichiers .stl pour imprimer la coque de la manette.
- `hardware` : dossier contenant le schéma des branchements et le code Arduino de la manette. 

# Dossier `conception3D`

*En cours de construction*

# Dossier `hardware`

Le fichier `GoOneGame_main.ino`contient le code pour le prototype v2 de la manette Go One Game, qui comprend 2 joysticks (1 classique et 1 par gyroscope), les 4 boutons d'action ABXY, les 2 boutons LB et RB, les 2 gâchettes LT et RT (remplacées par des boutons poussoirs et donc non-analogique).  
L'Arduino se comporte comme une manette Xbox.

Matériel utilisé (voir `Schema_electronique.pdf` pour le branchement):

- Arduino Micro
- Module gyroscope-accéléromètre MPU6050
- Joystick
- 8 résistances 10 kOhm
- 8+1 boutons poussoirs

NB : Changer les valeurs des angles limites du gyroscope pour s'adapter à l'amplitude des mouvements possibles.

```cpp
int upperLimit = 45; // 10 est une bonne valeur
int lowerLimit = -45; 
```

## Prérequis

### __Arduino XInput Library__

<https://github.com/dmadison/ArduinoXInput>

Prérequis : <https://github.com/dmadison/ArduinoXInput_AVR?tab=readme-ov-file>

Utiliser la carte Arduino comme Xbox

### __Arduino MPU6050_tockn Library__

<https://github.com/tockn/MPU6050_tockn>

Librairie pour utiliser le gyroscope MPU6050

## Tutoriels utiles

### __DIY MPU-6050 USB Joystick__

<https://www.instructables.com/DIY-MPU-6050-USB-Joystick/>

Tutoriel et code pour utiliser un gyroscope MPU6050 comme joystick

Prérequis : librairie MPU6050_tockn, librairie Joystick de MHeironimus

A adapter pour utiliser avec XInput plutôt que Joystick

### __How to Emulate an Xbox Controller with Arduino (XInput)__

<https://www.partsnotincluded.com/how-to-emulate-an-xbox-controller-with-arduino-xinput/>

Tutoriel pour installer et utiliser la librairie XInput