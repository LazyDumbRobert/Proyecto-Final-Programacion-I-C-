#pragma once
#include "Persona.h"
#include "iostream"
#include "ConexionDB2.h"
#include<mysql.h>

using namespace std;

class Empleado : Persona {
private:
	string direccion, dpi, fecha_nacimiento, idpuesto, fecha_inicio_labores, fechaingreso;

public:
	Empleado() {

	}
	Empleado(string name, string lastname, string tel, string genre, string adress, string dpi_1, string date_birth, string id_puesto, string fecha_inc, string date_ing) : Persona(name, lastname, tel, genre) {
		direccion = adress;
		dpi = dpi_1;
		fecha_nacimiento = date_birth;
		idpuesto = id_puesto;
		fecha_inicio_labores = fecha_inc;
		fechaingreso = date_ing;
	}
	//metodos set y get
	void setDireccion(string adress) { direccion = adress; }
	void setDPI(string dp_i) { dpi = dp_i; }
	void setFechaNacimiento(string date_birth) { fecha_nacimiento = date_birth; }
	void setIdpuesto(string id_puesto) { idpuesto = id_puesto; }
	void setFechaInicioLabores(string fecha_inc) { fecha_inicio_labores = fecha_inc; }
	void setFechaIngreso(string date_ing) { fechaingreso = date_ing; }
	void setNombres(string name) { nombres = name; }
	void setApellidos(string lastname) { apellidos = lastname; }
	void setTelefono(string tel) { telefono = tel; }
	void setGenero(string genre) { genero = genre; }

	string getDireccion() { return direccion; }
	string getDPI() { return dpi; }
	string getFechaNacimiento() { return fecha_nacimiento; }
	string getIdpuesto() { return idpuesto; }
	string getFechaInicioLabores() { return fecha_inicio_labores; }
	string getFechaIngreso() { return fechaingreso; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getTelefono() { return telefono; }
	string getGenero() { return genero; }


	void leer() {
		system("cls");
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select *, if(genero = 1, 'Masculino','Femenino') as Genero from empleados;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "\t\tEmpleados" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << "ID del empleado: " << fila[0] << endl;
					cout << "Nombres: " << fila[1] << endl;
					cout << "Apellidos: " << fila[2] << endl;
					cout << "direccion: " << fila[3] << endl;
					cout << "Telefono: " << fila[4] << endl;
					cout << "DPI: " << fila[5] << endl;
					cout << "Fecha de nacimiento: " << fila[7] << endl;
					cout << "ID de puesto: " << fila[8] << endl;
					cout << "Fecha de incio de labores: " << fila[9] << endl;
					cout << "Fecha de ingreso del empleado: " << fila[10] << endl;
					cout << "Genero: " << fila[11] << endl;
					cout << "____________________________________________" << endl;
				}
			}
		}
		cout << "____________________________________________" << endl;
		cn.cerrar_conexion();
		system("pause");
	}

	void ingresar() {
		int q_estado;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();



		if (cn.getConectar()) {
			string insertar = "INSERT INTO `proyecto_final_programacion`.`empleados` (`nombres`,`apellidos`,`direccion`,`telefono`,`DPI`,`genero`,`fecha_nacimiento`,`idpuestos`,`fecha_inicio_labores`,`fechaingreso`) VALUES('"+nombres+"', '"+apellidos+"', '"+direccion+"', '"+telefono+"', '"+dpi+"', if ('" + genero + "' = 'M', 1, 0), '"+fecha_nacimiento+"', "+idpuesto+", '"+fecha_inicio_labores+"', '"+fechaingreso+"')";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				system("cls");
				cout << "Ingreso exitoso" << endl;
			}
		}
		else {
			system("cls");
			cout << "Hubo un error al ingresar los datos" << endl;

		}
		cn.cerrar_conexion();
		system("pause");
	}

	void eliminar(int id_p) {

		int q_estado;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string id_p1 = to_string(id_p);
			string eliminar = "DELETE from empleados where idempleado = " + id_p1 + "";
			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				system("cls");
				cout << "Eliminacion exitosa" << endl;

			}
		}
		else {
			system("cls");
			cout << "Hubo un error a la hora de eliminar el registro deseado" << endl;
		}
		cn.cerrar_conexion();
		system("pause");
	}

	void actualizar(int id_p) {

		int q_estado;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string id_p1 = to_string(id_p);
			string actualizar = "UPDATE `proyecto_final_programacion`.`empleados` SET `nombres` = '" + nombres + "', `apellidos` = '" + apellidos + "', `direccion` = '" + direccion + "', `telefono` = '" + telefono + "', `DPI` = '" + dpi + "', `genero` = '" + genero + "', `fecha_nacimiento` = '" + fecha_nacimiento + "', `idpuestos` = '" + idpuesto + "', `fecha_inicio_labores` = '" + fecha_inicio_labores + "', `fechaingreso` = '" + fechaingreso + "' WHERE `idempleado` = " + id_p1 + ";";
			const char* i = actualizar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (q_estado) {
				system("cls");
				cout << "Actualizacion exitosa" << endl;
			}
		}
		else {
			system("cls");
			cout << "Hubo un error a la hora de eliminar el registro deseado" << endl;
		}
		cn.cerrar_conexion();
		system("pause");
	}
};
