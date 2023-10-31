#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

struct ListadodeImagenes{
	int Codigo;
	char NombredeArchivo[MAX];
	char ExtensiondeArchivo[MAX];
	int Bytes;
	float Precio;
	struct ListadodeImagenes *Siguiente;
};

struct ListadodeImagenes *AgregarDatos();

void MostrarImagen(struct ListadodeImagenes *Actual);

void EliminarImagen(struct ListadodeImagenes **PrimerNodo,struct ListadodeImagenes **UltimoNodo, int Buscador);

void BuscarDatos(struct ListadodeImagenes *Actual,int QueBuscar,int Codigo,char *NombredeArchivo,char *ExtensiondeArchivo,int Bytes,float Precio);

void Ordenar(struct ListadodeImagenes *Actual);

void ImagenesOrdenadas(struct ListadodeImagenes *NodoInicial);

int CantidadDeElementos(struct ListadodeImagenes *NodoInicial);

struct ListadodeImagenes *LeerArchivos(FILE *Archivo);

struct ListadodeImagenes *EncontarNodoFinal(struct ListadodeImagenes *NodoInicial);

int main(int argc, char *argv[]) {
	
	struct ListadodeImagenes *NodoInicial=NULL;

	struct ListadodeImagenes *NodoFinal=NULL;
	
	struct ListadodeImagenes *NodoTemporal=NULL;
	
	struct ListadodeImagenes *NodoTemporalEliminarImagen;
	
	FILE *ArchivoImagen;
	int Selecionador;
	int Selecionador2,Selecionador3,CodigoBuscar,BuscarBytes,Selecionador4;
	int Salir=0;
	int BuscarCodigo=0;
	char BuscarNombreArchivo[MAX],BuscarExtensionArchivo[MAX];
	float BuscarPrecio;
	
	NodoInicial=LeerArchivos(ArchivoImagen);
	if(NodoInicial!=NULL)
	{
		NodoTemporal=NodoInicial;
		NodoFinal=EncontarNodoFinal(NodoTemporal);
		NodoTemporal=NodoInicial;
		printf("\n SE ENCONTRO EN LA BASE DE DATOS: \n");
		MostrarImagen(NodoTemporal);
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
		NodoInicial=NULL;
		NodoFinal=NodoFinal;
	}
	system("pause");
	system("cls");	
	
	while(Salir!=1)
	{
	printf("    MENU PRINCIPAL ");
	printf("\n 1-Agregar Imagen\n 2-Imprimir Listado de imagenes\n 3-Eliminar Imagen\n 4-Buscar imagen \n 5-Ordenar Alfabeticamente \n 6-Archivo \n 7-Salir \n");
	scanf("%d",&Selecionador);
	fflush(stdin);
		switch(Selecionador)
		{
			case 1:
					NodoTemporal=AgregarDatos();
					if(NodoInicial==NULL)
					{
						NodoInicial=NodoTemporal;
						NodoInicial->Siguiente=NULL;
					}
					else
					{
						NodoFinal->Siguiente=NodoTemporal;
					}
					NodoFinal=NodoTemporal;
					system("cls");
				break;
			case 2: 
					system("cls");
					NodoTemporal=NodoInicial;
					MostrarImagen(NodoTemporal);
					system("pause");
					system("cls");
				break;
			case 3:
				system("cls");
				puts("\n Ingresa el codigo de la Imagen a Eliminar: ");
				scanf("%d",&BuscarCodigo);
				NodoTemporalEliminarImagen=NodoInicial;
				EliminarImagen(&NodoInicial,&NodoFinal,BuscarCodigo);
				system("pause");
				system("cls");
				break;
			case 4:
				puts("En que formato piensa buscar");
				printf("\n 1-Codigo\n 2-Nombre de Archivo\n 3-Extension de Archivo \n 4-Bytes\n 5-Precio");
				NodoTemporal=NodoInicial;
				scanf("%d",&Selecionador2);
				fflush(stdin);
				switch(Selecionador2)
				{
				case 1:
					printf("Ingresar codigo a buscar:");
					scanf("%d",&CodigoBuscar);
					fflush(stdin);
					BuscarDatos(NodoTemporal,Selecionador2,CodigoBuscar,BuscarNombreArchivo,BuscarExtensionArchivo,BuscarBytes,BuscarPrecio);
					break;
				case 2:
					printf("Ingresar el nombre de archivo a buscar:");
					gets(BuscarNombreArchivo);
					BuscarDatos(NodoTemporal,Selecionador2,CodigoBuscar,BuscarNombreArchivo,BuscarExtensionArchivo,BuscarBytes,BuscarPrecio);
					break;
				case 3:
					printf("Ingresar extension de archivo a buscar:");
					gets(BuscarExtensionArchivo);
					BuscarDatos(NodoTemporal,Selecionador2,CodigoBuscar,BuscarNombreArchivo,BuscarExtensionArchivo,BuscarBytes,BuscarPrecio);
					break;
				case 4:
					printf("Ingresar bytes a buscar:");
					scanf("%d",&BuscarBytes);
					fflush(stdin);
					BuscarDatos(NodoTemporal,Selecionador2,CodigoBuscar,BuscarNombreArchivo,BuscarExtensionArchivo,BuscarBytes,BuscarPrecio);
					break;
				case 5:
					printf("Ingresar precio a buscar:");
					scanf("%f",&BuscarPrecio);
					BuscarDatos(NodoTemporal,Selecionador2,CodigoBuscar,BuscarNombreArchivo,BuscarExtensionArchivo,BuscarBytes,BuscarPrecio);
					break;
				default :
					break;
				}
				break;
			case 5:
				NodoTemporal=NodoInicial;
				ImagenesOrdenadas(NodoTemporal);
				break;
			case 6:
				
					system("cls");
					printf("\n 1-Escribir en el Archivo\n 2-Volver al menu principal");
					scanf("%d",&Selecionador3);
					switch(Selecionador3)
					{
					case 1:
						if( (ArchivoImagen=fopen("ArchivoImagen.txt","wb+")) != NULL) 
							{
								NodoTemporal=NodoInicial;
								while(NodoTemporal!=NULL)
								{
									fwrite(NodoTemporal,sizeof(struct ListadodeImagenes),1,ArchivoImagen);
									NodoTemporal=NodoTemporal->Siguiente;
								}	
							}
							else
							{
								puts("Error al abrir el Archivo\n");
							} 
							fclose(ArchivoImagen);
							system("pause");
						break; 
					case 2:
						break;
					default :
						break;
					}
				break;
			case 7:
					Salir=1;
				break;
			default :
				break;
		}
	}
	return 0;
}
int CantidadDeElementos(struct ListadodeImagenes *NodoInicial)
{
	int cantidad=0;
	while(NodoInicial!=NULL)
	{
		cantidad++;
		NodoInicial=NodoInicial->Siguiente;
	}
	return(cantidad);
}
struct ListadodeImagenes *AgregarDatos()
{
	
	
		struct ListadodeImagenes *NuevaImagen = (struct ListadodeImagenes*) malloc (sizeof (struct ListadodeImagenes)); 
		
		NuevaImagen->Siguiente=NULL;
		
		printf("\nIngresar el codigo de la imagen:");
		scanf("%d",&NuevaImagen->Codigo);
		fflush(stdin);
		printf("\nNombre de Archivo: ");
		gets(NuevaImagen->NombredeArchivo);
		printf("\nExtension de Archivo ej (tiff, jpg, png): ");
		gets(NuevaImagen->ExtensiondeArchivo);
		printf("\nBytes: ");
		scanf("%d",&NuevaImagen->Bytes);
		fflush(stdin);
		printf("\nPrecio es: ");
		scanf("%f",&NuevaImagen->Precio);
		fflush(stdin);
	/*	Actual->Siguiente=NuevaImagen;*/
		return (NuevaImagen);
}
void MostrarImagen(struct ListadodeImagenes *Actual)
{
	int i=0;
	while(Actual!=NULL)
	{
		printf("==========IMAGEN %d ==========",i+1);
		
		printf("\nCodigo: %d",Actual->Codigo);
		
		printf("\nNombre de Archivo: ");
		puts(Actual->NombredeArchivo);
		
		printf("Extension de Archivo: ");
		puts(Actual->ExtensiondeArchivo);
		
		printf("Bytes: %d",Actual->Bytes);
		
		printf("\nPrecio es: %.2f\n",Actual->Precio);
		
		Actual=Actual->Siguiente;
		i++;
	}
}
// Trabajo con doble se utiliza para pasar un puntero a puntero a la función. Esto permite modificar el puntero original fuera de la función
//Puedo modificar el puntero original desde la función. Al pasar un puntero a puntero, estás pasando la dirección de memoria del puntero original
void EliminarImagen(struct ListadodeImagenes **PrimerNodo,struct ListadodeImagenes **UltimoNodo,int Buscador)
{
	struct ListadodeImagenes *Temporal=*PrimerNodo;
	struct ListadodeImagenes *Anterior=NULL;

	if( (Temporal != NULL) && (Temporal->Codigo==Buscador))
	{
		*PrimerNodo=Temporal->Siguiente;
		free(Temporal);
		printf("Se eliminio correctamente el primer elemento encontrado\n\n");
		return;
	}
	// Buscar el nodo que contiene el valor a eliminar
	while ((Temporal != NULL) && (Temporal->Codigo != Buscador))
	{
		Anterior = Temporal;
		Temporal = Temporal->Siguiente;
	}
	// Si el valor no está presente en la lista
	if (Temporal == NULL) {
		printf("El codigo %d no se encuentra en la lista.\n", Buscador);
		return;
	}
	if(Temporal->Siguiente==NULL)
	{
		*UltimoNodo=Anterior;
		(*UltimoNodo)->Siguiente=NULL;
		free(Temporal);
		printf("Se eliminio correctamente el primer elemento encontrado\n\n");
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
void BuscarDatos(struct ListadodeImagenes *Actual,int QueBuscar,int Codigo,char *NombredeArchivo,char *ExtensiondeArchivo,int Bytes,float Precio)
{
	struct ListadodeImagenes *Auxiliar=(struct ListadodeImagenes*) malloc (sizeof (struct ListadodeImagenes)); 
	Auxiliar=Actual;
	int SelecionarFormaDeCodigo,SelecionarFormaDeBytes,SelecionarFormaDePrecio;
			if(QueBuscar==1)
			{
				printf("\n Buscar codigo por:\n 1-Valor igual\n 2-Valor menor \n 3-Valor Mayor \n");
				scanf("%d",&SelecionarFormaDeCodigo);
				switch(SelecionarFormaDeCodigo)
				{
					case 1:
						while(Auxiliar!=NULL)
						{
							if(Auxiliar->Codigo==Codigo)
							{
								puts("        Se encontro la imagen");
								printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
							}
							Auxiliar=Auxiliar->Siguiente;
						}
						break;
					case 2:
						while(Auxiliar!=NULL)
						{
							if(Auxiliar->Codigo <= Codigo)
							{
								puts("         Se encontro la imagen");
								printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
							}
							Auxiliar=Auxiliar->Siguiente;
						}
						break;
					case 3:
						while(Auxiliar!=NULL)
						{
							if(Auxiliar->Codigo >= Codigo)
							{
								puts("Se encontro la imagen");
								printf(" Codigo:%d\n NombredeArchivo:%s \n Extension de archivo:%s\n Bytes:%d \n Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
							}
							Auxiliar=Auxiliar->Siguiente;
						}
						break;
				}
				
			}
			if(QueBuscar==2)
			{
				while(Auxiliar!=NULL)
				{
					if(*Auxiliar->NombredeArchivo == *NombredeArchivo)
					{
						puts("		Se encontro la imagen");
						printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
					}
					Auxiliar=Auxiliar->Siguiente;					
				}
				
			}
			if(QueBuscar==3)
			{
				while(Auxiliar!=NULL)
				{
					if(*Auxiliar->ExtensiondeArchivo == *ExtensiondeArchivo)
					{
						puts("		Se encontro la imagen");
						printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
					}
					Auxiliar=Auxiliar->Siguiente;					
				}
			}
			if(QueBuscar==4)
			{
				printf("\n 1-Valor igual\n 2-Valor menor\n 3-Valor Mayor\n");
				scanf("%d",&SelecionarFormaDeBytes);
					switch(SelecionarFormaDeBytes)
					{
					case 1:
						while(Auxiliar!=NULL)
						{
							if(Auxiliar->Bytes == Bytes)
							{
								puts("		Se encontro la imagen");
								printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
							}
							Auxiliar=Auxiliar->Siguiente;
						}
						break;
					case 2:
						while(Auxiliar!=NULL)
						{
							if(Auxiliar->Bytes <= Bytes)
							{
								puts("		Se encontro la imagen");
								printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
							}
							Auxiliar=Auxiliar->Siguiente;
						}
						break;
					case 3:
						while(Auxiliar!=NULL)
						{
							if(Auxiliar->Bytes >= Bytes)
							{
								puts("		Se encontro la imagen");
								printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
							}
							Auxiliar=Auxiliar->Siguiente;
						}
						break;
					}
				
			}
			if(QueBuscar==5)
			{
				printf("\n 1-Valor igual\n 2-Valor menor\n 3-Valor Mayor\n");
				scanf("%d",&SelecionarFormaDePrecio);
				switch(SelecionarFormaDePrecio)
				{
				case 1:
					while(Auxiliar!=NULL)
					{
						if(Auxiliar->Precio == Precio)
						{
							puts("		Se encontro la imagen");
							printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
						}
						Auxiliar=Auxiliar->Siguiente;
					}
					break;
				case 2:
					while(Auxiliar!=NULL)
					{
						if(Auxiliar->Precio <= Precio)
						{
							puts("		Se encontro la imagen");
							printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
						}
						Auxiliar=Auxiliar->Siguiente;
					}
					break;
				case 3:
					while(Auxiliar!=NULL)
					{
						if(Auxiliar->Precio >= Precio)
						{
							puts("		Se encontro la imagen");
							printf(" -Codigo:%d\n -NombredeArchivo:%s \n -Extension de archivo:%s\n -Bytes:%d \n -Precio:%.2f \n",Auxiliar->Codigo,Auxiliar->NombredeArchivo,Auxiliar->ExtensiondeArchivo,Auxiliar->Bytes,Auxiliar->Precio);
						}
						Auxiliar=Auxiliar->Siguiente;
					}
					break;
				}
				
			}
}
/*void Ordenar(struct ListadodeImagenes *Actual)*/
/*{*/
/*	struct ListadodeImagenes *Sig=Actual->Siguiente; */
/*	struct ListadodeImagenes *ActualTemporal=Actual;*/
/*	struct ListadodeImagenes *SigSig=Actual->Siguiente->Siguiente;*/
/*	struct ListadodeImagenes *AuxiliarSig=NULL; */
/*	struct ListadodeImagenes *AuxiliarActualTemporal=NULL;*/
/*	struct ListadodeImagenes *AuxDelSigSig=NULL;*/
/*	while(ActualTemporal!=NULL)*/
/*	{*/
/*		while(Auxiliar!=NULL)*/
/*		{*/
/*			if(*ActualTemporal->NombredeArchivo < *Sig->NombredeArchivo)*/
/*			{*/
			
/*				AuxiliarActualTemporal=ActualTemporal;*/
/*				AuxiliarSig=Sig;*/
/*				AuxDelSigSig=SigSig;*/
				
/*				ActualTemporal=AuxDelSigSig;*/
				
/*				Sig=AuxiliarActualTemporal;*/
				
/*				SigSig=AuxiliarSig;*/
/*				puts(Sig->NombredeArchivo);*/
/*				puts("entro");*/
/*				*Actual->Siguiente=*Auxiliar;*/
/*			}*/
/*			Auxiliar=Auxiliar->Siguiente;*/
/*		}*/
/*	ActualTemporal=ActualTemporal->Siguiente;*/
/*	Auxiliar=ActualTemporal;*/
/*	Auxiliar=Auxiliar->Siguiente;*/
/*	}*/
/*}*/
void ImagenesOrdenadas(struct ListadodeImagenes *NodoInicial)
{
	
	struct ListadodeImagenes *actual = NodoInicial;
	struct ListadodeImagenes *minimo=NULL;
	struct ListadodeImagenes*temp=NULL;
	int tempCodigo;
	char tempNombre[100];
	char tempExtension[100];
	int tempBytes;
	float tempPrecio;
	
	while (actual != NULL)
	{
		minimo = actual;
		temp = actual->Siguiente;
		
		while (temp != NULL)
		{
			//Compara el primer valor con todos los otros para ver cual es el mas chico 
			if (strcmp(temp->NombredeArchivo, minimo->NombredeArchivo) < 0)
			{
				minimo = temp;
			}
			
			temp = temp->Siguiente;
		}
		// Intercambiar los campos de los nodos
		if (minimo != actual)
		{
			tempCodigo = actual->Codigo;
			strcpy(tempNombre, actual->NombredeArchivo);
			strcpy(tempExtension, actual->ExtensiondeArchivo);
			tempBytes=actual->Bytes;
			tempPrecio=actual->Precio;
			
			actual->Codigo = minimo->Codigo;
			strcpy(actual->NombredeArchivo, minimo->NombredeArchivo);
			strcpy(actual->ExtensiondeArchivo, minimo->ExtensiondeArchivo);
			actual->Bytes=minimo->Bytes;
			actual->Precio=minimo->Precio;
			
			minimo->Codigo = tempCodigo;
			strcpy(minimo->NombredeArchivo, tempNombre);
			strcpy(minimo->ExtensiondeArchivo, tempExtension);
			minimo->Bytes=tempBytes;
			minimo->Precio=tempPrecio;
		}
		
		actual = actual->Siguiente;
	}
}
//Leo el archivo con datos
struct ListadodeImagenes *LeerArchivos(FILE *Archivo)
{
	struct ListadodeImagenes *Cabeza=NULL;
	struct ListadodeImagenes *Ultimo=NULL;
	if(Archivo=fopen("ArchivoImagen.txt","rb+"))
	{
		do
		{
		struct ListadodeImagenes *NuevoNodo=(struct ListadodeImagenes *) malloc(sizeof(struct ListadodeImagenes));
		fread(NuevoNodo,sizeof(struct ListadodeImagenes),1,Archivo);
			if(Cabeza==NULL)
			{
				Cabeza=NuevoNodo;
				Ultimo=NuevoNodo;
			}
			else
			{
				//Enlaza mis nodos con el siguiente valor, el valor que se incrementa en cada pasada es NuevoNodo, una vez que sea nulo sale del Do While
				Ultimo->Siguiente=NuevoNodo;
				Ultimo=NuevoNodo;
			}
		}while(Ultimo->Siguiente!=NULL);
	}
	// Devuelvo mi nodo inicial para poder trabajar con el en programa principal
	return(Cabeza);
}
//Recorro el nodo para poder tener nocion de donde esta mi nodo final para poder trabajar en el programa principal
struct ListadodeImagenes *EncontarNodoFinal(struct ListadodeImagenes *NodoInicial)
{
	struct ListadodeImagenes *NodoTemp=NodoInicial;
	struct ListadodeImagenes *NodoFinal=NULL;
	while(NodoTemp!=NULL)
	{
		NodoFinal=NodoTemp;
		NodoTemp=NodoTemp->Siguiente;
	}
	return(NodoFinal);
}
