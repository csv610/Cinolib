#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/ellipsoid.mesh";
    std::cout << "NOGUI Test: 21_coarse_hex_layouts loading " << s << std::endl;
    Hexmesh<> m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 21_coarse_hex_layouts PASSED" << std::endl;
    return 0;
}
