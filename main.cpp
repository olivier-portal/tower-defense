#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "include/EnemyFactory.h"

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? "✓" : "✗") << " " << testName << std::endl;
}

// Test des fonctionnalités de base de EnemyCreator
void testEnemyCreatorBasics(EnemyCreator* enemy) {
    std::cout << "\nTest des fonctionnalités de base :" << std::endl;
    
    try {
        printTestResult("getId() retourne une valeur non vide", 
            !enemy->getId().empty());
        
        printTestResult("getSpeed() retourne une valeur positive", 
            enemy->getSpeed() > 0);
        
        printTestResult("getLives() retourne une valeur positive", 
            enemy->getLives() > 0);
        
        printTestResult("getCredit() retourne une valeur non négative", 
            enemy->getCredit() >= 0);
        
        printTestResult("getScore() retourne une valeur non négative", 
            enemy->getScore() >= 0);
    } catch (const std::exception& e) {
        std::cout << "Erreur dans les tests de base : " << e.what() << std::endl;
    }
}

// Test du système de dégâts
void testDamageSystem(EnemyCreator* enemy) {
    std::cout << "\nTest du système de dégâts :" << std::endl;
    
    try {
        int initialLives = enemy->getLives();
        int damageAmount = 10;
        
        // Test de takeDamage
        int remainingLives = enemy->takeDamage(damageAmount);
        printTestResult("takeDamage réduit correctement les points de vie", 
            remainingLives == initialLives - damageAmount);
        
        // Test de queueDamage et update
        enemy->queueDamage(damageAmount);
        enemy->update(32.0f);
        printTestResult("queueDamage et update appliquent correctement les dégâts", 
            enemy->getLives() == initialLives - (2 * damageAmount));
        
        // Test de mort
        enemy->takeDamage(1000);
        printTestResult("isDead détecte correctement la mort", enemy->isDead());
    } catch (const std::exception& e) {
        std::cout << "Erreur dans les tests de dégâts : " << e.what() << std::endl;
    }
}

// Test du système de mouvement
void testMovementSystem(EnemyCreator* enemy) {
    std::cout << "\nTest du système de mouvement :" << std::endl;
    
    try {
        const float TILE_SIZE = 32.0f;
        
        // Test de la position initiale
        auto gridPos = enemy->getGridPosition();
        printTestResult("Position initiale est valide", 
            gridPos.x >= 0 && gridPos.y >= 0);
        
        // Test du calcul de direction
        sf::Vector2f direction = enemy->computePixelDirection(TILE_SIZE);
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        printTestResult("Vecteur de direction normalisé", 
            std::abs(length - 1.0f) < 0.001f || length == 0.0f);
        
        // Test de mise à jour de position
        sf::Vector2f initialPixelPos = enemy->getPixelPosition();
        enemy->update(TILE_SIZE);
        sf::Vector2f newPixelPos = enemy->getPixelPosition();
        
        printTestResult("Mise à jour de position effectuée", 
            initialPixelPos != newPixelPos || enemy->hasArrived());
        
    } catch (const std::exception& e) {
        std::cout << "Erreur dans les tests de mouvement : " << e.what() << std::endl;
    }
}

// Test de la factory d'ennemis
void testEnemyFactory() {
    std::cout << "\nTest de la factory d'ennemis :" << std::endl;
    
    std::deque<sf::Vector2i> testPath = {
        sf::Vector2i(0, 0),
        sf::Vector2i(1, 0),
        sf::Vector2i(1, 1),
        sf::Vector2i(2, 1)
    };
    
    try {
        EnemyFactory factory;
        
        auto grunt = factory.create("grunt", "grunt_1", testPath);
        printTestResult("Création d'un Grunt", grunt != nullptr);
        
        auto stalker = factory.create("stalker", "stalker_1", testPath);
        printTestResult("Création d'un Stalker", stalker != nullptr);
        
        auto juggernaut = factory.create("juggernaut", "juggernaut_1", testPath);
        printTestResult("Création d'un Juggernaut", juggernaut != nullptr);
        
        try {
            auto invalid = factory.create("invalid_type", "error", testPath);
            printTestResult("Test type invalide", false);
        } catch (const std::runtime_error&) {
            printTestResult("Exception type invalide attrapée", true);
        }
        
    } catch (const std::exception& e) {
        std::cout << "Erreur dans les tests de factory : " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== Début des tests ===" << std::endl;
    
    std::deque<sf::Vector2i> testPath = {
        sf::Vector2i(0, 0),
        sf::Vector2i(1, 0),
        sf::Vector2i(1, 1),
        sf::Vector2i(2, 1)
    };
    
    try {
        // Test de la factory
        testEnemyFactory();
        
        // Création d'un ennemi pour les tests
        EnemyFactory factory;
        auto enemy = factory.create("grunt", "test_grunt", testPath);
        
        // Tests des différents systèmes
        testEnemyCreatorBasics(enemy.get());
        testDamageSystem(enemy.get());
        
        // Créer un nouvel ennemi pour les tests de mouvement
        auto movementEnemy = factory.create("grunt", "movement_test", testPath);
        testMovementSystem(movementEnemy.get());
        
        std::cout << "\n=== Tests terminés avec succès ! ===" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cout << "\n✗ Une erreur est survenue : " << e.what() << std::endl;
        return 1;
    }
}