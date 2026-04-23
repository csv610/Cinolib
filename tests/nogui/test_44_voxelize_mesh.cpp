#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/lion_vase_poly.off";
    std::cout << "NOGUI Test: 44_voxelize_mesh loading " << s << std::endl;
    Hexmesh<> m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 44_voxelize_mesh PASSED" << std::endl;
    return 0;
}
