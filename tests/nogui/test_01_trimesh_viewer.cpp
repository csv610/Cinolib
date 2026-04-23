#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/bunny.obj";
    std::cout << "NOGUI Test: 01_trimesh_viewer loading " << s << std::endl;
    Trimesh<> m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 01_trimesh_viewer PASSED" << std::endl;
    return 0;
}
