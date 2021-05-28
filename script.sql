CREATE DATABASE base_ejemplo;

USE base_ejemplo;

CREATE TABLE productos (
  id int(3) NOT NULL auto_increment,
  nombre varchar(50) default NULL,
  descripcion varchar(100) default NULL,
  precio int(3) NOT NULL default '0',
  cantidad varchar(40) default NULL,
  PRIMARY KEY  (id)
) AUTO_INCREMENT=1 ;

INSERT INTO productos(nombre, descripcion, precio, cantidad) VALUES('Jabon Dove Dermo Aclarant', 'Jabon para uso diario dove', 7, '250');
INSERT INTO productos(nombre, descripcion, precio, cantidad) VALUES('Salsa naturas ranchera', 'Salsa naturas para cocina excentrica', 3, '35');
INSERT INTO productos(nombre, descripcion, precio, cantidad) VALUES('Pasta colgate triple accion', 'Pasta para limpieza de dientes colgate triple accion', 10, '20');

SELECT * FROM productos;