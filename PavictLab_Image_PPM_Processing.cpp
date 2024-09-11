// PPM Image processing - Pavic Lab 2023 - Turma 01

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

//
//// Load Images - Read like std::Cin
//void Readimage()
//{
//    ifstream imageIn;
//    imageIn.open("image/Input.ppm");
//    imageIn.close();
//}
//
//void writeimage()
//{//ofstream image2; like std::Cout
//    ofstream newimage;
//    newimage.open("NewImage.ppm");
//    newimage.close();
//
//}
//// Read Header Images
//void ReadimageHeader()
//{
//
//    Readimage();
//    if (image2.is_open()) {
//        // place header info
//        image2 << "P3" << endl;
//        image2 << "250 250" << endl;
//        image2 << "255" << endl;
//
//}

// Read Body Image

// Save Images


int main() {

    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "------------------------         PAVIC LAB 2023            ------------" << std::endl;
    std::cout << "------------------------            UFAC                   ------------" << std::endl;
    std::cout << "------------------------          TURMA 2023               ------------" << std::endl;
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
    Image image;
    image.loadPPM("image/input.ppm");
    std::cout << "------------------------     Load Images PPM   ---------------------" << std::endl;
    std::cout << "***********************************************************************" << std::endl;

    std::cout << "------------------------  Filter: Invert ColorImages PPM   ----------" << std::endl;
    image.invertColors();
    std::cout << "***********************************************************************" << std::endl;


    image.savePPM("image/Outputs/output.ppm");
    std::cout << "--------------------------   Save Images PPM     -------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "***********************************************************************" << std::endl;
    std::cout << "                               Code: END                            " << std::endl;

    return 0;

}