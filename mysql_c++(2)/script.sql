CREATE DATABASE `db2_empresa` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;

/*Statement para crear la tabla marcas*/
CREATE TABLE `marcas` (
  `id_marca` smallint NOT NULL AUTO_INCREMENT,
  `marca` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id_marca`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*Statement para crear la tabla productos*/
CREATE TABLE `productos` (
  `id_producto` int NOT NULL AUTO_INCREMENT,
  `producto` varchar(50) DEFAULT NULL,
  `id_marca` smallint DEFAULT NULL,
  `descripcion_producto` varchar(100) DEFAULT NULL,
  `precio_costo` decimal(8,2) DEFAULT NULL,
  `precio_venta` decimal(8,2) DEFAULT NULL,
  `existencia` int DEFAULT NULL,
  `fecha_ingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`id_producto`),
  KEY `id_marca_marca_productos_idx` (`id_marca`),
  CONSTRAINT `id_marca_marca_productos` FOREIGN KEY (`id_marca`) REFERENCES `marcas` (`id_marca`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
