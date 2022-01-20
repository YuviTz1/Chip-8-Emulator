#include<chrono>
#include<iostream>
#include<string>
#include"renderer.h"
#include"Chip8.h"

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <Delay> <ROM>\n";
		std::exit(EXIT_FAILURE);
	}

	// the chip-8 has no standard clock speed so control game speed using this(in milliseconds)
	int cycleDelay = std::stoi(argv[1]);
	std::string romFilename = argv[2];
	
	renderer OpenGl_renderer;
	Chip8 chip8;
	chip8.LoadROM(romFilename);

	// for keeping track of time since last frame
	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	
	while (!glfwWindowShouldClose(OpenGl_renderer.window))
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		
		if (dt > cycleDelay)			// only process the next instruction if a set amount of time has passed
		{
			lastCycleTime = currentTime;
			chip8.Cycle();
			OpenGl_renderer.updateQuad(chip8.video, chip8.keypad);			
		}
	}

	return 0;
}