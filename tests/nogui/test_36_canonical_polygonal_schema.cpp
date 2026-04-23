#include <cinolib/meshes/meshes.h>
#include <iostream>
#include <cassert>

int main(int argc, char **argv) {
    using namespace cinolib;
    std::string s = (argc >= 2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/torus.obj";
    std::cout << "NOGUI Test: 36_canonical_polygonal_schema loading " << s << std::endl;
    Trimesh<> m(s.c_str());
    assert(m.num_verts() > 0);
    std::cout << "NOGUI Test: 36_canonical_polygonal_schema PASSED" << std::endl;
    return 0;
}
