package com.techlab.main;

import java.util.ArrayList;
import java.util.Scanner;

import com.techlab.pedidos.Pedido;
import com.techlab.productos.Producto;

public class Main {
    public static void main(String[] args) {
        ArrayList<Producto> productos = new ArrayList<>();
        ArrayList<Pedido> pedidos = new ArrayList<>(); // Cambiar a ArrayList<Pedido>
        Scanner scanner = new Scanner(System.in);
        int opcion;
    
        do {
            System.out.println("\n--- Menú Principal ---");
            System.out.println("1. Agregar producto");
            System.out.println("2. Listar productos");
            System.out.println("3. Buscar/Actualizar producto");
            System.out.println("4. Eliminar producto");
            System.out.println("5. Crear un pedido");
            System.out.println("6. Listar pedidos");
            System.out.println("7. Salir");
            System.out.print("Selecciona una opción: ");
            opcion = scanner.nextInt();
            scanner.nextLine();

            switch (opcion) {
                case 1:
                    agregarProducto(scanner, productos);
                    break;
                case 2:
                    listarProductos(productos);
                    break;
                case 3:
                    buscarYActualizarProducto(scanner, productos);
                    break;
                case 4:
                    eliminarProducto(scanner, productos);
                    break;
                case 5:
                    crearPedido(scanner, productos, pedidos);
                    break;
                case 6:
                    listarPedidos(pedidos);
                    break;
                case 7:
                    System.out.println("¡Hasta luego!");
                    break;
                default:
                    System.out.println("Opción no válida, intenta nuevamente.");
            }
        
        } while (opcion != 7);
    }

    public static void agregarProducto(Scanner scanner, ArrayList<Producto> productos) {
        System.out.print("Nombre del producto: ");
        String nombre = scanner.nextLine();
        System.out.print("Precio del producto: ");
        double precio = scanner.nextDouble();
        System.out.print("Cantidad en stock: ");
        int stock = scanner.nextInt();
        scanner.nextLine();

        Producto nuevoProducto = new Producto(nombre, precio, stock);
        productos.add(nuevoProducto);
        System.out.println("Producto agregado con éxito.");
    }

    public static void listarProductos(ArrayList<Producto> productos) {
        if (productos.isEmpty()) {
            System.out.println("No hay productos disponibles."); // Revertido
            return;
        }

        System.out.println("\n--- Lista de Productos ---");
        System.out.printf("%-5s %-20s %-10s %-10s\n", "ID", "Nombre", "Precio", "Stock");
        System.out.println("--------------------------------------------------");
        for (Producto producto : productos) {
            System.out.println(producto); // El método toString ya tiene el formato tabular
        }
    }

    public static void buscarYActualizarProducto(Scanner scanner, ArrayList<Producto> productos) {
        System.out.print("Ingrese el ID o nombre del producto: ");
        String input = scanner.nextLine();

        Producto productoEncontrado = null;

        try {
            int id = Integer.parseInt(input);
            for (Producto producto : productos) { // Buscar por ID
                if (producto.getId() == id) {
                    productoEncontrado = producto;
                    break;
                }
            }
        } catch (NumberFormatException e) {
            for (Producto producto : productos) { // Buscar por nombre
                if (producto.getNombre().equalsIgnoreCase(input)) {
                    productoEncontrado = producto;
                    break;
                }
            }
        }

        if (productoEncontrado != null) {
            System.out.println("Producto encontrado: " + productoEncontrado);
            System.out.print("¿Deseas actualizar el precio? (s/n): ");
            String actualizarPrecio = scanner.nextLine();
            if (actualizarPrecio.equalsIgnoreCase("s")) {
                System.out.print("Nuevo precio: ");
                double nuevoPrecio = scanner.nextDouble();
                scanner.nextLine();
                productoEncontrado.setPrecio(nuevoPrecio);
            }
            System.out.print("¿Deseas actualizar el stock? (s/n): ");
            String actualizarStock = scanner.nextLine();
            if (actualizarStock.equalsIgnoreCase("s")) {
                System.out.print("Nuevo stock: ");
                int nuevoStock = scanner.nextInt();
                scanner.nextLine();
                if (nuevoStock >= 0) {
                    productoEncontrado.setStock(nuevoStock);
                } else {
                    System.out.println("El stock no puede ser negativo.");
                }
            }
            System.out.println("Producto actualizado: " + productoEncontrado);
        } else {
            System.out.println("Producto no encontrado.");
        }
    }

    public static void eliminarProducto(Scanner scanner, ArrayList<Producto> productos) {
        System.out.print("Ingrese el ID del producto a eliminar: "); // Revertido
        int id = scanner.nextInt();
        scanner.nextLine();

        Producto productoAEliminar = null;
        for (Producto producto : productos) { // Buscar por ID
            if (producto.getId() == id) {
                productoAEliminar = producto;
                break;
            }
        }

        if (productoAEliminar != null) {
            productos.remove(productoAEliminar);
            System.out.println("Producto eliminado con éxito."); // Revertido
        } else {
            System.out.println("Producto no encontrado."); // Revertido
        }
    }

    public static void crearPedido(Scanner scanner, ArrayList<Producto> productos, ArrayList<Pedido> pedidos) {
        Pedido pedido = new Pedido();
        while (true) {
            System.out.print("Ingresa el ID del producto a agregar al pedido (o -1 para terminar): ");
            int id = scanner.nextInt();
            scanner.nextLine();

            if (id == -1) {
                break;
            }

            Producto productoSeleccionado = null;
            for (Producto producto : productos) { // Buscar por ID
                if (producto.getId() == id) {
                    productoSeleccionado = producto;
                    break;
                }
            }

            if (productoSeleccionado != null) {
                System.out.print("Cantidad: ");
                int cantidad = scanner.nextInt();
                scanner.nextLine();

                try {
                    pedido.agregarProducto(productoSeleccionado, cantidad);
                } catch (Pedido.StockInsuficienteException e) {
                    System.out.println(e.getMessage());
                }
            } else {
                System.out.println("Producto no encontrado.");
            }
        }
        pedidos.add(pedido);
        System.out.println("Pedido creado con éxito.");
    }

    public static void listarPedidos(ArrayList<Pedido> pedidos) {
        if (pedidos.isEmpty()) {
            System.out.println("No hay pedidos realizados."); // Revertido
            return;
        }

        System.out.println("\n--- Lista de Pedidos ---");
        for (int i = 0; i < pedidos.size(); i++) {
            System.out.println("Pedido #" + (i + 1));
            pedidos.get(i).mostrarPedido();
            System.out.println();
        }
    }

}

/*
6. Menú Principal Interactivo 
○ Presentar un menú con opciones como: 
■ Agregar producto 
■ Listar productos 
■ Buscar/Actualizar producto 
■ Eliminar producto 
■ Crear un pedido 
■ (Opcional) Listar pedidos 
■ Salir 
○ El programa se repite hasta que el usuario elija “Salir”.
 */