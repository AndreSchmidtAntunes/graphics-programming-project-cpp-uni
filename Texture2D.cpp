#include "GLLibs.h"
#include "Texture2D.h"
#include <fstream>
#include <iostream>

#define SIZE_TYPE size_t

const Texture2D* Texture2D::Load(const char* path, const SIZE_TYPE width, const SIZE_TYPE height)
{
    Texture2D* new_tex_pointer = new Texture2D();
    new_tex_pointer->width = width;
    new_tex_pointer->height = height;

    char* tempTextureData; std::ifstream inFile; size_t fileSize;
    inFile.open(path, std::ios::binary);

        if (!inFile.good()) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return nullptr;
        }

        inFile.seekg(0, std::ios::end);
        fileSize = inFile.tellg(); 
        tempTextureData = new char[fileSize];

        inFile.seekg(0, std::ios::beg);
        inFile.read(tempTextureData, fileSize);

    inFile.close();

    glGenTextures(1, &(new_tex_pointer->_ID));

    glBindTexture(GL_TEXTURE_2D, new_tex_pointer->_ID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

    delete[fileSize] tempTextureData;

    return new_tex_pointer;
}

#undef SIZE_TYPE