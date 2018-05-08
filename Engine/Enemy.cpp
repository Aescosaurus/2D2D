#include "Enemy.h"
#include "SpriteEffect.h"

const Surface Enemy::spr = Surface( size,size,Colors::LightRed );

Enemy::Enemy( const Vec2& pos )
	:
	pos( pos ),
	hitbox( pos,float( size ),float( size ) )
{
}

void Enemy::Update( float dt )
{
	if( damageTimer <= damageCooldown )
	{
		damageTimer += dt;

		pos += vel * knockbackSpeed * dt;
	}

	grav += gravAcc * dt;
	pos.y += grav * dt;
	
	hitbox.MoveTo( pos );
}

void Enemy::Draw( Graphics& gfx ) const
{
	if( damageTimer < damageCooldown )
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,
			SpriteEffect::Substitution( Colors::Magenta,
				Colors::White ) );
	}
	else
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),
			spr,SpriteEffect::Copy() );
	}

#if !NDEBUG
	if( hitbox.IsContainedBy( Graphics::GetScreenRect() ) )
	{
		gfx.DrawHitbox( hitbox );
	}
#endif
}

void Enemy::Move( const Vec2& amount )
{
	pos += amount;

	hitbox.MoveTo( pos );
}

void Enemy::HitFrom( const Vec2& pos,float damage )
{
	vel = -( pos - hitbox.GetCenter() ).GetNormalized();

	health -= damage;

	damageTimer = 0.0f;
}

void Enemy::CheckHits( const std::vector<Platform>& plats )
{
	for( const auto& p : plats )
	{
		const auto& rect = p.GetRect();
		if( HitTestBot( rect ) )
		{
			pos.y = rect.top - size;
			Land();
		}
		if( HitTestTop( rect ) )
		{
			pos.y = rect.bottom;
			Fall();
		}

		if( HitTestLeft( rect ) )
		{
			pos.x = rect.right;
		}

		if( HitTestRight( rect ) )
		{
			pos.x = rect.left - size;
		}
	}
}

const Rect& Enemy::GetRect() const
{
	return( hitbox );
}

void Enemy::Land()
{
	grav = 0.0f;
}

void Enemy::Fall()
{
	grav = 0.0f;
}

bool Enemy::HitTestTop( const Rect& rect ) const
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

bool Enemy::HitTestBot( const Rect& rect ) const
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

bool Enemy::HitTestLeft( const Rect& rect ) const
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

bool Enemy::HitTestRight( const Rect& rect ) const
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