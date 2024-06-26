#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

int main() {
    string location;
    Image imageFile;

    if (!imageFile.loadFromFile("")) {
        cout << "Failed to load File from " << location << endl;
   }

    return 0;
}