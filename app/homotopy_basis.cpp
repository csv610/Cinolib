#include <cinolib/meshes/meshes.h>
#include <cinolib/homotopy_basis.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: homotopy_basis <input> [root_vertex]\n\n"
                  << "Compute shortest homotopy basis for a surface mesh.\n"
                  << "Input: surface mesh (OBJ, OFF)\n"
                  << "Root vertex: basis root vertex ID (default: 0)\n"
                  << "\nOutput: basis loops saved to [input]_basis.obj\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    uint root = (argc>=3) ? atoi(argv[2]) : 0;

    Trimesh<> m(input.c_str());

    std::vector<std::vector<uint>> basis;
    std::vector<bool> tree, cotree;

    double len = homotopy_basis(m, root, basis, tree, cotree);
    std::cout << "Homotopy basis length: " << len << std::endl;
    std::cout << "Basis loops: " << basis.size() << std::endl;

    std::vector<vec3d> loop_verts;
    std::vector<std::vector<uint>> loop_polys;
    for(auto &loop : basis)
    {
        std::vector<uint> poly;
        for(auto vid : loop) loop_verts.push_back(m.vert(vid));
        for(uint i=0; i<loop.size(); ++i)
        {
            std::vector<uint> p = {loop[i], loop[(i+1)%loop.size()]};
            loop_polys.push_back(p);
        }
    }
    if(!loop_verts.empty())
    {
        std::string output = get_file_name(input, false) + "_basis.obj";
        Trimesh<>(loop_verts, loop_polys).save(output.c_str());
        std::cout << "Saved basis to " << output << std::endl;
    }

    return 0;
}