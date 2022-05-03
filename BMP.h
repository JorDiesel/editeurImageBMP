#pragma once
#include "Headers.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class BMP
{
public:
	BMP(string);
	BMP(int, int);
	void lireImage(string);
	void write(string);
	void remplir();
	void rectangle(uint32_t positionX, uint32_t positionY, uint32_t hauteur, uint32_t largeur);
	void filtreNegatif();
	void flou();
	void steganographe(string);
private:
	vector<uint8_t> data{};
	BMPFilheader fileHeader;
	BMPInfoHeader infoHeader;
	BMPColorHeader colorHeader;
	uint32_t row_stride{ 0 };
};

