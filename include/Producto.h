#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>

class Producto {
public:
    // Constructor
    Producto(int id, const std::string& descripcion, int cantidad, double precio, int idCategoria);

    // Método para imprimir información del producto
    void mostrarInformacion() const;

    std::string getDescripcion() const;
    int getCantidad() const;
    double getPrecio() const;
    int getIdCategoria() const;

    // Métodos getter
    int getId() const;

    // Método setter
    void setCantidad(int nuevaCantidad);

private:
    int id;
    std::string descripcion;
    int cantidad;
    double precio;
    int idCategoria;
};

#endif // PRODUCTO_H
