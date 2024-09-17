#include <thread>
#include <iostream>
#include "nn16x16.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

nn16x16 model1;

// Override base class with your custom functionality
class DigitIdentifier : public olc::PixelGameEngine
{
public:
	DigitIdentifier()
	{
		// Name your application
		sAppName = "DigitIdentifier";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		Clear(olc::BLACK);
		DrawString({10, 10}, "coe maluco");
		return true;
	}
};

int main()
{
	std::thread thread_cmd(
		[](){
			while (1)
			{
				
			}
		}
	);

	thread_cmd.detach();

	DigitIdentifier demo;
	if (demo.Construct(150, 150, 4, 4))
		demo.Start();

	return 0;
}
