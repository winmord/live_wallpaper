#include <iostream>

#include "include\live_wallpapers\live_wallpapers.hpp"
//IActiveDesktop* active_desktop = 0;
int main()
{
	try
	{
		/*const std::string host = "https://apod.nasa.gov";
		const std::string path = "/apod/astropix.html";
*/
		live_wallpapers::live_wallpapers lw;
		//lw.get_image(host, path);

		lw.slide_show("D:/photos", 1);
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
		return -1;
	}
	
	return 0;
}