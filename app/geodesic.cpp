#include <cinolib/meshes/meshes.h>
#include <cinolib/geodesics.h>
#include <cinolib/string_utilities.h>
#include <cinolib/scalar_field.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: geodesic <input> [seed_vertices]\n\n"
                  << "Compute geodesic distances from seed vertices.\n"
                  << "Input: surface mesh (OBJ, OFF)\n"
                  << "Seed vertices: comma-separated vertex IDs (default: 0)\n"
                  << "\nOutput: scalar field saved as .scalar file\n"
                  << std::endl;
        return -1;
    }

    std::string mesh_file(argv[1]);
    std::vector<uint> seeds;
    seeds.push_back(0);

    if(argc>=3)
    {
        seeds.clear();
        std::string seed_str(argv[2]);
        size_t pos = 0, end;
        while((end = seed_str.find(',', pos)) != std::string::npos)
        {
            seeds.push_back(std::stoi(seed_str.substr(pos, end-pos)));
            pos = end + 1;
        }
        seeds.push_back(std::stoi(seed_str.substr(pos)));
    }

    Trimesh<> m(mesh_file.c_str());

    ScalarField geodesic = compute_geodesics(m, seeds);

    std::string out_name = get_file_name(mesh_file, false) + ".scalar";
    geodesic.serialize(out_name.c_str());

    std::cout << "Saved geodesic field to " << out_name << std::endl;

    return 0;
}