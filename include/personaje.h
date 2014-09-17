/**
@title personaje.h
@class personaje
@brief Clase para la gestión del TDA personaje. Guarda la informción de personaje del quien es quien
@author Borja Molina Zea. borja.mz8@gmail.com
@date 14/05/2009
*/

#ifndef _personaje
#define _personaje

#include<fstream>
#include<new>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include"imagen.h"

using namespace std;

class personaje{
	
	private:
		char* nombre; //Nombre del personaje.
		char* ruta; //Ruta de la imagen .bmp
		int nRasgos; //Números de rasgo se personaje.
		char** rasgos; //Rasgos del personaje.
		char** valores;//Valores de los rasgos del personaje.
			
	public:
		/**
		@brief Constructor de la clase. Crea un personaje "vacio".
		*/
		personaje();
		
		/**
		@brief Constructor de copias de la clase.
		@param otro. Objeto a copiar.
		*/
		personaje(const personaje& otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		personaje& operator=(const personaje& otro);
		
		/**
		@brief Destructor de la clase.
		*/
		~personaje();
		
		/**
		@brief Operador lógico ==. Compara dos personajes.
		@return true sin los dos personajes son iguales. False en otro caso.
		*/
		bool operator==(const personaje& otro);
		
		/**
		@brief Operador lógico !=. Compara dos personajes.
		@return true si los dos personajes son distintos. False en otro caso.
		*/
		bool operator!=(const personaje& otro);
		
		/**
		@brief Dibuja un personaje en la pantalla.
		@param x Coordenada del eje x donde queremos que el personaje se dibuje.
		@param y Coordenada del eje y donde queremos que el personaje se dibuje.
		*/
		void dibujar(int x, int y);
		
		/**
		@return El número de rasgos del personaje.
		*/
		int getNRasgos();
		
		/**
		@return El nombre del  personaje.
		*/
		char* getNombre();
		
		/**
		@return El rasgo i-ésimo del  personaje.
		*/
		char* getRasgo(int n);
		
		/**
		@return El valor del rasgo i-ésimo del  personaje.
		*/
		char* getValor(int n);
		
		/**
		@return El alto de la imagen asociada al personaje.
		*/
		int alto();
		
		/**
		@return El ancho de la imagen asociada al personaje.
		*/
		int ancho();
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator>>(istream& in, personaje& otro);
		
		/**
		@brief Sobrecarga del operador de extración <<
		*/
		friend ostream& operator<<(ostream& out, const personaje& otro);
	
	private:
		/**
		@brief Copia el personaje otro en el personaje implícito de la clase.
		@param otro El personaje a copiar.
		*/
		void copiar(const personaje& otro);
		
		/**
		@brief Libera la memoria asociada a un personaje.
		*/
		void liberarMemoria();
};

#endif
