// Obtener productos desde la API
fetch('https://dummyjson.com/products?limit=48')
.then(response => response.json())
.then(data => {
    var cardContainer = document.getElementById('card-container');
    const isDarkMode = localStorage.getItem('darkMode') === 'true';

    // Crear y mostrar los productos en la página
    data.products.forEach((product, index) => {

        const price = product.price.toFixed(2);

        var productDiv = document.createElement('div');
        productDiv.className = 'card-product flex';
        productDiv.innerHTML = `
            <div class="container-img">
                <img src="${product.images[0]}" alt="${product.title}">
            </div>
            <div class="card-details">
                <h3 class="card-product_title">${product.title}</h3>
                <p class="price">$ ${price}</p>
                <button class="btn-add" onclick="addToCart(${index}, '${product.title}', ${price}, '${product.images[0]}');">COMPRAR</button>
            </div>
        `;
        cardContainer.appendChild(productDiv);

        // Aplicar el estilo para el modo oscuro
        if (isDarkMode) {
            productDiv.classList.add('dark-mode');
            let priceElement = productDiv.querySelector('.price');
            if (priceElement) {
                priceElement.classList.add('dark-mode');
            }
        }
    });
})
.catch(error => console.error('Error al cargar los productos:', error));

// Función para agregar un producto al carrito
function addToCart(index, title, price, image) {
    console.log("Producto añadido:", { index, title, price, image });

    let cart = JSON.parse(localStorage.getItem('cart')) || [];
    let cartItem = cart.find(item => item.title === title);

    if (cartItem) {
        cartItem.quantity += 1;
    } else {
        cart.push({ title, price, image, quantity: 1 });
    }

    console.log("Carrito actualizado:", cart); // Depurar carrito actualizado
    localStorage.setItem('cart', JSON.stringify(cart));
    updateCartDisplay();  // Actualiza la vista del carrito
    document.getElementById("cart-sidebar").classList.add("active");
}

// Función para actualizar la visualización del carrito
function updateCartDisplay() {
    const cartContainer = document.getElementById('cart-container');
    cartContainer.innerHTML = ''; // Limpiar contenido

    let cart = JSON.parse(localStorage.getItem('cart')) || [];
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
                <button class="btn btn-danger btn-sm" onclick="updateCartQuantity(${index}, -1)">-</button>
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
}
