# ToDoList-QT

Le projet consiste à créer 

## Getting Started

SFML est une interface de programmation destinée à construire des jeux vidéo ou des programmes interactifs. Elle est écrite en C++, mais également disponible dans divers langages comme C, D, Python, Ruby, OCaml ou Microsoft .NET. Elle a entre autres pour but de proposer une alternative orientée objet


## Installing

l'installation du package sfml avec toute les bibliothèque

    https://www.sfml-dev.org/download/sfml/2.5.1/index-fr.php


Après l'installation en extrait le fichier zip


## Configuration de SFML sur Mon projet 
 
https://github.com/youneshimi/pongSFML/blob/main/SFML%20(1).gif

## input.h

```ts
#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Input
{
	struct Button { bool left, right, up, down, escape; };

public:
	
	Input();
	
	Button GetButton(void) const;
	void InputHandler(Event event, RenderWindow& window);

private:
	Button button;
};

#endif
```


Bibliothèque `SFML` pour gérer la partie graphique et la fenêtre : 
```ts
#include <SFML/Graphics.hpp>
```
de façon de pouvoir utiliser les fonctions `SFML` son besoin de taper toujours `Sf :` en utilise : 
```ts
using namespace sf;
```

La déclaration des `cinq button` que je gerre dans se projet : 
```ts
struct Button { bool left, right, up, down, escape; };
```
Propriété de classe : 
```ts
public:
	
	Input();
	
	Button GetButton(void) const;
	void InputHandler(Event event, RenderWindow& window);

private:
	Button button;
```	


## input.cpp
```ts
#include "input.h"

Input::Input()
{
	button.left = button.right = button.up = button.down = button.escape = false;
}

Input::Button Input::GetButton(void) const
{
	return button;
}
void Input::InputHandler(Event event, RenderWindow& window)
{
	if (event.type == Event::Closed)
	{
		window.close();
	}
	if (event.type == Event::KeyPressed)
	{
		switch(event.key.code) 
		{
		case Keyboard::Escape:
			button.escape = true;
			break;
		case Keyboard::Left:
			button.left = true;
			break;

		case Keyboard::Right:
			button.right = true;
			break;
		case Keyboard::Down:
			button.down = true;
			break;
		default:
			break;
		}
	}
	if (event.type == Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:
				button.escape = false;
			break;
			case Keyboard::Left:
				button.left = false;
				break;
			case Keyboard::Right:
					button.right = false;
					break;
			case Keyboard::Down:
						button.down = false;
						break;
		    case Keyboard::Up:
							button.up = false;
							break;
			default:
				break;
		}
	}
}
```
Définition de constructeur & l'état des different buttons : 
```ts
Input::Input()
{
	button.left = button.right = button.up = button.down = button.escape = false;
}
```
implémentation de la fonction `GetButton` : 
```ts
Input::Button Input::GetButton(void) const
{
	return button;
}
```
Fonction de gestion des inputs `InputHandler` :
```ts
void Input::InputHandler(Event event, RenderWindow& window)
{
```
Fermer la fenetre si on clique sur la croix 
```ts
if (event.type == Event::Closed)
	{
		//On Ferme la fenetre
		window.close();
	}
```
`window.close` **c'est pur la ferméture de la fenétre** 

> Gestion des inputs `appuyés`  :
```ts
if (event.type == Event::KeyPressed)
	{
		switch(event.key.code)
		{
		case Keyboard::Escape:
			button.escape = true;
			break;
		case Keyboard::Left:
			button.left = true;
			break;
		case Keyboard::Right:
			button.right = true;
			break;
		case Keyboard::Down:
			button.down = true;
			break;
		default:
			break;
		}
	}
```
> Gestion des inputs `relachée`  :
```ts
if (event.type == Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:
				button.escape = false;
			break;
			case Keyboard::Left:
				button.left = false;
				break;
			case Keyboard::Right:
					button.right = false;
					break;
			case Keyboard::Down:
						button.down = false;
						break;
		    case Keyboard::Up:
							button.up = false;
							break;
			default:
				break;
		}
	}
```


## main.h
```ts

#include <iostream>
#include<SFML/Graphics.hpp>
#include "input.h"

const int WIN_WIDTH = 800; 
const int WIN_HEIGHT = 600;  


using namespace sf;
using namespace std;

void SetText(Text& txt, String str);
void CheckBtn();
```
Constantes du Programme : 

> largeur `const int WIN_WIDTH = 800`

> Hauteur `const int WIN_HEIGHT = 600`

Prototypes : 

```ts
void SetText(Text& txt, String str);
void CheckBtn();
```









## main.cpp
```ts

#include "main.h"


RenderWindow window;
Input input;
Font font;
Text txt;
float posRaquettesLeftX = 50;
float posRaquettesRightX = WIN_WIDTH - 70;
float posRaquettesLeftY = WIN_HEIGHT / 2;
float posRaquettesRightY = posRaquettesLeftY;
float RaquettesSpeed = 0.25f;
int RaquettesHeight = 150;
int RaquettesWidth= 20;
float ballSpeed = 0.75f;
Vector2f ballDir = Vector2f(1.5f, 2.0f);
float ballPosX = WIN_WIDTH / 2;
float ballPosY = WIN_HEIGHT / 2;
int scoreJ1 = 0;
int scoreJ2 = 0;
void RaquetteIA() 
{
	posRaquettesRightY = ballPosY;
}
void UpdateBall() {
	ballPosX += ballDir.x * ballSpeed;
	ballPosY += ballDir.y * ballSpeed;
	if ((ballPosX < posRaquettesLeftX + RaquettesWidth && ballPosX > posRaquettesLeftX && ballPosY+7
		< posRaquettesLeftY + RaquettesHeight && ballPosY+7 > posRaquettesLeftY)
		||
		(ballPosX > posRaquettesRightX - RaquettesWidth && ballPosX
			< posRaquettesRightX && ballPosY+7 < posRaquettesRightY + RaquettesHeight &&
			ballPosY+7 > posRaquettesRightY)) {
		ballDir.x *= -1;
	}
	if (ballPosX < 0) {
		scoreJ2++;
		ballPosX = WIN_WIDTH / 2;
		ballPosY = WIN_HEIGHT / 2;
		ballDir.x = fabs(ballDir.x);
		ballDir.y *= -1;
		SetText(txt, std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));

	}
	if (ballPosX < WIN_WIDTH) {
		scoreJ1++;
		ballPosX = WIN_WIDTH / 2;
		ballPosY = WIN_HEIGHT / 2;
		ballDir.x = -fabs(ballDir.x);
		ballDir.y *= -1;
		SetText(txt, std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));
	}
	if (ballPosY > WIN_HEIGHT || ballPosY < 0) {
		ballDir.y *= -1;
	}
} 
int main()
{
	window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Pong C++", Style::Default);
	font.loadFromFile("res/Poppins-Italic.ttf");
	SetText(txt, std::to_string(scoreJ1) + " | " + to_string(scoreJ2));
		CircleShape circleShape(15);
	circleShape.setPosition(ballPosX, ballPosY);
	RectangleShape rectangleShape(Vector2f(RaquettesWidth, RaquettesHeight));
	rectangleShape.setPosition(posRaquettesLeftX, posRaquettesRightY);
	RectangleShape rectangleShape2(Vector2f(RaquettesWidth, RaquettesHeight));
	rectangleShape2.setPosition(posRaquettesRightX, posRaquettesRightY);
	while (window.isOpen())
	{

		Event event; //Variable pour gérer l'événement
		// On boucle sur les événements
		while (window.pollEvent(event))
		{
			input.InputHandler(event, window);
		}
		CheckBtn();
		RaquetteIA();
		rectangleShape.setPosition(posRaquettesLeftX, posRaquettesLeftY);
		rectangleShape2.setPosition(posRaquettesLeftX, posRaquettesLeftY);
			UpdateBall();
		circleShape.setPosition(ballPosX, ballPosY);
		window.clear(Color::Black);
		window.draw(txt);
		window.draw(circleShape);
		window.draw(rectangleShape);
		window.draw(rectangleShape2);
	}
	return 0;
}
void SetText(Text& txt, String str)
{
	txt.setFont(font);
	txt.setString(str);
	txt.setCharacterSize(26);
	txt.setFillColor(Color::White);	
	txt.setPosition((WIN_WIDTH / 2) - 40, 10);
}
void CheckBtn()
{
	if (input.GetButton().up == true)
	{
		posRaquettesLeftY -= RaquettesSpeed;
		if (posRaquettesLeftY < 0)
 		posRaquettesLeftY = 0;
	}
	if (input.GetButton().down == true)
	{
		posRaquettesLeftY += RaquettesSpeed;
		if (posRaquettesLeftY + RaquettesHeight > WIN_HEIGHT)
			posRaquettesLeftY = WIN_HEIGHT - RaquettesHeight;
	}
	if (input.GetButton().left == true)
	{
		posRaquettesRightY -= RaquettesSpeed;
		if (posRaquettesRightY < 0)
			posRaquettesRightY = 0;
	}
	if (input.GetButton().right == true)
	{
		posRaquettesRightY += RaquettesSpeed;
		if (posRaquettesRightY + RaquettesHeight > WIN_HEIGHT)
			posRaquettesRightY = WIN_HEIGHT - RaquettesHeight;
	}
	if (input.GetButton().escape == true)
	{
		window.close();
	}
}
```

variables du programme : 
```ts
float posRaquettesLeftX = 50;
float posRaquettesRightX = WIN_WIDTH - 70;
float posRaquettesLeftY = WIN_HEIGHT / 2;
float posRaquettesRightY = posRaquettesLeftY;
float RaquettesSpeed = 0.25f;
int RaquettesHeight = 150;
int RaquettesWidth= 20;
```
info du balle : 
```ts
float ballSpeed = 0.75f;
Vector2f ballDir = Vector2f(1.5f, 2.0f);
float ballPosX = WIN_WIDTH / 2;
float ballPosY = WIN_HEIGHT / 2;
```
affichage du score au début : 
```ts
int scoreJ1 = 0;
int scoreJ2 = 0;
```
Une mini **IA** pour gérer l'une des raquettes : 
```ts
void RaquetteIA() 
{
	posRaquettesRightY = ballPosY;
}
```
Mettre à jour la balle : 
```ts
void UpdateBall() {
	
	ballPosX += ballDir.x * ballSpeed;
	ballPosY += ballDir.y * ballSpeed;

	if ((ballPosX < posRaquettesLeftX + RaquettesWidth && ballPosX > posRaquettesLeftX && ballPosY+7
		< posRaquettesLeftY + RaquettesHeight && ballPosY+7 > posRaquettesLeftY)
		||
		(ballPosX > posRaquettesRightX - RaquettesWidth && ballPosX
			< posRaquettesRightX && ballPosY+7 < posRaquettesRightY + RaquettesHeight &&
			ballPosY+7 > posRaquettesRightY)) {

		ballDir.x *= -1;
	}
	if (ballPosX < 0) {
		scoreJ2++;
		ballPosX = WIN_WIDTH / 2;
		ballPosY = WIN_HEIGHT / 2;
		ballDir.x = fabs(ballDir.x);
		ballDir.y *= -1;
		SetText(txt, std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));
	}
	if (ballPosX < WIN_WIDTH) {
		scoreJ1++;
		ballPosX = WIN_WIDTH / 2;
		ballPosY = WIN_HEIGHT / 2;
		ballDir.x = -fabs(ballDir.x);
		ballDir.y *= -1;
		SetText(txt, std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));
	}
	if (ballPosY > WIN_HEIGHT || ballPosY < 0) {
		ballDir.y *= -1;
	}
} 
```
Point de départ du programme `Main` : 

```ts
int main()
{
	window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Pong C++", Style::Default);
	font.loadFromFile("res/Poppins-Italic.ttf");
	SetText(txt, std::to_string(scoreJ1) + " | " + to_string(scoreJ2));
		CircleShape circleShape(15);
	circleShape.setPosition(ballPosX, ballPosY);
	RectangleShape rectangleShape(Vector2f(RaquettesWidth, RaquettesHeight));
	rectangleShape.setPosition(posRaquettesLeftX, posRaquettesRightY);
	RectangleShape rectangleShape2(Vector2f(RaquettesWidth, RaquettesHeight));
	rectangleShape2.setPosition(posRaquettesRightX, posRaquettesRightY);
	while (window.isOpen())
	{

		Event event; 
		
		while (window.pollEvent(event))
		{
			input.InputHandler(event, window);
		}
		CheckBtn();
		RaquetteIA();
		rectangleShape.setPosition(posRaquettesLeftX, posRaquettesLeftY);
		rectangleShape2.setPosition(posRaquettesLeftX, posRaquettesLeftY);
			UpdateBall();
		circleShape.setPosition(ballPosX, ballPosY);
		window.clear(Color::Black);
		window.draw(txt);
		window.draw(circleShape);
		window.draw(rectangleShape);
		window.draw(rectangleShape2);
	}
	return 0;
}
```

> On Lui indique quelle police Utiliser : 
```ts
	txt.setFont(font);
```
> on indique la chaine de caractéres à afficher :
```ts
	txt.setString(str);
```
> indique la taille de la police d'écriture :
```ts
	txt.setCharacterSize(26);
```
> En indique La couleur :
```ts
	txt.setFillColor(Color::White);
```
> la position : 
```ts
	txt.setPosition((WIN_WIDTH / 2) - 40, 10);
```

> `Propriété RAquette gauche`

```ts
	if (input.GetButton().up == true)
	{
		posRaquettesLeftY -= RaquettesSpeed;
		if (posRaquettesLeftY < 0)
			posRaquettesLeftY = 0;
	}
	if (input.GetButton().down == true)
	{
		posRaquettesLeftY += RaquettesSpeed;
		if (posRaquettesLeftY + RaquettesHeight > WIN_HEIGHT)
			posRaquettesLeftY = WIN_HEIGHT - RaquettesHeight;
	}
```
> `Propriété RAquette Droite`

```ts
	if (input.GetButton().left == true)
	{
		posRaquettesRightY -= RaquettesSpeed;
		if (posRaquettesRightY < 0)
			posRaquettesRightY = 0;
	}
	if (input.GetButton().right == true)
	{
		posRaquettesRightY += RaquettesSpeed;
		if (posRaquettesRightY + RaquettesHeight > WIN_HEIGHT)
			posRaquettesRightY = WIN_HEIGHT - RaquettesHeight;
	}
	if (input.GetButton().escape == true)
	{
		window.close();
	}
```
##  jeux de pong : 
![GIF (2)](https://user-images.githubusercontent.com/96379214/150384991-d9ca29a7-a9bb-44ff-b157-dc1d083d8c5c.gif)
