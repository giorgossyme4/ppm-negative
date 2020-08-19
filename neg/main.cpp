#include <iostream>
#include <string>
#include "Image.h"
#include "ppm/ppm.h"



using namespace imaging;

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Enter file name of the image to load : "<< std::endl << "> neg ";
		std::cin >> *argv;
	}

	std::string filename(*argv);
	std::size_t pos = filename.find(".");
	std::string format = filename.substr(pos + 1);

	Image *img = new Image();
	bool loading = img->load(filename, format);

	if (loading) {
		unsigned int w = img->getWidth();
		unsigned int h = img->getHeight();
		std::cout <<"Image dimensions are "<< w <<" x "<<h<< std::endl;
		for (unsigned int x = 0; x < w; x++) {
			for (unsigned int y = 0; y < h; y++) {
				Color pixel = img->getPixel(x, y);
				Color negpixel = Color(1,1,1) - pixel;
				img->setPixel(x, y,negpixel);
			}
		}
		std::string negfilename = filename.substr(0, pos) + "_neg.ppm";
		img->save(negfilename, "ppm");
	}
	std::system("PAUSE");
	delete img;
}


