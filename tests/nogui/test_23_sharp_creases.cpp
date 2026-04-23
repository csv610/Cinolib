#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/cube_minus_sphere.obj";
    std::cout << "NOGUI Test: 23_sharp_creases loading " << s << std::endl;
    Trimesh<> m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 23_sharp_creases PASSED" << std::endl;
    return 0;
}
