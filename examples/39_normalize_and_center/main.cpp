#include <cinolib/meshes/meshes.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nNormalize and Center" << std::endl;
        std::cout << "====================" << std::endl;
        std::cout << "Usage: normalize_and_center input output" << std::endl;
        std::cout << "\nNormalizes and centers a mesh:" << std::endl;
        std::cout << "  - Translates mesh so bbox center is at origin" << std::endl;
        std::cout << "  - Scales mesh to fit in unit cube" << std::endl;
        std::cout << "Input: polygon mesh (OBJ, OFF, STL, etc.)" << std::endl;
        std::cout << "Output: normalized mesh in same format" << std::endl;
        return 0;
    }

    if(argc<2)
    {
        std::cout << "\n\nusage:\n\tnormalize_and_center input output\n\n" << std::endl;;
        return -1;
    }
    Polygonmesh<> m(argv[1]);
    m.translate(-m.bbox().center());
    m.normalize_bbox();
    m.save(argv[2]);
    return 0;
}
