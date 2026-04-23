#include <cinolib/meshes/meshes.h>
#include <cinolib/octree.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: octree <input> [max_depth] [items_per_leaf]\n\n"
                  << "Build an octree from a surface mesh.\n"
                  << "Input: polygon mesh (OBJ, OFF)\n"
                  << "Max depth: maximum tree depth (default: 7)\n"
                  << "Items per leaf: max primitives per leaf (default: 50)\n"
                  << "\nOutput: prints octree stats\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    uint max_depth = (argc>=3) ? atoi(argv[2]) : 7;
    uint items_per_leaf = (argc>=4) ? atoi(argv[3]) : 50;

    Polygonmesh<> m(input.c_str());

    Octree octree(max_depth, items_per_leaf);
    octree.build_from_mesh_polys(m);
    std::cout << "Octree built successfully for " << input << std::endl;
    std::cout << "Max depth: " << max_depth << ", Items per leaf: " << items_per_leaf << std::endl;
    std::cout << "Mesh: " << m.num_verts() << "V " << m.num_polys() << "P" << std::endl;

    return 0;
}