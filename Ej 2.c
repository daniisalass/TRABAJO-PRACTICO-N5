#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50
struct BaseDeSensores
{
	char MarcaSensor[15];
	char TipoSensor[15];
	char UnidadMedida[15];
	
}SensorTipo[2];

struct Mediciones
{
	char Fecha[15];
	char Hora[15];
	struct BaseDeSensores Sensor;
	float ValorMedido;
	char Comentarios[150];
	struct Mediciones *Siguiente;
	struct Mediciones *Anterior;
};

struct Mediciones *AgregarDatos();

void MostrarMediciones(struct Mediciones *Actual);

void MostrarMedicionesDelUltimoAlFinal(struct Mediciones *Actual);

void MostrarBaseDeDatos();

void CargarBaseDeDatos();

struct Mediciones *LeerMediciones(FILE *Archivo);

void EliminarMediciones(struct Mediciones **PrimerNodo,struct Mediciones **UltimoNodo, int EliminarPorMedicion);

void BuscarDatos(struct Mediciones *Actual,int QueBuscar,float ValorMedido);

void MostrarMedicionActual(struct Mediciones *Actual);

void MedicionesOrdenadas(struct Mediciones *NodoInicial);

struct Mediciones *EncontarNodoFinal(struct Mediciones *NodoInicial);



int main(int argc, char *argv[]) {
	
	struct Mediciones *NodoInicial=NULL;
	
	struct Mediciones *NodoFinal=NULL;
	
	struct Mediciones *NodoTemporal=NULL;
	
	int Seleccionador=0,Salir=0,Eliminar=0,Selecionador3=0,Selecionador4=0;
	
	FILE* ArchivoMediciones;
	
	NodoInicial=LeerMediciones(ArchivoMediciones);
	
	if(NodoInicial!=NULL)
	{
		NodoTemporal=NodoInicial;
		NodoFinal=EncontarNodoFinal(NodoTemporal);
		NodoTemporal=NodoInicial;
		
		printf("\n SE ENCONTRO EN LA BASE DE DATOS: \n");
		
		MostrarMediciones(NodoTemporal);
		
		printf("\n Desea recuperarlo ? \n 1-Si\n 2-No \n");
		scanf("%d",&Selecionador4);
	}
	else
	{
		printf("NO SE ENCONTRO NINGUNA BASE DE DATOS \n");
		
	}
	
	if(Selecionador4==2)
	{
		free(NodoInicial);
		free(NodoFinal);
		NodoInicial=NULL;
		NodoFinal=NodoFinal;
	}
	system("pause");
	system("cls");	
	CargarBaseDeDatos();
	while(Salir!=1)
	{	printf("\n========MENU PRINCIPAL========\n");
		printf("\n 1-Ingresar una nueva medicion \n 2-Mostrar Mediciones \n 3-Eliminar Mediciones\n 4-Buscar Datos\n 5-Ordenar Mediciones\n 6-Mostrar Mediciones de atras hacia adelante \n 7-Cargar en Archivos \n 8-Salir \n");
		scanf("%d",&Seleccionador);
		fflush(stdin);
		switch(Seleccionador)
		{
			case 1:
				NodoTemporal=AgregarDatos(NodoFinal);
				if(NodoInicial==NULL)
				{
					NodoInicial=NodoTemporal;
					NodoInicial->Siguiente=NULL;
					NodoInicial->Anterior=NULL;
				}
				else
				{
					NodoFinal->Siguiente=NodoTemporal;
					NodoTemporal->Siguiente=NULL;
					NodoTemporal->Anterior=NodoFinal;
				}
				NodoFinal=NodoTemporal;
				if(NodoFinal->Siguiente == NULL)
				{
					puts("Entro");
				}
				break;
			case 2:
				system("cls");
				NodoTemporal=NodoInicial;
				MostrarMediciones(NodoTemporal);
				system("pause");
				system("cls");
				break;
			case 3:
				system("cls");
				NodoTemporal=NodoInicial;
				MostrarMediciones(NodoTemporal);
				printf("  ¿ QUE MEDICION DESEA ELIMINAR ? ");
				scanf("%d",&Eliminar);
				EliminarMediciones(&NodoInicial,&NodoFinal,Eliminar);
				system("pause");
				system("cls");
				break;
			case 4:
				system("cls");
				puts("En que formato piensa buscar");
				printf("\n 1-Valor Medido\n 2-Tipo de sensor\n");
				NodoTemporal=NodoInicial;
				int Selecionador2;
				float ValorMedidoABuscar;
				scanf("%d",&Selecionador2);
				fflush(stdin);
				switch(Selecionador2)
				{
					case 1:
						printf("Ingresar el valor medido a buscar:");
						scanf("%f",&ValorMedidoABuscar);
						fflush(stdin);
						BuscarDatos(NodoTemporal,Selecionador2,ValorMedidoABuscar);
						break;
					case 2:
						BuscarDatos(NodoTemporal,Selecionador2,ValorMedidoABuscar);
						break;
					default :
						break;
				}
				system("pause");
				system("cls");
				break;
			case 5:
				NodoTemporal=NodoInicial;
				MedicionesOrdenadas(NodoTemporal);
				break;
			case 6:
					NodoTemporal=NodoFinal;
					MostrarMedicionesDelUltimoAlFinal(NodoTemporal);
				break;
			case 7:
				system("cls");
				printf("\n 1-Escribir en el Archivo\n 2-Volver al menu principal");
				scanf("%d",&Selecionador3);
				switch(Selecionador3)
				{
				case 1:
					if( (ArchivoMediciones=fopen("ArchivoMediciones.txt","wb+")) != NULL) 
					{
						NodoTemporal=NodoInicial;
						while(NodoTemporal!=NULL)
						{
							fwrite(NodoTemporal,sizeof(struct Mediciones),1,ArchivoMediciones);
							NodoTemporal=NodoTemporal->Siguiente;
						}	
					}
					else
					{
						puts("Error al abrir el Archivo\n");
					} 
					fclose(ArchivoMediciones);
					system("pause");
					break; 
				case 2:
					break;
					default :
						break;
				}
				break;
			case 8:
				Salir=1;
				break;
			default :
				break;
			
		}
	}
	return 0;
}
struct Mediciones *AgregarDatos(struct Mediciones *UltimoNodo)
{
	int selecionador=0;
	struct Mediciones *NuevaMedicion = (struct Mediciones*) malloc (sizeof (struct Mediciones)); 
	NuevaMedicion->Siguiente=NULL;
	
	printf("\nIngrese la Fecha (**/**/****): ");
	gets(NuevaMedicion->Fecha);

	printf("\nIngrese la hora (**/**/****): ");
	gets(NuevaMedicion->Hora);
	MostrarBaseDeDatos();
	scanf("%d",&selecionador);
	fflush(stdin);
	switch(selecionador)
	{
		case 1:
			printf("   Se Selecciono el Sensor 1\n");
			strcpy(NuevaMedicion->Sensor.MarcaSensor,SensorTipo[0].MarcaSensor);
			strcpy(NuevaMedicion->Sensor.TipoSensor,SensorTipo[0].TipoSensor);
			strcpy(NuevaMedicion->Sensor.UnidadMedida,SensorTipo[0].UnidadMedida);
			break;
		case 2:
			printf("   Se Selecciono el Sensor 2\n");
			strcpy(NuevaMedicion->Sensor.MarcaSensor,SensorTipo[1].MarcaSensor);
			strcpy(NuevaMedicion->Sensor.TipoSensor,SensorTipo[1].TipoSensor);
			strcpy(NuevaMedicion->Sensor.UnidadMedida,SensorTipo[1].UnidadMedida);
			break;
		case 3:
			printf("   Se Selecciono el Sensor 3\n");
			strcpy(NuevaMedicion->Sensor.MarcaSensor,SensorTipo[2].MarcaSensor);
			strcpy(NuevaMedicion->Sensor.TipoSensor,SensorTipo[2].TipoSensor);
			strcpy(NuevaMedicion->Sensor.UnidadMedida,SensorTipo[2].UnidadMedida);
			break;
		default : 
			break;
	}
	
	printf("\nIngresar el valor medido: ");
	scanf("%f",&NuevaMedicion->ValorMedido);
	fflush(stdin);

	printf("\nIngrese comentarios respecto a la medicion: ");
	gets(NuevaMedicion->Comentarios);
	return(NuevaMedicion);
}
void MostrarMediciones(struct Mediciones *Actual)
{
	int i=0;
	while(Actual!=NULL)
	{
		printf("==========MEDICION %d ==========",i+1);
		printf("\n  Fecha: ");
		puts(Actual->Fecha);
		printf("\n  Hora: ");
		puts(Actual->Hora);
		printf("\n  Sensor: ");
		puts(Actual->Sensor.MarcaSensor);
		printf("\n  Tipo de sensor: ");
		puts(Actual->Sensor.TipoSensor);
		printf("\n  Unidad de medida: ");
		puts(Actual->Sensor.UnidadMedida);
		printf("\n  Valor medido: %.2f\n",Actual->ValorMedido);
		printf("\n  Comentarios: ");
		puts(Actual->Comentarios);
		printf("\n");
		i++;
		Actual=Actual->Siguiente;
	}
}
void CargarBaseDeDatos()
{
	strcpy(SensorTipo[0].MarcaSensor,"Sony");
	strcpy(SensorTipo[0].TipoSensor,"HPR");
	strcpy(SensorTipo[0].UnidadMedida,"Milimetros");
	
	strcpy(SensorTipo[1].MarcaSensor,"Philips");
	strcpy(SensorTipo[1].TipoSensor,"JPG");
	strcpy(SensorTipo[1].UnidadMedida,"Decimetros");
	
	strcpy(SensorTipo[2].MarcaSensor,"Liliana");
	strcpy(SensorTipo[2].TipoSensor,"PKH");
	strcpy(SensorTipo[2].UnidadMedida,"Nanometros");
}
void MostrarBaseDeDatos()
{
	int i=1;
	printf("\n-------QUE SENSORES UTILIZO-------");
	printf("\n      SENSOR %d",i);
	printf("\nMarca sensor: ");
	puts(SensorTipo[0].MarcaSensor);
	printf("Tipo sensor: ");
	puts(SensorTipo[0].TipoSensor);
	printf("Unidad Medida: ");
	puts(SensorTipo[0].UnidadMedida);
	i++;
	printf("\n      SENSOR %d",i);
	printf("\nMarca sensor: ");
	puts(SensorTipo[1].MarcaSensor);
	printf("Tipo sensor: ");
	puts(SensorTipo[1].TipoSensor);
	printf("Unidad Medida: ");
	puts(SensorTipo[1].UnidadMedida);
	i++;
	printf("\n      SENSOR %d",i);
	printf("\nMarca sensor: ");
	puts(SensorTipo[2].MarcaSensor);
	printf("Tipo sensor: ");
	puts(SensorTipo[2].TipoSensor);
	printf("Unidad Medida: ");
	puts(SensorTipo[2].UnidadMedida);
	i++;
}
void EliminarMediciones(struct Mediciones **PrimerNodo,struct Mediciones **UltimoNodo, int EliminarPorMedicion)
{
	struct Mediciones *Temporal=*PrimerNodo;
	struct Mediciones *Anterior=NULL;
	int Posicion=1;
	if( (Temporal != NULL) && (EliminarPorMedicion==1))
	{
		*PrimerNodo=Temporal->Siguiente;
		free(Temporal);
		printf("Se eliminio correctamente la medicion %d \n\n",EliminarPorMedicion);
		return;
	}
	// Buscar el nodo que contiene el valor a eliminar
	while ((Temporal != NULL) && (Posicion != EliminarPorMedicion))
	{
		Anterior = Temporal;
		Temporal = Temporal->Siguiente;
		Posicion++;
	}
	// Si el valor no está presente en la lista
	if (Temporal == NULL) {
		printf("La medicion %d no se encuentra en la lista.\n", EliminarPorMedicion);
		return;
	}
	if(Temporal->Siguiente==NULL)
	{
		*UltimoNodo=Anterior;
		(*UltimoNodo)->Siguiente=NULL;
		free(Temporal);
		printf("Se eliminio correctamente la medicion %d \n\n",EliminarPorMedicion);
		return;
	}
	else
	{
		// Enlazar el nodo anterior con el siguiente nodo
		Anterior->Siguiente = Temporal->Siguiente;
		free(Temporal);
		return;
	}
}

void BuscarDatos(struct Mediciones *Actual,int QueBuscar,float ValorMedido)
{
	struct Mediciones *Auxiliar=(struct Mediciones*) malloc (sizeof (struct Mediciones)); 
	Auxiliar=Actual;
	int PosicionDeMedicion=1;
	int SelecionadorSensorABuscar=0,SeleccionadorDeValorMedido=0;
	if(QueBuscar==1)
	{
		printf("\n Buscar medicion por:\n 1-Valor igual\n 2-Valor menor \n 3-Valor Mayor \n");
		scanf("%d",&SeleccionadorDeValorMedido);
		switch(SeleccionadorDeValorMedido)
		{
		case 1:
			PosicionDeMedicion=1;
			while(Auxiliar!=NULL)
			{
				if(Auxiliar->ValorMedido==ValorMedido)
				{
					puts("Se encontro la medicion: ");
					printf("==========MEDICION %d ==========",PosicionDeMedicion);
					MostrarMedicionActual(Auxiliar);
				}
				PosicionDeMedicion++;
				Auxiliar=Auxiliar->Siguiente;
			}
			break;
		case 2:
			PosicionDeMedicion=1;
			while(Auxiliar!=NULL)
			{
				if(Auxiliar->ValorMedido <= ValorMedido)
				{
					puts("Se encontro la medicion: ");
					printf("==========MEDICION %d ==========",PosicionDeMedicion);
					MostrarMedicionActual(Auxiliar);
				}
				PosicionDeMedicion++;
				Auxiliar=Auxiliar->Siguiente;
			}
			break;
		case 3:
			PosicionDeMedicion=1;
			while(Auxiliar!=NULL)
			{
				if(Auxiliar->ValorMedido >= ValorMedido)
				{
					puts("Se encontro la medicion: ");
					printf("==========MEDICION %d ==========",PosicionDeMedicion);
					MostrarMedicionActual(Auxiliar);
					
				}
				PosicionDeMedicion++;
				Auxiliar=Auxiliar->Siguiente;
			}
			break;
		}
		
	}
	if(QueBuscar==2)
	{
		MostrarBaseDeDatos();
		scanf("%d",&SelecionadorSensorABuscar);
		switch(SelecionadorSensorABuscar)
		{
		case 1:
			PosicionDeMedicion=1;
				while(Auxiliar!=NULL)
				{
					if( (strcmp(Auxiliar->Sensor.MarcaSensor,SensorTipo[0].MarcaSensor))==0 )
					{
						puts("Se encontro la medicion: ");
						printf("==========MEDICION %d ==========",PosicionDeMedicion);
						MostrarMedicionActual(Auxiliar);
					}
					PosicionDeMedicion++;
					Auxiliar=Auxiliar->Siguiente;					
				}
			break;
		case 2: 
			PosicionDeMedicion=1;
			while(Auxiliar!=NULL)
			{
				if( (strcmp(Auxiliar->Sensor.MarcaSensor,SensorTipo[1].MarcaSensor))==0 )
				{
					puts("Se encontro la medicion: ");
					printf("==========MEDICION %d ==========",PosicionDeMedicion);
					MostrarMedicionActual(Auxiliar);
				}
				PosicionDeMedicion++;
				Auxiliar=Auxiliar->Siguiente;					
			}
			
			break;
		case 3:
			PosicionDeMedicion=1;
			while(Auxiliar!=NULL)
			{
				if( (strcmp(Auxiliar->Sensor.MarcaSensor,SensorTipo[2].MarcaSensor))==0 )
				{
					puts("Se encontro la medicion: ");
					printf("==========MEDICION %d ==========",PosicionDeMedicion);
					MostrarMedicionActual(Auxiliar);
				}
				PosicionDeMedicion++;
				Auxiliar=Auxiliar->Siguiente;					
			}
			
			break;
		default :
			break;
		}
	}
}
void MostrarMedicionActual(struct Mediciones *Actual)
{
	
	printf("\n  Fecha: ");
	puts(Actual->Fecha);
	
	printf("\n  Hora: ");
	puts(Actual->Hora);
	
	printf("\n  Sensor: ");
	puts(Actual->Sensor.MarcaSensor);
	
	printf("\n  Tipo de sensor: ");
	puts(Actual->Sensor.TipoSensor);
	
	printf("\n  Unidad de medida: ");
	puts(Actual->Sensor.UnidadMedida);
	
	printf("\n  Valor medido: %.2f\n",Actual->ValorMedido);
	
	printf("\n  Comentarios: ");
	puts(Actual->Comentarios);
	
	printf("\n");

	
}
void MedicionesOrdenadas(struct Mediciones *NodoInicial)
{
	struct Mediciones *actual = NodoInicial;
	struct Mediciones *minimo=NULL;
	struct Mediciones *temp=NULL;
	char tempFecha[15];
	char tempHora[15];
	float tempValorMedido;
	char tempComentarios[150];
	struct BaseDeSensores tempSensor;
	while (actual != NULL)
	{
		minimo = actual;
		temp = actual->Siguiente;
		
		while (temp != NULL)
		{
			//Compara el primer valor con todos los otros para ver cual es el mas chico 
			if (strcmp(temp->Fecha, minimo->Fecha) < 0)
			{
				minimo = temp;
			}
			
			temp = temp->Siguiente;
		}
		// Intercambiar los campos de los nodos
		if (minimo != actual)
		{
			strcpy(tempHora, actual->Hora);
			strcpy(tempFecha, actual->Fecha);
			strcpy(tempComentarios, actual->Comentarios);
			tempValorMedido=actual->ValorMedido;
			tempSensor=actual->Sensor;
			
			strcpy(actual->Hora, minimo->Hora);
			strcpy(actual->Fecha, minimo->Fecha);
			strcpy(actual->Comentarios, minimo->Comentarios);
			actual->ValorMedido=minimo->ValorMedido;
			actual->Sensor=minimo->Sensor;
			
			strcpy(minimo->Hora, tempHora);
			strcpy(minimo->Fecha, tempFecha);
			strcpy(minimo->Comentarios, tempComentarios);
			minimo->ValorMedido=tempValorMedido;
			minimo->Sensor=tempSensor;
		}
		actual = actual->Siguiente;
	}
}
void MostrarMedicionesDelUltimoAlFinal(struct Mediciones *Actual)
{
	int i=0;
	while(Actual!=NULL)
	{
		printf("==========MEDICION %d ==========",i+1);
		printf("\n  Fecha: ");
		puts(Actual->Fecha);
		printf("\n  Hora: ");
		puts(Actual->Hora);
		printf("\n  Sensor: ");
		puts(Actual->Sensor.MarcaSensor);
		printf("\n  Tipo de sensor: ");
		puts(Actual->Sensor.TipoSensor);
		printf("\n  Unidad de medida: ");
		puts(Actual->Sensor.UnidadMedida);
		printf("\n  Valor medido: %.2f\n",Actual->ValorMedido);
		printf("\n  Comentarios: ");
		puts(Actual->Comentarios);
		printf("\n");
		i++;
		Actual=Actual->Anterior;
	}
}
struct Mediciones *LeerMediciones(FILE *Archivo)
{
	struct Mediciones *Cabeza=NULL;
	struct Mediciones *Ultimo=NULL;
	struct Mediciones *Temp=NULL;
	int control=0;
	
	if(Archivo=fopen("ArchivoMediciones.txt","rb+"))
	{
		do
		{
			struct Mediciones *NuevoNodo=(struct Mediciones *) malloc(sizeof(struct Mediciones));
			control=fread(NuevoNodo,sizeof(struct Mediciones),1,Archivo);
			Temp=NuevoNodo->Siguiente;
			if(control==1)
			{
				if(Cabeza==NULL)
				{
					Cabeza=NuevoNodo;
					Cabeza->Siguiente=NULL;
					Cabeza->Anterior=NULL;
					Ultimo=NuevoNodo;
				}
				else
				{
					//Enlaza mis nodos con el siguiente valor, el valor que se incrementa en cada pasada es NuevoNodo, una vez que sea nulo sale del Do While
					Ultimo->Siguiente = NuevoNodo;
					NuevoNodo->Siguiente = NULL;
					NuevoNodo->Anterior = Ultimo;
					Ultimo=NuevoNodo;
				}
			}
			else
			{
				return(Cabeza);
			}
		}while(Temp!=NULL);
	}
	else
	{
		printf("\nProblemas para abrir el archivo");
	}
	
	fclose(Archivo);
	// Devuelvo mi nodo inicial para poder trabajar con el en programa principal
	return(Cabeza);
}
struct Mediciones *EncontarNodoFinal(struct Mediciones *NodoInicial)
{
	struct Mediciones *NodoTemp=NodoInicial;	
	struct Mediciones *NodoFinal=NULL;
	while(NodoTemp!=NULL)
	{
		NodoFinal=NodoTemp;
		NodoTemp=NodoTemp->Siguiente;
	}
	return(NodoFinal);
}

