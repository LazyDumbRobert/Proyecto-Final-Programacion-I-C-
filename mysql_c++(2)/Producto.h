#pragma once
#include "ConexionDB2.h"
#include "string"
#include<mysql.h>



class Producto {
private:
	string producto, idmarca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso;

public:
	Producto() {

	}
	Producto(string product, string id_marca, string description, string img, string p_c, string p_v, string exist, string f_i) {
		producto = product;
		idmarca = id_marca;
		descripcion = description;
		imagen = img;
		precio_costo = p_c;
		precio_venta = p_v;
		existencia = exist;
		fecha_ingreso = f_i;
	}

	//metodos set y get
	void setProducto(string product) { producto = product; }
	void setIdMarca(string id_marca) { idmarca = id_marca; }
	void setDescripcion(string descrip) { descripcion = descrip; }
	void setImagen(string img) { imagen = img; }
	void setPrecioCosto(string p_c) { precio_costo = p_c; }
	void setPrecioVenta(string p_v) { precio_venta = p_v; }
	void setExistencia(string exist) { existencia = exist; }
	void setFechaIngreso(string f_i) { fecha_ingreso = f_i; }

	string getProducto() { return producto; }
	string getIdMarca() { return idmarca; }
	string getDescripcion() { return descripcion; }
	string getImagen() { return imagen; }
	string getPrecioCosto() { return precio_costo; }
	string getPrecioVenta() { return precio_venta; }
	string getExistencia() { return existencia; }
	string getFechaIngreso() { return fecha_ingreso; }


	void leer() {
		system("cls");
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select * from productos";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "\t\tProductos" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << "ID de de producto: " << fila[0] << endl;
					cout << "Producto: " << fila[1] << endl;
					cout << "ID de marca: " << fila[2] << endl;
					cout << "Descripcion: " << fila[3] << endl;
					cout << "Imagen: " << fila[4] << endl;
					cout << "Precio costo: " << fila[5] << endl;
					cout << "Precio venta: " << fila[6] << endl;
					cout << "Existencia: " << fila[7] << endl;
					cout << "Fecha de ingreso: " << fila[8] << endl;
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
			string insertar = "INSERT INTO `proyecto_final_programacion`.`productos` (`producto`, `idmarca`,`descripcion`,`imagen`,`precio_costo`,`precio_venta`,`existencia`,`fecha_ingreso`) VALUES('" + producto + "','" + idmarca + "','" + descripcion + "','" + imagen + "','" + precio_costo + "','" + precio_venta + "','" + existencia + "','" + fecha_ingreso + "')";
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
			string eliminar = "DELETE from productos where idproducto = " + id_p1 + "";
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
			string eliminar = "UPDATE `proyecto_final_programacion`.`productos` SET `producto` = '"+producto+"', `idmarca` = '"+idmarca+"', `descripcion` = '"+descripcion+"', `imagen` = '"+imagen+"', `precio_costo` = '"+precio_costo+"', `precio_venta` = '"+precio_venta+"', `existencia` = '"+existencia+"', `fecha_ingreso` = '"+fecha_ingreso+"' WHERE `idproducto` = "+id_p1+"";
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
