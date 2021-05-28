//Proyecto final de programacion I
//Universidad Mariano Galvez

#include "sql_db.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// Definición de estructura
struct producto{ 
   int id; 
   char nombre[50]; 
   char descripcion[100]; 
   int cantidad; 
   char precio[40]; 
};

typedef struct producto Producto;

// Objeto global
sql_db obj_mysql("localhost", "root", "1234", "base_ejemplo");

// Prototipos de metodos
void ingresar(), insertar(Producto info); 
void buscar(), modificar(), actualizar(Producto info), eliminar();
void mostrar(); 
char menu(void); void pausa();

int main(int argc, char *argv[])
{
   system("CLS"); 
   char op; 

   for(;;) 
   { 
     fflush(stdin);
     switch(op=menu()) 
     { 
        case '1': 
           ingresar(); 
           pausa(); 
           break; 
        case '2': 
           buscar(); 
           pausa();
           break; 
        case '3': 
           modificar(); 
           pausa(); 
           break; 
        case '4': 
           eliminar(); 
           pausa(); 
           break; 
        case '5': 
           mostrar(); 
           pausa(); 
           break; 
        case '6': 
           break; 
        default : 
           cout << "Opcion no valida"; 
           pausa();
           break; 
     } 

     if(op=='6') break; 
     system("CLS"); 
   } 

   return 0;
}

void ingresar() 
{ 
   Producto info; 

   cout << "Ingrese nombre: ";
   cin >> info.nombre;
   cout << "Ingrese descripcion: ";
   cin >> info.descripcion;
   cout << "Ingrese cantidad: ";
   cin >> info.cantidad;
   cout << "Ingrese precio: ";
   cin >> info.precio;   
   insertar(info);
   cout << "Producto ingresado exitosamente" << endl;
}

void insertar(Producto info) 
{  
   char *consulta;
   char sentencia[] = "INSERT INTO productos(nombre, descripcion, cantidad, precio) VALUES(\'%s\', \'%s\', %d, \'%s\')";
   
   consulta = new char[strlen(sentencia)+sizeof(Producto)-sizeof(int)];   
   sprintf(consulta, sentencia, info.nombre, info.descripcion, info.cantidad, info.precio);
   
   obj_mysql.ejecutar_sql(consulta);
} 

void buscar()
{
   char nombre[50];
   char *consulta;
   char sentencia[] =  "SELECT * FROM productos WHERE nombre=\'%s\'";
   MYSQL_RES *res;
   MYSQL_ROW  row;   
   
   cout << "Ingrese nombre a buscar: ";
   cin >> nombre;
   
   consulta = new char[strlen(sentencia)+strlen(nombre)];   
   sprintf(consulta, sentencia, nombre);
   res = obj_mysql.ejecutar_sql(consulta);
   
   if(obj_mysql.filas_afectadas()>0)
   {
       row = obj_mysql.obtener_fila(res);
	   cout << "Id: " << row[0] << endl;
	   cout << "Nombre: " << row[1] << endl;	   
	   cout << "descripcion: " << row[2] << endl;	   
	   cout << "cantidad: " << row[3] << endl;
	   cout << "precio: " << row[4] << endl;       	   
   }
   else
      cout << "Producto no encontrado" << endl;
}

void modificar()
{
   char nombre[50];
   char *consulta;
   char *temp;
   char sentencia[] = "SELECT * FROM productos WHERE nombre=\'%s\'";
   MYSQL_RES *res;
   MYSQL_ROW  row;   
   Persona info;
   
   cout << "Ingrese nombre a modificar: ";
   cin >> nombre;

   consulta = new char[strlen(sentencia)+strlen(nombre)];   
   sprintf(consulta, sentencia, nombre);
   res = obj_mysql.ejecutar_sql(consulta);

   if(obj_mysql.filas_afectadas()>0)
   {
       row = obj_mysql.obtener_fila(res);
       sprintf(temp, "%s", row[0]);
       info.id = atoi(temp);
       cout << "Ingrese nombre: ";
       cin >> info.nombre;
       cout << "Ingrese descripcion: ";
       cin >> info.descripcion;
       cout << "Ingrese cantidad: ";
       cin >> info.cantidad;
       cout << "Ingrese precio: ";
       cin >> info.precio;         
       actualizar(info);
       cout << "Datos actualizados exitosamente" << endl;       
   }
   else
      cout << "Producto no encontrado" << endl;
} 

void actualizar(Producto info)
{
   char nombre[50];
   char *consulta;
   char sentencia[] = "UPDATE productos SET nombre=\'%s\', descripcion=\'%s\', edad=%d, precio=\'%s\' WHERE id=%d";
   
   consulta = new char[strlen(sentencia)+strlen(nombre)];   
   sprintf(consulta, sentencia, info.nombre, info.descripcion, info.cantidad, info.precio, info.id);
   obj_mysql.ejecutar_sql(consulta);
} 

void eliminar() 
{ 
   char nombre[50];
   char *consulta;
   char *temp;
   char sentencia_buscar[] = "SELECT * FROM productos WHERE nombre=\'%s\'";
   char sentencia_eliminar[] = "DELETE FROM productos WHERE id=%d";
   MYSQL_RES *res;
   MYSQL_ROW  row;   
   Productos info;
   
   cout << "Ingrese nombre a eliminar: ";
   cin >> nombre;

   consulta = new char[strlen(sentencia_buscar)+strlen(nombre)];   
   sprintf(consulta, sentencia_buscar, nombre);
   res = obj_mysql.ejecutar_sql(consulta);

   if(obj_mysql.filas_afectadas()>0)
   {
       row = obj_mysql.obtener_fila(res);
       sprintf(temp, "%s", row[0]);
       int id = atoi(temp);
       consulta = new char[strlen(sentencia_eliminar)+sizeof(int)];   
       sprintf(consulta, sentencia_eliminar, id);
       obj_mysql.ejecutar_sql(consulta);
       cout << "Datos eliminados exitosamente" << endl;       
   }
   else
      cout << "Producto no encontrado" << endl;
} 

void mostrar() 
{ 
   MYSQL_RES *res;
   MYSQL_ROW row;
   int filas, columnas;
   
   res = obj_mysql.ejecutar_sql("SELECT * FROM productos");
   filas = obj_mysql.numero_filas(res);
   columnas = obj_mysql.numero_columnas(res);
   
   cout << "--- Listado de productos ("  << filas << ") ---" << endl; 
   
   for(int j=0; j<columnas; j++)
       cout << obj_mysql.nombre_columna(res, j) <<  " - ";
   cout << endl;

   while(row = obj_mysql.obtener_fila(res)) 
   {
       for(int j=0; j<columnas; j++)
       {
           cout << row[j] << ", ";
       }
       cout << endl;
   }   
} 


char menu(void) 
{ 
   char c; 
   cout << "(1)Ingresar, (2)Buscar, (3)Modificar, (4)Eliminar, (5)Mostrar lista\n(6)Salir\n"; 

   printf("Seleccion: "); 
   c=getchar(); 
   cout << endl; 
   return(c); 
}

void pausa()
{
   cout << endl;
   system("PAUSE");
   cout << endl;
}

