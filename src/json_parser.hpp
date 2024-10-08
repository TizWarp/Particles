#pragma once

#include <string>
#include <vector>
struct Interaction{
  std::string name;
  float strength;
};


class JsonParser{
  public:
    JsonParser(std::string filename);
    bool parseFile();
    void loadInteractions();
  private:
    std::string filename;
    std::vector<Interaction> interactions;
};
