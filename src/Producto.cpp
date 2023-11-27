#include "Producto.h"

// Constructor
Producto::Producto(int id, const std::string& descripcion, int cantidad, double precio, int idCategoria)
    : id(id), descripcion(descripcion), cantidad(cantidad), precio(precio), idCategoria(idCategoria) {
}

// Método para imprimir información del producto
void Producto::mostrarInformacion() const {
    std::cout << "ID: " << id
              << ", Descripción: " << descripcion
              << ", Cantidad: " << cantidad
              << ", Precio: " << precio << "$"
              << ", Categoría ID: " << idCategoria
              << std::endl;
}

std::string Producto::getDescripcion() const {
    return descripcion;
}

int Producto::getCantidad() const {
    return cantidad;
}

double Producto::getPrecio() const {
    return precio;
}

int Producto::getIdCategoria() const {
    return idCategoria;
}


// Implementación de los métodos getter y setter
int Producto::getId() const {
    return id;
}

void Producto::setCantidad(int nuevaCantidad) {
    cantidad = nuevaCantidad;
}