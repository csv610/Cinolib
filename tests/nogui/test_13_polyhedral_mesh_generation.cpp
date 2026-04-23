#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/3holes.obj";
    std::cout << "NOGUI Test: 13_polyhedral_mesh_generation loading " << s << std::endl;
    Polyhedralmesh<> m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 13_polyhedral_mesh_generation PASSED" << std::endl;
    return 0;
}
