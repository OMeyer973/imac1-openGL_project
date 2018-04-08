#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <stdio.h>
#include <math.h>

//Basic geometry elements & functions

typedef struct vec2 {
	float x, y;
} Vec2, Point2D, Vector2D;

Point2D pointXY(float x, float y); 
	//Construit le point (x, y)
Vector2D vectorXY(float x, float y); 
	//Construit le vecteur (x, y) 
Vector2D vector(Point2D A, Point2D B);
	//Construit le vecteur AB = B − A  
Point2D pointPlusVector(Point2D P, Vector2D V); 
	//Construit le point P + V 
Vector2D addVectors(Vector2D A, Vector2D B);
Vector2D subVectors(Vector2D A, Vector2D B);
	//fonctions d’addition et soustraction de vecteurs 
Vector2D multVector(Vector2D V, float a);
Vector2D divVector(Vector2D V, float a); 
	//fonctions de multiplication et division d’un vecteur par un scalaire  
float dot(Vector2D A, Vector2D B); 
	//Fonction calculant le produit scalaire de deux vecteurs 
float norm(Vector2D A); 
	//fonction calculant la norme d’un vecteur 
Vector2D normalize(Vector2D A); 
	//fonction retournant le vecteur normalisé passé en paramètre
void printVector2D(Vector2D A);
	//affiche les 2 composantes de V
void printVector2D(Vector2D A);
	//affiche les 2 composantes de P



#endif