/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "FrameTimer.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	moveTriggerArea( Graphics::GetScreenRect()
		.GetExpanded( -Graphics::ScreenWidth / 3 ) )
{
	Map::Load( "Maps/Level1.lvl" );
	for( int y = 0; y < Map::Height; ++y )
	{
		for( int x = 0; x < Map::Width; ++x )
		{
			// 0 = background.
			// [W]all or [E]nemy.
			if( Map::Get( x,y ) == 'W' )
			{
				plats.emplace_back( Platform( { x * Platform::Size,
					y * Platform::Size } ) );
			}
			else if( Map::Get( x,y ) == 'E' )
			{
				enemies.emplace_back( std
					::make_unique<Enemy>( Vec2( Vei2{ x *
					Platform::Size,y * Platform::Size } ) ) );
			}
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = FrameTimer::Mark();
	// Make sure dt isn't like 1,000,000
	if( dt > 0.05f ) dt = 0.0f;

	while( !pl.GetRect().IsContainedBy( moveTriggerArea ) )
	{
		const Vec2 displacement = -( pl.GetPos() - Graphics
			::GetScreenRect().GetCenter() ).GetNormalized();

		for( auto& p : plats )
		{
			p.Move( displacement );
		}
		for( auto& e : enemies )
		{
			e->Move( displacement );
		}

		pl.Move( displacement );
	}

	pl.Update( wnd.kbd,wnd.mouse,dt );
	pl.CheckHits( plats );

	for( auto& e : enemies )
	{
		e->Update( dt );

		e->CheckHits( plats );

		pl.CheckEnemyHit( *e );
	}
}

void Game::ComposeFrame()
{
	for( const Platform& plat : plats )
	{
		plat.Draw( gfx );
	}

	for( const auto& e : enemies )
	{
		e->Draw( gfx );
	}

	pl.Draw( gfx );

#if 0
	gfx.DrawHitbox( moveTriggerArea,Colors::Green );
#endif
}
