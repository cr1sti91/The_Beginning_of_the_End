#include "Game.h"

int main()
{	
	std::unique_ptr<Game> game = std::make_unique<Game>(width, height, gameName, frameLimit);


   std::thread playMusicThread([&game]()
    {
        for (short i{}; i < themes; i++)
        {
            game->playMusic(); 
            std::this_thread::sleep_for(std::chrono::milliseconds(1800));
        }
<<<<<<< HEAD
   });
=======
    });
>>>>>>> faaa16ec2dadcdf2473e45f2552fc26578cf45d3


    game->run();


   if (playMusicThread.joinable())
    {
        playMusicThread.join();
    }

	return 0; 
}
