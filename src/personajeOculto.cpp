#include "personajeOculto.h"

personajeOculto::personajeOculto(conjuntoPersonajes& fichas, bool modo){
	/*
	Tenemos dos modos de generar el personaje oculto.
	Esto es así, debido a que al generar un numero aleatorio este depende del reloj del sistema.
	Por lo tanto si se generan dos aleatorios muy seguido en verdad se nos devuelve el mismo número.
	Por ello un aleatorio lo generamos usando nuestra funcion de generar aleatorios del 0 al número de personajes máximo.
	Y el otro simplemente generamos un aleatorio entre 0 y 1000 y a ese número le hacemos % número de personajes máximo
	*/
	if(modo) PJoculto=fichas.get(aleatorio(fichas.tamanho()-1));
	else{
		PJoculto=fichas.get(aleatorio(1000)%fichas.tamanho());
	}
	
	ocultado=false;
}
		
personajeOculto::personajeOculto(const personajeOculto&  otro){
	copiar(otro);
}

personajeOculto& personajeOculto::operator= (const personajeOculto& otro){
	if(this!=&otro)
		copiar(otro);
	return *this;
}

bool personajeOculto::operator== (personaje& otro) {
	return(PJoculto==otro);
}

bool personajeOculto::operator!= (personaje& otro) {
	return(PJoculto!=otro);
}

personaje personajeOculto::getPersonaje(){
	return PJoculto;
}

void personajeOculto::ocultar(){
	ocultado=true;
	oculto.leer(ruta);	//Establecemos la imagen de jugador oculto
}

void personajeOculto::setRuta(const char* rutaImagen){
	strcpy(ruta,rutaImagen);
}

void personajeOculto::dibujar(){
	RectanguloR(x, y, x+ancho, y+alto, colorFondo[0], colorFondo[1], colorFondo[2]);
	DibujarMarco(anchoMarco,altoMarco,x,y,x+ancho,y+alto,colorMarco);
	if(ocultado==false)
		PJoculto.dibujar(x+anchoMarco, y+altoMarco);
	
	//Si es oculto lo dibujamos con la imagen de oculto en vez de con la que le correspondería
	else
		oculto.dibujar(x+anchoMarco, y+altoMarco);
	
		
}

istream& operator>>(istream& in, personajeOculto& otro){
	char buffer[999],buffer1[999],buffer2[999],buffer3[999];
	
	//Leemos del fichero de configuración todos los datos referentes a un personaje oculto.
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.x=atoi(buffer1);
	otro.y=atoi(buffer2);
		
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.ancho=atoi(buffer1);
	otro.alto=atoi(buffer2);
	
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFondo[0]=atoi(buffer1);
	otro.colorFondo[1]=atoi(buffer2);
	otro.colorFondo[2]=atoi(buffer3);
	
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoMarco=atoi(buffer1);
	otro.altoMarco=atoi(buffer2);
	
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorMarco[0]=atoi(buffer1);
	otro.colorMarco[1]=atoi(buffer2);
	otro.colorMarco[2]=atoi(buffer3);
	
	return in;
}

ostream& operator<<(ostream& out,const personajeOculto& otro){
	out<<otro.PJoculto<<otro.x<<endl<<otro.y<<endl<<otro.ancho<<endl<<otro.alto<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorFondo[i]<<endl;
	out<<otro.altoMarco<<endl<<otro.anchoMarco<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorMarco[i]<<endl;
	out<<otro.ruta<<endl<<otro.ocultado<<endl;
	return out;
}
	
void personajeOculto::copiar(const personajeOculto& otro){
	PJoculto=otro.PJoculto;
	x=otro.x;
	y=otro.y;
	ancho=otro.ancho;
	alto=otro.alto;
	for(int i=0;i<3;i++)
		colorFondo[i]=otro.colorFondo[i];
	anchoMarco=otro.anchoMarco;
	altoMarco=otro.altoMarco;
	for(int i=0;i<3;i++)
		colorMarco[i]=otro.colorMarco[i];
	strcpy(ruta,otro.ruta);
	oculto=otro.oculto;
	ocultado=ocultado;
}
