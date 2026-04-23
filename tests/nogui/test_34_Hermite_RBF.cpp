#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/sphere_coarse.obj";
    std::cout << "NOGUI Test: 34_Hermite_RBF loading " << s << std::endl;
    Tetmesh<> m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 34_Hermite_RBF PASSED" << std::endl;
    return 0;
}
