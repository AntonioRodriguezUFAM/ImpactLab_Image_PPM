// PPM Image processing - Impact Lab 2023

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Pixel 
struct Pixel {
    int r, g, b;
};

// Class Image
class Image {
public:
    int width, height, max_color;
    vector<Pixel> pixels;

    Image() {}

    Image(int w, int h, int m) {
        width = w;
        height = h;
        max_color = m;
        pixels.resize(width * height);
    }

    // Load PPM Images
    void loadPPM(string filename) {
        ifstream infile(filename, ios::binary);
        string magic_number;
        infile >> magic_number >> width >> height >> max_color;
        pixels.resize(width * height);

        for (int i = 0; i < width * height; i++) {
            Pixel pixel;
            infile >> pixel.r >> pixel.g >> pixel.b;
            pixels[i] = pixel;
        }

        infile.close();
    }

    // PPM Image save
    void savePPM(string filename) {
        ofstream outfile(filename, ios::binary);
        outfile << "P6" << endl << width << " " << height << endl << max_color << endl;

        for (int i = 0; i < width * height; i++) {
            Pixel pixel = pixels[i];
            outfile << (unsigned char)pixel.r << (unsigned char)pixel.g << (unsigned char)pixel.b;
        }

        outfile.close();
    }

    // Images Filter: Invert Colors
    void invertColors() {
        for (int i = 0; i < width * height; i++) {
            Pixel pixel = pixels[i];
            pixel.r = max_color - pixel.r;
            pixel.g = max_color - pixel.g;
            pixel.b = max_color - pixel.b;
            pixels[i] = pixel;
        }
    }
};




int main() {

	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "-------------------------- IMPACT LAB 2023 ---------------------------" << std::endl;
	std::cout << "--------------------------  ICOMP - UFAM   ---------------------------" << std::endl;
	std::cout << "--------------------------   TURMA 2023    ---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "--------------------------   Programação em Parallel --------------------" << std::endl;
    std::cout << "                           Code: PPM Image processing in C++             " << std::endl;

	std::cout << "                     Prog. Antonio Souto Rodriguez                    " << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

    Image image;
    image.loadPPM("image/input.ppm");
    std::cout << "--------------------------   Load Images PPM     -------------------" << std::endl;
  

    image.invertColors();

    image.savePPM("image/Outputs/output.ppm");
    std::cout << "--------------------------   Save Images PPM     -------------------" << std::endl;
    std::cout<<std::endl;
    std::cout << "                               Code: END                  " << std::endl;

	return 0;

}