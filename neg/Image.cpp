#include <iostream>
#include "Color.h"
#include <string>
#include "Image.h"
#include <fstream>
#include "ppm\ppm.h"

using namespace imaging;
using namespace std;


	Color * Image::getRawDataPtr() {
		return buffer;
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const {
		if ((x > width) || (y > height)){			
		   return Color();
        }
		return buffer[x + width * y];
		
	}

	void Image::setPixel(unsigned int x, unsigned int y, Color & value) { //elegxos an to x kai to y einai stis times pou thelw
		if ((x > width) || (y > height)) {
			return;
		}
		
		buffer[x + width * y] = value;
	}

	void Image::setData(const Color * & data_ptr) { //w = 0 h=0 buffer = ptr
		if ((width = 0) || (height = 0) || (buffer == nullptr)) {
			return;
		}
		*buffer = *data_ptr;


	}

	Image::Image() {
		width = 0;
		height = 0;
		buffer = nullptr;
	}


	Image::Image(unsigned int width, unsigned int height) {
		this->width = width;
		this->height = height;
		buffer = nullptr;
	}

	Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) {
		this->width = width;
		this->height = height;
		setData(data_ptr);
	}

	Image::Image(const Image &src) {
		width = src.width;
		height = src.height;
		buffer = src.buffer;
	}

	Image::~Image() {
		std::cout << "Destructor Called " << std::endl;
		delete[] buffer;
	}

	Image & Image::operator = (const Image & right) {
		int size = width * height;
		int n_size = right.width * right.height;
		if (size != n_size) {
			delete[] buffer;
			size = n_size;
			buffer = new Color[size];
		}

		this->width = right.width;
		this->height = right.height;
		this->buffer = right.buffer;
		
		return *this;
	}	

	bool Image::load(const std::string & filename, const std::string & format) {
		if (format == "ppm") {
			int w = 0;
			int h = 0;
			float *array = imaging::ReadPPM(filename.c_str(), &w, &h);
			width =w;
			height =h;
			if (array == nullptr) { return false; }
			delete[] buffer;
			buffer = new Color[width*height];
			float r, g, b;
			int j = 0;
			for (unsigned int i = 0; i < 3 * width * height; i = i + 3){
			    r = array[i];
			    g = array[i + 1];
			    b = array[i + 2];
			    buffer[j] = Color(r, g, b);
				j++;
			}
			
			return true;
		}
		else {
			return false; }
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		if (format == "ppm") {
			float *sarray = new float[width * height * 3];
			if (buffer == nullptr) { return false; }
			int j = 0;
			for (unsigned int i = 0; i < width * height * 3; i = i + 3) {
				
				sarray[i] = buffer[j].r;
				sarray[i + 1] = buffer[j].g;
				sarray[i + 2] = buffer[j].b;
				j++;
			}
			bool saving = imaging::WritePPM(sarray, width, height, filename.c_str());
			if (saving = true) {
				return true;
			} else {
				return false;
			}
		} else { return false; }
	}

	
	