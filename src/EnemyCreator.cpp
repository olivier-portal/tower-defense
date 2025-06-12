//
// Created by gravy on 06/06/2025.
//

#include "../include/EnemyCreator.h"

// ==================== Constructor ====================
// Initializes enemy with base attributes and starts its path
EnemyCreator::EnemyCreator(const std::string& id, const std::deque <sf::Vector2i>& path, float speed, int lives, const int credit, const int score, const std::string sprite) : id(id), path(path), speed(speed), lives(lives), credit(credit), score(score), sprite(sprite) {
    if (path.empty()) {
        throw std::invalid_argument("Path cannot be empty");
    }
    advancePath();
    // 32.0f is the tile size used in the game
    pixelPosition = pixelPositionFromGridPosition(gridPosition.value(), 64.0f);
};

// ==================== Basic Getters ====================
// Straightforward accessors - implementation is self-explanatory
std::string EnemyCreator::getId() const {
    return id;
}

sf::Vector2i& EnemyCreator::getGridPosition() {
    return gridPosition.value();
}

sf::Vector2f& EnemyCreator::getPixelPosition() {
    return pixelPosition.value();
}

float EnemyCreator::getSpeed() const {
    return speed;
}

int EnemyCreator::getLives() const {
    return lives;
}

int EnemyCreator::getCredit() const {
    return credit;
}

int EnemyCreator::getScore() const {
    return score;
}

// ==================== Movement Logic ====================

// Moves to the next position in the path
void EnemyCreator::advancePath() {
    if (path.empty()) {
        gridPosition.reset();
        isArrived = true; // If path is empty, marks the enemy as arrived
        return;
    }
    gridPosition = path.front();
    path.pop_front();

    if (!path.empty()) {
        nextGridPosition = path.front();
    } else {
        nextGridPosition.reset();
    }
}

// Converts grid coordinates to pixel coordinates for rendering
sf::Vector2f EnemyCreator::pixelPositionFromGridPosition(const sf::Vector2i& gridPosition, float tileSize) {
    return sf::Vector2f(gridPosition.x * tileSize, gridPosition.y * tileSize);
}

// Calculates normalized direction vector between current and next position
sf::Vector2f EnemyCreator::computePixelDirection(float tileSize) {
    // Attention définir une grille plus large pour les directions
    if (!gridPosition || !nextGridPosition) {
        return sf::Vector2f(0.0f, 0.0f); // Returns (0,0) if positions are invalid
    }

    // Convert grid positions to pixel coordinates
    sf::Vector2f currentPixelPos = pixelPositionFromGridPosition(*gridPosition, tileSize);
    sf::Vector2f targetPixelPos = pixelPositionFromGridPosition(*nextGridPosition, tileSize);

    // Calculate and normalize direction vector
    sf::Vector2f direction = targetPixelPos - currentPixelPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.0f) {
        direction.x /= length;
        direction.y /= length;
    }

    return direction;
}

// Updates enemy position, handles grid-to-grid movement
void EnemyCreator::updatePixelPosition(float tileSize) {
    sf::Vector2f direction = computePixelDirection(tileSize);
    sf::Vector2f newPixelPos = pixelPosition.value() + direction * speed;

    // Snap to grid position if close enough, otherwise continue a smooth movement
    if (hasReachedNextGrid(tileSize)) {
        pixelPosition = pixelPositionFromGridPosition(*nextGridPosition, tileSize);
        advancePath();
    } else {
        pixelPosition = newPixelPos;
    }
}

// Checks if the enemy is close enough to the next grid position to snap to it
bool EnemyCreator::hasReachedNextGrid(float tileSize) {
    if (!gridPosition || !nextGridPosition) {
        return false;
    }

    // Calculate distance to target position
    sf::Vector2f targetPixelPos = pixelPositionFromGridPosition(*nextGridPosition, tileSize);
    float distanceToTarget = std::sqrt(
        std::pow(pixelPosition->x - targetPixelPos.x, 2) +
        std::pow(pixelPosition->y - targetPixelPos.y, 2)
    );

    // Consider reached if within half a speed unit
    return distanceToTarget < (speed / 2.0f);
}

// Render
void EnemyCreator::render(sf::RenderWindow& window, float tileSize) {}

// ==================== Health System ====================

// Adds damage to the queue for processing during the next update
void EnemyCreator::queueDamage(int damage) {
    pendingDamage.push(damage);
}

// Applies damage and updates enemy state
int EnemyCreator::takeDamage(int damage) {
    lives -= damage;
    if (lives <= 0) {
        isAlive = false;
    }
    return lives; // Returns remaining health points
}

// ==================== State Checks ====================

bool EnemyCreator::hasArrived() const {
    return isArrived;
}

bool EnemyCreator::isDead() const {
    return !isAlive;
}

// ==================== Update Logic ====================

// Main update loop: processes pending damage and updates position
void EnemyCreator::update(float tileSize) {
    if (!isAlive || isArrived) {
        return;
    }

    // Process pending damage until death or queue empty
    while (!pendingDamage.empty()) {
        if (isAlive) { // Check added to stop processing damage once dead
            int damage = pendingDamage.front();
            pendingDamage.pop();
            takeDamage(damage);
        } else {
            break; // Exit loop early if the enemy dies
        }
    }

    // Update position if still alive
    updatePixelPosition(tileSize);
}