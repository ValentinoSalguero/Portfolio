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

const isDarkMode = localStorage.getItem('darkMode') === 'true';

// Crear y mostrar los productos en la página
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

    if (isDarkMode) {
        productDiv.classList.add('dark-mode');
        let priceElement = productDiv.querySelector('.price');
        if (priceElement) {
            priceElement.classList.add('dark-mode');
        }
    }
});
