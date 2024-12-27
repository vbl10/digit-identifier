#include <thread>
#include <iostream>
#include <fstream>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "nn16x16.h"

std::vector<std::pair<matrix<28*28, 1>, char>> train_dataset, test_dataset;

nn16x16 model1;

// Override base class with your custom functionality
class DigitIdentifier : public olc::PixelGameEngine
{
	int image_idx = 0;

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

		if (GetKey(olc::Key::TAB).bPressed)
			image_idx = (image_idx + 1) % 60000;

		for (int y = 0; y < 28; y++)
		{
			for (int x = 0; x < 28; x++)
			{
				char val = test_dataset[image_idx].first[x + y * 28][0];
				Draw({x, y}, olc::Pixel(val, val, val));
			}
		}

		DrawString({0, 30}, std::string(1, "0123456789"[test_dataset[image_idx].second]));

		return true;
	}
};

int main()
{
	/*
	std::thread thread_cmd(
		[](){
			while (1)
			{
				
			}
		}
	);

	thread_cmd.detach();
	*/

	try
	{
		// load train dataset
		{
			std::ifstream train_images_file("/home/vinicius/repos/cpp/digit_identifier/src/assets/train-images.idx3-ubyte", std::ios_base::binary);
			if (!train_images_file.is_open()) throw std::runtime_error("Failed to open file \"/home/vinicius/repos/cpp/digit_identifier/src/assets/train-images.idx3-ubyte\"");
			train_images_file.seekg(16);


			std::ifstream train_labels_file("/home/vinicius/repos/cpp/digit_identifier/src/assets/train-labels.idx1-ubyte", std::ios_base::binary);
			if (!train_labels_file.is_open()) throw std::runtime_error("Failed to open file \"/home/vinicius/repos/cpp/digit_identifier/src/assets/train-labels.idx1-ubyte\"");
			train_labels_file.seekg(8);


			for (int i = 0; i < 60000; i++)
			{
				matrix<28*28, 1> mat;
				for (int j = 0; j < 28 * 28; j++)
				{
					mat[j][0] = (float)train_images_file.get();
				}

				train_dataset.push_back({mat, train_labels_file.get()});
			}

			train_images_file.close();
			train_labels_file.close();
		}

		// load test dataset
{
			std::ifstream test_images_file("/home/vinicius/repos/cpp/digit_identifier/src/assets/t10k-images.idx3-ubyte", std::ios_base::binary);
			if (!test_images_file.is_open()) throw std::runtime_error("Failed to open file \"/home/vinicius/repos/cpp/digit_identifier/src/assets/t10k-images.idx3-ubyte\"");
			test_images_file.seekg(16);


			std::ifstream test_labels_file("/home/vinicius/repos/cpp/digit_identifier/src/assets/t10k-labels.idx1-ubyte", std::ios_base::binary);
			if (!test_labels_file.is_open()) throw std::runtime_error("Failed to open file \"/home/vinicius/repos/cpp/digit_identifier/src/assets/t10k-labels.idx1-ubyte\"");
			test_labels_file.seekg(8);


			for (int i = 0; i < 10000; i++)
			{
				matrix<28*28, 1> mat;
				for (int j = 0; j < 28 * 28; j++)
				{
					mat[j][0] = (float)test_images_file.get();
				}

				test_dataset.push_back({mat, test_labels_file.get()});
			}

			test_images_file.close();
			test_labels_file.close();
		}


		DigitIdentifier demo;
		if (demo.Construct(150, 150, 4, 4))
			demo.Start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	


	return 0;
}
