// PPM image Impact lab 2024


#include <iostream>
#include <fstream>
/*
- ifstream is input file stream which allows you to read the contents of a file.
- ofstream is output file stream which allows you to write contents to a file.
- fstream allows both reading from and writing to files by default.

*/
using namespace std;


int main() {
	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------         IMPACT LAB 2024            ------------" << std::endl;
	std::cout << "------------------------            UFAM                   ------------" << std::endl;
	std::cout << "------------------------          TURMA 2024               ------------" << std::endl;
	std::cout << "***********************************************************************" << std::endl;
	std::cout << "***********************************************************************" << std::endl;

	std::cout << std::endl;
	std::cout << "------------------------   Programacao em Parallel         ------------" << std::endl;
	std::cout << "------------------------ Code: PPM Image processing in C++ ------------" << std::endl;

	std::cout << "########################    Prog. Antonio Souto Rodriguez  ############ " << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;


	std::cout << "------------------------       MAIN PROGRAM   -------------------------" << std::endl;
	std::cout << "***********************************************************************" << std::endl;


	std::cout << "------------------------     TASK 1: Images PPM   ---------------------" << std::endl;
	std::cout << "***********************************************************************" << std::endl;
	// Task 1: file name: image_2024.ppm


	// Task 1: read Image // imageout
	// Task 2: write Image // imagein
	// Task 3: save Image

	std::ofstream imagein; // Write images = std::cin
	std::ifstream imageout; // Read image = std::cout
	imagein.open("image/imageCopy.ppm");

	// Read Image
	imageout.open("image/teapot.ppm");
	string P3, size, valueMax;
	if (imageout.is_open()) {
		imageout >> P3; // Formato P3
		imageout >> size ; // tamanho da Image
		imageout >> valueMax; // 0 - 255

	}

	// Task 2: write Image // imagein
	//P3 = "P3";
		imagein << P3;


	/* Header
	P3
	1920 1080
	W H
	Valor: 0 - 255


	imagein.open("image/image_2024_05.ppm");



	// Task 1: read Image // imageout

	// Task 2:  PPM Header

	/* Header
	P3
	1920 1080
	W H
	Valor: 0 - 255
	*/
	std::cout << "------------------------  TASK 2:  Create PPM Header    ----------" << std::endl;
	std::cout << "***********************************************************************" << std::endl;

	cout << " Task 2:  PPM Header" << endl;

	if (imagein.is_open()) {
		std::cout << "Header" << std::endl;
		imagein << "P3" << std::endl; // Formato P3
		imagein << "10 10" << std::endl; // tamanho da Image
		imagein << "255" << std::endl; // 0 - 255

		int 33 ou 
			string 


	}



	std::cout << "------------------------     TASK 3: Create PPM Body   ---------------------" << std::endl;
	std::cout << "***********************************************************************" << std::endl;
	// Task 3: PPM Body
	cout << "Task 3: PPM Body" << endl;
	// 255 0 0 RGB- Red 
	//imagein << "255 0 0" << endl; // red
	//imagein << "0 255 0" << endl; // G
	//imagein << "0 0 255" << endl; // B
	//imagein << "255 255 0" << endl; // Y
	//imagein << "255 255 255" << endl; // W
	//imagein << "0 0 0" << endl; // B



	// Across the images W H
	// Pixel RGB
	int red = 0;
	int green = 0;
	int blue = 0;

	int W = 150;
	int H = 100;
	// 2MB


	for (int w = 0; w < W; w++) {
		for (int h = 0; h < H;h++) {
			red = w * 50;
			green = h * 10;
			blue = (w + h) * 15;

			if (h > 20) {
				imagein << h << " " << green << " " << blue << " ";
			}
			if (h > 50) {
				imagein << w << " " << green << " " << blue << " ";
			}


			//imagein << "255 0 0" << endl; // red
		}
		imagein << std::endl;
	}


	imagein.close();

	std::cout << "***********************************************************************" << std::endl;
	std::cout << "                               Code: END                            " << std::endl;
	return 0;
}