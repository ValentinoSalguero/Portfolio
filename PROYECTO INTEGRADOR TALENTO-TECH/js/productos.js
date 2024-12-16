// Actualiza la cantidad del producto
function updateQuantity(button, change) {
    const quantitySpan = button.parentElement.querySelector('.quantity');
    let currentQuantity = parseInt(quantitySpan.textContent);
    currentQuantity += change;

    if (currentQuantity < 0) currentQuantity = 0;
    quantitySpan.textContent = currentQuantity;
}

// Añadir al carrito
function addToCart(index) { 
    const quantity = document.querySelectorAll('.card-product')[index].querySelector('.quantity').innerText;

    if (parseInt(quantity) > 0) {
        products[index].quantity = parseInt(quantity);
        let cart = JSON.parse(localStorage.getItem('cart')) || [];

        let productInCart = cart.find(product => product.title === products[index].title);
        if (productInCart) {
            productInCart.quantity += parseInt(quantity);
        } else {
            cart.push({
                title: products[index].title,
                price: products[index].price,
                image: products[index].image,
                quantity: parseInt(quantity)
            });
        }

        localStorage.setItem('cart', JSON.stringify(cart));
        window.location.href = "carrito.html"; // Redirige al carrito
    } else {
        alert("Por favor, selecciona una cantidad mayor a 0");
    }
}

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

var cardContainer = document.getElementById('card-container');

for (var i = 0; i < products.length; i++) {
    var productDiv = document.createElement('div');
    productDiv.className = 'card-product flex';
    productDiv.innerHTML = `
        <div class="container-img">
            <a href="#"><img src="${products[i].image}" alt="${products[i].title}"></a>
        </div>
        <div class="card-details">
            <h3 class="card-product_title">${products[i].title}</h3>
            <p class="price">$ ${products[i].price}</p>
            <div class="quantity-controls">
                <button class="btn btn-danger btn-sm" onclick="updateQuantity(this, -1)">-</button>
                <span class="quantity">0</span>
                <button class="btn btn-info btn-sm" onclick="updateQuantity(this, 1)">+</button>
            </div>
            <button class="btn-add" onclick="addToCart(${i});">COMPRAR</button>
        </div>
    `;
    cardContainer.appendChild(productDiv);

    // Verificar si el modo oscuro está activado y aplicarlo
    const isDarkMode = localStorage.getItem('darkMode') === 'true';
    if (isDarkMode) {
        productDiv.classList.add('dark-mode');
        productDiv.querySelector('.price').classList.add('dark-mode');
        productDiv.querySelector('.quantity').classList.add('dark-mode');
        productDiv.querySelectorAll('.quantity-controls button').forEach(button => button.classList.add('dark-mode'));
    }
}
