#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
#include "Surface.h"
#include "Platform.h"

class Enemy
{
public:
	Enemy( const Vec2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void Move( const Vec2& amount );
	void HitFrom( const Vec2& pos,float damage );
	void CheckHits( const std::vector<Platform>& plats );

	const Rect& GetRect() const;
private:
	void Land();
	void Fall();

	bool HitTestTop( const Rect& rect ) const;
	bool HitTestBot( const Rect& rect ) const;
	bool HitTestLeft( const Rect& rect ) const;
	bool HitTestRight( const Rect& rect ) const;
private:
	static const Surface spr;

	static constexpr int size = 32;
	static constexpr float offset = float( size / 4 );
	Vec2 pos;
	Rect hitbox;
	Vec2 vel = { 0.0f };

	float health = 10.0f;
	static constexpr float knockbackSpeed = 400.2f;
	static constexpr float damageCooldown = 0.03f;
	float damageTimer = damageCooldown;

	static constexpr float gravAcc = 12.1f / 0.0175771527f;
	float grav = 0.0f;
};