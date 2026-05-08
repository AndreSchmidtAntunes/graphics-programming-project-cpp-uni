#include "GLLibs.h"
#include "Texture2D.h"
#include <fstream>
#include <iostream>

const bool Texture2D::LoadRawData(const char* data, const size_t width, const size_t height, const char* file_path = nullptr)
{
	glGenTextures(1, &_ID);

	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	if (!glIsTexture(_ID)) {
		std::cerr << "[GL] Failed to generate texture name for file: " << ((file_path) ? file_path : "FILE PATH UNDEFINED") << std::endl;
		return false;
	}

	delete[] data;

	return true;
}



const bool Texture2D::LoadFileRAW(const char* file_path, const size_t width, const size_t height)
{
    if (_ID != 0) // if there is already a texture stored here, de-allocated it.
        glDeleteTextures(1, &_ID);

    Texture2D* texture = new Texture2D();
    this->width = width;
    this->height = height;

    char* tempTextureData; std::ifstream inFile; size_t fileSize;
    inFile.open(file_path, std::ios::binary);

    if (!inFile.good()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return false;
    }

    inFile.seekg(0, std::ios::end);
    fileSize = (int)inFile.tellg();
    tempTextureData = new char[fileSize];

    inFile.seekg(0, std::ios::beg);
    inFile.read(tempTextureData, fileSize);

    inFile.close();

	return LoadRawData(tempTextureData, width, height, file_path);
}


// Below I Have taken the bmp file loader we were provided and I have changed to to return a char* intead of writing to a file.
// Using this I can load .bmp files at runtime.

typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

struct bmpfile_ft {
	unsigned char magic[2];
};

struct bmpfile_header {
	uint32_t filesz;
	uint16_t creator1;
	uint16_t creator2;
	uint32_t bmp_offset;
};

static BITMAPINFOHEADER bitMapInfo;

struct bmp_colour {
	unsigned char b, g, r;
};

char* loadBitMap(const char* fileName, size_t *out_width, size_t *out_height) {
	bmpfile_ft magic;
	bmpfile_header header;
	int row, col;
	bmp_colour* image_buffer;

	FILE* inFile;
	inFile = fopen(fileName, "rb");
	
	if (inFile == NULL)
	{
		printf("\ncan't open input %s\n", fileName);
		exit(1);
	}
	printf("\nOpened file\n");
	fread(&magic, sizeof(bmpfile_ft), 1, inFile);
	fread(&header, sizeof(bmpfile_header), 1, inFile);
	fread(&bitMapInfo, sizeof(BITMAPINFOHEADER), 1, inFile);
	if (bitMapInfo.biWidth != bitMapInfo.biHeight)
	{
		printf("\nBitmap is not square\n");
		exit(1);
	}

	*out_width = bitMapInfo.biWidth;
	*out_height = bitMapInfo.biHeight;

	image_buffer = (bmp_colour*)malloc(sizeof(bmp_colour) * bitMapInfo.biWidth);
	char* tempTextureData = new char[bitMapInfo.biWidth * bitMapInfo.biHeight * 3];
	for (row = 0; row < bitMapInfo.biHeight; row++) {
		fread(image_buffer, sizeof(bmp_colour), bitMapInfo.biWidth, inFile);
		for (col = 0; col < bitMapInfo.biWidth; col++)
		{
			size_t colour_index = (row * bitMapInfo.biWidth + col) * 3;
			tempTextureData[colour_index + 0] = image_buffer[col].r;
			tempTextureData[colour_index + 1] = image_buffer[col].g;
			tempTextureData[colour_index + 2] = image_buffer[col].b;
		}
	}

	fclose(inFile);
	free(image_buffer);

	return tempTextureData;
}

const bool Texture2D::LoadFileBMP(const char* file_path) {
	char* raw_data = loadBitMap(file_path, &width, &height);
	return LoadRawData(raw_data, width, height, file_path);
}

Texture2D* Texture2D::FromFileRAW(const char* file_path, const size_t width, const size_t height)
{
	Texture2D* texture = new Texture2D();
	if (texture->LoadFileRAW(file_path, width, height)) {
		return texture;
	}
	else {
		delete texture;
		return nullptr;
	}
}

 Texture2D* Texture2D::FromFileBMP(const char* file_path)
{
	Texture2D* texture = new Texture2D();
	if (texture->LoadFileBMP(file_path)) {
		return texture;
	}
	else {
		delete texture;
		return nullptr;
	}
}