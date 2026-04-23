#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/bamboo_pen.obj";
    std::cout << "NOGUI Test: 29_ambient_occlusion loading " << s << std::endl;
    Quadmesh<> m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 29_ambient_occlusion PASSED" << std::endl;
    return 0;
}
