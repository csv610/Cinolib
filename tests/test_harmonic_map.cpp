#include <cinolib/meshes/meshes.h>
#include <cinolib/harmonic_map.h>
#include <cinolib/geometry/n_sided_poygon.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : "examples/data/Laurana.obj";
    std::cout << "Testing Harmonic Map on: " << s << std::endl;

    Trimesh<> m_xyz(s.c_str());
    assert(m_xyz.num_verts() > 0);

    std::vector<uint> boundary = m_xyz.get_ordered_boundary_vertices();
    assert(!boundary.empty());

    std::vector<vec3d> uv_boundary = n_sided_polygon((uint)boundary.size(), CIRCLE);
    std::map<uint,vec3d> dirichlet_bcs;
    for(uint i=0; i<boundary.size(); ++i) dirichlet_bcs[boundary.at(i)] = uv_boundary.at(i);

    std::vector<vec3d> uv_map = harmonic_map_3d(m_xyz, dirichlet_bcs);
    assert(uv_map.size() == m_xyz.num_verts());

    std::cout << "Harmonic Map Test PASSED" << std::endl;
    return 0;
}
