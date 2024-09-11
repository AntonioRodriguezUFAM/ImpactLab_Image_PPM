#include<iostream>
#include<fstream>

// Converte String to Int
#include<sstream>
/*
- ifstream is input file stream which allows you to read the contents of a file. 
- ofstream is output file stream which allows you to write contents to a file. 
- fstream allows both reading from and writing to files by default.

*/
using namespace std;

int main() {
	ifstream image;
	//ofstream image2;
	ofstream newimage;

	image.open("Imge.ppm");
	//image2.open("img2.ppm");
	newimage.open("NewImage.ppm");

	// Copy over header Information
	string type = "", width = "", height = "", RGB = "";
	image >> type;
	image >> width;
	image >> height;
	image >> RGB;

	//cout << type << width << height << RGB << endl;

	// Copy new images
	newimage << type << endl;
	newimage << width << "" << height << endl;
	newimage << RGB << endl;
	string red = "", greem = "", blue = "";
	int r = 0, g = 0, b = 0;

	while (!image.eof()) {
		image >> red;
		image >> greem;
		image >> blue;

		//int number = stoi("12")

		// Converte String to number
		stringstream redstream(red);
		stringstream greemstream(greem);
		stringstream bluestream(blue);

		redstream >> r;
		greemstream >> g;
		bluestream >> b;

		// add the blue filter
		if (b + 50 >= 255) {
			b = 255;
		}
		else {
			b += 50;
		}
		newimage << r << "" << g << "" << b << endl;

	}
	image.close();
	//image2.close();
	newimage.close();

	
		if (image2.is_open()) {
			// place header info
			image2 << "P3" << endl;
			image2 << "250 250" << endl;
			image2 << "255" << endl;

			for (int y = 0; y < 250; y++) {
				for (int x = 0; x < 250; x++) {
				//	image << x << " " << x << " " << x << endl;
					// Max 255 - (x*y)> 255!!
					image2 << (x *y)%255 << " " << (x + y) % 255 << " " << (x * 2) % 255 << endl;
				}
			}
		}
		image2.close();

		return 0;
		
}