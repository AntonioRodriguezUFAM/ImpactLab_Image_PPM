
// PPM Image processing  - MultiThreads - Impact Lab 2023

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono> // Timer

using namespace std;
using namespace std::chrono; // Timer


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

    // PPM Images Filter Processing: Invert Colors
    void invertColors() {
        auto start = high_resolution_clock::now(); // Start Timer
        for (int i = 0; i < width * height; i++) {
            Pixel pixel = pixels[i];
            pixel.r = max_color - pixel.r;
            pixel.g = max_color - pixel.g;
            pixel.b = max_color - pixel.b;
            pixels[i] = pixel;
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "---------------  Run Secuential: Invert Color Time:" << duration.count() << "ms" << std::endl;
    }

    // PPM Image Filter processing - Multithreading
    void TheadsinvertColors() {
        const int num_threads = thread::hardware_concurrency();
        vector<thread> threads(num_threads);

        int chunk_size = static_cast<int>(ceil(static_cast<double>(width * height) / num_threads));
        int remaining_pixels = width * height;

        auto start = high_resolution_clock::now();


        for (int i = 0; i < num_threads; i++) {
            int pixels_to_process = min(chunk_size, static_cast<int>(remaining_pixels));
            threads[i] = thread([this, i, pixels_to_process, chunk_size]() {
                int start = i * chunk_size;
                for (int j = start; j < start + pixels_to_process; j++) {
                    Pixel pixel = pixels[j];
                    pixel.r = max_color - pixel.r;
                    pixel.g = max_color - pixel.g;
                    pixel.b = max_color - pixel.b;
                    pixels[j] = pixel;
                }
                });

            remaining_pixels -= pixels_to_process;
            if (remaining_pixels <= 0) {
                break;
            }
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "---------------  Run Parallel: Invert Color Time:" << duration.count() << "ms" << std::endl;
        
    }


};



int main() {

    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "-------------------------- IMPACT LAB 2023: ICOMP - UFAM   -----------" << std::endl;
    std::cout << "--------------------------        TURMA 2023    ----------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------   Programação em Parallel --------------------" << std::endl;
    std::cout << "                       CODE: PPM Image processing in C++                 " << std::endl;
    std::cout << "                         - Secuential VS Parallel -                      " << std::endl;

    std::cout << "                         Prof. Antonio Souto Rodriguez                   " << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    Image image;
    image.loadPPM("image/Image01.ppm");
    std::cout << "--------------------------   Load Images PPM     -------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "----------------------  Run Secuential: Invert Color   ---------------" << std::endl;
    std::cout << std::endl;
    image.invertColors();       // Serial Code
    std::cout << std::endl;
    std::cout << "----------------------  Run Parallel: Invert Color   ---------------" << std::endl;
    std::cout << std::endl;
    image.TheadsinvertColors(); // Parallel Code
    std::cout << std::endl;
    image.savePPM("image/out/Parallel_output01.ppm");
    std::cout << "--------------------------   Save Images PPM     -------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "                               Code: END                  " << std::endl;

    return 0;

}