#pragma once
#include "ConexionDB2.h"
#include "string"
#include<mysql.h>
#include<stdlib.h>
#include <fstream>

class Compra{
private:
	int no_orden_compra = 0;
	string idproveedor, fecha_orden, fechaingreso, nombre_proveedor;


public:
	Compra() {

	}
	Compra(string idproveedor_cs, string fecha_orden_cs, string fecha_ingreso_cs) {
		idproveedor = idproveedor_cs;
		fecha_orden = fecha_orden_cs;
		fechaingreso = fecha_ingreso_cs;
	}

	//metodos set y get
	void setNo_orden_compra(int no_orden) { no_orden_compra = no_orden; }
	void setIdproveedor(string idprov) { idproveedor = idprov; }
	void setFecha_orden(string fechaord) { fecha_orden = fechaord; }
	void setFechaingreso(string fechaing) { fechaingreso = fechaing; }


	int getNo_orden_compra() { return no_orden_compra; }
	string getIdproveedor() { return idproveedor; }
	string getFecha_orden() { return fecha_orden; }
	string getFechaingreso() { return fechaingreso; }

	void ingresar() {
		int q_estado;
		string no_factura_compra_aux;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();
		if (cn.getConectar()) {
			no_factura_compra_aux = to_string(no_orden_compra);
			string insertar = "INSERT INTO `proyecto_final_programacion`.`compras` (`no_orden_compra`,`idproveedor`,`fecha_orden`,`fechaingreso`)VALUES(" + no_factura_compra_aux + "," + idproveedor + ",'" + fecha_orden + "','" + fechaingreso + "');";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (q_estado) {
				cout << "Hubo un error al ingresar los datos" << endl;
			}
		}
		cn.cerrar_conexion();
	}

	void name_proveedor() {
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select proveedor from proveedores where idproveedor = "+idproveedor+";";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					nombre_proveedor = fila[0];

				}
			}
		}
		cn.cerrar_conexion();
	}

	void no_facturas_compras() {
		no_orden_compra = 0;
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select max(idcompra) from compras";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					no_orden_compra = stoi(fila[0]) + 1;

				}
			}
		}
		cn.cerrar_conexion();
	}

	void escribir_factura_archivo() {
		ofstream archivo;
		archivo.open("factura_compra.txt", ios::out);
		name_proveedor();
		no_facturas_compras();
		archivo << "NOMBRE DE LA EMPRESA EN QUE EXTIENDE LA FACTURA" << endl;
		archivo << "Proveedor: " << nombre_proveedor << endl;
		archivo << "EL TEJAR, CHIMALTENANGO" << endl;
		archivo << "Fecha orden: " << fecha_orden << endl;
		archivo << "\n";
		archivo << "HORA" << endl;
		archivo << "Serie " << "" << endl;
		archivo << "No orden: " << no_orden_compra << "" << endl;
		archivo << "\n";
		archivo.close();
	}

	void crear_factura() {
		system("cls");
		name_proveedor();
		no_facturas_compras();
		cout << "NOMBRE DE LA EMPRESA EN QUE EXTIENDE LA FACTURA" << endl;
		cout << "Proveedor: " << nombre_proveedor << endl;
		cout << "EL TEJAR, CHIMALTENANGO" << endl;
		cout << "Fecha orden: " << fecha_orden << endl;
		cout << "\n";
		cout << "HORA" << endl;
		cout << "Serie " <<  "" << endl;
		cout << "No orden: "<< no_orden_compra << "" << endl;
		cout << "\n";
		escribir_factura_archivo();
	}

	void leer() {
		system("cls");
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select * from compras";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "\t\tVentas" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << "ID de compra: " << fila[0] << endl;
					cout << "No. orden de compra: " << fila[1] << endl;
					cout << "ID del proveedor: " << fila[2] << endl;
					cout << "Fecha de orden: " << fila[3] << endl;
					cout << "Fecha de ingreso: " << fila[4] << endl;
					cout << "____________________________________________" << endl;
				}
			}
		}
		cout << "____________________________________________" << endl;
		cn.cerrar_conexion();
		system("pause");
	}

	void eliminar(int id_p) {

		int q_estado;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string id_p1 = to_string(id_p);
			string eliminar = "DELETE from compras where idcompra = " + id_p1 + "";
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
			string eliminar = "UPDATE `proyecto_final_programacion`.`compras` SET `idproveedor` = "+idproveedor+", `fecha_orden` = '"+fecha_orden+"', `fechaingreso` = '"+fechaingreso+"' WHERE `idcompra` = "+id_p1+";";
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

