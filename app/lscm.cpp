#include <cinolib/meshes/meshes.h>
#include <cinolib/lscm.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: lscm <input> [output]\n\n"
                  << "Compute LSCM (Least Squares Conformal Maps) UV parameterization.\n"
                  << "Input: surface mesh (OBJ, OFF)\n"
                  << "Output: OBJ with UV coordinates (default: input_name_uv.obj)\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    std::string output = (argc>=3) ? argv[2] : get_file_name(input, false) + "_uv.obj";

    Trimesh<> m(input.c_str());

    std::cout << "Computing LSCM UV mapping..." << std::endl;
    ScalarField uv = LSCM(m);
    uv.copy_to_mesh(m, UV_param);

    m.save(output.c_str());
    std::cout << "Saved UV-mapped mesh to " << output << std::endl;

    return 0;
}