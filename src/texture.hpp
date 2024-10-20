#pragma once

#include "shader.hpp"
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.hpp"
class Texture{
  public:
    unsigned int ID;

    Texture(std::string texture_path){
      glGenTextures(1, &ID);
      glBindTexture(GL_TEXTURE_2D, ID);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      int width, height, nrChannels;
      unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);


      if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
      } else {
        spdlog::error("Failed to load texture {}", texture_path);
      }

      stbi_image_free(data);

    }

    void use(){
      glBindTexture(GL_TEXTURE_2D, ID);
    }

  private:
    
};
