/**
@title conjuntoRasgos.h
@class conjuntoRasgos
@brief Clase para el almacenamiento de un conjunto de TDA rasgo
@author Borja Molina Zea. borja.mz8@gmail.com
@date 15/05/2009
*/

#ifndef _conjuntoRasgos
#define _conjuntoRasgos

#include<new>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include"rasgo.h"

using namespace std;

class conjuntoRasgos{
	private:
		int tam; //Tamaño del conjunto (Número total de rasgos que puede albergar)
		rasgo* datos; //Puntero al conjunto de rasgos
	
	public:
		/**
		@brief Crea un conjunto de rasgos vacio.
		*/
		conjuntoRasgos();
		
		/**
		@brief Constructor de copias de la clase.
		@param otro. Objeto a copiar.
		*/
		conjuntoRasgos(const conjuntoRasgos& otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		conjuntoRasgos& operator= (const conjuntoRasgos& otro);
		
		/**
		@brief Destructor de la clase. Libera los recursos asociados a un conjunto de rasgos.
		*/
		~conjuntoRasgos();
		
		/**
		@brief Obtiene un rasgo del conjunto
		@param i. Número del rasgo.
		@return El rasgo obtenido.
		*/
		rasgo get(int i);
		
		/**
		@return El número de rasgos del conjunto.
		*/
		int tamanho();
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator>> (istream& in, conjuntoRasgos& otro);
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend ostream& operator<< (ostream& out, const conjuntoRasgos& otro);
		
	private:
		/**
		@brief Crea un conjunto de rasgos de un tamaño dado
		@param n. Tamaño del conjunto a crear.
		*/
		void crear(int n);
		
		/**
		@brief Copia un conjunto de rasgos en otro.
		@param otro. Conjunto a copiar.
		*/
		void copiar(const conjuntoRasgos& otro);			
		
		/**
		@brief Libera los recursos asociados a un conjunto de rasgos.
		*/
		void liberarMemoria();
};

#endif
