let cart = JSON.parse(localStorage.getItem('cart')) || [];

// Función para agregar un producto al carrito
function addToCart(title, price, image) {
    try {
        let cartItem = cart.find(item => item.title === title);
        if (cartItem) {
            cartItem.quantity += 1;
        } else {
            cart.push({ title, price, image, quantity: 1 });
        }
        localStorage.setItem('cart', JSON.stringify(cart));
        updateCartDisplay();
        document.getElementById("cart-sidebar").classList.add("active");
    } catch (error) {
        console.error("Error al agregar al carrito:", error);
        alert("Ocurrió un error al agregar el producto al carrito.");
    }
}

// Función para actualizar la visualización del carrito
function updateCartDisplay() {
    try {
        const cartContainer = document.getElementById('cart-container');
        cartContainer.innerHTML = ''; 
        let total = 0;

        cart.forEach((item, index) => {
            const itemTotal = (item.price * item.quantity).toFixed(2);
            total += item.price * item.quantity;

            const itemDiv = document.createElement('div');
            itemDiv.classList.add('cart-item');
            itemDiv.innerHTML = `
                <img src="${item.image}" alt="${item.title}" class="img">
                <div class="item-details">
                    <h4>${item.title}</h4>
                    <p>$${item.price.toFixed(2)}</p>
                </div>
                <div class="quantity-controls">
                    <button class="btn btn-danger btn-sm" onclick="updateCartQuantity(${index}, -1)">
                        ${item.quantity > 1 ? '-' : 'x'}
                    </button>
                    <span class="quantity">${item.quantity}</span>
                    <button class="btn btn-info btn-sm" onclick="updateCartQuantity(${index}, 1)">+</button>
                </div>
                <div class="cart-summary">
                    <p>$${itemTotal}</p>
                </div>
            `;
            cartContainer.appendChild(itemDiv);
        });

        const totalDiv = document.createElement('div');
        totalDiv.classList.add('cart-total');
        totalDiv.innerHTML = `<h3>Total: $${total.toFixed(2)}</h3>`;
        cartContainer.appendChild(totalDiv);
    } catch (error) {
        console.error("Error al actualizar el carrito:", error);
        alert("Ocurrió un error al mostrar el carrito.");
    }
}

// Actualizar la cantidad de un producto en el carrito
function updateCartQuantity(index, change) {
    try {
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
    } catch (error) {
        console.error("Error al actualizar la cantidad del producto:", error);
        alert("Ocurrió un error al actualizar la cantidad del producto.");
    }
}

// Vaciar el carrito
function clearCart() {
    try {
        cart = [];
        localStorage.removeItem('cart');
        updateCartDisplay();
    } catch (error) {
        console.error("Error al vaciar el carrito:", error);
        alert("Ocurrió un error al vaciar el carrito.");
    }
}

// Finalizar la compra
function finalizePurchase(event) {
    try {
        event.preventDefault();
        if (cart.length === 0) {
            alert("Tu carrito está vacío. No se puede finalizar la compra.");
            return;  
        }
        clearCart();
        document.getElementById("cart-sidebar").classList.remove("active");
        document.getElementById('success-modal').style.display = 'flex';
    } catch (error) {
        console.error("Error al finalizar la compra:", error);
        alert("Ocurrió un error al finalizar la compra.");
    }
}

document.getElementById("checkout-button").addEventListener("click", finalizePurchase);

document.getElementById("empty-button").addEventListener("click", function() {
    try {
        if (cart.length > 0) {
            clearCart();
        } else {
            alert("El carrito ya está vacío.");
        }
    } catch (error) {
        console.error("Error al vaciar el carrito:", error);
        alert("Ocurrió un error al intentar vaciar el carrito.");
    }
});

document.getElementById('close-success-modal').addEventListener('click', function() {
    try {
        document.getElementById('success-modal').style.display = 'none';
    } catch (error) {
        console.error("Error al cerrar el modal:", error);
    }
});

// Función para cargar el carrito desde localStorage
function loadCart() {
    try {
        const cartContainer = document.getElementById('cart-container');
        if (!cartContainer) return;

        cartContainer.innerHTML = '';

        if (cart.length === 0) {
            cartContainer.innerHTML = '<p>Tu carrito está vacío.</p>';
            return;
        }

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
                    <button class="btn btn-danger btn-sm" onclick="updateCartQuantity(${index}, -1)">
                        ${item.quantity > 1 ? '-' : 'x'}
                    </button>
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
    } catch (error) {
        console.error("Error al cargar el carrito:", error);
        alert("Ocurrió un error al cargar el carrito.");
    }
}

document.addEventListener('DOMContentLoaded', loadCart);
