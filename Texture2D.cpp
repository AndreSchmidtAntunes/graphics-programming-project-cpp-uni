#include "GLLibs.h"
#include "Texture2D.h"
#include <fstream>
#include <iostream>

const Texture2D* Texture2D::FromFile(const char* file_path, const size_t width, const size_t height)
{
    Texture2D* texture = new Texture2D();
    if (texture->LoadFile(file_path, width, height)) {
        return texture;
    }
    else {
        delete texture;
        return nullptr;
    }
}

#undef SIZE_TYPE

const bool Texture2D::LoadFile(const char* file_path, const size_t width, const size_t height)
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
        fileSize = inFile.tellg();
        tempTextureData = new char[fileSize];

        inFile.seekg(0, std::ios::beg);
        inFile.read(tempTextureData, fileSize);

    inFile.close();

    glGenTextures(1, &_ID);

    if (!glIsTexture(_ID)) {
        std::cerr << "[GL] Failed to generate texture name for file: " << file_path << std::endl;
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, _ID);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

    delete[fileSize] tempTextureData;

    return true;
}
