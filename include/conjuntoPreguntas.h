/**
@class conjuntoPreguntas 
@brief Clase para gestión de un conjunto del TDA pregunta.
@author Borja Molina Zea. borja.mz8@gmail.com
@date 22/05/2009
*/

#ifndef _conjuntoPreguntas
#define _conjuntoPreguntas
#include "pregunta.h"
#include "graficos.h"
#include "conjuntoRasgos.h"
#include "personaje.h"
#include<iostream>
using namespace std;

class conjuntoPreguntas{
	private:
		//Variables acerca del posicionamiento en pantalla y tamaño de la zona de preguntas
		int x,y;
		int ancho, alto;
		int colorFondo[3];
		int anchoMarco, altoMarco;
		int colorMarco[3];
		
		//Ruta, tamaño y color de la fuente usada
		char* ruta;
		GRF_Fuente tipoFuente;
		int tamFuente;
		int colorFuente[3];
		
		int tam;//Número de preguntas
		pregunta* preguntas;//Puntero a todas las preguntas.
		bool* realizadas;//Vector de booleanos. Indica si la pregunta i-ésima ha sido o no realizada.
	
	public:
		/**
		@brief Crea un conjunto de preguntas a partir de un conjunto de rasgos. Genera todas las posibles pregunta sobre ese conjunto de rasgos.
		@param rasgos. Conjunto de rasgos a partir del cual se crearán las posibles preguntas.
		*/
		conjuntoPreguntas(conjuntoRasgos& rasgos);
		
		/**
		@brief Constructor de copias de la clase.
		@param otro. Objeto a copiar.
		*/
		conjuntoPreguntas(const conjuntoPreguntas& otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		conjuntoPreguntas& operator=(const conjuntoPreguntas& otro);
		
		/**
		@brief Destructor de la clase. Libera los recursos asociados a un conjunto de preguntas.
		*/
		~conjuntoPreguntas();
		
		/**
		@return El número de preguntas del conjunto.
		*/
		int tamanho();
		
		/**
		@brief Obtiene una pregunta del conjunto
		@param i. Número de la pregunta.
		@return La pregunta obtenida.
		*/
		pregunta getPregunta(int n);
		
		/**
		@brief Obtiene una pregunta de forma aleatoria del conjunto
		@return La pregunta obtenida.
		*/
		pregunta getAleatoria();
		
		/**
		@brief Responde una pregunta realizada sobre un personaje
		@param pj. Personaje sobre el que se realiza la pregunta.
		@param realizada. Pregunta sobre el personaje
		@return true si la respuesta es afirmativa, en caso contrario false
		*/
		bool responder(personaje& pj, pregunta& realizada);
		
		/**
		@brief Dibuja en pantalla un conjunto de botones
		*/
		void dibujar();
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator>>(istream& in, conjuntoPreguntas& otro);
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend ostream& operator<<(ostream& out, const conjuntoPreguntas& otro);
	
	private:
		/**
		@brief Copia un conjunto de preguntas en otro.
		@param otro. Conjunto a copiar.
		*/
		void copiar(const conjuntoPreguntas& otro);
		
		/**
		@brief Libera los recursos asociados a un conjunto de preguntas.
		*/
		void liberarMemoria();	
};

#endif
