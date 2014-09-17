/**
@title funcionesAuxiliares.h
@brief Conjunto de funciones auxiliares usadas en distintas partes del programa.
@author Borja Molina Zea. borja.mz8@gmail.com
@date 11/05/2009
*/

#ifndef _funcionesAuxiliares
#define _funcionesAuxiliares

#include <cstdlib>
#include <time.h>
#include "graficos.h"
#include <iostream>
#include <fstream>

using namespace graficos;
using namespace std;

/**
@brief Genera un número aleatorio entre 0 y n.
@pre n>0;
@param n. Maximo número aleatorio generable.
@return El número aleatorio generado.
*/
int aleatorio(int n);

/**
@brief Genera un número aleatorio escogiendolo entre un conjunto de números.
@param v. Array con el conjunto de números seleccionables. Si un número se encuentra repetido tendra mayor posibilidad de ser elegido.
@param tam. Tamaño del array v;
@return Un número cualquiera de array de enteros v.
*/
int aleatorio(int* v, int tam);

/**
@brief Busca un caracter en una cadena de caracteres y devuelve la posición en la que fue encontrado.
@param encontrar. Caracter que se quiere encontrar en la cadena.
@param ocurrencia. Número de ocurrencia por la que se quiere busacar, si 1 devuelve la posición de su primera aparición en la cadena, si dos su segunda apariación...;
@param cad. Cadena dónde se buscará el caranter
@return La poscición en la cadena del caracter. -1 en el caso de que no haya sido encontrado.
*/
int Buscar(char encontrar, int ocurrencia, char* cad);

/**
@brief Recoge un fichero de confuguración con comentarios y lo guarda sin comentarios en otro fichero sin alterar el original.
@param conComentarios Un fichero de config con comentarios.
@param sinComentarios El mismo fichero de config pero sin comentarios.
*/
void QuitarComentarios(istream& conComentarios, ostream& sinComentarios);


/**
@brief Dibuja un marco con los parámetros deseados
@param ancho. El ancho del marco.
@param alto. El alto del marco.
@param x1. Coordenada x del punto superior izqdo.
@param y1. Coordenada y del punto superior izqdo.
@param x2. Coordenada x del punto inferior derecha.
@param y2. Coordenada y del punto inferior derecha.
@param rgb. Color del marco.
*/
void DibujarMarco(int ancho, int alto, int x1, int y1, int x2, int y2, int rgb[3]);

/**
@brief Divide una cadena de caracteres en dos.
@param orig. Cadena a dividir.
@param destino1. Cadenas  donde se guarda la primera parte de orig.
@param destino2. Cadenas  donde se guarda la segunda parte de orig.
@param pos. Posicion en la que se cortará la cadena orig.
*/
void DividirEnDos(char* orig, char* destino1, char* destino2, int pos);

/**
@brief Divide una cadena de caracteres en tres.
@param orig. Cadena a dividir.
@param destino1. Cadenas  donde se guarda la primera parte de orig.
@param destino2. Cadenas  donde se guarda la segunda parte de orig.
@param destino2. Cadenas  donde se guarda la tercera parte de orig.
@param pos1. Posicion en la que se hara el primer corte.
@param pos1. Posicion en la que se hara el segundo corte.
*/
void DividirEnTres(char* orig, char* destino1, char* destino2, char* destino3, int pos1, int pos2);

/**
@brief Convierte un entero a un cadena de caracteres.
@param cadena. cadena en la que se almacenará el entero.
@param n. Número a transformar a cadena.
*/
void EnteroACadena(char* cadena, int n);

#endif
