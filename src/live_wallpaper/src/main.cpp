#include <iostream>
#include <thread>
#include <conio.h>
#include <WinSock2.h>
#include <Windows.h>

#include "include/live_wallpaper/live_wallpaper.hpp"
#include "include/live_wallpaper/wallpaper_storage.hpp"

void sh(live_wallpaper::wallpaper_storage & ws, live_wallpaper::live_wallpaper & lw, std::string const& name)
{
	lw.slide_show(ws.get_wallpaper(name));
}

class say
{
public:
	say()
	{
		std::thread thr(&say::say_a, this);
		thr.detach();
	}

	void say_a()
	{
		while(true)
		{
			std::cout << "a";
			std::this_thread::sleep_for(std::chrono::seconds(5));

			if (stop_) return;
		}
	}

	void stop()
	{
		stop_ = true;
	}
private:
	bool stop_{ false };
};

int main()
{
	/*say a;

	while(true)
	{
		if (_getch()) a.stop();
	}*/
	try
	{
		live_wallpaper::wallpaper_storage ws;
		ws.restore_wallpapers();
		
		//ws.create_wallpaper("road", "D:/photos/road", false, 0, 0);
		//ws.create_wallpaper("daytime", "D:/photos/daytime", false, 0, 0);
		//ws.create_wallpaper("lights", "D:/photos/lights", true, 0, 3);
		//ws.create_wallpaper("forest", "D:/photos/forest", false, 0, 0);

		live_wallpaper::live_wallpaper lw;
		std::string name{};

		std::cout << "Input wallpaper name: ";
		std::cin >> name;

		//lw.start_slide_show(ws.get_wallpaper(name));

		while (true)
		{
			lw.start_slide_show(ws.get_wallpaper(name));
	
			if(_getch())
			{
				lw.stop();
				std::cout << "Input wallpaper name: ";
				std::cin >> name;
				lw.start();
			}
		}
		//lw.slide_show(ws.get_wallpaper("lights"));
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return -1;
	}

	return 0;
}
