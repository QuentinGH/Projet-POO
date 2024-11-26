#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>

int main() {
    std::cout << "You may enter the value of the grid's height and width (one after the other with a space between them): " << std::endl;
    std::pair<int, int> values;
    
    std::string line;
    std::getline(std::cin, line); // Lire toute la ligne d'entrée
    
    std::stringstream ss(line); // Créer un flux de chaîne pour analyser la ligne
    ss >> values.first >> values.second; // Extraire les deux entiers
    
    std::cout << "\nYour values are :"
         << "\n- Height : " << values.first
         << "\n- Width : " << values.second << std::endl;
    return 0;
}
