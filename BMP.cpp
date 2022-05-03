#include "BMP.h"

BMP::BMP(string nomImage)
{
    lireImage(nomImage);
}

BMP::BMP(int largeur, int hauteur)
{
    infoHeader.width = largeur;
    infoHeader.height = hauteur;

    infoHeader.size = sizeof(infoHeader) + sizeof(colorHeader);
    fileHeader.offset = sizeof(fileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
    infoHeader.bit_count = 32;
    infoHeader.compression = 3;
    row_stride = largeur * 4;
    data.resize(row_stride * hauteur);
    fileHeader.file_size = fileHeader.offset + data.size();
         
}

void BMP::write(string nomImage)
{
    ofstream outImage{ nomImage, ios_base::binary };
    if (outImage)
    {
        outImage.write((char*)&fileHeader, sizeof(fileHeader));
        outImage.write((char*)&infoHeader, sizeof(infoHeader));
        outImage.write((char*)&colorHeader, sizeof(colorHeader));
        outImage.write((char*)data.data(), data.size());
    }
}

void BMP::remplir()
{
    for (int i = 0; i < data.size(); i += 4)
    {
        data[i] = 255;
        data[i + 1] = 255;
        data[i + 2] = 255;
        data[i + 3] = 255;
    }
}

void BMP::rectangle(uint32_t positionX, uint32_t positionY, uint32_t hauteur, uint32_t largeur)
{
    uint32_t index{ 0 };
    uint32_t pixel = infoHeader.bit_count / 8;
    for (uint32_t y = positionY; y < positionY + hauteur; y++)
    {
        for (uint32_t x = positionX; x < positionX + largeur; x++)
        {
            index = (y * infoHeader.width) + x;
            data[pixel * index] = 0;
            data[pixel * index + 1] = 0;
            data[pixel * index + 2] = 0;
            data[pixel * index + 3] = 255;
        }
    }
}

void BMP::filtreNegatif()
{
    for (int i = 0; i < data.size(); i += 4)
    {
        data[i] = ~data[i];
        data[i + 1] = ~data[i + 1];
        data[i + 2] = ~data[i + 2];
        data[i + 3] = 255;
    }
}

void BMP::flou()
{
}

void BMP::steganographe(string)
{
}


void BMP::lireImage(string nomImage)
{
    ifstream image{ nomImage, ios::in | ios::binary };
    if (image.is_open())
    {
        image.read((char*)&fileHeader, sizeof(fileHeader));
        image.read((char*)&infoHeader, sizeof(infoHeader));
        image.read((char*)&colorHeader, sizeof(colorHeader));

        image.seekg(fileHeader.offset, image.beg);

        if (infoHeader.bit_count == 32) {
            infoHeader.size = sizeof(infoHeader) + sizeof(colorHeader);
            fileHeader.offset = sizeof(fileHeader) + sizeof(infoHeader) + sizeof(colorHeader);
                
        }
        else {
            infoHeader.size = sizeof(infoHeader);
            fileHeader.offset = sizeof(fileHeader) + sizeof(infoHeader);

        }
        fileHeader.file_size = fileHeader.offset;

        data.resize(infoHeader.width * infoHeader.height * infoHeader.bit_count / 8);

        
        image.read((char*)data.data(), data.size());
        fileHeader.file_size += data.size();

        image.close();
    }
}
