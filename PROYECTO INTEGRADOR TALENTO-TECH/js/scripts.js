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
        document.querySelectorAll('.price').forEach(priceElement => priceElement.classList.add('dark-mode'));
        document.querySelectorAll('.cart-container').forEach(cart => cart.classList.add('dark-mode'));
        document.querySelectorAll('.cart-item').forEach(item => item.classList.add('dark-mode'));
        document.querySelectorAll('.checkout-btn').forEach(btn => btn.classList.add('dark-mode'));
        document.querySelectorAll('.cart-summary').forEach(summary => summary.classList.add('dark-mode'));
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
    document.querySelectorAll('.price').forEach(priceElement => priceElement.classList.toggle('dark-mode', isDarkMode));
    document.querySelectorAll('.cart-container').forEach(cart => cart.classList.toggle('dark-mode', isDarkMode));
    document.querySelectorAll('.cart-item').forEach(item => item.classList.toggle('dark-mode', isDarkMode));
    document.querySelectorAll('.checkout-btn').forEach(btn => btn.classList.toggle('dark-mode', isDarkMode));
    document.querySelectorAll('.cart-summary').forEach(summary => summary.classList.toggle('dark-mode', isDarkMode));

    localStorage.setItem('darkMode', isDarkMode);
});
