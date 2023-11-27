cmake_minimum_required(VERSION 3.10)

project(sistema_ventas_productos)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)  # Agrega esta línea

add_executable(EjecutableVentas
    src/Main.cpp 
    src/Database.cpp 
    src/Producto.cpp 
    src/Carrito.cpp 
)

target_link_libraries(EjecutableVentas mysqlcppconn)

# Agregar estas líneas para establecer las opciones del ejecutable en windows
set_target_properties(EjecutableVentas PROPERTIES
    WIN32_EXECUTABLE YES  # Indica que es una aplicación de consola de Windows
    LINK_FLAGS "/SUBSYSTEM:CONSOLE"  # Establece el subsistema de Windows a consola
)