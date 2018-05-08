#pragma once

#include <vector>
#include "Graphics.h"
#include <fstream>
#include <cassert>
#include "Platform.h"

class Map
{
public:
	static void Load( const std::string& filePath );
	static char Get( int x,int y );
	static char Get( int index );
public:
	static constexpr int Width = 1 + Graphics
		::ScreenWidth / Platform::Size * 2;
	static constexpr int Height = 1 + Graphics
		::ScreenHeight / Platform::Size * 2;
	static std::vector<char> Data;
};