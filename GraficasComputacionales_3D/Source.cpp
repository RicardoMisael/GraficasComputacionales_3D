#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ventana SFML");

    // Crear un círculo
    sf::CircleShape circle(50); // Radio de 50
    circle.setFillColor(sf::Color::Green); // Color verde
    circle.setPosition(375, 275); // Posición en el centro de la ventana (ajustada a mano)

    // Bucle principal del programa
    while (window.isOpen()) {
        // Manejar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Cerrar ventana
            }
        }

        // Limpiar la ventana con un color negro
        window.clear(sf::Color::Black);

        // Dibujar el círculo
        window.draw(circle);

        // Mostrar los gráficos en la ventana
        window.display();
    }

    return 0;
}
