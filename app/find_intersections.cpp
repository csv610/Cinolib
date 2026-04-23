#include <cinolib/meshes/meshes.h>
#include <cinolib/find_intersections.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: find_intersections <input> [output]\n\n"
                  << "Detect self-intersections in a triangle mesh.\n"
                  << "Input: surface mesh (OBJ, OFF)\n"
                  << "Output: OBJ with intersected triangles marked (default: input_inter.obj)\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    std::string output = (argc>=3) ? argv[2] : get_file_name(input, false) + "_inter.obj";

    Trimesh<> m(input.c_str());

    std::set<ipair> inters;
    find_intersections(m, inters);

    std::cout << "Found " << inters.size() << " intersecting triangle pairs" << std::endl;

    for(const auto & i : inters)
    {
        m.poly_data(i.first).color = Color::RED();
        m.poly_data(i.second).color = Color::RED();
    }

    if(!inters.empty())
    {
        m.save(output.c_str());
        std::cout << "Saved marked mesh to " << output << std::endl;
    }

    return 0;
}