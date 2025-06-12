#include <SFML/Graphics.hpp>
#include "src/tileMap.h"

int main() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1024, 512), "Tower Defense Game");

    // Déclarer et charger la carte de tuiles une seule fois
    TileMap map;
    const int mapWidth = 16;
    const int mapHeight = 8;
    int tiles[] = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 0,
        2, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 3, 3,
        0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1, 1, 3, 3,
    };

    if (!map.load("../assets/images/tileset.png", sf::Vector2u(64, 64), tiles, mapWidth, mapHeight)) {
        // Gérer l'erreur de chargement de la texture
        return -1;
    }

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(map);  // Dessiner la carte
        window.display();
    }

    return 0;
}
