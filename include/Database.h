#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <vector>
#include "Producto.h"

class Database {
public:
    Database(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    ~Database();

    bool connect();
    void disconnect();

    bool executeQuery(const std::string& query);
    sql::ResultSet* executeQueryWithResults(const std::string& query);
    bool executeUpdate(const std::string& query);

    std::vector<Producto> obtenerProductos();

    bool agregarProducto(const Producto& producto);

    void actualizarStockProducto(int idProducto, int nuevaCantidad);
    void actualizarInformacionProducto(int idProducto, const std::string& campo, const std::string& nuevoValor);
    void eliminarProducto(int idProducto);


private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
};

#endif // DATABASE_H
