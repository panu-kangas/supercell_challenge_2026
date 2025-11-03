#pragma once

#include "Entity.h"
#include <memory>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf { class Sprite; }

class Player final : public Entity
{

public:
    static constexpr float collisionRadius = 23.0f; // PANU: Make this dynamical instead...?

    Player();
    virtual ~Player() = default;
    
    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:

	void checkGrounded();

	bool m_isInAir = false;
	bool m_spaceHold = false;

};
