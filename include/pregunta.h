/**
@title pregunta .h
@class prengunta
@brief Clase para gestión de preguntas asociadas a un conjunto de rasgos.
@author Borja Molina Zea. borja.mz8@gmail.com
@date 21/05/2009
*/

#ifndef _pregunta
#define _pregunta

#include<new>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include"funcionesAuxiliares.h"
#include"rasgo.h"

class pregunta{
	private:
		char* nombre; //Nombre del rasgo del que se realiza la pregunta. PJ: color del pelo
		char* valor; //Valor del rasgo. PJ: negro
		char* enunciado;//Enunciado de la pregunta. PJ:¿Tiene el perlo negro?
	
	public:
		/**
		@brief Constructor de la clase. Crea una pregunta vacia.
		*/
		pregunta();
		
		/**
		@brief Constructor de copias de la clase.
		@param otro Objeto de la clase que se copiara
		*/
		pregunta(const pregunta& otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		pregunta& operator=(const pregunta& otro);
		
		/**
		@brief Destructor de la clase. Libera los recursos asociados a una pregunta
		*/
		~pregunta();
		
		/**
		@brief Operador lógico ==. Compara dos preguntas.
		@return true sin los dos personajes son iguales. False en otro caso.
		*/
		bool operator==(const pregunta& otro);
		
		/**
		@brief Operador lógico !=. Compara dos preguntas. 
		@return true si los dos personajes son distintos. False en otro caso.
		*/
		bool operator!=(const pregunta& otro);
		
		/**
		@return El nombre rasgo de la pregunta.
		*/
		char* getNombre();
		
		/**
		@return El valor rasgo de la pregunta.
		*/
		char* getValor();
		
		/**
		@return El enunciado de la pregunta.
		*/
		char* getEnunciado();
		
		/**
		@brief Establece el enunciado de una pregunta a partir de un rasgo y el valor del mismo
		@param n. El número del posible valor del rasgo. PJ: rasgo->Color pelo, valores->negro, rubio ,marron. n=0. Crearía-> ¿Tiene el pelo negro?
		*/
		void set(rasgo otro, int n);	
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend ostream& operator<<(ostream& out, const pregunta& otro);
	
	private:
		/**
		@brief Copia una pregunta en otra.
		@param otro. pregunta a copiar.
		*/
		void copiar(const pregunta& otro);
		
		/**
		@brief Libera los recursos asociados a un conjunto de rasgos.
		*/
		void liberarMemoria();
};

#endif
