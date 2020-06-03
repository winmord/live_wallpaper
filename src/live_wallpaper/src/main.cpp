#include <iostream>

#include "include/live_wallpaper/live_wallpaper.hpp"

int main()
{
	try
	{
		live_wallpaper::live_wallpaper lw;
		lw.slide_show("D:/photos/road", 0);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return -1;
	}

	return 0;
}
