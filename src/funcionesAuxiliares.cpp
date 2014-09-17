#include "funcionesAuxiliares.h"

int aleatorio(int n){
	srand(time(0));//Semilla para generar el aleatorio
	return rand()%(n+1);
}

int aleatorio(int* v, int tam){
	srand(time(0));//Semilla para generar el aleatorio
	return v[rand()%(tam)];
}

int Buscar(char encontrar, int ocurrencia, char* cad){
	int lugar=-1;
	for(int i=0;i<strlen(cad) && ocurrencia!=0;i++){
		if(cad[i]==encontrar){//Si encontramos el caracter, guardamos la posicion y decrementamos el numero de ocurrencia
			lugar=i;
			ocurrencia--;
		}
			
	}
	return lugar;
}

void QuitarComentarios(istream& conComentarios, ostream& sinComentarios){
	char buffer[999];
	int pos;
	while(conComentarios.eof()!=true){//Mientras no lleguemos al final del fichero
		buffer[0]=conComentarios.peek();
		if(buffer[0]!='\n' && buffer[0]!=' '){//Si la linea tiene algo. Puede que sea una lineas con un simple retorno de carro o con espacios en blanco y luego el retorno.
			conComentarios.getline(buffer,999);//Cogemos la linea
			pos=Buscar('#',1,buffer);
			if(pos==-1){//Si la linea no tiene comentarios
				for(int i=0;i<strlen(buffer);i++)//Copiamos la linea tal cual
					sinComentarios.put(buffer[i]);
				sinComentarios.put('\n');
			}
			if(pos>0){//Si el comentario no está al principio. Ya que si está al principio no hacemos nada y descartamos la linea entera.
				if(buffer[pos-1]!=' '){//Comprobamos si hay un ' ' antes del # para quitar el ' ' tambien.
					buffer[pos]='\n';
					buffer[pos+1]='\0';
					for(int i=0;i<strlen(buffer);i++)
						sinComentarios.put(buffer[i]);
				}
				else{//Si no lo hay no lo quitamos
					while(buffer[pos-1]==' '){
						buffer[pos-1]='\n';
						buffer[pos]='\0';
						pos--;
					}
					for(int i=0;i<strlen(buffer);i++)//Ponemos la linea ya sin comentarios y sin ' ' basura en nuestro fichero sin comentarios
						sinComentarios.put(buffer[i]);
				}
			}
		}
		else
			conComentarios.get();
	}		
}

void DibujarMarco(int ancho, int alto, int x1, int y1, int x2, int y2, int rgb[3]){
	RectanguloR(x1,y1,x2,y1+alto,rgb[0],rgb[1],rgb[2]);//Esquina superior
	RectanguloR(x1,y1,x1+ancho,y2,rgb[0],rgb[1],rgb[2]);//Esquina derecha
	RectanguloR(x2-ancho,y1,x2,y2,rgb[0],rgb[1],rgb[2]);//Esquina izqda
	RectanguloR(x1,y2-alto,x2,y2,rgb[0],rgb[1],rgb[2]);//Esquina inferiror
}

void DividirEnDos(char* orig, char* destino1, char* destino2, int pos){
	//Copiamos la primera parte en la cadena destino 1
	for(int i=0;i<pos;i++)
		destino1[i]=orig[i];
	destino1[pos]='\0';
	
	//Copiamos la segunda parte en la cadena destino 2
	int i,j;
	for(i=0, j=pos+1;j<strlen(orig);i++,j++)
		destino2[i]=orig[j];
	destino2[i]='\0';
	}
	
void DividirEnTres(char* orig, char* destino1, char* destino2, char* destino3, int pos1, int pos2){
	int i,j,k;
	//Copiamos la primera parte en la cadena destino 1
	for(i=0;i<pos1;i++)
		destino1[i]=orig[i];
	destino1[pos1]='\0';
	i++;
	
	//Copiamos la segunda parte en la cadena destino 2
	for(j=0;i<pos2;i++,j++)
		destino2[j]=orig[i];
	destino2[j]='\0';
	i++;
	
	//Copiamos la tercera parte en la cadena destino 3
	for(k=0;i<strlen(orig);i++,k++)
		destino3[k]=orig[i];
	destino3[k]='\0';
}

void EnteroACadena(char* cadena, int n){
	char base[10]={'0','1','2','3','4','5','6','7','8','9'};
	int nCifras=1,a=10;
	while(n/a>0){nCifras++;a*=10;}//Calculamos el número de cifras del número
	a/=10;
	for(int i=0;i<nCifras;i++,a/=10){//Lo dividimos entre a y hayamos su resto para ir obteniendo la cifra más significativa
		cadena[i]=base[n/a];
		n%=a;	
	}
	cadena[nCifras]='\0';
}

