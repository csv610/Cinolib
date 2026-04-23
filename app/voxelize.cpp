#include <cinolib/meshes/meshes.h>
#include <cinolib/voxelize.h>
#include <cinolib/voxel_grid_to_hexmesh.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: voxelize <input> [resolution] [type]\n\n"
                  << "Voxelize a surface mesh into a hexahedral grid.\n"
                  << "Input: polygon mesh (OBJ, OFF)\n"
                  << "Resolution: max voxels per side (default: 64)\n"
                  << "Type: 1=boundary, 2=inside, 3=both (default: 3)\n"
                  << "\nOutput: .mesh file\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    uint resolution = (argc>=3) ? atoi(argv[2]) : 64;
    int voxel_type = (argc>=4) ? atoi(argv[3]) : VOXEL_BOUNDARY | VOXEL_INSIDE;

    Polygonmesh<> m(input.c_str());

    VoxelGrid g;
    voxelize(m, resolution, g);
    std::cout << "Grid dimensions: " << g.dim[0] << " x " << g.dim[1] << " x " << g.dim[2] << std::endl;

    Hexmesh<> h;
    voxel_grid_to_hexmesh(g, h, voxel_type);

    std::string output = get_file_name(input, false) + ".mesh";
    h.save(output.c_str());
    std::cout << "Saved voxelized mesh to " << output << std::endl;

    return 0;
}