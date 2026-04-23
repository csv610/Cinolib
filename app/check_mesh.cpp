#include <cinolib/meshes/meshes.h>
#include <cinolib/connected_components.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: check_mesh <input>\n\n"
                  << "Check mesh for topological issues.\n"
                  << "  - self-intersections\n"
                  << "  - non-manifold vertices/edges\n"
                  << "  - disconnected components\n"
                  << "Input: mesh (OBJ, OFF)\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    Trimesh<> m(input.c_str());

    std::cout << "Mesh: " << m.num_verts() << "V " << m.num_edges() << "E " << m.num_polys() << "P" << std::endl;

    std::vector<std::unordered_set<uint>> ccs;
    uint n_ccs = connected_components(m, ccs);
    std::cout << "Connected components: " << n_ccs << std::endl;

    return 0;
}