// src/Main.cpp
#include <iostream>
#include <string>

#include "Database.h"
#include "Producto.h"
#include "Carrito.h"

int main() {
    std::cout << "Bienvenido a la aplicación de ventas.\n";

    // Autenticación
    std::string usuario, contrasena;
    std::cout << "Ingrese como 'cliente' o 'admin': ";
    std::cin >> usuario;

    // Crear una instancia de la base de datos MySQL
    // Crear una instancia de la base de datos
    Database db("localhost", "root", "", "sistemaVentas");

    if (!db.connect()) {
        std::cout << "Error al conectar a la base de datos. Saliendo.\n";
        return 1;
    }

    if (usuario == "cliente") {
        Carrito carrito;

        // Mostrar la lista de productos al cliente
        std::cout << "Lista de productos disponibles:\n";

        // Obtener productos usando el nuevo método de Database
        std::vector<Producto> productos = db.obtenerProductos();

        // Mostrar información de cada producto
        for (const auto& producto : productos) {
            producto.mostrarInformacion();
        }
        
        // Pienso en agregar un carrito de compras
        // Agregar productos al carrito
        std::cout << "Seleccione productos para comprar (Ingrese el ID del producto y la cantidad):\n";
        std::cout << "Ingrese 0 para finalizar la compra.\n";

        int idProducto;
        int cantidad;

        while (true) {
            std::cout << "ID del producto (0 para finalizar): ";
            std::cin >> idProducto;

            if (idProducto == 0) {
                break; // El cliente ha finalizado la compra
            }

            // Buscar el producto en la lista de productos
            auto it = std::find_if(productos.begin(), productos.end(),
                [idProducto](const Producto& producto) { return producto.getId() == idProducto; });

            if (it != productos.end()) {
                // Producto encontrado
                std::cout << "Cantidad a comprar: ";
                std::cin >> cantidad;

                // Verificar si hay suficientes existencias
                if (cantidad > 0 && cantidad <= it->getCantidad()) {
                    // Actualizar la cantidad disponible del producto
                    it->setCantidad(it->getCantidad() - cantidad);

                    // Actualizar la cantidad disponible del producto en la base de datos
                    db.actualizarStockProducto(it->getId(), it->getCantidad());

                    // Agregar al carrito
                    carrito.agregarProducto(*it, cantidad);

                    std::cout << "Producto agregado a la compra.\n";
                } else {
                    std::cout << "Error: Cantidad no válida o insuficiente stock.\n";
                }
            } else {
                std::cout << "Error: Producto no encontrado.\n";
            }
        }

        // Mostrar el contenido del carrito y el total de la compra
        carrito.mostrarCarrito();
        std::cout << "Total de la compra: $" << carrito.obtenerTotal() << std::endl;
        // Realizar la venta
        

        // Mostrar el historial de ventas del cliente
       
    } else if (usuario == "admin") {
        // Autenticación de administrador
        std::cout << "Ingrese la contraseña de administrador: ";
        std::cin >> contrasena;

        // Verificar la contraseña (puedes cambiar esto por una lógica más segura)
        if (contrasena == "123456") {
            // Lógica del administrador aquí
            std::cout << "Bienvenido, administrador.\n";
            int opcion;

            do {
                std::cout << "\nMenú del Administrador:\n";
                std::cout << "1. Ver Inventario\n";
                std::cout << "2. Agregar Producto\n";
                std::cout << "3. Editar Producto\n";
                std::cout << "4. Eliminar Producto\n";
                std::cout << "5. Salir\n";
                std::cout << "Seleccione una opción: ";
                std::cin >> opcion;

                switch (opcion) {
                    case 1: {
                        // Mostrar inventario
                        // Mostrar la lista de productos al cliente
                        std::cout << "Lista de productos disponibles:\n";

                        // Obtener productos usando el nuevo método de Database
                        std::vector<Producto> productos = db.obtenerProductos();

                        // Mostrar información de cada producto
                        for (const auto& producto : productos) {
                            producto.mostrarInformacion();
                        }
                        break;
                    }

                    case 2: {
                        // Agregar producto
                        // Solicitar al administrador la información del nuevo producto
                        std::string descripcion;
                        int cantidad;
                        double precio;
                        int idCategoria;

                        std::cout << "Ingrese la descripción del nuevo producto: ";
                        std::cin.ignore();  // Para manejar correctamente la entrada después de leer un número
                        std::getline(std::cin, descripcion);

                        std::cout << "Ingrese la cantidad del nuevo producto: ";
                        std::cin >> cantidad;

                        std::cout << "Ingrese el precio del nuevo producto: ";
                        std::cin >> precio;

                        std::cout << "Ingrese el ID de categoría del nuevo producto: ";
                        std::cin >> idCategoria;

                        // Crear un nuevo objeto Producto con la información proporcionada
                        Producto nuevoProducto(0, descripcion, cantidad, precio, idCategoria);

                        // Agregar el nuevo producto a la base de datos
                        // Aquí necesitarás agregar un método a tu clase Database para realizar la inserción
                        if (db.agregarProducto(nuevoProducto)) {
                            std::cout << "Producto agregado exitosamente.\n";
                        } else {
                            std::cout << "Error al agregar el producto.\n";
                        }
                        break;
                    }
                    case 3: {
                        // Mostrar la lista de productos
                        std::cout << "Lista de productos disponibles:\n";

                        // Obtener productos usando el método de Database
                        std::vector<Producto> productos = db.obtenerProductos();

                        // Mostrar información de cada producto
                        for (const auto& producto : productos) {
                            producto.mostrarInformacion();
                        }

                        // Pedir al administrador que seleccione el producto a editar
                        std::cout << "Ingrese el ID del producto que desea editar: ";
                        int idProductoEditar;
                        std::cin >> idProductoEditar;

                        // Buscar el producto en la lista de productos
                        auto it = std::find_if(productos.begin(), productos.end(),
                            [idProductoEditar](const Producto& producto) { return producto.getId() == idProductoEditar; });

                        if (it != productos.end()) {
                            // Producto encontrado, solicitar al administrador qué desea editar
                            std::cout << "Seleccione qué desea editar:\n";
                            std::cout << "1. Nombre\n";
                            std::cout << "2. Cantidad\n";
                            std::cout << "3. Precio\n";
                            std::cout << "4. Categoría\n";
                            int opcionEditar;
                            std::cin >> opcionEditar;

                            // Variable para almacenar el nuevo valor
                            std::string nuevoValor;
                            std::string campo;

                            switch (opcionEditar) {
                                case 1: {
                                    // Editar nombre
                                    std::cout << "Ingrese el nuevo nombre: ";
                                    std::cin >> nuevoValor;
                                    campo = "descrip_productos";

                                    break;
                                }
                                case 2: {
                                    // Editar cantidad
                                    std::cout << "Ingrese la nueva cantidad: ";
                                    std::cin >> nuevoValor;
                                    campo = "cantidad";
                                    break;
                                }
                                case 3: {
                                    // Editar precio
                                    std::cout << "Ingrese el nuevo precio: ";
                                    std::cin >> nuevoValor;
                                    campo = "precio";
                                    break;
                                }
                                case 4: {
                                    // Editar categoría
                                    std::cout << "Ingrese la nueva categoría: ";
                                    std::cin >> nuevoValor;
                                    campo = "id_categoria";
                                    break;
                                }
                                default:
                                    std::cout << "Opción no válida.\n";
                                    break;
                            }

                            // Guardar los cambios en la base de datos
                            db.actualizarInformacionProducto(it->getId(), campo, nuevoValor);
                            std::cout << "Producto actualizado correctamente.\n";
                        } else {
                            std::cout << "Error: Producto no encontrado.\n";
                        }
                        break;
                    }
                    case 4: {
                       // Eliminar producto
                        // Mostrar la lista de productos
                        std::cout << "Lista de productos disponibles:\n";

                        // Obtener productos usando el método de Database
                        std::vector<Producto> productos = db.obtenerProductos();

                        // Mostrar información de cada producto
                        for (const auto& producto : productos) {
                            producto.mostrarInformacion();
                        }
                        
                        std::cout << "Ingrese el ID del producto que desea eliminar: ";
                        int idProductoEliminar;
                        std::cin >> idProductoEliminar;

                        // Buscar el producto en la lista de productos
                        auto it = std::find_if(productos.begin(), productos.end(),
                            [idProductoEliminar](const Producto& producto) { return producto.getId() == idProductoEliminar; });

                        if (it != productos.end()) {
                            // Producto encontrado, confirmar la eliminación
                            std::cout << "¿Está seguro de que desea eliminar este producto? (Sí/No): ";
                            std::string confirmacion;
                            std::cin >> confirmacion;

                            if (confirmacion == "Sí" || confirmacion == "si" || confirmacion == "S" || confirmacion == "s") {
                                // Eliminar el producto de la base de datos y de la lista
                                db.eliminarProducto(idProductoEliminar);
                                productos.erase(it);

                                std::cout << "Producto eliminado correctamente.\n";
                            } else if (confirmacion == "No" || confirmacion == "no" || confirmacion == "N" || confirmacion == "n") {
                                std::cout << "Eliminación cancelada.\n";
                            } else {
                                std::cout << "Entrada no válida. Eliminación cancelada.\n";
                            }
                        } else {
                            std::cout << "Error: Producto no encontrado.\n";
                        }
                        break;
                    }
                    case 5:
                        // Salir    
                        break;
                    default:
                        std::cout << "Opción no válida. Intente nuevamente.\n";
                }

            } while (opcion != 5);
        } else {
            std::cout << "Contraseña incorrecta. Saliendo.\n";
            return 1; // Salir con código de error
        }
    } else {
        std::cout << "Rol no reconocido. Saliendo.\n";
        return 1; // Salir con código de error
    }

    return 0;
}
