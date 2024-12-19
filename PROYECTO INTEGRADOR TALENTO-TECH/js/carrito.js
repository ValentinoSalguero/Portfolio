let cart = JSON.parse(localStorage.getItem('cart')) || [];

// Agregar un producto al carrito
function addToCart(index) {
    const product = products[index];
    const quantity = 1;
    let cartItem = cart.find(item => item.title === product.title);

    if (cartItem) {
        cartItem.quantity += quantity;
    } else {
        cart.push({...product, quantity});
    }

    localStorage.setItem('cart', JSON.stringify(cart));
    updateCartDisplay();

    document.getElementById("cart-sidebar").classList.add("active");
}

// Actualizar la visualización del carrito
function updateCartDisplay() {
    const cartContainer = document.getElementById('cart-container');
    cartContainer.innerHTML = '';

    let total = 0;
    cart.forEach((item, index) => {
        total += item.price * item.quantity;
        const itemDiv = document.createElement('div');
        itemDiv.classList.add('cart-item');
        itemDiv.innerHTML = `
            <img src="${item.image}" alt="${item.title}" class="img">
            <div class="item-details">
                <h4>${item.title}</h4>
                <p>$${item.price}</p>
            </div>
            <div class="quantity-controls">
                <button class="btn btn-danger btn-sm" onclick="updateCartQuantity(${index}, -1)">-</button>
                <span class="quantity">${item.quantity}</span>
                <button class="btn btn-info btn-sm" onclick="updateCartQuantity(${index}, 1)">+</button>
            </div>
            <div class="cart-summary">
            <p>$${item.price * item.quantity}</p>
            </div>
        `;
        cartContainer.appendChild(itemDiv);
    });

    const totalDiv = document.createElement('div');
    totalDiv.classList.add('cart-total');
    totalDiv.innerHTML = `<h3>Total: $${total}</h3>`;
    cartContainer.appendChild(totalDiv);
}

// Actualizar la cantidad de un producto en el carrito
function updateCartQuantity(index, change) {
    const cartItem = cart[index];

    if (cartItem) {
        cartItem.quantity += change;

        if (cartItem.quantity < 0) cartItem.quantity = 0;

        if (cartItem.quantity === 0) {
            cart.splice(index, 1);
        }

        localStorage.setItem('cart', JSON.stringify(cart));

        updateCartDisplay();
    }
}

// Vaciar el carrito
function clearCart() {
    cart = [];
    localStorage.removeItem('cart');
    updateCartDisplay();
    document.getElementById("cart-sidebar").classList.remove("active");
}

// Finalizar la compra y vaciar el carrito
function finalizePurchase() {
    if (cart.length === 0) {
        alert("Tu carrito está vacío. No se puede finalizar la compra.");
        return;
    }

    clearCart();
    document.getElementById('success-modal').style.display = 'flex'; // Mostrar el modal
}

document.getElementById("checkout-button").addEventListener("click", finalizePurchase);

document.getElementById('close-success-modal').addEventListener('click', function() {
    // Cerrar el modal
    document.getElementById('success-modal').style.display = 'none';
});

// Función para cargar el carrito desde localStorage
function loadCart() {
    // Obtiene el carrito del localStorage
    let cart = JSON.parse(localStorage.getItem('cart')) || [];
    
    // Verifica si el contenedor del carrito está presente en la página
    const cartContainer = document.getElementById('cart-container');
    if (!cartContainer) return;

    // Limpiar el carrito actual
    cartContainer.innerHTML = '';

    // Si el carrito está vacío, mostrar un mensaje
    if (cart.length === 0) {
        cartContainer.innerHTML = '<p>Tu carrito está vacío.</p>';
        return;
    }

    let total = 0;
    // Mostrar cada producto en el carrito
    cart.forEach((item, index) => {
        total += item.price * item.quantity;

        const itemDiv = document.createElement('div');
        itemDiv.classList.add('cart-item');
        itemDiv.innerHTML = `
            <img src="${item.image}" alt="${item.title}" class="img">
            <div class="item-details">
                <h4>${item.title}</h4>
                <p>$${item.price}</p>
            </div>
            <div class="quantity-controls">
                <button class="btn btn-danger btn-sm" onclick="updateCartQuantity(${index}, -1)">-</button>
                <span class="quantity">${item.quantity}</span>
                <button class="btn btn-info btn-sm" onclick="updateCartQuantity(${index}, 1)">+</button>
            </div>
            <div class="cart-summary">
            <p>$${item.price * item.quantity}</p>
            </div>
        `;
        cartContainer.appendChild(itemDiv);
    });

    // Mostrar el total del carrito
    const totalDiv = document.createElement('div');
    totalDiv.classList.add('cart-total');
    totalDiv.innerHTML = `<h3>Total: $${total}</h3>`;
    cartContainer.appendChild(totalDiv);
}

// Llamar a loadCart cuando la página se cargue
document.addEventListener('DOMContentLoaded', loadCart);
