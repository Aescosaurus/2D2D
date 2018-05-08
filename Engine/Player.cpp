#include "Player.h"

Player::Player( const Vei2& pos )
	:
	pos( Vec2( pos ) ),
	shotPos( pos ),
	hitbox( pos,float( size ),float( size ) )
{
}

void Player::Update( const Keyboard& kbd,const Mouse& ms,
	float dt )
{
	lastPos = pos;

	if( kbd.KeyIsPressed( 'A' ) )
	{
		vel -= speed;
	}
	else if( kbd.KeyIsPressed( 'D' ) )
	{
		vel += speed;
	}
	else if( abs( vel ) < 23.5f ) vel = 0.0;

	if( vel > maxSpeed ) vel = maxSpeed;
	if( vel < -maxSpeed ) vel = -maxSpeed;

	pos.x += vel * dt;

	vel *= slowdownFactor;

	grav += gravAcc * dt;
	pos.y += grav * dt;

	if( kbd.KeyIsPressed( 'W' ) && canJump )
	{
		jumping = true;
		canJump = false;
	}

	if( jumping )
	{
		pos.y -= float( jumpPower ) * dt;
	}

	if( grav > float( jumpPower ) / 1.5f && jumping )
	{
		grav = 0.0f;
		jumping = false;
		canJump = false;
	}

	hitbox.MoveTo( pos );

	shotPos = pos + Vec2( float( size ) ) / 2.0f;

	if( shotTimer > refireTime )
	{
		if( ms.LeftIsPressed() )
		{
			shotTimer = 0.0f;

			bullets.emplace_back( Bullet{ shotPos,
				ms.GetPos(),bloom + bloomAdd } );

			if( bloomAdd < maxBloom ) bloomAdd += 0.012f;
		}
		else
		{
			bloomAdd -= 0.035f;
			if( bloomAdd < 0.0f ) bloomAdd = 0.0f;
		}
	}
	else if( shotTimer <= refireTime )
	{
		shotTimer += dt;
	}

	for( auto& it = bullets.begin();
		it < bullets.end();
		++it )
	{
		it->Update( dt );

		if( it->WillDelete() )
		{
			it = bullets.erase( it );
			if( it == bullets.end() ) break;
		}
	}
}

void Player::Draw( Graphics& gfx ) const
{
	gfx.DrawRect( int( pos.x ),int( pos.y ),
		size,size,Colors::Blue );

	for( const auto& b : bullets )
	{
		b.Draw( gfx );
	}

#if !NDEBUG
	if( hitbox.IsContainedBy( Graphics::GetScreenRect() ) )
	{
		gfx.DrawHitbox( hitbox );
	}

	consolas.DrawText( std
		::to_string( abs( int( round( lastPos.x - pos.x ) ) ) ),
		{ 15,15 },Colors::White,gfx );
#endif
}

bool Player::CheckHit( const Rect& rect )
{
	bool hasHit = false;
	if( HitTestBot( rect ) )
	{
		pos.y = rect.top - size;
		Land();
		hasHit = true;
	}
	if( HitTestTop( rect ) )
	{
		pos.y = rect.bottom;
		Fall();
		hasHit = true;
	}

	if( HitTestLeft( rect ) )
	{
		pos.x = rect.right;
		hasHit = true;
	}

	if( HitTestRight( rect ) )
	{
		pos.x = rect.left - size;
		hasHit = true;
	}

	return hasHit;
}

void Player::Move( const Vec2& amount )
{
	pos += amount;

	MoveBullets( amount );

	hitbox.MoveTo( pos );
}

void Player::MoveBullets( const Vec2& amount )
{
	for( auto& b : bullets )
	{
		b.Move( amount );
	}
}

bool Player::CheckEnemyHit( Enemy& e )
{
	bool isHit = false;

	for( auto& b : bullets )
	{
		if( b.GetRect().IsOverlappingWith( e.GetRect() ) )
		{
			e.HitFrom( b.GetPos(),1.0f );
			b.Kill();

			isHit = true;
		}
	}

	return isHit;
}

const Vec2& Player::GetPos() const
{
	return( pos );
}

const Rect& Player::GetRect() const
{
	return( hitbox );
}

void Player::Land()
{
	grav = 0.0f;
	jumping = false;
	canJump = true;
}

void Player::Fall()
{
	jumping = false;
	grav = 0.0f;
}

bool Player::HitTestTop( const Rect& rect ) const
{
	if( pos.x + offset < rect.right &&
		pos.x + size - offset > rect.left &&
		pos.y < rect.bottom &&
		pos.y + offset > rect.top )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::HitTestBot( const Rect& rect ) const
{
	if( pos.x + offset < rect.right &&
		pos.x + size - offset > rect.left &&
		pos.y + size - offset < rect.bottom &&
		pos.y + size > rect.top )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::HitTestLeft( const Rect& rect ) const
{
	if( pos.x < rect.right &&
		pos.x + offset > rect.left &&
		pos.y + offset < rect.bottom &&
		pos.y + size - offset > rect.top )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::HitTestRight( const Rect& rect ) const
{
	if( pos.x + size - offset < rect.right &&
		pos.x + size > rect.left &&
		pos.y + offset < rect.bottom &&
		pos.y + size - offset > rect.top )
	{
		return true;
	}
	else
	{
		return false;
	}
}
