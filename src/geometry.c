#include <stdio.h>
#include <geometry.h>
#include <math.h>

//Basic geometry functions

Point2D pointXY(float x, float y) { 
	//Construit le point (x, y)
	Point2D P;
	P.x = x;
	P.y = y;
	return P;
}

Vector2D vectorXY(float x, float y) {
	//Construit le vecteur (x, y)
	Vector2D V;
	V.x = x;
	V.y = y;
	return V;
}

Vector2D vector(Point2D A, Point2D B) {
	//Construit le vecteur AB = B − A
	return vectorXY(B.x - A.x, B.y - A.y);	 
}

Point2D pointPlusVector(Point2D P, Vector2D V) { 
	//Construit le point P + V
	return pointXY(P.x + V.x, P.y + V.y);
}

Vector2D addVectors(Vector2D A, Vector2D B) {
	//fonction d’addition de vecteurs
	return vectorXY(A.x + B.x, A.y + B.y);
}

Vector2D subVectors(Vector2D A, Vector2D B) {
	//fonction de soustraction de vecteurs
	return vectorXY(A.x - B.x, A.y - B.y);
}

Vector2D multVector(Vector2D V, float a) {
	//fonction de multiplication d’un vecteur par un scalaire
	return vectorXY(V.x * a, V.y * a);
}

Vector2D divVector(Vector2D V, float a) {
	//fonction de division d’un vecteur par un scalaire
	if (a != 0) {
		return vectorXY(V.x / a, V.y / a);
	}
	return V;
}

float dot(Vector2D A, Vector2D B) {
	//Fonction calculant le produit scalaire de deux vecteurs
	//produit des longueurs d'un vecteur et de l'autre projeté sur lui
	return A.x * B.x + A.y * B.y;
}

float norm(Vector2D A) {
	//fonction calculant la norme d’un vecteur 
	return sqrtf(dot(A,A));
}

Vector2D normalize(Vector2D A) { 
	//fonction retournant le vecteur normalisé passé en paramètre 
	float lenght = norm(A);
	if (lenght != 0) {
		divVector(A, lenght);
	}
	return A;
}

void printVector2D(Vector2D V) {
	//affiche les 2 composantes de V
	printf("(%f, %f)", V.x, V.y);
}

void printPoint2D(Point2D P) {
	//affiche les 2 composantes de P
	printf("(%f, %f)", P.x, P.y);
}
