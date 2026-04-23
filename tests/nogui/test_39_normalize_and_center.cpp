#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/bunny.obj";
    std::cout << "NOGUI Test: 39_normalize_and_center loading " << s << std::endl;
    Polygonmesh<>  m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 39_normalize_and_center PASSED" << std::endl;
    return 0;
}
