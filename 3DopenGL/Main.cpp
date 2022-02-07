#include "Game.h"
#include "AudioManager.h"

int main()
{
	//AudioManager audio;
	//audio.LoadSong("Soundtrack.wav");

	//MAIN LOOP
	while (!Game::Get().getWindowShouldClose())
	{
		if (glfwGetKey(Game::Get().window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			//audio.PlaySong("Soundtrack.wav");
		}

		//UPDATE INPUT ---
		Game::Get().update();
		//DRAW
		Game::Get().render();

		//audio.Update(Game::Get().dt);
		
	}
   

	return 0;
}