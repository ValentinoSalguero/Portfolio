// Crear productos dinámicamente
var products = [
    { title: "Alfajor Deuble Negro", price: 1000, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 00.png" },
    { title: "Alfajor Simple Night", price: 700, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 01.png" },
    { title: "Alfajor Genio", price: 500, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 02.png" },
    { title: "Alfajor Guachoo Blanco", price: 600, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 03.png" },
    { title: "Alfajor Happy Food", price: 600, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 04.png" },
    { title: "Alfajor Guolis", price: 900, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 05.png" },
    { title: "Alfajor Cachafaz", price: 1200, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 06.png" },
    { title: "Alfajor Lule Muu", price: 600, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 07.png" },
    { title: "Alfajor Oreo Trilogía", price: 1000, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 08.png" },
    { title: "Alfajor Full Maní", price: 800, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 09.png" },
    { title: "Alfajor Café Martínez Blanco", price: 700, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 10.png" },
    { title: "Alfajor Smams", price: 800, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 11.png" },
    { title: "Alfajor Café Martínez Negro", price: 700, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 12.png" },
    { title: "Alfajor Capitán Del Espacio", price: 900, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 13.png" },
    { title: "Alfajor Rasta", price: 800, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 14.png" },
    { title: "Alfajor Guachoo Negro", price: 800, image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 15.png" },
];

// Arreglo que guarda los productos agregados al carrito
var cart = [];

// Referencia al contenedor de productos
var cardContainer = document.getElementById('card-container');

// Verificar si el modo oscuro está activado
const isDarkMode = localStorage.getItem('darkMode') === 'true';

// Crear cada producto
products.forEach((product, index) => {
    var productDiv = document.createElement('div');
    productDiv.className = 'card-product flex';
    productDiv.innerHTML = `
        <div class="container-img">
            <img src="${product.image}" alt="${product.title}">
        </div>
        <div class="card-details">
            <h3 class="card-product_title">${product.title}</h3>
            <p class="price">$ ${product.price}</p>
            <button class="btn-add" onclick="addToCart(${index});">COMPRAR</button>
        </div>
    `;
    cardContainer.appendChild(productDiv);

    // Aplicar modo oscuro si está activado
    if (isDarkMode) {
        productDiv.classList.add('dark-mode');
        productDiv.querySelector('.price').classList.add('dark-mode');
        productDiv.querySelector('.quantity').classList.add('dark-mode');
        productDiv.querySelectorAll('.quantity-controls button').forEach(button => button.classList.add('dark-mode'));
    }
});

// Función para agregar productos al carrito
function addToCart(index) {
    const product = products[index];
    
    // Establecer siempre la cantidad a 1
    const quantity = 1;

    // Verifica si el producto ya está en el carrito
    let cartItem = cart.find(item => item.title === product.title);
    
    if (cartItem) {
        // Si ya está, incrementa la cantidad en 1
        cartItem.quantity += quantity;
    } else {
        // Si no está, lo agrega con la cantidad 1
        cart.push({...product, quantity});
    }

    updateCartDisplay();

    // Abre el modal del carrito
    document.getElementById("cart-sidebar").classList.add("active");
}

// Función para actualizar el carrito visualmente
function updateCartDisplay() {
    const cartContainer = document.getElementById('cart-container');
    cartContainer.innerHTML = '';  // Limpiar carrito

    let total = 0;
    cart.forEach((item, index) => {
        total += item.price * item.quantity;
        const itemDiv = document.createElement('div');
        itemDiv.classList.add('cart-item');
        itemDiv.innerHTML = `
            <h4>${item.title}</h4>
            <p>$${item.price}</p>
            <div class="quantity-controls">
                <button class="btn btn-danger btn-sm" onclick="updateCartQuantity(${index}, -1)">-</button>
                <span class="quantity">${item.quantity}</span>
                <button class="btn btn-info btn-sm" onclick="updateCartQuantity(${index}, 1)">+</button>
            </div>
            <p>$${item.price * item.quantity}</p>
        `;
        cartContainer.appendChild(itemDiv);
    });

    const totalDiv = document.createElement('div');
    totalDiv.classList.add('cart-total');
    totalDiv.innerHTML = `<h3>Total: $${total}</h3>`;
    cartContainer.appendChild(totalDiv);
}

// Función para actualizar la cantidad de productos dentro del carrito
function updateCartQuantity(index, change) {
    const cartItem = cart[index];

    if (cartItem) {
        // Actualiza la cantidad del producto
        cartItem.quantity += change;

        // Asegúrate de que la cantidad no sea negativa
        if (cartItem.quantity < 0) cartItem.quantity = 0;

        // Si la cantidad llega a 0, elimina el producto
        if (cartItem.quantity === 0) {
            cart.splice(index, 1);
        }

        // Actualiza el carrito visualmente
        updateCartDisplay();
    }
}
