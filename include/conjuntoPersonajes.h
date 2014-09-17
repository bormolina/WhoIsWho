/**
@class conjuntoPersonaje
@brief Clase para el almacenamiento de un conjunto de TDA personaje
@author Borja Molina Zea. borja.mz8@gmail.com
@date 15/05/2009
*/

#ifndef _conjuntoPersonajes
#define _conjuntoPersonajes

#include<new>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include"personaje.h"

using namespace std;

class conjuntoPersonajes{
	private:
		int tam; //Tamaño del conjunto (Número total de Personajes que puede albergar)
		personaje* datos; //Puntero al conjunto de Personajes
	
	public:
		/**
		@brief Crea un conjunto de personajes vacio.
		*/
		conjuntoPersonajes();
		
		/**
		@brief Constructor de copias de la clase.
		@param otro. Objeto a copiar.
		*/
		conjuntoPersonajes(const conjuntoPersonajes& otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		conjuntoPersonajes& operator= (const conjuntoPersonajes& otro);
		
		/**
		@brief Destructor de la clase. Libera los recursos asociados a un conjunto de personajes.
		*/
		~conjuntoPersonajes();
		
		/**
		@brief Obtiene un personaje del conjunto
		@param i. Número del personaje.
		@return El personaje obtenido.
		*/
		personaje get(int i);
		
		/**
		@return El número de personajes del conjunto.
		*/
		int tamanho();
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator>> (istream& in, conjuntoPersonajes& otro);
		
		/**
		@brief Sobrecarga del operador de extración <<
		*/
		friend ostream& operator<< (ostream& out, const conjuntoPersonajes& otro);
		
	private:
		/**
		@brief Crea un conjunto de personajes de un tamaño dado
		@param n. Tamaño del conjunto a crear.
		*/
		void crear(int n);
		
		/**
		@brief Copia un conjunto de personajes en otro.
		@param otro. Conjunto a copiar.
		*/
		void copiar(const conjuntoPersonajes& otro);			
		
		/**
		@brief Libera los recursos asociados a un conjunto de personajes.
		*/
		void liberarMemoria();
};

#endif
