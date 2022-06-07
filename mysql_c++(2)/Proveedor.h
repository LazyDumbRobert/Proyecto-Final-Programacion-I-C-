#pragma once
#include "ConexionDB2.h"
#include "string"
#include<mysql.h>



class Proveedor {
private:
	string proveedor, nit, direccion, telefono;

public:
	Proveedor() {

	}
	Proveedor(string prov, string NIT, string adress, string tel) {
		proveedor = prov;
		nit = NIT;
		direccion = adress;
		telefono = tel;
	}

	//metodos set y get
	void setProveedor(string prov) { proveedor = prov;; }
	void setNit(string NIT) { nit = NIT; }
	void setDireccion(string adress) { direccion = adress; }
	void setTelefono(string tel) { telefono = tel; }

	string getProveedor() { return proveedor; }
	string getNit() { return nit; }
	string getDireccion() { return direccion; }
	string getTelefono() { return telefono; }


	void leer() {
		system("cls");
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select * from proveedores";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "\t\tProveedores" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << "ID de proveedor: " << fila[0] << endl;
					cout << "Proveedor: " << fila[1] << endl;
					cout << "NIT: " << fila[2] << endl;
					cout << "Direccion: " << fila[3] << endl;
					cout << "Telefono: " << fila[4] << endl;
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
			string insertar = "INSERT INTO `proyecto_final_programacion`.`proveedores` (`proveedor`, `NIT`, `direccion`, `telefono`) VALUES('" + proveedor + "','" + nit + "','" + direccion + "','" + telefono + "');";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
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
			string eliminar = "DELETE from proveedores where idproveedor = " + id_p1 + "";
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
			string eliminar = "UPDATE `proyecto_final_programacion`.`proveedores` SET `proveedor` = '" + proveedor + "', `NIT` = '" + nit + "', `direccion` = '" + direccion + "', `telefono` = '" + telefono + "' WHERE `idproveedor` = " + id_p1 + ";";
			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				system("cls");
				cout << "Actualizacion exitosa" << endl;
			}
		}
		else {
			system("cls");
			cout << "Hubo un error a la hora de actualizar el registro deseado" << endl;
		}
		cn.cerrar_conexion();
		system("pause");
	}
};