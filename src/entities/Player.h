#pragma once

#include "Entity.h"
#include "Constants.h"
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

	void handleInput();
	void checkJumps(bool wPressed);
	void checkTurboJump(bool sPressed);
	void handleSideMovement(bool aPressed, bool dPressed);
	void applyGravity(float dt);
	void checkGrounded();
	void checkOutOfBounds();
	void checkTimers();

	void updateJumpLoadBar();

	bool m_isInAir = false;
	bool m_didDoubleJump = false;
	bool m_isTurboJumping = false;
	bool m_isLoadingTurbo = false;
	bool m_wHold = false;
	bool m_sHold = false;

	float m_speed = PlayerSpeed;

	sf::Clock m_turboLoadClock;
	sf::Clock m_turboEffectClock;
	sf::RectangleShape m_jumpLoadBar;

};
