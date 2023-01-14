#include <stdio.h>

// Programa que le pide al usuario el valor de la base y la altura de un rectangulo y regresa su area.
int main(){
	int base, altura, area;
	
	// Obtener base
	printf("Por favor, ingrese el valor de la base del rectangulo: \n");
	scanf("%d", &base);
	
	// Obtener altura
	printf("Por favor, ingrese el valor de la altura del rectangulo: \n");
	scanf("%d", &altura);
	
	// Calcular area
	area = base * altura;
	
	// Imprimir area
	printf("El area del rectangulo es %d", area);
	
	return 0;
}

// Una disculpa por las faltas de ortografia, no se como poner acentos en este IDE. :(
