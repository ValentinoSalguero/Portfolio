// Aplica el modo oscuro guardado en localStorage
function applySavedMode() {
    try {
        const isDarkMode = localStorage.getItem('darkMode') === 'true';
        if (isDarkMode) {
            document.body.classList.add('dark-mode');
            document.querySelector('header').classList.add('dark-mode');
            document.querySelector('footer').classList.add('dark-mode');
            document.querySelectorAll('.navbar-nav .nav-link').forEach(link => link.classList.add('dark-mode'));
            document.querySelectorAll('form button').forEach(button => button.classList.add('dark-mode'));
            document.querySelectorAll('.card-product').forEach(card => card.classList.add('dark-mode'));
            document.querySelectorAll('.price').forEach(priceElement => priceElement.classList.add('dark-mode'));
            document.querySelectorAll('.cart-container').forEach(cart => cart.classList.add('dark-mode'));
            document.querySelectorAll('.cart-item').forEach(item => item.classList.add('dark-mode'));
            document.querySelectorAll('.checkout-button').forEach(btn => btn.classList.add('dark-mode'));
            document.querySelectorAll('.cart-summary').forEach(summary => summary.classList.add('dark-mode'));
            document.querySelectorAll('.success-modal .modal-content').forEach(modal => modal.classList.add('dark-mode'));
            document.querySelectorAll('.btn-pagination-secondary').forEach(button => button.classList.add('dark-mode'));
            document.querySelectorAll('#page-info').forEach(pageInfo => pageInfo.classList.add('dark-mode'));

            document.getElementById('input').checked = true;
        }
    } catch (error) {
        console.error("Error al aplicar el modo oscuro guardado:", error);
    }
}

applySavedMode();

// Evento para cambiar entre el modo claro y oscuro cuando se marca el checkbox
document.getElementById('input').addEventListener('change', function () {
    try {
        const isDarkMode = this.checked;
        document.body.classList.toggle('dark-mode', isDarkMode);
        document.querySelector('header').classList.toggle('dark-mode', isDarkMode);
        document.querySelector('footer').classList.toggle('dark-mode', isDarkMode);
        document.querySelectorAll('.navbar-nav .nav-link').forEach(link => link.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('form button').forEach(button => button.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('.card-product').forEach(card => card.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('.price').forEach(priceElement => priceElement.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('.cart-container').forEach(cart => cart.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('.cart-item').forEach(item => item.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('.checkout-button').forEach(btn => btn.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('.cart-summary').forEach(summary => summary.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('.success-modal .modal-content').forEach(modal => modal.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('.btn-pagination-secondary').forEach(button => button.classList.toggle('dark-mode', isDarkMode));
        document.querySelectorAll('#page-info').forEach(pageInfo => pageInfo.classList.toggle('dark-mode', isDarkMode));

        localStorage.setItem('darkMode', isDarkMode);
    } catch (error) {
        console.error("Error al cambiar entre modo claro y oscuro:", error);
    }
});

// Lógica para abrir y cerrar el carrito de compras
document.addEventListener("DOMContentLoaded", () => {
    try {
        const openCartBtn = document.getElementById("open-cart");
        const closeCartBtn = document.getElementById("close-cart");
        const cartSidebar = document.getElementById("cart-sidebar");

        openCartBtn.addEventListener("click", () => {
            cartSidebar.classList.add("active");
        });

        closeCartBtn.addEventListener("click", () => {
            cartSidebar.classList.remove("active");
        });
    } catch (error) {
        console.error("Error en la lógica de abrir/cerrar el carrito:", error);
    }
});

// Lógica para mostrar y cerrar el modal de éxito al finalizar la compra
try {
    document.getElementById('checkout-button').addEventListener('click', function () {
        const successModal = document.getElementById("success-modal");
        successModal.style.display = 'flex';
        document.getElementById("cart-sidebar").classList.remove("active");
    });

    const closeSuccessModalButton = document.getElementById("close-success-modal");

    closeSuccessModalButton.addEventListener('click', function () {
        const successModal = document.getElementById("success-modal");
        successModal.style.display = 'none';
    });
} catch (error) {
    console.error("Error en la lógica del modal de éxito:", error);
}
