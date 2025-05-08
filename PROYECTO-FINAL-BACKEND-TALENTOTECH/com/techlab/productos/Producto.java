package com.techlab.productos;

public class Producto {
    private static int contador = 1;

    private int id;
    private String nombre;
    private double precio;
    private int stock;

    public Producto(String nombre, double precio, int stock) {
        this.id = contador++;
        this.nombre = nombre;
        this.precio = precio;
        this.setStock(stock); // Solo una llamada a setStock
    }

    public int getId() {
        return id;
    }

    public String getNombre() {
        return nombre;
    }

    public double getPrecio() {
        return precio;
    }

    public int getStock() {
        return stock;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setNombre(String nombre) {
        if (nombre != null && !nombre.isEmpty()) {
            this.nombre = nombre;
        } else {
            System.out.println("El nombre no puede ser nulo o vacío."); // Revertido
        }
    }

    public void setPrecio(double precio) {
        if (precio >= 0) {
            this.precio = precio;
        } else {
            System.out.println("El precio no puede ser negativo."); // Revertido
        }
    }

    public void setStock(int stock) {
        if (stock >= 0) {
            this.stock = stock;
        } else {
            System.out.println("El stock no puede ser negativo."); // Revertido
        }
    }

    @Override
    public String toString() {
        return String.format("%-5d %-20s %-10.2f %-10d", id, nombre, precio, stock); // Formato tabular
    }

}


/*
1. Ingreso de Productos 
○ Implementar una funcionalidad para agregar productos con: 
■ Nombre (String). 
■ Precio (double). 
■ Cantidad en Stock (int). 
○ Almacenarlos en una colección dinámica (ej. ArrayList<Producto>). 
2. Visualización de Productos 
○ Listar todos los productos, mostrando: 
■ ID (autogenerado o posición en la lista). 
■ Nombre, Precio, Stock. 
○ El sistema debe mostrar un menú con la opción de “Listar productos”. 
3. Búsqueda y Actualización 
○ Permitir buscar un producto por nombre o ID. 
○ Si se encuentra, mostrar su información (mínimo: nombre, precio, stock). 
○ (Opcional) Poder actualizar algunos datos (precio o stock), validando que los 
valores sean coherentes (ej., stock no negativo). 
4. Eliminación de Productos 
○ Habilitar la eliminación de un producto por ID o por posición. 
○ (Opcional) Pedir confirmación antes de borrarlo. 
 */