// PPM Image processing - MultiThreads - Impact Lab 2023
/*
This code should now be compatible with both Windows and Linux operating systems. 
It uses preprocessor directives to include the necessary headers and handle system-specific functions
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono> // Timer

#ifdef _WIN32
#include <windows.h> // Header for Windows OS
#else
#include <unistd.h> // Header for Linux OS
#endif

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
        cout << "---------------  Run Sequential: Invert Color Time:" << duration.count() << "ms" << endl;
    }

    // PPM Image Filter processing - Multithreading
    void ThreadsInvertColors() {
        int num_threads = thread::hardware_concurrency();
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
        cout << "---------------  Run Parallel: Invert Color Time:" << duration.count() << "ms" << endl;
    }
};

int main() {
    cout << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "-------------------------- IMPACT LAB 2023: ICOMP - UFAM   -----------" << endl;
    cout << "--------------------------        TURMA 2023    ----------------------" << endl;
    cout << endl;
    cout << "--------------------------   Programação em Parallel --------------------" << endl;
    cout << "                       CODE: PPM Image processing in C++                 " << endl;
    cout << "                         - Sequential VS Parallel -                      " << endl;
    cout << "                         Prof. Antonio Souto Rodriguez                   " << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << endl;

    Image image;
    image.loadPPM("image/Image01.ppm");
    cout << "--------------------------   Load Images PPM     -------------------" << endl;
    cout << endl;

    cout << "----------------------  Run Sequential: Invert Color   ---------------" << endl;
    cout << endl;
    image.invertColors();       // Serial Code
    cout << endl;
    cout << "----------------------  Run Parallel: Invert Color   ---------------" << endl;
    cout << endl;
    image.ThreadsInvertColors(); // Parallel Code
    cout << endl;
    image.savePPM("image/out/Parallel_output01.ppm");
    cout << "--------------------------   Save Images PPM     -------------------" << endl;
    cout << endl;
    cout << "                               Code: END                  " << endl;

#ifdef _WIN32
    system("pause");
#else
    cout << "Press Enter to continue...";
    cin.ignore();
#endif

    return 0;
}

