/**
@title rasgo.h
@class rasgo
@brief Clase para la gestión del TDA rasgo. Guarda la informción de un rasgo físico de los personajes del quien es quien
@author Borja Molina Zea. borja.mz8@gmail.com
@date 13/05/2009
*/

#ifndef _rasgo
#define _rasgo

#include<fstream>
#include<new>
#include<cstring>
#include<iostream>
#include<cstdlib>

using namespace std;

class rasgo{
	
	private:
		char* nombre; //Nombre del rasgo.
		char* patron; //Patrón para la realización de la pregunta.
		int nValores; //Número de valores que el rasgo puede tomar.
		char** valores; //Array donde se almacenan todos estos valores.
	
	public:
		/**
		@brief Constructor de la clase. Crea un rasgo "vacio".
		*/
		rasgo();
		
		/**
		@brief Constructor de copias de la clase.
		@param otro. Objeto a copiar.
		*/
		rasgo(const rasgo& otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		rasgo& operator= (const rasgo& otro);
		
		/**
		@brief Destructor de la clase. Libera los recursos asociados a un rasgo.
		*/
		~rasgo();
		
		/**
		@return El nombre del rasgo.
		*/
		char* getNombre();
		
		/**
		@return El patrón del rasgo.
		*/
		char* getPatron();
		
		/**
		@return El número de posible valores del rasgo.
		*/
		int getNValores();
		
		/**
		@return El valor n-ésimo del rasgo.
		*/
		char* getValores(int n);
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator>>(istream& in, rasgo& otro);
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend ostream& operator<<(ostream& out, const rasgo& otro);
		
	private:
		/**
		@brief Copia el contenido del rasgo otro en el rasgo implícito.
		*/
		void copiar(const rasgo& otro);
		
		/**
		@brief Libera la memoria asociada a un rasgo.
		*/
		void liberarMemoria();
};

#endif
