# Sistema de Gestión de Librería 📚

Sistema de consola desarrollado en C++ como proyecto universitario. Permite gestionar libros, clientes, ventas y pedidos a través de un menú con dos roles: administrador y usuario.

## Funcionalidades

### Administrador
- Registrar libros y ventas
- Ver reporte de stock, ventas, pedidos y clientes frecuentes

### Usuario
- Registrar clientes
- Realizar pedidos con carrito de compras
- Consultar stock disponible

## Validaciones implementadas
- Verificación de tipos de dato en todas las entradas
- Control de stock antes de registrar ventas o pedidos
- IDs únicos para libros y ventas
- Validación de DNI (8 dígitos numéricos)
- Verificación de que el cliente exista antes de operar
- Límite de capacidad en los arreglos

## Tecnologías
- Lenguaje: C++
- Entorno: Visual Studio 2022
- Estructuras utilizadas: structs, arreglos, funciones

## Ejecución
1. Abrir el proyecto en Visual Studio
2. Compilar y ejecutar con `Ctrl + F5`
