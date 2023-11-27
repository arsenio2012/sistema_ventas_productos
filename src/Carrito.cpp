// Carrito.cpp
#include "Carrito.h"
#include <iostream>

void Carrito::agregarProducto(const Producto& producto, int cantidad) {
    items.push_back({producto, cantidad});
}

void Carrito::mostrarCarrito() const {
    std::cout << "Contenido del carrito:\n";
    for (const auto& item : items) {
        std::cout << "ID: " << item.producto.getId() << ", Descripción: " << item.producto.getDescripcion()
                  << ", Cantidad: " << item.cantidad << ", Precio unitario: " << item.producto.getPrecio() << "$\n";
    }
}

double Carrito::obtenerTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.producto.getPrecio() * item.cantidad;
    }
    return total;
}
