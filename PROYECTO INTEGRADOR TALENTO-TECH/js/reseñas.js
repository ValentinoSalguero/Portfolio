try {
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

    if (!gridContainer) {
        throw new Error("No se encontró el contenedor con id 'grid-container'.");
    }

    for (var i = 0; i < reviews.length; i++) {
        var gridDiv = document.createElement('div');
        gridDiv.className = 'review-card';
        gridDiv.innerHTML = `
            <p class="stars">${reviews[i].stars}</p>
            <div class="review-img">
                <img src="${reviews[i].image}" alt="${reviews[i].author}">
            </div>
            <p>"${reviews[i].text}"</p>
            <h4>- ${reviews[i].author}</h4>
        `;
        gridContainer.appendChild(gridDiv);
    }

} catch (error) {
    console.error("Ocurrió un error al generar las reseñas:", error.message);
}
