#include"rasgo.h"

rasgo::rasgo(){
	nombre=patron=0;
	valores=0;
	nValores=0;	
}

rasgo::rasgo(const rasgo& otro){
	copiar(otro);
}

rasgo& rasgo::operator= (const rasgo& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);
	}
	return *this;
}

rasgo::~rasgo(){
	liberarMemoria();
}

char* rasgo::getNombre(){
	return nombre;	
}
		
char* rasgo::getPatron(){
	return patron;	
}
		
int rasgo::getNValores(){
	return nValores;	
}
		
char* rasgo::getValores(int n){
	return valores[n];
}

istream& operator>>(istream& in, rasgo& otro){
	char buffer[9999];
	
	//Leemos nombre del rasgo
	in.getline(buffer,9999);
	otro.nombre=new(nothrow) char[strlen(buffer)+1];
	if(!otro.nombre){cerr<<"Error en la reserva de memoria 5\n";exit(1);}
	strcpy(otro.nombre,buffer);
	
	//Leemos el patrón de la pregunta
	in.getline(buffer,9999);
	otro.patron=new(nothrow) char[strlen(buffer)+1];
	if(!otro.patron){cerr<<"Error en la reserva de memoria 6\n";exit(1);}
	strcpy(otro.patron,buffer);
		
	//Leemos el número de posibles valores para el rasgo.
	in.getline(buffer,9999);
	otro.nValores=atoi(buffer);
	otro.valores=new(nothrow) char*[otro.nValores];
	if(!otro.valores){cerr<<"Error en la reserva de memoria 7\n";exit(1);}
	
	//Leemos todos los posibles valores.
	for(int i=0;i<otro.nValores;i++){
		in.getline(buffer,9999);
		otro.valores[i]=new(nothrow) char[strlen(buffer)+1];
		if(!otro.valores[i]){cerr<<"Error en la reserva de memoria 8."<<i<<endl;exit(1);}
		strcpy(otro.valores[i],buffer);
	}
return in;
}

ostream& operator<<(ostream& out, const rasgo& otro){
	out<<otro.nombre<<endl<<otro.patron<<endl<<otro.nValores<<endl;
	for(int i=0;i<otro.nValores;i++)
		out<<otro.valores[i]<<endl;
	out<<endl;
	return out;
}

void rasgo::copiar (const rasgo& otro){
	nValores=otro.nValores;
		
	nombre=new(nothrow) char[strlen(otro.nombre)+1];
	if(!nombre){cerr<<"Error en la reserva de memoria 1\n";exit(1);}
	strcpy(nombre,otro.nombre);
	
	patron=new(nothrow) char[strlen(otro.patron)+1];
	if(!patron){cerr<<"Error en la reserva de memoria 2\n";exit(1);}
	strcpy(patron,otro.patron);
	   
	valores=new(nothrow) char*[nValores];
	if(!valores){cerr<<"Error en la reserva de memoria 3\n";exit(1);}
		
	for(int i=0;i<nValores;i++){
		valores[i]=new(nothrow) char[strlen(otro.valores[i])+1];
		if(!valores[i]){cerr<<"Error en la reserva de memoria 4."<<i<<endl;exit(1);}
		strcpy(valores[i],otro.valores[i]);
	}
}

void rasgo::liberarMemoria(){
	if(nombre)
		delete [] nombre;
	if(patron)
		delete [] patron;
	if(valores){
		for(int i=0;i<nValores;i++)
			delete [] valores[i];
		delete[] valores;
	}
	
}
