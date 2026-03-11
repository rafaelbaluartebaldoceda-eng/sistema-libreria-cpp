#include <iostream>
#include <string>
#include <limits>
#include <climits>
using namespace std;

const int MAX = 100;

struct Libro {
    int id;
    string titulo;
    string autor;
    string categoria;
    int precio;
    int stock;
};

struct Cliente {
    string dni;
    string nombre;
    string correo;
    string direccion;
    bool frecuente;
};

struct Venta {
    int idVenta;
    int idLibro;
    int cantidad;
    string dniCliente;
    int total;
};

struct ItemCarrito {
    int idLibro;
    int cantidad;
};

struct Pedido {
    int idPedido;
    string dniCliente;
    ItemCarrito carrito[MAX];
    int cantidadItems;
    string metodoEntrega;
    int total;
    string estado;
};

Libro libros[MAX];
Cliente clientes[MAX];
Venta ventas[MAX];
Pedido pedidos[MAX];
int cl = 0, cc = 0, cv = 0, cp = 0;

// ─────────────────────────────────────────────
// FUNCIONES DE VALIDACION
// ─────────────────────────────────────────────

// Leer un entero con validacion: rechaza letras y valores fuera de rango
int leerEntero(const string& mensaje, int minimo = INT_MIN, int maximo = INT_MAX) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            // El usuario ingreso algo que no es numero
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Entrada invalida. Ingrese un numero entero." << endl;
        } else if (valor < minimo || valor > maximo) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] El valor debe estar entre " << minimo << " y " << maximo << "." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

// Leer una linea de texto (acepta espacios) y verifica que no este vacia
string leerTexto(const string& mensaje) {
    string texto;
    while (true) {
        cout << mensaje;
        getline(cin, texto);
        if (!texto.empty()) return texto;
        cout << "  [!] Este campo no puede estar vacio." << endl;
    }
}

// Leer un DNI: exactamente 8 digitos numericos
string leerDNI(const string& mensaje) {
    string dni;
    while (true) {
        cout << mensaje;
        getline(cin, dni);
        bool valido = (dni.length() == 8);
        for (char c : dni) if (!isdigit(c)) valido = false;
        if (valido) return dni;
        cout << "  [!] El DNI debe tener exactamente 8 digitos numericos." << endl;
    }
}

// Verificar si ya existe un libro con ese ID
bool existeIdLibro(int id) {
    for (int i = 0; i < cl; i++)
        if (libros[i].id == id) return true;
    return false;
}

// Verificar si ya existe una venta con ese ID
bool existeIdVenta(int id) {
    for (int i = 0; i < cv; i++)
        if (ventas[i].idVenta == id) return true;
    return false;
}

// Verificar si existe un cliente con ese DNI
bool existeCliente(const string& dni) {
    for (int i = 0; i < cc; i++)
        if (clientes[i].dni == dni) return true;
    return false;
}

// Verificar si existe un libro con ese ID y retornar su indice (-1 si no existe)
int buscarLibro(int id) {
    for (int i = 0; i < cl; i++)
        if (libros[i].id == id) return i;
    return -1;
}

// ─────────────────────────────────────────────
// PRECARGA DE DATOS
// ─────────────────────────────────────────────

void precargar() {
    libros[0] = { 101, "El Principito", "Antoine de Saint-Exupery", "Ficcion", 35, 10 };
    libros[1] = { 102, "Cien Anios de Soledad", "Gabriel Garcia Marquez", "Realismo Magico", 45, 8 };
    libros[2] = { 103, "1984", "George Orwell", "Distopia", 50, 6 };
    cl = 3;

    clientes[0] = { "12345678", "Ana Torres", "ana@gmail.com", "Lima", true };
    clientes[1] = { "23456789", "Carlos Ruiz", "carlos@gmail.com", "Cusco", false };
    clientes[2] = { "34567890", "Lucia Vega", "lucia@gmail.com", "Arequipa", true };
    clientes[3] = { "45678901", "Marco Rios", "marco@gmail.com", "Piura", false };
    cc = 4;

    ventas[0] = { 1, 101, 1, "12345678", libros[0].precio };
    ventas[1] = { 2, 102, 2, "23456789", libros[1].precio * 2 };
    ventas[2] = { 3, 103, 1, "34567890", libros[2].precio };
    ventas[3] = { 4, 101, 1, "45678901", libros[0].precio };
    cv = 4;
}

// ─────────────────────────────────────────────
// FUNCIONES PRINCIPALES
// ─────────────────────────────────────────────

void registrarLibro() {
    cout << endl << "--- REGISTRAR LIBRO ---" << endl;

    // Verificar espacio disponible
    if (cl >= MAX) {
        cout << "[!] No se pueden registrar mas libros. Limite alcanzado." << endl;
        return;
    }

    // ID unico
    int id;
    do {
        id = leerEntero("ID: ", 1);
        if (existeIdLibro(id))
            cout << "  [!] Ya existe un libro con ese ID. Ingrese uno diferente." << endl;
    } while (existeIdLibro(id));
    libros[cl].id = id;

    libros[cl].titulo    = leerTexto("Titulo: ");
    libros[cl].autor     = leerTexto("Autor: ");
    libros[cl].categoria = leerTexto("Categoria: ");
    libros[cl].precio    = leerEntero("Precio (S/.): ", 1);
    libros[cl].stock     = leerEntero("Stock: ", 0);
    cl++;
    cout << "Libro registrado correctamente." << endl;
}

void registrarCliente() {
    cout << endl << "--- REGISTRAR CLIENTE ---" << endl;

    if (cc >= MAX) {
        cout << "[!] No se pueden registrar mas clientes. Limite alcanzado." << endl;
        return;
    }

    // DNI unico
    string dni;
    do {
        dni = leerDNI("DNI: ");
        if (existeCliente(dni))
            cout << "  [!] Ya existe un cliente con ese DNI." << endl;
    } while (existeCliente(dni));
    clientes[cc].dni = dni;

    clientes[cc].nombre    = leerTexto("Nombre completo: ");
    clientes[cc].correo    = leerTexto("Correo: ");
    clientes[cc].direccion = leerTexto("Direccion: ");
    clientes[cc].frecuente = (leerEntero("Frecuente (1: Si / 0: No): ", 0, 1) == 1);
    cc++;
    cout << "Cliente registrado correctamente." << endl;
}

void registrarVenta() {
    cout << endl << "--- REGISTRAR VENTA ---" << endl;

    if (cv >= MAX) {
        cout << "[!] No se pueden registrar mas ventas. Limite alcanzado." << endl;
        return;
    }

    // ID de venta unico
    int idVenta;
    do {
        idVenta = leerEntero("ID de venta: ", 1);
        if (existeIdVenta(idVenta))
            cout << "  [!] Ya existe una venta con ese ID." << endl;
    } while (existeIdVenta(idVenta));
    ventas[cv].idVenta = idVenta;

    // Libro existente
    int idLibro;
    int indiceLibro;
    do {
        idLibro = leerEntero("ID del libro: ", 1);
        indiceLibro = buscarLibro(idLibro);
        if (indiceLibro == -1)
            cout << "  [!] No existe un libro con ese ID." << endl;
    } while (indiceLibro == -1);
    ventas[cv].idLibro = idLibro;

    // Cliente existente
    string dni;
    do {
        dni = leerDNI("DNI del cliente: ");
        if (!existeCliente(dni))
            cout << "  [!] No existe un cliente con ese DNI." << endl;
    } while (!existeCliente(dni));
    ventas[cv].dniCliente = dni;

    // Cantidad con validacion de stock
    int cantidad;
    do {
        cantidad = leerEntero("Cantidad: ", 1);
        if (cantidad > libros[indiceLibro].stock)
            cout << "  [!] Stock insuficiente. Stock disponible: " << libros[indiceLibro].stock << endl;
    } while (cantidad > libros[indiceLibro].stock);
    ventas[cv].cantidad = cantidad;

    ventas[cv].total = cantidad * libros[indiceLibro].precio;
    libros[indiceLibro].stock -= cantidad;

    cout << "Total de la venta: S/. " << ventas[cv].total << endl;
    cv++;
    cout << "Venta registrada correctamente." << endl;
}

void realizarPedido() {
    if (cp >= MAX) {
        cout << "[!] No se pueden registrar mas pedidos. Limite alcanzado." << endl;
        return;
    }

    Pedido& p = pedidos[cp];
    p.idPedido = cp + 1;
    cout << endl << "--- REALIZAR PEDIDO ---" << endl;

    // Cliente existente
    do {
        p.dniCliente = leerDNI("DNI del cliente: ");
        if (!existeCliente(p.dniCliente))
            cout << "  [!] No existe un cliente con ese DNI." << endl;
    } while (!existeCliente(p.dniCliente));

    p.cantidadItems = 0;
    p.total = 0;

    char continuar;
    do {
        if (p.cantidadItems >= MAX) {
            cout << "[!] Limite de items en el carrito alcanzado." << endl;
            break;
        }

        // Libro existente
        int idLibro;
        int indice;
        do {
            idLibro = leerEntero("ID del libro: ", 1);
            indice = buscarLibro(idLibro);
            if (indice == -1)
                cout << "  [!] No existe un libro con ese ID." << endl;
        } while (indice == -1);

        // Cantidad con validacion de stock
        int cantidad;
        do {
            cantidad = leerEntero("Cantidad: ", 1);
            if (cantidad > libros[indice].stock)
                cout << "  [!] Stock insuficiente. Stock disponible: " << libros[indice].stock << endl;
        } while (cantidad > libros[indice].stock);

        p.carrito[p.cantidadItems].idLibro  = idLibro;
        p.carrito[p.cantidadItems].cantidad = cantidad;
        p.total += libros[indice].precio * cantidad;
        p.cantidadItems++;

        cout << "Agregar otro libro? (s/n): ";
        cin >> continuar;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Validar respuesta s/n
        while (continuar != 's' && continuar != 'n') {
            cout << "  [!] Ingrese 's' para si o 'n' para no: ";
            cin >> continuar;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (continuar == 's');

    // Resumen del pedido
    cout << endl << "--- Resumen del pedido ---" << endl;
    for (int i = 0; i < cc; i++) {
        if (clientes[i].dni == p.dniCliente) {
            cout << "Cliente: " << clientes[i].nombre << endl;
            break;
        }
    }

    cout << "Libros pedidos:" << endl;
    for (int i = 0; i < p.cantidadItems; i++) {
        int indice = buscarLibro(p.carrito[i].idLibro);
        cout << "- " << libros[indice].titulo << " (Cantidad: " << p.carrito[i].cantidad << ")" << endl;
    }
    cout << "Total a pagar: S/. " << p.total << endl;

    // Confirmacion
    char confirmar;
    cout << "Desea confirmar el pedido? (s/n): ";
    cin >> confirmar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (confirmar != 's' && confirmar != 'n') {
        cout << "  [!] Ingrese 's' para si o 'n' para no: ";
        cin >> confirmar;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (confirmar != 's') {
        cout << "Pedido cancelado por el usuario." << endl;
        return;
    }

    // Metodo de entrega
    string metodo;
    do {
        metodo = leerTexto("Metodo de entrega (Tienda/Domicilio): ");
        if (metodo != "Tienda" && metodo != "Domicilio")
            cout << "  [!] Ingrese exactamente 'Tienda' o 'Domicilio'." << endl;
    } while (metodo != "Tienda" && metodo != "Domicilio");
    p.metodoEntrega = metodo;

    if (p.metodoEntrega == "Domicilio") {
        p.estado = "Pendiente - A Domicilio";
        cout << "Su pedido sera entregado en un plazo de 3 dias habiles." << endl;
    } else {
        p.estado = "Pendiente - En Tienda";
        cout << "Elegir sede:" << endl;
        cout << "1. Surco" << endl;
        cout << "2. La Molina" << endl;
        cout << "3. Miraflores" << endl;
        leerEntero("Sede: ", 1, 3);
        cout << "Horario de atencion: 8:00 a.m. a 6:00 p.m. de lunes a sabado." << endl;
        cout << "Recuerde que si no recoge su pedido en un maximo de 3 dias, este sera cancelado." << endl;
    }

    // Descontar stock al confirmar
    for (int i = 0; i < p.cantidadItems; i++) {
        int indice = buscarLibro(p.carrito[i].idLibro);
        libros[indice].stock -= p.carrito[i].cantidad;
    }

    cout << "Estado del pedido: " << p.estado << endl;
    cp++;
}

// ─────────────────────────────────────────────
// REPORTES
// ─────────────────────────────────────────────

void reporteStock() {
    cout << endl << "--- REPORTE DE STOCK ---" << endl;
    if (cl == 0) { cout << "No hay libros registrados." << endl; return; }
    for (int i = 0; i < cl; i++)
        cout << "ID: " << libros[i].id << " - " << libros[i].titulo
             << " | Stock: " << libros[i].stock << endl;
}

void reporteClientesFrecuentes() {
    cout << endl << "--- CLIENTES FRECUENTES ---" << endl;
    bool hayFrecuentes = false;
    for (int i = 0; i < cc; i++) {
        if (clientes[i].frecuente) {
            cout << "Cliente: " << clientes[i].nombre << " (DNI: " << clientes[i].dni << ")" << endl;
            hayFrecuentes = true;
        }
    }
    if (!hayFrecuentes) cout << "No hay clientes frecuentes registrados." << endl;
}

void reporteVentas() {
    cout << endl << "--- REPORTE DE VENTAS ---" << endl;
    if (cv == 0) { cout << "No hay ventas registradas." << endl; return; }
    for (int i = 0; i < cv; i++) {
        int indice = buscarLibro(ventas[i].idLibro);
        string tituloLibro = (indice != -1) ? libros[indice].titulo : "Libro no encontrado";
        cout << "Venta ID: " << ventas[i].idVenta
             << " | Cliente: " << ventas[i].dniCliente
             << " | Libro: " << tituloLibro
             << " | Cantidad: " << ventas[i].cantidad
             << " | Total: S/. " << ventas[i].total << endl;
    }
}

void reportePedidos() {
    cout << endl << "--- REPORTE DE PEDIDOS ---" << endl;
    if (cp == 0) { cout << "No hay pedidos registrados." << endl; return; }
    for (int i = 0; i < cp; i++)
        cout << "Pedido ID: " << pedidos[i].idPedido
             << " | Cliente: " << pedidos[i].dniCliente
             << " | Total: S/. " << pedidos[i].total
             << " | Estado: " << pedidos[i].estado << endl;
}

// ─────────────────────────────────────────────
// MENUS
// ─────────────────────────────────────────────

void menuAdministrador() {
    int op;
    do {
        cout << endl << "--- MENU ADMINISTRADOR ---" << endl;
        cout << "1. Registrar libro" << endl;
        cout << "2. Registrar venta" << endl;
        cout << "3. Reporte de stock" << endl;
        cout << "4. Reporte de clientes frecuentes" << endl;
        cout << "5. Reporte de ventas" << endl;
        cout << "6. Reporte de pedidos" << endl;
        cout << "0. Volver" << endl;
        op = leerEntero("Opcion: ", 0, 6);
        switch (op) {
            case 1: registrarLibro(); break;
            case 2: registrarVenta(); break;
            case 3: reporteStock(); break;
            case 4: reporteClientesFrecuentes(); break;
            case 5: reporteVentas(); break;
            case 6: reportePedidos(); break;
        }
    } while (op != 0);
}

void menuUsuario() {
    int op;
    do {
        cout << endl << "--- MENU USUARIO ---" << endl;
        cout << "1. Registrar cliente" << endl;
        cout << "2. Realizar pedido" << endl;
        cout << "3. Ver stock de libros" << endl;
        cout << "0. Volver" << endl;
        op = leerEntero("Opcion: ", 0, 3);
        switch (op) {
            case 1: registrarCliente(); break;
            case 2: realizarPedido(); break;
            case 3: reporteStock(); break;
        }
    } while (op != 0);
}

int main() {
    system("cls");
    cout << R"(
 L       III  M   M   AAAAA    BBBBB   OOO   OOO     K   K
 L        I   MM MM  A     A   B    B  O   O  O   O  K  K
 L        I   M M M  AAAAAAA   BBBBB   O   O  O   O  KKK
 L        I   M   M  A     A   B    B  O   O  O   O  K  K
 LLLLL   III  M   M  A     A   BBBBB   OOO   OOO     K   K
)" << endl;

    precargar();

    int opcion;
    do {
        cout << endl << "        M E N U        " << endl;
        cout << "  SISTEMA DE LIBRERIA  " << endl;
        cout << "1. Administrador" << endl;
        cout << "2. Usuario" << endl;
        cout << "0. Salir" << endl;
        opcion = leerEntero("Seleccione una opcion: ", 0, 2);
        switch (opcion) {
            case 1: menuAdministrador(); break;
            case 2: menuUsuario(); break;
            case 0: cout << "Gracias por usar el sistema." << endl; break;
        }
    } while (opcion != 0);

    return 0;
}
