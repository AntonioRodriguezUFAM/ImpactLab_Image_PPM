// PPM Image processing - Pavic Lab 2023 - Turma 01


#include<iostream>
#include<fstream>

using namespace std;



int main() {

    // Call program Header
    programHeader();  

    std::cout << "------------------------       MAIN PROGRAM   -------------------------" << std::endl;
    std::cout << "***********************************************************************" << std::endl;
    
    // Load Images - Read like std::Cin
    ofstream imageIn;
    //ofstream image2; like std::Cout
    ofstream newimage;

    imageIn.open("image/Input.ppm");
    newimage.open("NewImage.ppm");
    
    imageIn.close();
    newimage.close();

    std::cout << "------------------------     Load Images PPM   ---------------------" << std::endl;
    std::cout << "***********************************************************************" << std::endl;

    std::cout << "------------------------  Header: Image PPM   ----------" << std::endl;
    if (imageIn.is_open()) {
        // place header info
        imageIn << "P3" << endl;
        imageIn << "250 250" << endl;
        imageIn << "255" << endl;

    }
    std::cout << "***********************************************************************" << std::endl;


    std::cout << "--------------------------   Save Images PPM     -------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "***********************************************************************" << std::endl;
    std::cout << "                               Code: END                            " << std::endl;



    





    return 0;

}



void programHeader( void) {
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
}

