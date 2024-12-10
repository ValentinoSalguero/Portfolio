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
        {
            title: "Alfajor Deuble Negro",
            price: 1000,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 00.png",
            description: "Alfajor Deuble Negro",
        },
        {
            title: "Alfajor Simple Night",
            price: 700,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 01.png",
            description: "Alfajor Simple Night",
        },
        {
            title: "Alfajor Genio",
            price: 500,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 02.png",
            description: "Alfajor Genio",
        },
        {
            title: "Alfajor Guachoo Blanco",
            price: 600,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 03.png",
            description: "Alfajor Guachoo Blanco",
        },
        {
            title: "Alfajor Happy Food",
            price: 600,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 04.png",
            description: "Alfajor Happy Food",
        },
        {
            title: "Alfajor Guolis",
            price: 900,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 05.png",
            description: "Alfajor Guolis",
        },
        {
            title: "Alfajor Cachafaz",
            price: 1200,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 06.png",
            description: "Alfajor Cachafaz",
        },
        {
            title: "Alfajor Lule Muu",
            price: 600,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 07.png",
            description: "Alfajor Lule Muu",
        },
        {
            title: "Alfajor Oreo Trilogía",
            price: 1000,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 08.png",
            description: "Alfajor Oreo Trilogía",
        },
        {
            title: "Alfajor Full Maní",
            price: 800,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 09.png",
            description: "Alfajor Full Maní",
        },
        {
            title: "Alfajor Café Martínez Blanco",
            price: 700,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 10.png",
            description: "Alfajor Café Martínez Blanco",
        },
        {
            title: "Alfajor Smams",
            price: 800,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 11.png",
            description: "Alfajor Smams",
        },
        {
            title: "Alfajor Café Martínez Negro",
            price: 700,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 12.png",
            description: "Alfajor Café Martínez Negro",
        },
        {
            title: "Alfajor Capitán Del Espacio",
            price: 900,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 13.png",
            description: "Alfajor Capitán Del Espacio",
        },
        {
            title: "Alfajor Rasta",
            price: 800,
            image: "/PROYECTO INTEGRADOR TALENTO-TECH/images/products/Photo 14.png",
            description: "Alfajor Rasta",
        },
    ];


    var cardContainer = document.getElementById('card-container');

    for (var i = 0; i < products.length; i++) {
        var cardDiv = document.createElement('div');
        cardDiv.className = 'col-md-4 mb-4';
        cardDiv.innerHTML = `
                            <div class="card h-100">
                                <img src="${products[i].image}" class="card-img-top" alt="${products[i].description}">
                                <div class="card-body">
                                    <h5 class="card-title">${products[i].title}</h5>
                                    <p class="price text-warning">$ ${products[i].price}</p>
                                    <div class="quantity-controls d-flex justify-content-between align-items-center">
                                        <button class="btn btn-danger btn-sm" onclick="updateQuantity(this, -1)">-</button>
                                        <span class="quantity">0</span>
                                        <button class="btn btn-info btn-sm" onclick="updateQuantity(this, 1)">+</button>
                                    </div>
                                    <button class="btn btn-primary w-100 mt-3">COMPRAR</button>
                                </div>
                            </div>
        `;

        cardContainer.appendChild(cardDiv);
    };
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
        gridDiv.className = 'col-md-6 mb-4';
        gridDiv.innerHTML = `
                            <div class="card h-100 text-center">
                                <div class="card-body">
                                    <p class="stars">${reviews[i].stars}</p>
                                <div class="review-img mb-3">
                                <img src="${reviews[i].image}" alt="${reviews[i].author}" class="rounded-circle img-fluid" style="width: 100px; height: 100px;">
                                </div>
                                    <p class="card-text">"${reviews[i].text}"</p>
                                    <h4 class="card-title">- ${reviews[i].author}</h4>
                                </div>
                            </div>
        `;

        gridContainer.appendChild(gridDiv);
    };
};  