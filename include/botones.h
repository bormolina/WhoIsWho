/**
@title botones.h
@class botones
@brief Clase para gestión de la zona de botones e información del juego.
@author Borja Molina Zea. borja.mz8@gmail.com
@date 26/05/2009
*/

#ifndef _botones
#define _botones

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<new>
#include"graficos.h"
#include"funcionesAuxiliares.h"

using namespace std;
using namespace graficos;

class botones{
	private:
		//Variables acerca del posicionamiento en pantalla y tamaño de la zona de botones e información
		int x,y;
		int ancho,alto;
		int colorFondo[3];
		int anchoMarco,altoMarco;
		int colorMarco[3];
		
		//Variables acerca del posicionamiento en pantalla y tamaño del recuadro del tiempo acumulado por el jugador
		int xTiempo,yTiempo;
		int anchoTiempo,altoTiempo;
		int colorFondoTiempo[3];
		int anchoMarcoTiempo,altoMarcoTiempo;
		int colorMarcoTiempo[3];
		
		//Variables acerca del posicionamiento en pantalla y tamaño del botón de stop
		int xStop,yStop;
		int anchoStop,altoStop;
		int colorFondoStop[3];
		int anchoMarcoStop,altoMarcoStop;
		int colorMarcoStop[3];
		
		//Variables acerca del posicionamiento en pantalla y tamaño del cronómetro
		int xCrono,yCrono;
		int anchoCrono,altoCrono;
		int colorFondoCrono[3];
		int anchoMarcoCrono,altoMarcoCrono;
		int colorMarcoCrono[3];
		
		//Variables acerca del posicionamiento en pantalla y tamaño del botón de restaurar tablero
		int xRestaurar,yRestaurar;
		int anchoRestaurar,altoRestaurar;
		int colorFondoRestaurar[3];
		int anchoMarcoRestaurar,altoMarcoRestaurar;
		int colorMarcoRestaurar[3];
		
		int colorCrono[3];
		
		//Ruta, tamaño y color de la fuente usada
		char* ruta;
		GRF_Fuente font;
		int tamFuente;
		int colorFuente[3];
		
		int tiempo;//Tiempo para responder
		int tTranscurrido;//Tiempo total transcurrido desde que se inciara la partida
		
	public:
		/**
		@brief Constructor de la clase. Crea una zona de botones vacia.
		*/
		botones();
		
		/**
		@brief Constructor de copias de la clase.
		@param otro Objeto de la clase que se copiara
		*/
		botones(const botones& otro);
		
		/**
		@brief Operador igual. Iguala una zona de botones a otro
		@param otro Objeto al que se igualara el objeto left-value
		*/
		botones& operator=(const botones& otro);
		
		/**
		@brief Destructor de la clase. Libera los recursos asociados a una zona de botones
		*/
		~botones();
		
		/**
		@brief Dibuja en pantalla una zona de botones
		*/
		void dibujar();
		
		/**
		@brief Actualiza el cronómetro.
		@param tiempoTranscurrido. Valor con el que se actualizará el cronómetro.
		*/
		void actualizar(long tiempoTrasncurrido);
		
		/**
		@brief Suma una puntuacion al recuadro de puntuación de un jugador.
		@param t. Puntuación a sumar.
		*/
		void sumarPuntuacion(int t);
		
		/**
		@brief Indica si el botón de stop ha sido pulsado.
		@param x. Coordenada x en la que se pulsó con el ratón.
		@param y. Coordenada y en la que se pulsó con el ratón.
		@return true si el boton stop ha sido pulsado, false si no.
		*/
		bool stop(int x, int y);
		
		/**
		@brief Indica si el botón de restaurar ha sido pulsado.
		@param x. Coordenada x en la que se pulsó con el ratón.
		@param y. Coordenada y en la que se pulsó con el ratón.
		@return true si el boton restaurar ha sido pulsado, false si no.
		*/
		bool restaurar(int x, int y);
		
		/**
		@brief Pone el cronómetro a cero.
		*/
		void resetCrono();
		
		/**
		@brief Establece el tiempo que el jugador tiene para tachar personajes.
		@param t. Tiempo que tiene el usuario para tachar los personajes del tablero en cada turno.
		*/
		void setTiempo(int t);
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator>>(istream& in, botones& otro);
		
		/**
		@brief Sobrecarga del operador de extración <<
		*/
		friend ostream& operator<<(ostream& out, const botones& otro);
	
	private:
		/**
		@brief Copia una zona de botones en otra
		@param otro Objeto de la clase que se copiara
		*/
		void copiar(const botones& otro);
		
		/**
		@brief Libera los recursos asociados a una zona de botones.
		*/
		void liberarMemoria();
};

#endif
