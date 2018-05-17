/*
#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "Keyboard.h"
#include "Rect.h"
#include "Platform.h"
#include "Bullet.h"
#include "Mouse.h"
#include "Font.h"
#include "Enemy.h"

class Player
{
public:
	Player( const Vei2& pos );

	void Update( const Keyboard& kbd,const Mouse& ms,
		float dt );
	void Draw( Graphics& gfx ) const;

	// Call once for everything you want to collide with.
	bool CheckHit( const Rect& rect );
	// Call with a vector of items to collide with.
	template<typename T>
	bool CheckHits( const std::vector<T>& items )
	{
		// Only allow to jump if touching ground.
		canJump = false;

		bool hasHit = false;

		for( const T& item : items )
		{
			if( CheckHit( item.GetRect() ) ) hasHit = true;

			for( auto& b : bullets )
			{
				b.CheckHit( item.GetRect() );
			}
		}

		return hasHit;
	}
	void Move( const Vec2& amount );
	void MoveBullets( const Vec2& amount );
	bool CheckEnemyHit( Enemy& e );

	const Vec2& GetPos() const;
	const Rect& GetRect() const;
private:
	void Land();
	void Fall();

	bool HitTestTop( const Rect& rect ) const;
	bool HitTestBot( const Rect& rect ) const;
	bool HitTestLeft( const Rect& rect ) const;
	bool HitTestRight( const Rect& rect ) const;
private:
	Vec2 pos;
	Rect hitbox;
	static constexpr int size = 32;
	// For hit test math.
	static constexpr int offset = size / 4;

	float vel = 0.0f;
	static constexpr float speed = 123.5f;
	static constexpr float maxSpeed = speed * 2.5f;
	static constexpr float slowdownFactor = 0.96f;

	static constexpr float gravAcc = 9.0f / 0.0175771527f;
	float grav = 0.0f;
	static constexpr int jumpPower = 395;
	bool jumping = false;
	bool canJump = false;

	static constexpr float refireTime = 0.025f;
	float shotTimer = 0.0f;
	std::vector<Bullet> bullets;
	Vec2 shotPos;
	static constexpr float bloom = 0.05f;
	static constexpr float maxBloom = 0.8f;
	float bloomAdd = 0.0f;

	const Font consolas = { "Fonts/FixedSys16x28.bmp" };

	Vec2 lastPos;
};
*/
#pragma once

#include "GravObject.h"

class Player
	:
	public GravObject
{
public:
	Player( const Vec2& pos );
	
	void Update( const Keyboard& kbd,float dt) override;
private:
	static constexpr int size = 32;
	static constexpr float speed = 123.5f;
	static constexpr float maxSpeed = speed * 2.5f;
	static constexpr float slowdownFactor = 0.96f;
	float vel = 0.0f;
};