// Función para actualizar la cantidad en el carrito
function updateQuantity(button, change) {
    const quantitySpan = button.closest('.cart-item').querySelector('.quantity');
    let currentQuantity = parseInt(quantitySpan.innerText);

    // Asegurarse que la cantidad no sea menor a 0
    currentQuantity = Math.max(0, currentQuantity + change);

    quantitySpan.innerText = currentQuantity;
}

// Función para agregar productos al carrito
function addToCart(index) {
    const quantity = document.querySelectorAll('.card-product')[index].querySelector('.quantity').innerText;

    if (parseInt(quantity) > 0) {
        const product = products[index];
        product.quantity = parseInt(quantity); // Asegurarse de que la cantidad esté correctamente establecida

        // Recuperar el carrito actual desde localStorage
        const cart = JSON.parse(localStorage.getItem('cart')) || [];

        // Verificar si el producto ya está en el carrito
        const existingProduct = cart.find(item => item.title === product.title && item.brand === product.brand);

        if (existingProduct) {
            // Si el producto ya está, incrementar la cantidad
            existingProduct.quantity += product.quantity;
        } else {
            // Si no está, agregarlo con la cantidad seleccionada
            cart.push({ ...product });
        }

        // Guardar el carrito actualizado en localStorage
        localStorage.setItem('cart', JSON.stringify(cart));

        // Para asegurarnos de que el carrito se muestra actualizado sin recargar la página
        updateCartCount();

        // Redirigir al carrito después de agregar el producto
        window.location.href = "carrito.html";  // Asegúrate de que esta URL sea la de la página del carrito
    } else {
        alert("Por favor, selecciona una cantidad mayor a 0");
    }
}

// Función para mostrar los productos en el carrito y permitir la actualización de cantidad y eliminación de productos
window.onload = function() {
    // Recuperar el carrito desde localStorage
    const cart = JSON.parse(localStorage.getItem('cart')) || [];
    const cartContainer = document.getElementById('cart-container'); // Asegúrate de tener un contenedor con este ID en la página del carrito

    // Si el carrito tiene productos
    if (cart.length > 0) {
        cartContainer.innerHTML = '';  // Limpiar el carrito antes de mostrar los productos
        cart.forEach((product, index) => {
            // Crear un elemento para cada producto
            const productDiv = document.createElement('div');
            productDiv.className = 'cart-item';
            productDiv.innerHTML = `
                <img src="${product.image}" alt="${product.title}">
                <h3>${product.title}</h3>
                <p>Precio: $${product.price}</p>
                <p>Cantidad: <span class="quantity">${product.quantity}</span></p>
                <button class="update-btn">Actualizar cantidad</button>
                <button class="remove-btn">Eliminar producto</button>
            `;
            cartContainer.appendChild(productDiv);

            // Agregar funcionalidad para actualizar la cantidad
            productDiv.querySelector('.update-btn').addEventListener('click', function() {
                const newQuantity = prompt('Ingresa la nueva cantidad:', product.quantity);
                if (newQuantity && !isNaN(newQuantity)) {
                    product.quantity = parseInt(newQuantity);
                    localStorage.setItem('cart', JSON.stringify(cart));
                    // Recargar la página para ver el cambio
                    window.location.reload();
                }
            });

            // Agregar funcionalidad para eliminar el producto
            productDiv.querySelector('.remove-btn').addEventListener('click', function() {
                // Eliminar el producto del carrito
                cart.splice(index, 1);
                // Guardar el carrito actualizado en localStorage
                localStorage.setItem('cart', JSON.stringify(cart));

                // Eliminar el producto del DOM
                productDiv.remove();

                // Actualizar el contador del carrito
                updateCartCount();

                // Mostrar mensaje si el carrito está vacío
                if (cart.length === 0) {
                    cartContainer.innerHTML = "<p>No hay productos en el carrito.</p>";
                }
            });
        });
    } else {
        cartContainer.innerHTML = "<p>No hay productos en el carrito.</p>";
    }

    // Actualizar el contador del carrito
    updateCartCount();
};

// Función para actualizar el contador del carrito
function updateCartCount() {
    const cart = JSON.parse(localStorage.getItem('cart')) || [];
    const cartCount = cart.reduce((acc, item) => acc + item.quantity, 0);
    document.getElementById('cart-count').innerText = cartCount; // Asegúrate de tener un elemento con el id "cart-count" en tu HTML
}

// Llamada inicial para mostrar los productos en el carrito y el contador
document.addEventListener("DOMContentLoaded", function() {
    updateCartCount();  // Actualizar el contador del carrito
});

// Función para finalizar la compra y mostrar el modal
function finalizarCompra() {
    // Muestra el modal
    document.getElementById('modal-exito').style.display = 'block';
}

// Función para cerrar el modal
function cerrarModal() {
    // Oculta el modal
    document.getElementById('modal-exito').style.display = 'none';
}

// También se puede cerrar el modal si el usuario hace clic fuera de la ventana del modal
window.onclick = function(event) {
    if (event.target == document.getElementById('modal-exito')) {
        cerrarModal();
    }
}
