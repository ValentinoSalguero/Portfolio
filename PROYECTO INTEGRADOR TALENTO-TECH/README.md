# Proyecto Integrador

## Descripción del Proyecto

Este proyecto consiste en el desarrollo de un **sitio web de e-commerce** interactivo y dinámico, diseñado para ofrecer una experiencia de usuario agradable. La página incluye varias secciones, como **Inicio**, **Productos**, **Reseñas**, **Contacto** y un **Carrito de Compras**. El objetivo es demostrar el uso de tecnologías como **HTML**, **CSS**, **JavaScript**, y el consumo de datos desde una **API REST**. Además, se implementaron funcionalidades interactivas como la manipulación del DOM y el uso de **localStorage** para el carrito de compras.

## Estructura del Proyecto

El proyecto se organiza en las siguientes áreas clave:

- **HTML**: Se utilizó una estructura semántica, utilizando etiquetas como `<header>`, `<nav>`, `<main>`, `<section>`, `<footer>`.
- **CSS**: Se aplicaron estilos básicos y avanzados, incluyendo diseño responsivo con **Flexbox** y **Grid**. Se utilizaron **Google Fonts** para la tipografía.
- **JavaScript**: Se incorporó la manipulación del DOM para gestionar dinámicamente los productos y el carrito de compras.
- **API REST**: Se consumieron datos de una API pública utilizando **fetch** para obtener y mostrar productos en el sitio.
- **Carrito de Compras**: Implementación de un carrito de compras que permite a los usuarios añadir productos, modificar cantidades y eliminar elementos, utilizando **localStorage** para persistir la información después de recargar la página.

## Requisitos Cumplidos

### Estructura Básica HTML
- Se estructuró la página utilizando etiquetas semánticas (`<header>`, `<nav>`, `<main>`, `<section>`, `<footer>`).
- Se incluyó un archivo **README.md** explicando el propósito y detalles del proyecto.

### Contenido Multimedia y Navegación
- Se integraron imágenes y otros recursos multimedia en la página.
- Implementación de una lista desordenada con enlaces que simula la navegación interna (Inicio, Productos, Contacto).

### Estilos y Diseño
- Estilos aplicados a las secciones de la página, incluyendo el uso de **Flexbox** para la sección de productos y **Grid** para reseñas.
- Uso de **Media Queries** para asegurar que el diseño sea responsivo y se ajuste a diferentes tamaños de pantalla.
- Se utilizó el **Modelo de Caja** para aplicar márgenes, rellenos y bordes a los elementos.

### Funcionalidad JavaScript
- Creación de una función que genera dinámicamente una lista de productos disponibles.
- Implementación de una función para aplicar el modo oscuro basado en la preferencia guardada en el `localStorage`.
- Cambio dinámico entre modo claro y oscuro, afectando elementos como `header`, `footer`, botones, productos, y otros componentes de la página.
- Almacenamiento de la preferencia de modo oscuro en `localStorage` para mantener la configuración entre sesiones. 

### Asincronía y Consumo de API REST
- Se utilizó **fetch** para obtener datos de una API pública y mostrarlos en la sección de productos.
- Los productos obtenidos se organizan en **cards** usando **Flexbox** para mantener la coherencia en el diseño.

### Carrito de Compras
- El carrito permite añadir, modificar y eliminar productos, manteniendo la información persistente en **localStorage**.
- Se asegura que la información del carrito se conserve incluso después de recargar la página.

### Implementación y Despliegue
- El proyecto se encuentra desplegado en **Netlify** para su visualización pública.
- El código fuente está versionado en **GitHub**, con un historial de commits que documenta el progreso y los cambios.

### Enlaces
- [Enlace a Netlify](https://dulce-alfajor2.netlify.app/)
