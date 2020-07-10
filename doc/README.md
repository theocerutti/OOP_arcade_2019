# ARCADE

## Introduction

Ce projet consiste à créer une borne d'arcade pouvant intégrer des jeux ou bien des librairies graphiques, à la manière d'un plugin.
Les jeux peuvent alors être joués sur toutes les librairies graphiques disponibles en passant par la librairie terminal jusqu'à la 2D.

## Architecture des dossiers

```
assets/
├── fonts/   	 # Fonts of games
├── images/  	 # Images of games
├── levels/  	 # Levels of games
├── scores/  	 # Scores of games
games/       	 # Contains all libraries .so of games
lib/             # Contains all libraries .so of libraries
doc/
src/
├── core/        # Source of Core
├── errors/      # Custom errors class
├── games/       # Contains sources of games
├── graphicals/  # Contains sources of libraries
├── utils/       # Contains all basics objects
```

## Lancer la borne d’arcade

Pour lancer notre borne d’arcade, il suffit simplement de l’exécuter avec le path d'une librairie.

-  ``make re ; ./arcade path_to_lib.so``

Le menu du jeu apparaît, vous n’avez qu’à choisir le jeu auquel vous voulez jouer avec les touches ``z/q/s/d`` puis en pressant ``ENTRER``

## Ajouter un jeu

La particularité de cette borne d’arcade est que vous pouvez rajouter un nouveau jeu très simplement. Pour ce faire, suivez ces instructions :

- Préparer un dossier portant le nom de votre jeu dans le dossier associer (``./src/games/``)
- Mettez-y un Makefile compilant votre jeu, ainsi que vos fichiers en .cpp

**Attention**: Votre librairie doit être compilé en format **.so**.

Votre jeu devra hériter de notre classe **AGame**, une classe abstraite, qui fournira les fonctions de bases permettant de créer votre jeu.
Pour réaliser votre jeu d’arcade, différentes fonctionnalités sont mises à votre disposition (update, draw, handleEvent...).

**Attention**: ne créer ni ne fermez pas la Window de la lib. De plus, il ne faut pas appeller les fonctions clear() et drawWindow() de la librairie. Le Core s'en occupe pour vous.

De plus: il faudra rajouter un point d'entrée dans votre librairie:

```c++
extern "C" Arcade::IGame *entryPoint(void)
{
    return (new MyGame());
}
```

**Attention**: cette fonction doit être appellé ``entryPoint``!

## Ajouter une librairie

Pour créer votre librairie:
- Préparer un dossier portant le nom de votre jeu dans le dossier associer (``./src/graphicals/``)
- Mettez-y un Makefile compilant votre jeu, ainsi que vos fichiers en .cpp

**Attention**: Votre librairie doit être compilé en format **.so**.

Votre librairie devra hériter de l'interface **ILibGFX**.

De plus: il faudra rajouter un point d'entrée dans votre librairie:

```c++
extern "C" Arcade::ILibGFX *entryPoint(void)
{
    return (new MyLib());
}
```

**Attention**: cette fonction doit être appellé ``entryPoint``!

## Utilitaires

### Formes

Toutes les formes sont hérités de la classe AMovable. Elle fournit les fonctions et les attributs de base permettant la rotation, le positionnement, de votre objet.
Le point d'origine de chaque forme est en haut à gauche.

#### Circle

Les fonctions de la classe Circle :

```c++
void setFillColor(const Color &color);
const Color &getColor(void) const;
void setRadius(int radius);
int getRadius(void) const;
bool contains(const Vector2f &point) const;
```

#### Rectangle

Les fonctions de la classe Rect :

```c++
void setFillColor(const Color &color);
const Color &getColor(void) const;
float getWidth() const;
float getHeight() const;
void setWidth(float width);
void setHeight(float height);
void setDimension(float width, float height);
void setDimension(const Vector2f &dimension);
const Vector2f &getDimension() const;
bool contains(const Vector2f &point);
```

### Gestion du temps

#### Clock

Les fonctions de la classe Clock:

```c++
- double getElapsedTime() const;
- void restart();
```

#### Les couleurs

La structure ``Color`` contenant les composantes des couleurs (RGBA).
Par ailleurs une énumération contenant les couleurs de bases peuvent être utilisés.
Pour convertir il suffit d'utiliser ``Arcade::getColor() ``.
Exemple:
``Color REDcolor = Arcade::getColor(Arcade::Colors::RED);``

Toutes les couleurs de bases intégrées dans l'Arcade:
Les couleurs précédées par un B sont les versions claires.
```
BLACK
BBLACK
RED
BRED
GREEN
BGREEN
YELLOW
BYELLOW
BLUE
BBLUE
MAGENTA
BMAGENTA
CYAN
BCYAN
WHITE
BWHITE
```

#### Event

Plusieurs events sont également disponibles :
La structure Event est constitué:
- d'un type
- d'une key
- d'un unicode

Type:
```
KEY_PRESSED
KEY_RELEASE
CLOSE
TEXT_ENTERED
```

Keys:
```
Z Q S D 
UP DOWN LEFT RIGHT
ECHAP
ENTER
SPACE
```

#### Image

Pour notre Arcade nous utilisons notre propre format d'image.
Un utilitaire ``ImageConverter`` est fourni pour convertir des jpg, png... dans le format Arcade.
Ce format est constitué:
- les 2 premiers bytes sont la largeur.
- les 2 bytes suivants sont la longueur.
- les autres bytes sont l'image elle même. Chaques pixels sont sur 4 bytes (RGBA, dans l'ordre).

Ces fonctions sont:
```c++
const Vector2i &getDimension() const;
const unsigned char *getBufferRGBA(unsigned int id = 0);
const - unsigned int countBuffers();
```

#### Text

Les différentes fonctions de la classe Text :

```c++
const std::string &getText() const;
void setText(const std::string &text);
void setColor(const Color &color);
const Color &getColor() const;
const std::string &getPathFont() const;
void setPathFont(const std::string &pathFont);
void setTextSize(unsigned short textSize);
unsigned short getTextSize() const;
```

#### Vector Template

La template class ``Vector`` sont construite avec les paramètres x et y, et contiennent tous les opérateurs dont vous aurez besoin pour les manier.

## Equipe

Nos développeurs:
- Mathilde Couston
- Théo Cerutti
- Axel Pierson

## Remerciements

- Antoine Maillard
- Yannick Combes
- Honorin Pouteau
- Cyril Begard
- Yoan Vessiere
- Michael Fabrie