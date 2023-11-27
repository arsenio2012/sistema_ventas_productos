#include "Database.h"

Database::Database(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
    : driver(nullptr), con(nullptr) {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(host, user, password);
    con->setSchema(database);
}

Database::~Database() {
    disconnect();
}

bool Database::connect() {
    return con && !con->isClosed();
}

void Database::disconnect() {
    if (con) {
        delete con;
        con = nullptr;
    }
}

bool Database::executeQuery(const std::string& query) {
    if (!connect()) {
        return false;
    }

    try {
        sql::Statement *stmt = con->createStatement();
        stmt->execute(query);
        delete stmt;
        return true;
    } catch (const sql::SQLException& e) {
        // Manejar la excepción (por ejemplo, imprimir el error)
        return false;
    }
}

sql::ResultSet* Database::executeQueryWithResults(const std::string& query) {
    if (!connect()) {
        return nullptr;
    }

    try {
        sql::Statement *stmt = con->createStatement();
        return stmt->executeQuery(query);
    } catch (const sql::SQLException& e) {
        // Manejar la excepción (por ejemplo, imprimir el error)
        return nullptr;
    }
}

bool Database::executeUpdate(const std::string& query) {
    if (!connect()) {
        return false;
    }

    try {
        sql::Statement *stmt = con->createStatement();
        stmt->executeUpdate(query);
        delete stmt;
        return true;
    } catch (const sql::SQLException& e) {
        // Manejar la excepción (por ejemplo, imprimir el error)
        return false;
    }
}

std::vector<Producto> Database::obtenerProductos() {
    std::vector<Producto> productos;

    // Consulta SQL para obtener todos los productos
    std::string query = "SELECT * FROM productos";

    // Ejecutar la consulta
    sql::ResultSet* resultSet = executeQueryWithResults(query);

    // Procesar los resultados y crear objetos Producto
    if (resultSet) {
        while (resultSet->next()) {
            Producto producto(resultSet->getInt("id_productos"),
                              resultSet->getString("descrip_productos"),
                              resultSet->getInt("cantidad"),
                              resultSet->getDouble("precio"),
                              resultSet->getInt("id_categoria"));

            productos.push_back(producto);
        }

        delete resultSet;
    } else {
        std::cout << "Error al obtener la lista de productos.\n";
    }

    return productos;
}

bool Database::agregarProducto(const Producto& producto) {
    if (!connect()) {
        return false;
    }

    try {
        // Verificar si el producto ya existe en la base de datos por su nombre
        sql::PreparedStatement *stmtCheck = con->prepareStatement(
            "SELECT * FROM productos WHERE descrip_productos = ?");
        stmtCheck->setString(1, producto.getDescripcion());

        sql::ResultSet *result = stmtCheck->executeQuery();

        if (result->next()) {
            // El producto ya existe, sumar la cantidad
            int cantidadExistente = result->getInt("cantidad");
            int nuevaCantidad = cantidadExistente + producto.getCantidad();

            // Actualizar la cantidad
            sql::PreparedStatement *stmtUpdate = con->prepareStatement(
                "UPDATE productos SET cantidad = ? WHERE descrip_productos = ?");
            stmtUpdate->setInt(1, nuevaCantidad);
            stmtUpdate->setString(2, producto.getDescripcion());
            stmtUpdate->executeUpdate();
            delete stmtUpdate;

            // Liberar recursos
            delete stmtCheck;
            delete result;

            return true;
        }

        // El producto no existe, agregarlo
        sql::PreparedStatement *stmtAdd = con->prepareStatement(
            "INSERT INTO productos (descrip_productos, cantidad, precio, id_categoria) "
            "VALUES (?, ?, ?, ?)");
        stmtAdd->setString(1, producto.getDescripcion());
        stmtAdd->setInt(2, producto.getCantidad());
        stmtAdd->setDouble(3, producto.getPrecio());
        stmtAdd->setInt(4, producto.getIdCategoria());
        stmtAdd->executeUpdate();
        delete stmtAdd;

        // Liberar recursos
        delete stmtCheck;
        delete result;

        return true;
    } catch (const sql::SQLException& e) {
        // Manejar la excepción (por ejemplo, imprimir el error)
        return false;
    }
}

void Database::actualizarStockProducto(int idProducto, int nuevaCantidad) {
    try {
        std::string query = "UPDATE productos SET cantidad = ? WHERE id_productos = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(query));
        pstmt->setInt(1, nuevaCantidad);
        pstmt->setInt(2, idProducto);
        pstmt->executeUpdate();
    } catch (const sql::SQLException& e) {
        // Maneja las excepciones según tus necesidades
        std::cerr << "Error al actualizar el stock del producto: " << e.what() << std::endl;
    }
}

void Database::actualizarInformacionProducto(int idProducto, const std::string& campo, const std::string& nuevoValor) {
    try {
        std::string query = "UPDATE productos SET " + campo + " = ? WHERE id_productos = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(query));
        pstmt->setString(1, nuevoValor);
        pstmt->setInt(2, idProducto);
        pstmt->executeUpdate();
    } catch (const sql::SQLException& e) {
        // Maneja las excepciones según tus necesidades
        std::cerr << "Error al actualizar la información del producto: " << e.what() << std::endl;
    }
}

void Database::eliminarProducto(int idProducto) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("DELETE FROM productos WHERE id_productos = ?"));
        pstmt->setInt(1, idProducto);
        pstmt->executeUpdate();
    } catch (sql::SQLException& e) {
        // Manejar la excepción según tus necesidades
        std::cerr << "Error al eliminar el producto: " << e.what() << std::endl;
    }
}