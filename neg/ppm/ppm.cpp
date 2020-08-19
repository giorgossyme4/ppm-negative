#include "ppm.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>




float * imaging::ReadPPM(const char * filename, int * w, int * h) {

	std::ifstream file(filename, std::ios::binary);



	if (!file.is_open()) {
		printf("Error opening\n");
		return 0;
	}

	std::string header;
	int b;
	file >> header;

	if (strcmp(header.c_str(), "P6") != 0) {
		printf("The PPM file isn't a P6 type..!!\n");
		return 0;
	}

	char c;
	file >> *w >> *h >> b >> c;

	if (*w == 0) {
		printf("The width is missing");
		return 0;
	}
	if (*h == 0) {
		printf("The heigth is missing");
		return 0;
	}

	if ((b > 255) || (b == 0)) {
		printf("The highest permitted value is wrong!");
		return 0;
	}

	int length = 3 * *w * *h;
	char *temp = new char[length];
	float *data = new float[length];

	file.read(reinterpret_cast<char *>(temp), length);
	for (int i = 0; i < length; i++) {
		data[i] = (float)temp[i] / 255.0f;
	}

	file.close();
	return data;

}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {

	std::ofstream ofile(filename, std::ios::binary);
	ofile << "P6" << std::endl << w << std::endl << h << std::endl << "255\n" << std::endl;


	for (int i = 0; i < 3 * w * h; i++) {
		int temp = data[i] * 255;
		ofile.write(reinterpret_cast<char*>(&temp), 1);
	}

	ofile.clear();
	ofile.close();
	return true;

}


	

	


