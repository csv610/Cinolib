#include <cinolib/meshes/meshes.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: normalize <input> [output]\n\n"
                  << "Normalize and center a mesh.\n"
                  << "  - Translates bbox center to origin\n"
                  << "  - Scales to unit cube\n"
                  << "Input: mesh (OBJ, OFF, STL)\n"
                  << "Output: normalized mesh (default: input_norm.obj)\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    std::string output = (argc>=3) ? argv[2] : get_file_name(input, false) + "_norm.obj";

    Polygonmesh<> m(input.c_str());
    m.translate(-m.bbox().center());
    m.normalize_bbox();
    m.save(output.c_str());

    std::cout << "Saved normalized mesh to " << output << std::endl;

    return 0;
}