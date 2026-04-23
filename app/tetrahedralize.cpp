#include <cinolib/meshes/meshes.h>
#include <cinolib/tetgen_wrap.h>
#include <cinolib/string_utilities.h>
#include <cinolib/stl_container_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: tetrahedralize <input> [tetgen_flags]\n\n"
                  << "Tetrahedralize surface mesh using Tetgen.\n"
                  << "Input: polygon mesh (OBJ, OFF, STL)\n"
                  << "Optional tetgen flags (e.g., '-pq1.5')\n"
                  << "\nOutput: .mesh file\n"
                  << std::endl;
        return -1;
    }

    Polygonmesh<> m(argv[1]);
    std::string flags = (argc>=3) ? argv[2] : "";

    std::vector<vec3d> v_out;
    std::vector<uint>  e_in, p_out;
    tetgen_wrap(m.vector_verts(), m.vector_polys(), e_in, flags.c_str(), v_out, p_out);

    std::string out_name = get_file_name(std::string(argv[1]), false) + ".mesh";
    write_MESH(out_name.c_str(), v_out, polys_from_serialized_vids(p_out, 4));

    return 0;
}