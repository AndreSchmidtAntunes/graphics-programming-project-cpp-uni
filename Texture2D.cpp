#include "GLLibs.h"
#include "Texture2D.h"
#include <fstream>
#include <iostream>

#define SIZE_TYPE size_t

const Texture2D* Texture2D::Load(const char* path, const SIZE_TYPE width, const SIZE_TYPE height)
{

    std::ifstream inFile(path, std::ios::binary);

        if (!inFile.good()) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return nullptr;
        }

        Texture2D* new_tex_pointer = new Texture2D();
        new_tex_pointer->width = width;
        new_tex_pointer->height = height;

        inFile.seekg(0, std::ios::end);
        size_t fileSize = inFile.tellg(); 

        char* tempTextureData = new char[fileSize];

        inFile.seekg(0, std::ios::end);
        inFile.read(tempTextureData, fileSize);

    inFile.close();

    glGenTextures(1, &(new_tex_pointer->_ID));
    glBindTexture(GL_TEXTURE_2D, new_tex_pointer->_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete[] tempTextureData;

    return new_tex_pointer;
}

#undef SIZE_TYPE