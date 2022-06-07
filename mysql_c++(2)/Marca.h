#pragma once

#include<iostream>
#include "ConexionDB2.h"
#include<string>
#include<mysql.h>

using namespace std;

class Marca {
private:
	string marca;

public:
	Marca() {

	}
	Marca(string m) {
		marca = m;
	}


	//Metodos set y get

	void setMarca(string m) { marca = m; }
	string getMarca() { return marca; }



	void leer() {
		system("cls");
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select * from marcas";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "\t\tMarcas" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << "ID de la marca: " << fila[0] << endl;
					cout << "Nombre de la marca: " << fila[1] << endl;
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
			string insertar = "INSERT INTO `proyecto_final_programacion`.`marcas` (`marca`) VALUES('" + marca + "');";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (q_estado) {
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
			string eliminar = "DELETE from marcas where idmarca = " + id_p1 + "";
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
			string eliminar = "UPDATE `proyecto_final_programacion`.`marcas` SET `marca` = '" + marca + "' WHERE `idmarca` = " + id_p1 + "";
			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
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

