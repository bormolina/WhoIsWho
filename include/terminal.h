/**
@title terminal.h
@class terminal
@brief Clase para la gestión de la terminal, en la se irán mostrando distintos mensajes informativo a lo largo del juego.
@author Borja Molina Zea. borja.mz8@gmail.com
@date 27/05/2009
*/

#ifndef _terminal
#define _terminal

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<new>
#include"graficos.h"
#include"funcionesAuxiliares.h"
#include"personaje.h"

using namespace std;
using namespace graficos;

//Estructura para una linea de texto. Contiene el texto de la misma y de quien es ese texto, si del humano o de la máquina
struct LineaTexto{
	char texto[999];
	bool humano;
};

class terminal{
	private:
		LineaTexto* lineas; //Puntero a todas las lineas de texto de la terminal
		int nMaxLineas;//Número máximo de lineas en la terminal
		int nLineas;//Número de lineas ocupadas por texto en la terminal
		int x1,y1;//Posicion de una linea
		
		//Variables acerca del posicionamiento en pantalla y tamaño de la terminal
		int x,y;
		int ancho,alto;
		int colorFondo[3];
		int anchoMarco,altoMarco;
		int colorMarco[3];
		
		//Ruta, tamaño y color de la fuente usada
		char* ruta;
		GRF_Fuente font;
		int tamFuente;
		int colorFuente[3];
	
		char* nombreJugador;//Nombre del jugador humano
		char* nombreMaquina;//Nombre del juagador máquina
		
	public:
		/**
		@brief Crea una terminal vacia.
		*/
		terminal();
		
		/**
		@brief Constructor de copias de la clase.
		@param otro Objeto de la clase que se copiara
		*/
		terminal(const terminal& otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		terminal& operator =(const terminal& otro);
		
		/**
		@brief Destructor de la clase. Libera los recursos asociados a una terminal.
		*/
		~terminal();		
		
		/**
		@brief Dibuja en pantalla una terminal.
		*/
		void dibujar();
		
		/**
		@brief Inserta una linea de texto en la terminal.
		@param text. Texto de la linea.
		@param human. Indica si una linea de texto es insertada por el jugador humano o por la máquina.
		*/
		void insertarLinea(const char* text, bool human);
		
		/**
		@brief Borra la última linea escrita en la terminal.
		*/
		void borrarLinea();
		
		/**
		@brief Hace una pregunta del tipo ¿Es fulanito el personaje oculto?
		@param ultimo. Personaje sobre el que se pregunta si es él el oculto.
		@param human. Indica si la pregunta la realiza la termina o la máquina.
		*/
		void preguntarPorPersonaje(personaje ultimo, bool human);
		
		/**
		@brief Muesta un mensaje de error cuando se teclea un número incorrecto.
		*/
		void mensajeError();
		
		/**
		@brief Muesta un mensaje de error nos hemos equivocado al encontrar el personaje oculto de la máquina.
		*/
		void mensajeError2();
		
		/**
		@brief Muesta un mensaje de victoria cuando el jugador humano a ganado.
		*/
		void mensajeVictoria();
		
		/**
		@brief Muesta un mensaje de derrota cuando el jugador máquina a ganado.
		*/
		void mensajeDerrota();
		
		/**
		@brief Establece el nombre del jugador humano.
		@param nombre. Nombre del jugador humano.
		*/
		void setNombreJugador(const char* nombre);
		
		/**
		@brief Establece el nombre del jugador máquina.
		@param nombre. Nombre del jugador máquina.
		*/
		void setNombreMaquina(const char* nombre);
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator>> (istream& in, terminal& otro);
		
		/**
		@brief Sobrecarga del operador de extración <<
		*/
		friend ostream& operator<< (ostream& out, const terminal& otro);
	
	private:
		/**
		@brief Copia la terminal otro.
		@param otro La terminal a copiar.
		*/
		void copiar(const terminal& otro);
		
		/**
		@brief Libera los recursos asociados a una terminal.
		*/
		void liberarMemoria();
};

#endif

