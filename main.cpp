#include <iostream>
#include <vector>

#include "type_map.h"

enum PlanetCharacteristics{ Name, Aphelion, Perihelion, Radius, Satellites };

using Planet = type_map<key_value<Name,       std::string>,
                        key_value<Aphelion,   float>,
                        key_value<Perihelion, float>,
                        key_value<Radius,     float>,
                        key_value<Satellites, std::vector<std::string>>>;

std::ostream& operator<<(std::ostream& out, Planet& planet)
{
    out << "Name:\t"       << get<Name>      (planet) << std::endl;
    out << "Aphelion:\t"   << get<Aphelion>  (planet) << std::endl;
    out << "Perihelion:\t" << get<Perihelion>(planet) << std::endl;
    out << "Radius:\t"     << get<Radius>    (planet) << std::endl;
    out << "Satellites" << std::endl;
    for(const auto& i : get<Satellites>(planet)){
        out << "\t" << i << std::endl;
    }
    return out;
}

int main()
{

    Planet mars;
    get<Name>(mars) = "Mars";
    get<Aphelion>(mars) = 1.666;
    get<Perihelion>(mars) = 1.381;
    get<Radius>(mars) = 3389.5;
    get<Satellites>(mars) = {"Phobos", "Deimos"};

    std::cout << mars;

	return 0;
}
