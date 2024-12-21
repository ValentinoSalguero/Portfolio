document.addEventListener("DOMContentLoaded", () => {
    try {
        const cardContainer = document.getElementById('card-container');
        const prevBtn = document.getElementById("prev-btn");
        const nextBtn = document.getElementById("next-btn");
        const pageInfo = document.getElementById("page-info");

        const limit = 12;
        let currentPage = 1;
        let totalProductos = 0;

        let isDarkMode = localStorage.getItem('darkMode') === 'true';

        // Cargar productos según la página actual
        function fetchProductos(page) {
            try {
                const skip = (page - 1) * limit;

                fetch(`https://dummyjson.com/products?limit=${limit}&skip=${skip}`)
                .then(response => {
                    if (!response.ok) {
                        throw new Error('Error en la respuesta de la API');
                    }
                    return response.json();
                })
                .then(data => {
                    try {
                        totalProductos = data.total;
                        const productos = data.products;

                        cardContainer.innerHTML = '';

                        productos.forEach(product => {
                            const price = product.price.toFixed(2);

                            let productDiv = document.createElement('div');
                            productDiv.className = 'card-product flex';
                            productDiv.innerHTML = `
                                <div class="container-img">
                                    <img src="${product.images[0]}" alt="${product.title}">
                                </div>
                                <div class="card-details">
                                    <h3 class="card-product_title">${product.title}</h3>
                                    <p class="price">$ ${price}</p>
                                    <button class="btn-add" onclick="addToCart('${product.title}', ${price}, '${product.images[0]}');">COMPRAR</button>
                                </div>
                            `;
                            cardContainer.appendChild(productDiv);
                        });

                        applyDarkModeToCards();

                        pageInfo.textContent = currentPage;
                        prevBtn.disabled = currentPage === 1;
                        nextBtn.disabled = (currentPage * limit) >= totalProductos;
                    } catch (innerError) {
                        console.error('Error al procesar los datos de los productos:', innerError);
                    }
                })
                .catch(error => {
                    console.error('Error al cargar los productos desde la API:', error);
                });
            } catch (outerError) {
                console.error('Error en la función fetchProductos:', outerError);
            }
        }

        // Aplicar o quitar el modo oscuro de las tarjetas cargadas
        function applyDarkModeToCards() {
            try {
                const cardProducts = document.querySelectorAll('.card-product');
                cardProducts.forEach(card => {
                    if (isDarkMode) {
                        card.classList.add('dark-mode');
                        let priceElement = card.querySelector('.price');
                        if (priceElement) {
                            priceElement.classList.add('dark-mode');
                        }
                    } else {
                        card.classList.remove('dark-mode');
                        let priceElement = card.querySelector('.price');
                        if (priceElement) {
                            priceElement.classList.remove('dark-mode');
                        }
                    }
                });
            } catch (error) {
                console.error('Error al aplicar el modo oscuro a las tarjetas:', error);
            }
        }

        // Cambiar entre modo oscuro y claro cuando el checkbox es marcado o desmarcado
        document.getElementById('input').addEventListener('change', function () {
            try {
                isDarkMode = this.checked;

                // Guardar la preferencia en el almacenamiento local
                localStorage.setItem('darkMode', isDarkMode);
                applyDarkModeToCards(); // Aplicar el modo oscuro a las tarjetas

                // Cambiar el estilo de los elementos del documento según el modo
                document.body.classList.toggle('dark-mode', isDarkMode);
                document.querySelector('header').classList.toggle('dark-mode', isDarkMode);
                document.querySelector('footer').classList.toggle('dark-mode', isDarkMode);
                document.querySelectorAll('.navbar-nav .nav-link').forEach(link => link.classList.toggle('dark-mode', isDarkMode));
            } catch (error) {
                console.error('Error al cambiar entre modo claro y oscuro:', error);
            }
        });

        prevBtn.addEventListener("click", () => {
            try {
                if (currentPage > 1) {
                    currentPage--;
                    fetchProductos(currentPage);
                }
            } catch (error) {
                console.error('Error al cambiar a la página anterior:', error);
            }
        });

        nextBtn.addEventListener("click", () => {
            try {
                if ((currentPage * limit) < totalProductos) {
                    currentPage++;
                    fetchProductos(currentPage);
                }
            } catch (error) {
                console.error('Error al cambiar a la página siguiente:', error);
            }
        });

        fetchProductos(currentPage);
    } catch (error) {
        console.error('Error en la inicialización del DOMContentLoaded:', error);
    }
});
