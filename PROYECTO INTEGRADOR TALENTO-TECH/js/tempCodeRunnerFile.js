// Función para aplicar el modo guardado en localStorage
function applySavedMode() {
    const isDarkMode = localStorage.getItem('darkMode') === 'true';
    if (isDarkMode) {
        document.body.classList.add('dark-mode');
        document.querySelector('header').classList.add('dark-mode');
        document.querySelector('footer').classList.add('dark-mode');
        document.querySelectorAll('nav ul li a').forEach(link => link.classList.add('dark-mode'));
        document.querySelectorAll('form button').forEach(button => button.classList.add('dark-mode'));
        document.querySelectorAll('.card-product').forEach(card => card.classList.add('dark-mode'));
        document.querySelectorAll('.price').forEach(priceElement => { priceElement.classList.toggle('dark-mode', isDarkMode); });
        document.getElementById('input').checked = true;
    }
}

applySavedMode();

document.getElementById('input').addEventListener('change', function () {
    const isDarkMode = this.checked;
    document.body.classList.toggle('dark-mode', isDarkMode);
    document.querySelector('header').classList.toggle('dark-mode', isDarkMode);
    document.querySelector('footer').classList.toggle('dark-mode', isDarkMode);
    document.querySelectorAll('nav ul li a').forEach(link => link.classList.toggle('dark-mode', isDarkMode));
    document.querySelectorAll('form button').forEach(button => button.classList.toggle('dark-mode', isDarkMode));
    document.querySelectorAll('.card-product').forEach(card => card.classList.toggle('dark-mode', isDarkMode));
    document.querySelectorAll('.price').forEach(priceElement => { priceElement.classList.toggle('dark-mode', isDarkMode); });

    localStorage.setItem('darkMode', isDarkMode);
});

function updateQuantity(button, change) {
    const quantitySpan = button.closest('.card-product').querySelector('.quantity');
    let currentQuantity = parseInt(quantitySpan.innerText);

    // Asegurarse que la cantidad no sea menor a 0
    currentQuantity = Math.max(0, currentQuantity + change);

    quantitySpan.innerText = currentQuantity;
}

if (document.getElementById('card-container')) {
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
                <button class="btn-add">COMPRAR</button>
            </div>
        `;
        cardContainer.appendChild(productDiv);

        // Verificar si el modo oscuro está activado y aplicarlo a los nuevos productos
        const isDarkMode = localStorage.getItem('darkMode') === 'true';
        if (isDarkMode) {
            // Aplicar el modo oscuro a toda la tarjeta
            productDiv.classList.add('dark-mode');
            productDiv.querySelector('.price').classList.add('dark-mode');
            productDiv.querySelector('.quantity').classList.add('dark-mode'); // Asegúrate de agregar dark-mode al número de cantidad
            productDiv.querySelectorAll('.quantity-controls button').forEach(button => button.classList.add('dark-mode'));
        }
    }
};

if (document.getElementById('grid-container')) {
    var reviews = [
        {
            stars: "⭐⭐⭐⭐⭐",
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/reviews/Photo 00.png",
            text: "¡Excelente servicio y calidad de productos!",
            author: "Juan Pérez"
        },
        {
            stars: "⭐⭐⭐⭐⭐",
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/reviews/Photo 01.png",
            text: "Me encantó la experiencia de compra. ¡Volveré!",
            author: "Ana Gómez"
        },
        {
            stars: "⭐⭐⭐⭐⭐",
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/reviews/Photo 02.png",
            text: "Un lugar increíble con un personal muy amable.",
            author: "Carlos Martínez"
        },
        {
            stars: "⭐⭐⭐⭐⭐",
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/reviews/Photo 03.png",
            text: "Los productos son de alta calidad y llegan rápido.",
            author: "María López"
        },
        {
            stars: "⭐⭐⭐⭐⭐",
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/reviews/Photo 04.png",
            text: "Recomiendo este lugar a todos mis amigos :D",
            author: "Laura Torres"
        },
        {
            stars: "⭐⭐⭐⭐⭐",
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/reviews/Photo 05.png",
            text: "La atención fue rápida y amable. ¡Muy recomendable!",
            author: "Alberto Castillo"
        },
        {
            stars: "⭐⭐⭐⭐⭐",
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/reviews/Photo 06.png",
            text: "Gran variedad de productos y una excelente experiencia de compra.",
            author: "Sofía Ruiz"
        },
        {
            stars: "⭐⭐⭐⭐⭐",
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/reviews/Photo 07.png",
            text: "Los productos llegaron en perfectas condiciones.",
            author: "Miguel Hernández"
        }
    ];

    var gridContainer = document.getElementById('grid-container');

    for (var i = 0; i < reviews.length; i++) {
        var gridDiv = document.createElement('div');
        gridDiv.className = 'review-card';
        gridDiv.innerHTML = `
                            <p class="stars">⭐⭐⭐⭐⭐</p>
                            <div class="review-img">
                                <img src="${reviews[i].image}" alt="${reviews[i].author}">
                            </div>
                            <p>"${reviews[i].text}"</p>
                            <h4>- ${reviews[i].author}</h4>
        `;

        gridContainer.appendChild(gridDiv);
    };
};  