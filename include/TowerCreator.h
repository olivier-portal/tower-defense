//
// Created by gravy on 12/06/2025.
//

#ifndef TOWERCREATOR_H
#define TOWERCREATOR_H

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <SFML/System/Vector2.hpp>

#include "Projectile.h"


class TowerCreator {
public:
    TowerCreator(std::string& id, int cost, int attackDamage, float attackSpeed, std::vector<sf::Vector2i> attackArea, std::string sprite);

    virtual ~TowerCreator() = default;

    // Basic getters
    std:: string getId() const;
    int getCost() const;
    sf::Vector2i getGridPosition() const;
    int getAttackDamage() const;
    float getAttackSpeed() const;
    std::vector<sf::Vector2i> getAttackArea();
    std::vector<sf::Vector2i> getScannedTiles();
    bool getIsPlaced();
    bool getIsChoosen();

    // Basic setters
    void setGridPosition(sf::Vector2i gridPosition);
    void setScannedTiles();

    // Other methods
    Enemies* updateTargets(std::vector<sf::Vector2i> scannedTiles); // scan les tuiles alentour et retourne les ennemis présents

    bool canShoot();
    void shoot(); // création de projectil
    void applyDamage(Enemies* target);

    void updateCooldownTimer(float deltaTime);
    void resetCooldownTimer();

    std::unique_ptr<Projectile> createProjectile();

    void update(); // update du tower, appelé à chaque frame, gère cooldown +  détection + tir



protected:
    std::string id;
    int cost;
    std::optional<sf::Vector2i> gridPosition;
    int attackDamage;
    float attackSpeed;
    float cooldownTimer =  0.0f;
    std::vector<sf::Vector2i> attackArea;
    std::vector<sf::Vector2i> scannedTiles;
    std::string sprite;
    bool isChoosen = false;
    bool isPlaced = false;
};

#endif //TOWERCREATOR_H
