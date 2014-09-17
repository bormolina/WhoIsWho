#include"personaje.h"

personaje::personaje(){
	nombre=ruta=0;
	nRasgos=0;
	rasgos=valores=0;
}

personaje::personaje(const personaje& otro){
	copiar(otro);
}

personaje& personaje::operator=(const personaje& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);
	}
	return *this;
}

personaje::~personaje(){
	liberarMemoria();
}

bool personaje::operator==(const personaje& otro){
	bool iguales;
	//Comparamos el nombre de los personajes, sino es igual son los mismos, sino son distintos
	if(strcmp(nombre,otro.nombre)==0)
		iguales=true;
	else
		iguales=false;
	
	return iguales;
}

bool personaje::operator!=(const personaje& otro){
	return !(*this==otro);
}

void personaje::dibujar(int x, int y){
	imagen pj(ruta);
	pj.dibujar(x,y);
}

int personaje::getNRasgos(){
	return nRasgos;	
}

char* personaje::getNombre(){
	return nombre;
}

char* personaje::getRasgo(int n){
	return rasgos[n];
}
		
char* personaje::getValor(int n){
	return valores[n];
}

int personaje::alto(){
	int alt=0;
	if(ruta){
		imagen temp(ruta);
		alt=temp.alto();
	}	
	return alt;
}

int personaje::ancho(){
	int alt=0;
	if(ruta){
		imagen temp(ruta);
		alt=temp.ancho();
	}	
	return alt;
}

istream& operator>>(istream& in, personaje& otro){
	char buffer[9999];
		
	//Leemos el nombre el personaje
	in.getline(buffer,9999);
	otro.nombre=new(nothrow) char[strlen(buffer)+1];
	if(!otro.nombre){cerr<<"Error en la reserva de memoria 5\n";exit(1);}
	strcpy(otro.nombre,buffer);
	
	//Leemos la ruta de la imagen
	in.getline(buffer,9999);
	otro.ruta=new(nothrow) char[strlen(buffer)+1];
	if(!otro.ruta){cerr<<"Error en la reserva de memoria 6\n";exit(1);}
	strcpy(otro.ruta,buffer);
	
	
	//Leemos el numero de rasgos
	in.getline(buffer,9999);
	otro.nRasgos=atoi(buffer);
	otro.rasgos=new(nothrow) char*[otro.nRasgos];
	if(!otro.rasgos){cerr<<"Error en la reserva de memoria 7\n";exit(1);}
	
	otro.valores=new(nothrow) char*[otro.nRasgos];
	if(!otro.valores){cerr<<"Error en la reserva de memoria 8\n";exit(1);}
	
	//Leemos los rasgos del personaje y sus valores
	for(int i=0;i<otro.nRasgos;i++){
		in.getline(buffer,9999);
		otro.rasgos[i]=new(nothrow) char[strlen(buffer)+1];
		if(!otro.rasgos[i]){cerr<<"Error en la reserva de memoria 9\n";exit(1);}
		strcpy(otro.rasgos[i],buffer);
		
		in.getline(buffer,9999);
		otro.valores[i]=new(nothrow) char[strlen(buffer)+1];
		if(!otro.valores[i]){cerr<<"Error en la reserva de memoria 10\n";exit(1);}
		strcpy(otro.valores[i],buffer);	
	}	
	return in;
}

ostream& operator<<(ostream& out, const personaje& otro){
	out<<otro.nombre<<endl<<otro.ruta<<endl<<otro.nRasgos<<endl;
	for(int i=0;i<otro.nRasgos;i++){
		out<<otro.rasgos[i]<<endl;
		out<<otro.valores[i]<<endl;
	}
	return out;
}

void personaje::copiar(const personaje& otro){
	if(otro.nRasgos>0){//Comprobamos que no se trate de un personaje vacio
		nRasgos=otro.nRasgos;
		
		nombre=new(nothrow) char[strlen(otro.nombre)+1];
		if(!nombre){cerr<<"Error en la reserva de memoria 1\n";exit(1);}
		strcpy(nombre,otro.nombre);
		
		ruta=new(nothrow) char[strlen(otro.ruta)+1];
		if(!ruta){cerr<<"Error en la reserva de memoria 2\n";exit(1);}
		strcpy(ruta,otro.ruta);
		
		rasgos=new(nothrow) char*[nRasgos];
		if(!rasgos){cerr<<"Error en la reserva de memoria 3\n";exit(1);}
		
		valores=new(nothrow) char*[nRasgos];
		if(!valores){cerr<<"Error en la reserva de memoria 3.2\n";exit(1);}
		
		for(int i=0;i<nRasgos;i++){
			rasgos[i]=new(nothrow) char[strlen(otro.rasgos[i])+1];
			if(!rasgos[i]){cerr<<"Error en la reserva de memoria 4\n";exit(1);}
			strcpy(rasgos[i],otro.rasgos[i]);
			valores[i]=new(nothrow) char[strlen(otro.valores[i])+1];
			if(!valores[i]){cerr<<"Error en la reserva de memoria 4.2\n";exit(1);}
			strcpy(valores[i],otro.valores[i]);
		}
	}
	
	else{//Si se trata de un personaje "vacio"
		nombre=ruta=0;
		nRasgos=0;
		rasgos=valores=0;
	}
}

void personaje::liberarMemoria(){
	delete[] nombre;
	delete[] ruta;
	for(int i=0;i<nRasgos;i++){
		delete[] rasgos[i];
		delete[] valores[i];
	}
	delete[] rasgos;
	delete[] valores;
}
