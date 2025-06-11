//
// Created by gravy on 10/06/2025.
//
#ifndef STALKERENEMY_H
#define STALKERENEMY_H

# include "EnemyCreator.h"

/**
 * @class stalkerEnemy
 * @brief Fast but fragile enemy unit with high mobility
 *
 * Stalker represents a swift enemy unit that prioritizes speed over durability.
 * These units are designed to quickly traverse the map but can be eliminated
 * with less damage compared to other enemy types.
 *
 * Key characteristics:
 * - High movement speed (3.5f)
 * - Low health points (60)
 * - Medium credit reward (15)
 * - Medium score value (75)
 */
class stalkerEnemy : public EnemyCreator {
private:
    static constexpr int STALKER_SPEED = 3.5f;
    static constexpr int STALKER_LIVES = 60;
    static constexpr int STALKER_CREDIT = 15;
    static constexpr int STALKER_SCORE = 75;
    static constexpr std::string STALKER_SPRITE = "stalker.png";

public:
    /**
     * @brief Constructs a new stalker enemy
     *
     * @param id Unique identifier for this stalker instance
     * @param path Predefined path the stalker will follow
     * @param speed Movement speed (default: 3.5f)
     * @param lives Initial health points (default: 60)
     * @param credit Credits awarded when defeated (default: 15)
     * @param score Score points awarded when defeated (default: 75)
     * @param sprite Sprite filename for rendering (default: "stalker.png")
     */
    explicit stalkerEnemy(const std::string& id, const std::deque <sf::Vector2i>& path, float speed = STALKER_SPEED, int lives = STALKER_LIVES, int credit =  STALKER_CREDIT, int score = STALKER_SCORE, std::string sprite = STALKER_SPRITE);
};

#endif //STALKERENEMY_H
