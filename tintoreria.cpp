#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct subservicio {
	int codigoSubervicio;
	char nombreSubervicio[' '];
	float precioUnitario;
};

struct servicio {
	int codigoServicio;
	char nombreServicio[' '];
	struct subservicio subservicios[' '];
};

//int consultarArchivo(struct servicio* servicios);
//void guardarArchivo(struct servicio *servicios, int cantidad);
int consultarArchivo(struct servicio* servicios, int *cantidadSubservicios);
void guardarArchivo(struct servicio *servicios, int cantidad, int *cantidadSubservicios);

//void consultar(struct servicio *servicios, int cantidad);
//int eliminar(struct servicio *servicios, int cantidad);
int alta(struct servicio *servicios, int cantidad);
int editar(struct servicio *servicios, int cantidad);
int eliminar(struct servicio *servicios, int cantidad, int *cantidadSubservicios);
int buscarPorCodigo(struct servicio *servicios, int cantidad);
void consultar(struct servicio *servicios, int cantidad, int *cantidadSubservicios);

// Definiciones agregadas
void altaSubservicio(struct servicio *servicios, int cantidad, int *cantidadSubservicios);
void agregarSubservicio(struct servicio *servicios, int *cantidadSubservicios, int posicion);
void editarSubservicio(struct servicio *servicios, int cantidad, int *cantidadSubservicios);
void modificarSubservicio(struct servicio *servicios, int *cantidadSubservicios, int posicion);
void eliminarSubservicio(struct servicio *servicios, int cantidad, int *cantidadSubservicios);
void borrarSubservicio(struct servicio *servicios, int *cantidadSubservicios, int posicion);
void buscarSubserviciosPorCodigoServicio(struct servicio *servicios, int cantidad, int *cantidadSubservicios);
void buscarSubserviciosPorCodigo(struct servicio *servicios, int *cantidadSubservicios, int posicion);

void generarTicket(struct servicio *servicios, int cantidad, int *cantidadSubservicios);

bool codigoServicioValido(string codigoServicio);
string pedirCodigoServicio();
bool codigoSubservicioValido(string codigoSubservicio);
string pedirCodigoSubservicio();
bool numeroValido(string numero);
string pedirNumeroDePrendas();

int main(void) {
	
	int menu, cantidadServicios;
	int cantidadSubservicios[' '];
	struct servicio servicios[' '];

	cantidadServicios = consultarArchivo(servicios, cantidadSubservicios);

	do{
		system("cls");
		cout<<"TINTORERIA"<<endl;
		cout<<"1.- Agregar servicio"<<endl;
		cout<<"2.- Editar servicio"<<endl;
		cout<<"3.- Eliminar servicio"<<endl;
		cout<<"4.- Consultar servicio"<<endl;
		cout<<"5.- Catalogo"<<endl;

		//Opciones Agregadas
		cout<<"6.- Agregar subservicio"<<endl;
		cout<<"7.- Editar subservicio"<<endl;
		cout<<"8.- Eliminar subservicio"<<endl;
		cout<<"9.- Consultar subservicio"<<endl;
		
		cout<<"10.- Venta"<<endl;
		cout<<"0.- Salir"<<endl;
		cout<<"Opcion: "<<endl;
		cin>>menu;

		system("cls");
		switch(menu) {
			case 1:
			    cantidadSubservicios[cantidadServicios] = 0;
				cantidadServicios = alta(servicios, cantidadServicios);
				// Linea Agregada
				break;
			case 2:
				cantidadServicios = editar(servicios, cantidadServicios);
				break;
			case 3:
				cantidadServicios = eliminar(servicios, cantidadServicios, cantidadSubservicios);
				break;
			case 4:
				buscarPorCodigo(servicios, cantidadServicios);
				break;
			case 5:
				consultar(servicios, cantidadServicios, cantidadSubservicios);
				break;

            // Opciones agregadas
            case 6:
				altaSubservicio(servicios, cantidadServicios, cantidadSubservicios);
				break;
			case 7:
				editarSubservicio(servicios, cantidadServicios, cantidadSubservicios);
				break;
			case 8:
				eliminarSubservicio(servicios, cantidadServicios, cantidadSubservicios);
				break;
			case 9:
				buscarSubserviciosPorCodigoServicio(servicios, cantidadServicios, cantidadSubservicios);
				break;
			case 10: 
				generarTicket(servicios, cantidadServicios, cantidadSubservicios);
				break;

			case 0: // DEBERIA CAMBIARSE A CUALQUIER TECLA, O AL TERMINAR CUALQUIER ACCION
				guardarArchivo(servicios, cantidadServicios, cantidadSubservicios);
				break;
		}

	} while (menu != 0);
}

/*int consultarArchivo( struct servicio* servicios ) {
	int cantidad = 0;
	FILE *archivo = fopen ("servicios.txt", "r");
	char c;

	if(archivo == NULL){
		fclose(archivo);
		return cantidad;
	} else {
			if(fgetc(archivo) != EOF) {
				while(feof(archivo) == 0) {
				fscanf(archivo, "%d", &servicios[cantidad].codigoServicio);
				fgetc(archivo);
				fscanf(archivo, "%[^\n]", &servicios[cantidad].nombreServicio);
				fgetc(archivo);
				cantidad++;

				char cadena[' '];
				fscanf(archivo, "%[\n]", cadena);
			}
		}
		fclose(archivo);
		return cantidad;
	}
}*/
int consultarArchivo( struct servicio* servicios, int *cantidadSubservicios) {
	int cantidad = 0;
	FILE *archivo = fopen ("servicios.txt", "r");
	char c;

	if(archivo == NULL){
		fclose(archivo);
		return cantidad;
	} else {
        if(fgetc(archivo) != EOF) {
			while(feof(archivo) == 0) {
                int cantidadSubservicio = 0;
				fscanf(archivo, "%d", &servicios[cantidad].codigoServicio);
				cout << endl<<servicios[cantidad].codigoServicio<<"-";
				fgetc(archivo);
				fscanf(archivo, "%[^\n]", &servicios[cantidad].nombreServicio);
				cout << endl<<servicios[cantidad].nombreServicio<<"-";
				fgetc(archivo);
				cantidad++;

				if(fgetc(archivo) == '\t'){
                    do{
                        fscanf(archivo, "%d", &servicios[cantidad].subservicios[cantidadSubservicio].codigoSubervicio);
                        cout << endl<<servicios[cantidad].subservicios[cantidadSubservicio].codigoSubervicio<<"-";
                        fgetc(archivo);
                        fgetc(archivo);
                        fscanf(archivo, "%[^\n]", &servicios[cantidad].subservicios[cantidadSubservicio].nombreSubervicio);
                        cout << endl<< servicios[cantidad].subservicios[cantidadSubservicio].nombreSubervicio<<"-";
                        cantidadSubservicio++;
                    }while(feof(archivo) == 0 && fgetc(archivo) == '\t');
                }

				cantidadSubservicios[cantidad] = cantidadSubservicio;
				char cadena[' '];
				fscanf(archivo, "%[\n]", cadena);
			}
		}
		fclose(archivo);
		return cantidad;
	}
}

/*void guardarArchivo(struct servicio* servicios, int cantidad) {
	int c;
	FILE *archivo = fopen ("servicios.txt", "w");
	if(cantidad > 0){
		for(c = 0; c < cantidad; c++) {
			fprintf(archivo, "\n%d\n",servicios[c].codigoServicio);
			fprintf(archivo, "%s\n",servicios[c].nombreServicio);
		}
	}
	fclose(archivo);
}*/
void guardarArchivo(struct servicio* servicios, int cantidad, int *cantidadSubservicios) {
	int c, x;
	FILE *archivo = fopen ("servicios.txt", "w");
	if(cantidad > 0){
		for(c = 0; c < cantidad; c++) {
			fprintf(archivo, "\n%d\t",servicios[c].codigoServicio);
			fprintf(archivo, "%s",servicios[c].nombreServicio);
			if(cantidadSubservicios[c] > 0){
                for(x = 0; x < cantidadSubservicios[c]; x++) {
                    fprintf(archivo, "\n\t%d\t",servicios[c].subservicios[x].codigoSubervicio);
                    fprintf(archivo, "%s\t",servicios[c].subservicios[x].nombreSubervicio);
                    fprintf(archivo, "%f\n",servicios[c].subservicios[x].precioUnitario);
            }
			}else{
                fprintf(archivo, "\n");
			}
		}
	}
	fclose(archivo);
}

int alta(struct servicio *servicios, int cantidad) {
	cout<<"Ingrese el codigo de servicio del nuevo servicio: ";
	cin>>servicios[cantidad].codigoServicio;
	fflush(stdin);
	cout<<"Ingrese el Nombre de servicio del nuevo servicio: ";
	cin>>servicios[cantidad].nombreServicio;
	fflush(stdin);
	cantidad++;

	cout<<endl;
	cout<<"Se agrego el servicio"<<endl;
	system("pause");
	return cantidad;
}

int editar(struct servicio *servicios, int cantidad) {
	if(cantidad > 0) {
		int c, b;
		int codigo;
		cout<<"Ingrese el codigo del servicio que desea editar: ";
		cin>>codigo;
		fflush(stdin);
		for(c = 0; c < cantidad; c++) {
			if(servicios[c].codigoServicio == codigo) {
				cout<<"Ingrese el nuevo codigo del servicio: ";
				cin>>servicios[c].codigoServicio;
				fflush(stdin);
				cout<<"Ingrese el nuevo Nombre del servicio: ";
				cin>>servicios[c].nombreServicio;
				cout<<endl;
				cout<<"Se edito el servicio";
				system("pause");
				return cantidad;
			}
		}
		
		cout<<endl;
		cout<<"No se encontro el servicio especificado"<<endl;
		system("pause");
		return cantidad;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return cantidad;
	}
}

/*int eliminar(struct servicio *servicios, int cantidad) {
	if(cantidad > 0) {
		int c, b;
		int codigo;
		cout<<"Ingrese el Numero de servicio del servicio que desea eliminar: ";
		cin>>codigo;

		for(c = 0; c < cantidad; c++) {
			if(servicios[c].codigoServicio == codigo) {
				do{
					servicios[c] = servicios[c + 1];
					c++;
				} while(c < cantidad);
				cout<<endl;
				cout<<"Se elimino el servicio"<<endl;
				system("pause");
				return cantidad - 1;
			}
		}

		cout<<endl;
		cout<<"No se encontro el servicio especificado"<<endl;
		system("pause");
		return cantidad;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return cantidad;
	}
}*/
int eliminar(struct servicio *servicios, int cantidad, int *cantidadSubservicios) {
	if(cantidad > 0) {
		int c, b;
		int codigo;
		cout<<"Ingrese el Numero de servicio del servicio que desea eliminar: ";
		cin>>codigo;

		for(c = 0; c < cantidad; c++) {
			if(servicios[c].codigoServicio == codigo) {
				do{
                    cantidadSubservicios[c] = cantidadSubservicios[c + 1];
					servicios[c] = servicios[c + 1];
					c++;
				} while(c < cantidad);
				cout<<endl;
				cout<<"Se elimino el servicio"<<endl;
				system("pause");
				return cantidad - 1;
			}
		}

		cout<<endl;
		cout<<"No se encontro el servicio especificado"<<endl;
		system("pause");
		return cantidad;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return cantidad;
	}
}

int buscarPorCodigo(struct servicio *servicios, int cantidad) {
	if(cantidad > 0) {
		int c;
		int codigo;
		cout<<"Ingrese el Numero de servicio del servicio que desea buscar: ";
		cin>>codigo;

		for(c = 0; c < cantidad; c++) {
			if( servicios[c].codigoServicio == codigo) {
				cout<<servicios[c].codigoServicio<<" "<<servicios[c].nombreServicio<<endl;
				system("pause");
				return 0;
			}
		}

		cout<<endl;
		cout<<"No se encontro el servicio especificado"<<endl;
		system("pause");
		return 0;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return 0;
	}
}

/**
void consultar(struct servicio *servicios, int cantidad) {
	int c;
	if(cantidad == 0){
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
	} else {
		for(c = 0; c < cantidad; c++) {
			cout<<servicios[c].codigoServicio<<" "<<servicios[c].nombreServicio<<endl;
		}
		system("pause");
	}
}*/

// Métodos Agregados

void consultar(struct servicio *servicios, int cantidad, int *cantidadSubservicios) {
	int c, x;
	if(cantidad == 0){
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
	} else {
		for(c = 0; c < cantidad; c++) {
			cout<<"\n"<<servicios[c].codigoServicio<<" "<<servicios[c].nombreServicio<<endl;
			//cout<<"Tiene "<<cantidadSubservicios[c]<<" subservicios"<<endl;
			for(x = 0; x < cantidadSubservicios[c]; x++) {
                cout<<"\t"<< servicios[c].subservicios[x].codigoSubervicio<<" "<< servicios[c].subservicios[x].nombreSubervicio<<" $"<<servicios[c].subservicios[x].precioUnitario<<endl;
            }
		}
		system("pause");
	}
}

void altaSubservicio(struct servicio *servicios, int cantidad, int *cantidadSubservicios){
    if(cantidad > 0) {
		int c;
		int codigo;
		cout<<"Ingrese el Numero de servicio del servicio al que desea agregar subservicios: ";
		cin>>codigo;

		for(c = 0; c < cantidad; c++) {
			if( servicios[c].codigoServicio == codigo) {
				agregarSubservicio(servicios, cantidadSubservicios, c);
				return;
			}
		}

		cout<<endl;
		cout<<"No se encontro el servicio especificado"<<endl;
		system("pause");
		return;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return;
	}
}

void agregarSubservicio(struct servicio *servicios, int *cantidadSubservicios, int posicion){
    cout<<"Ingrese el codigo de subservicio del nuevo subservicio: ";
	cin>>servicios[posicion].subservicios[cantidadSubservicios[posicion]].codigoSubervicio;
	fflush(stdin);
	cout<<"Ingrese el Nombre de subservicio del nuevo subservicio: ";
	cin>>servicios[posicion].subservicios[cantidadSubservicios[posicion]].nombreSubervicio;
	fflush(stdin);
	cout<<"Ingrese el precio unitario del servicio: ";
	cin>>servicios[posicion].subservicios[cantidadSubservicios[posicion]].precioUnitario;
	cantidadSubservicios[posicion]++;
	cout<<endl;
	cout<<"Se agrego el subservicio"<<endl;
	system("pause");
	return;
}

void editarSubservicio(struct servicio *servicios, int cantidad, int *cantidadSubservicios){
    if(cantidad > 0) {
		int c;
		int codigo;
		cout<<"Ingrese el Numero de servicio del servicio al que desea editar: ";
		cin>>codigo;

		for(c = 0; c < cantidad; c++) {
			if( servicios[c].codigoServicio == codigo) {
				modificarSubservicio(servicios, cantidadSubservicios, c);
				return;
			}
		}

		cout<<endl;
		cout<<"No se encontro el servicio especificado"<<endl;
		system("pause");
		return;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return;
	}
}

void modificarSubservicio(struct servicio *servicios, int *cantidadSubservicios, int posicion) {
	if(cantidadSubservicios[posicion] > 0) {
		int c, b;
		int codigo;
		cout<<"Ingrese el Numero de Subservicio del Subservicio que desea editar: ";
		cin>>codigo;

		for(c = 0; c < cantidadSubservicios[posicion]; c++) {
			if(servicios[posicion].subservicios[c].codigoSubervicio == codigo) {
				cout<<"Ingrese el nuevo codigo de subservicio del subservicio: ";
				cin>>servicios[posicion].subservicios[c].codigoSubervicio;
				fflush(stdin);
				cout<<"Ingrese el nuevo nombre de subservicio del subservicio: ";
				cin>>servicios[posicion].subservicios[c].nombreSubervicio;
				fflush(stdin);
				cout<<"Ingrese el nuevo precio unitario del subservicio: ";
				cin>>servicios[posicion].subservicios[c].precioUnitario;
				cout<<endl;
				cout<<"Se edito el subServicio"<<endl;
				system("pause");
				return;
			}
		}

		cout<<endl;
		cout<<"No se encontro el subservicio especificado"<<endl;
		system("pause");
		return;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return;
	}
}

void eliminarSubservicio(struct servicio *servicios, int cantidad, int *cantidadSubservicios){
    if(cantidad > 0) {
		int c;
		int codigo;
		cout<<"Ingrese el Numero de servicio del servicio al que desea eliminar subservicios: ";
		cin>>codigo;

		for(c = 0; c < cantidad; c++) {
			if( servicios[c].codigoServicio == codigo) {
				borrarSubservicio(servicios, cantidadSubservicios, c);
				return;
			}
		}

		cout<<endl;
		cout<<"No se encontro el servicio especificado"<<endl;
		system("pause");
		return;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return;
	}
}

void borrarSubservicio(struct servicio *servicios, int *cantidadSubservicios, int posicion) {
	if(cantidadSubservicios[posicion] > 0) {
		int c, b;
		int codigo;
		cout<<"Ingrese el Numero de Subservicio del Subservicio que desea eliminar: ";
		cin>>codigo;

		for(c = 0; c < cantidadSubservicios[posicion]; c++) {
			if(servicios[posicion].subservicios[c].codigoSubervicio == codigo) {
				do{
					servicios[posicion].subservicios[c] = servicios[posicion].subservicios[c + 1];
					c++;
				} while(c < cantidadSubservicios[posicion]);
				cantidadSubservicios[posicion]--;
				cout<<endl;
				cout<<"Se elimino el servicio"<<endl;
				system("pause");
				return;
			}
		}

		cout<<endl;
		cout<<"No se encontro el subservicio especificado"<<endl;
		system("pause");
		return;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return;
	}
}

void buscarSubserviciosPorCodigoServicio(struct servicio *servicios, int cantidad, int *cantidadSubservicios){
    if(cantidad > 0) {
		int c;
		int codigo;
		cout<<"Ingrese el Numero de servicio del servicio que desea buscar: ";
		cin>>codigo;

		for(c = 0; c < cantidad; c++) {
			if( servicios[c].codigoServicio == codigo) {
				buscarSubserviciosPorCodigo(servicios, cantidadSubservicios, c);
				return;
			}
		}

		cout<<endl;
		cout<<"No se encontro el servicio especificado"<<endl;
		system("pause");
		return;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return;
	}
}

void buscarSubserviciosPorCodigo(struct servicio *servicios, int *cantidadSubservicios, int posicion){
    if(cantidadSubservicios[posicion] > 0) {
		int c, b;
		int codigo;
		cout<<"Ingrese el Numero de Subservicio del Subservicio que desea buscar: ";
		cin>>codigo;

		for(c = 0; c < cantidadSubservicios[posicion]; c++) {
			if(servicios[posicion].subservicios[c].codigoSubervicio == codigo) {
				cout<<"Encontrado "<<servicios[posicion].subservicios[c].codigoSubervicio<<" "<<servicios[posicion].subservicios[c].nombreSubervicio<<" $"<<servicios[posicion].subservicios[c].precioUnitario<<endl;
				system("pause");
				return;
			}
		}

		cout<<endl;
		cout<<"No se encontro el subservicio especificado"<<endl;
		system("pause");
		return;
	} else  {
		cout<<endl;
		cout<<"No hay elementos en la lista"<<endl;
		system("pause");
		return;
	}
}

void generarTicket(struct servicio *servicios, int cantidad, int *cantidadSubservicios) {
	string codigoServicio = pedirCodigoServicio();
  	string codigoSubServicio = pedirCodigoSubservicio();
  	string numeroDePrendas = pedirNumeroDePrendas();
  	
  	string servicioConsultado = "Buscar el servicio " + codigoServicio;
  	string subservicioConsultado = "Buscar el 1 subservicio " + codigoSubServicio;
  	
  	std::vector<std::string> subservicioConsultadoPartido;
	std::istringstream iss(subservicioConsultado);
	for(std::string s; iss >> s; )
    	subservicioConsultadoPartido.push_back(s);
  	
  	int posicionDelPrecioEnSubservicio = 2;
  	string precioSubServicio = subservicioConsultadoPartido[posicionDelPrecioEnSubservicio];
  	
  	int numPrendas = std::stoi(numeroDePrendas);
  	int precioSubServ = std::stoi(precioSubServicio);
  	
  	cout << endl;
  	cout << servicioConsultado << endl;
  	cout << subservicioConsultado << endl;
	cout << "Numero de prendas: " << numeroDePrendas << endl; 
	cout << endl;
	
	cout << "\tSubtotal: " << (numPrendas * precioSubServ) << endl;
	cout << "\tIVA: " << (numPrendas * precioSubServ) * (.16)<< endl;
	cout << "\tTotal: " << (numPrendas * precioSubServ) * (1.16)<< endl;
	cout << endl;	
	
	system("pause");
}

bool codigoServicioValido(string codigoServicio) {
	if (codigoServicio.length() != 4) {
		cout << "El codigo del servicio consta de 4 caracteres" << endl;
		return false;
	}
	
	for(std::string::size_type i = 0; i < codigoServicio.size(); ++i)
  	{
    	if( !std::isdigit(codigoServicio[i]) ) {
		
      		cout << "El codigo del servicio es un numero" << endl;
      		return false;
      	}
  	}
  	
  	return true;
}

string pedirCodigoServicio() {
	
	string codigoServicio;
	
	do {
		cout << "Ingresa el codigo del servicio: ";
		cin >> codigoServicio;
	} while (!codigoServicioValido(codigoServicio));	
  	
  	return codigoServicio;
}

bool codigoSubservicioValido(string codigoSubservicio) {
	if (codigoSubservicio.length() != 2) {
		cout << "El codigo del subservicio consta de 2 caracteres" << endl;
		return false;
	}
	
	for(std::string::size_type i = 0; i < codigoSubservicio.size(); ++i)
  	{
    	if( !std::isdigit(codigoSubservicio[i]) ) {
		
      		cout << "El codigo del subservicio es un numero" << endl;
      		return false;
      	}
  	}
  	
  	return true;
}

string pedirCodigoSubservicio() {
	
	string codigoSubservicio;
	
	do {
		cout << "Ingresa el codigo del subservicio: ";
		cin >> codigoSubservicio;
	} while (!codigoSubservicioValido(codigoSubservicio));	
  	
  	return codigoSubservicio;
}

bool numeroValido(string numero) {	
	for(std::string::size_type i = 0; i < numero.size(); ++i)
  	{
    	if( !std::isdigit(numero[i]) ) {
		
      		cout << "No es un numero" << endl;
      		return false;
      	}
  	}
  	
  	return true;
}

string pedirNumeroDePrendas() {
	
	string numeroDePrendas;
	
	do {
		cout << "Ingresa el numero de prendas a realizar el subservicio: ";
		cin >> numeroDePrendas;
	} while (!numeroValido(numeroDePrendas));	
  	
  	return numeroDePrendas;
}


