//
// Created by gravy on 12/06/2025.
//

#include "../include/TowerCreator.h"

// ==================== Constructor ====================
TowerCreator::TowerCreator(std::string& id, int cost, int attackDamage, float attackSpeed, std::vector<sf::Vector2i> attackArea, std::string sprite) : id(id), cost(cost), attackDamage(attackDamage), attackSpeed(attackSpeed), attackArea(attackArea), sprite(sprite) {}

// ==================== Basic Getters ====================
std:: string TowerCreator::getId() const {
    return id;
}

int TowerCreator::getCost() const {
    return cost;
}

sf::Vector2i TowerCreator::getGridPosition() const {
    return gridPosition.value();
}

int TowerCreator::getAttackDamage() const {
    return attackDamage;
}

float TowerCreator::getAttackSpeed() const {
    return attackSpeed;
}

std::vector<sf::Vector2i> TowerCreator::getAttackArea() {
    return attackArea;
}

std::vector<sf::Vector2i> TowerCreator::getScannedTiles() {
    return scannedTiles;
}

bool TowerCreator::getIsPlaced() {
    return isPlaced;
}

bool TowerCreator::getIsChoosen() {
    return isChoosen;
}

// ==================== Basics setters ====================
void TowerCreator::setGridPosition(sf::Vector2i gridPosition) {
    if (isPlaced) {
        this->gridPosition = gridPosition;
    }
}

void TowerCreator::setScannedTiles() {
    if (gridPosition.has_value()) {
        // ajoute les tuiles adjascantes à scannedTiles
    }
}

// ==================== Attack Logic ====================

