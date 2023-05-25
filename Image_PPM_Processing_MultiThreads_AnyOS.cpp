// PPM Image processing - MultiThreads - Impact Lab 2023
/*
This code should now be compatible with both Windows and Linux operating systems. 
It uses preprocessor directives to include the necessary headers and handle system-specific functions
*/

/*
added the opticFlow function to perform the Optic Flow algorithm for motion detection.
The function is called after inverting the colors of the image. The main function now includes the execution of the opticFlow function and waits for user input before exiting the program, depending on the operating system
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


   // Optic Flow - Motion Detection Secuential 
    void opticFlow() {
        auto start = high_resolution_clock::now(); // Start Timer

        // Define parameters for optic flow calculation
        int windowSize = 5; // Size of the neighborhood window
        double threshold = 10.0; // Threshold for motion detection

        // Create a new image to store the motion vectors
        Image motionVectors(width, height, 255);

        // Iterate over the image pixels
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // Calculate motion vector for each pixel
                int sumX = 0, sumY = 0;
                int count = 0;

                // Iterate over the neighborhood window
                for (int i = -windowSize; i <= windowSize; i++) {
                    for (int j = -windowSize; j <= windowSize; j++) {
                        int nx = x + i;
                        int ny = y + j;

                        // Check if the neighboring pixel is within the image bounds
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            // Calculate the difference between pixel values
                            int dx = pixels[ny * width + nx].r - pixels[y * width + x].r;
                            int dy = pixels[ny * width + nx].g - pixels[y * width + x].g;

                            // Accumulate the motion vectors
                            sumX += dx;
                            sumY += dy;
                            count++;
                        }
                    }
                }

                // Calculate the average motion vector
                int avgX = sumX / count;
                int avgY = sumY / count;

                // Mark the pixel as motion if the motion vector exceeds the threshold
                if (sqrt(avgX * avgX + avgY * avgY) > threshold) {
                    motionVectors.pixels[y * width + x].r = 255; // Set red channel to 255
                    motionVectors.pixels[y * width + x].g = 0;   // Set green channel to 0
                    motionVectors.pixels[y * width + x].b = 0;   // Set blue channel to 0
                }
            }
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "---------------  Run Optic Flow: Motion Detection Time: " << duration.count() << "ms" << endl;

        // Save the motion vectors image
        motionVectors.savePPM("image/out/MotionVectors.ppm");
    }

    // Optic Flow - Motion Detection MultiThreads
    void opticFlowThread() {
        auto start = high_resolution_clock::now(); // Start Timer

        // Define parameters for optic flow calculation
        int windowSize = 5; // Size of the neighborhood window
        double threshold = 10; // Threshold for motion detection

        // Create a new image to store the motion vectors
        Image motionVectors(width, height, 255);

        // Define the number of threads to use
        int num_threads = thread::hardware_concurrency();
        vector<thread> threads(num_threads);

        // Calculate the number of pixels to process per thread
        int chunk_size = static_cast<int>(ceil(static_cast<double>(width * height) / num_threads));

        // Function to calculate optic flow for a range of pixels
        auto calculateOpticFlow = [this, windowSize, threshold, &motionVectors](int start, int end) {
            // Iterate over the range of pixels
            for (int index = start; index < end; index++) {
                int x = index % width;
                int y = index / width;

                // Calculate motion vector for each pixel
                int sumX = 0, sumY = 0;
                int count = 0;

                // Iterate over the neighborhood window
                for (int i = -windowSize; i <= windowSize; i++) {
                    for (int j = -windowSize; j <= windowSize; j++) {
                        int nx = x + i;
                        int ny = y + j;

                        // Check if the neighboring pixel is within the image bounds
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            // Calculate the difference between pixel values
                            int dx = pixels[ny * width + nx].r - pixels[y * width + x].r;
                            int dy = pixels[ny * width + nx].g - pixels[y * width + x].g;

                            // Accumulate the motion vectors
                            sumX += dx;
                            sumY += dy;
                            count++;
                        }
                    }
                }

                // Calculate the average motion vector
                int avgX = sumX / count;
                int avgY = sumY / count;

                // Mark the pixel as motion if the motion vector exceeds the threshold
                if (sqrt(avgX * avgX + avgY * avgY) > threshold) {
                    motionVectors.pixels[y * width + x].r = 255; // Set red channel to 255
                    motionVectors.pixels[y * width + x].g = 0;   // Set green channel to 0
                    motionVectors.pixels[y * width + x].b = 0;   // Set blue channel to 0
                }
            }
        };

        // Start the threads to calculate optic flow for different ranges of pixels
        for (int i = 0; i < num_threads; i++) {
            int start = i * chunk_size;
            int end = start + chunk_size;
            if (i == num_threads - 1) {
                end = width * height; // Last thread handles any remaining pixels
            }
            threads[i] = thread(calculateOpticFlow, start, end);
        }

        // Wait for all threads to finish
        for (auto& thread : threads) {
            thread.join();
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "---------------  Run Optic Flow Threads: Motion Detection Time: " << duration.count() << "ms" << endl;

        // Save the motion vectors image
        motionVectors.savePPM("image/out/MotionVectorsThread01.ppm");
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
    image.loadPPM("image/sample_5184×3456.ppm");
    cout << "--------------------------   Load Images PPM     -------------------" << endl;
    cout << endl;

    cout << "----------------------  Run Sequential: Invert Color   ---------------" << endl;
    cout << endl;
    image.invertColors();       // Serial Code
    cout << endl;
    // Save images
    image.savePPM("image/out/Parallel_outputserial.ppm");
    cout << "----------------------  Run Parallel: Invert Color   ---------------" << endl;
    cout << endl;
    image.ThreadsInvertColors(); // Parallel Code
    cout << endl;
    

    cout << "----------------------  RunSequential: Optic Flow Motion Detection   ---------------" << endl;
    cout << endl;
    image.opticFlow(); // Optic Flow - Motion Detection Secuential
    cout << endl;


    cout << "-------------- Run Parallel: Optic Flow Motion Detection   --------------" << endl;
    cout << endl;
    image.opticFlowThread(); // Optic Flow - Motion Detection Multithreads
    cout << endl;


    // Save images
    image.savePPM("image/out/Parallel_output.ppm");
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

