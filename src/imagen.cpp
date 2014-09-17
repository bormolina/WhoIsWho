#include "imagen.h"

imagen::imagen(){
	img=0; 
}

imagen::imagen(int ancho, int alto){
	img=CrearImagen(ancho,alto);
}

imagen::imagen(const char* ruta){
	img=LeerImagen(ruta);
}

imagen::imagen(const imagen& otra){
	img=ObtenerCopiaImagen(otra.img);
}

imagen::~imagen(){
	LiberarImagen(img);
}

imagen& imagen::operator=(const imagen& otra){
	if (this != &otra){
		LiberarImagen(img);
		img=ObtenerCopiaImagen(otra.img);
		}
	return *this;
}

int imagen::alto()const{
	return AltoImagen(img);
}

int imagen::ancho()const{
	return AnchoImagen(img);
}

void imagen::leer(const char* ruta){
	if(img!=0)//Si la imagen ya contien algo lo borramos antes asignarle nuevos valores.
		LiberarImagen(img);
	img=LeerImagen(ruta);
}

void imagen::dibujar(int x, int y)const{
	if(img!=0)
		DibujarImagen(img,x,y);
}

void imagen::limpiar(){
	LimpiarImagen(img);
}

istream& operator>> (istream& in, imagen& img){
	char buffer[999];
	in.getline(buffer,999);
	img.leer(buffer);
	return in;
}
