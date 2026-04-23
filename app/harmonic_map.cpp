#include <cinolib/meshes/meshes.h>
#include <cinolib/harmonic_map.h>
#include <cinolib/geometry/n_sided_poygon.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: harmonic_map <input> [output]\n\n"
                  << "Map 3D mesh boundary to unit circle (harmonic parameterization).\n"
                  << "Input: surface mesh (OBJ, OFF)\n"
                  << "Output: OBJ with UV coords (default: input_uv.obj)\n"
                  << std::endl;
        return -1;
    }

    std::string input(argv[1]);
    std::string output = (argc>=3) ? argv[2] : get_file_name(input, false) + "_uv.obj";

    Trimesh<> m(input.c_str());

    std::vector<uint> boundary = m.get_ordered_boundary_vertices();
    std::vector<vec3d> uv_boundary = n_sided_polygon((uint)boundary.size(), CIRCLE);

    std::map<uint,vec3d> dirichlet_bcs;
    for(uint i=0; i<boundary.size(); ++i) dirichlet_bcs[boundary.at(i)] = uv_boundary.at(i);

    std::vector<vec3d> uv_map = harmonic_map_3d(m, dirichlet_bcs);

    for(uint vid=0; vid<m.num_verts(); ++vid) m.vert(vid) = uv_map[vid];
    for(uint vid=0; vid<m.num_verts(); ++vid) m.vert_data(vid).uvw = uv_map[vid];

    m.save(output.c_str());
    std::cout << "Saved harmonic map to " << output << std::endl;

    return 0;
}