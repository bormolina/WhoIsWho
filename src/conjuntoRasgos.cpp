#include"conjuntoRasgos.h"

conjuntoRasgos::conjuntoRasgos(){
	tam=0;
	datos=0;
}

conjuntoRasgos::conjuntoRasgos(const conjuntoRasgos& otro){
	copiar(otro);
}

conjuntoRasgos& conjuntoRasgos::conjuntoRasgos::operator= (const conjuntoRasgos& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);
	}
	return *this;
}

conjuntoRasgos::~conjuntoRasgos(){
	liberarMemoria();
}

rasgo conjuntoRasgos::get(int i){
	return datos[i];
}

int conjuntoRasgos::tamanho(){
	return tam;	
}
		
istream& operator>> (istream& in, conjuntoRasgos& otro){
	char buffer[999];
	
	//Leemos el número de rasgos
	in.getline(buffer,999);
	otro.tam=atoi(buffer);
	otro.datos=new(nothrow) rasgo[otro.tam];
	if(!otro.datos){cerr<<"Error en la reserva de memoria 2\n";exit(1);}
	
	//Leemos rasgo a rasgo
	for(int i=0;i<otro.tam;i++){
		in>>otro.datos[i];
	}
	return in;	
}

ostream& operator<< (ostream& out, const conjuntoRasgos& otro){
	out<<otro.tam<<endl;
	for(int i=0;i<otro.tam;i++)
		out<<otro.datos[i];
	return out;
}
		
void conjuntoRasgos::crear(int n){
	tam=n;
	datos=new(nothrow) rasgo[tam];
	if(!datos){cerr<<"Error en la reserva de memoria 1\n";exit(1);}
}

void conjuntoRasgos::copiar(const conjuntoRasgos& otro){
	crear(otro.tam);
	for(int i=0;i<otro.tam;i++)		
		datos[i]=otro.datos[i];
}
			
void conjuntoRasgos::liberarMemoria(){
	delete[] datos;
}

