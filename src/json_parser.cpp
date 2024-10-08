#include "json_parser.hpp"
#include "particle.hpp"
#include <cstdio>
#include <fstream>
#include <ios>
#include <string>

JsonParser::JsonParser(std::string filename) { this->filename = filename; }

bool JsonParser::parseFile() {
  std::ifstream file_stream(filename);

  std::string section;
  file_stream >> section;
  section.erase(0, 1);
  section.erase(section.find('"'), section.size() - 1);
  printf("%s\n", section.c_str());

  if (section == "interactions") {
    std::string name;
    while (file_stream >> name) {
      if (name.size() < 1){
        return true;
      }
      name.erase(0, 1);
      name.erase(name.size() - 1, 1);

      file_stream.ignore(2);

      float strength;
      file_stream >> strength;

      Interaction interaction{};
      interaction.name = name;
      interaction.strength = strength;
      interactions.push_back(interaction);

      printf("%s : %f\n", name.c_str(), strength);

      file_stream.ignore(2);
    }
  }

  return true;
}

void JsonParser::loadInteractions(){
  for (Interaction interaction : interactions){
    Particle::InteractionForcesMap[interaction.name] = interaction.strength;
  }
}
