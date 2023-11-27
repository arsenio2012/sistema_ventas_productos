// Carrito.h
#ifndef CARRITO_H
#define CARRITO_H

#include <vector>
#include "Producto.h"

class Carrito {
public:
    // Método para agregar un producto al carrito
    void agregarProducto(const Producto& producto, int cantidad);

    // Método para mostrar el contenido del carrito
    void mostrarCarrito() const;

    // Método para obtener el total de la compra
    double obtenerTotal() const;

private:
    // Estructura para almacenar información del producto en el carrito
    struct ItemCarrito {
        Producto producto;
        int cantidad;
    };

    std::vector<ItemCarrito> items;
};

#endif // CARRITO_H
