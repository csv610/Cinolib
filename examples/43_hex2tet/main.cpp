#include <cinolib/meshes/meshes.h>
#include <cinolib/tetrahedralization.h>
#include <cinolib/string_utilities.h>

using namespace cinolib;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main(int argc, char *argv[])
{
    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nHex to Tet" << std::endl;
        std::cout << "==========" << std::endl;
        std::cout << "Usage: hex2tet [hex_mesh_file]" << std::endl;
        std::cout << "\nConverts a hexahedral mesh to a tetrahedral mesh." << std::endl;
        std::cout << "Each hex is subdivided into 5 or 6 tetrahedra." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/ellipsoid.mesh" << std::endl;
        std::cout << "\nOutput: same basename with _tet.mesh extension." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/ellipsoid.mesh";
    Hexmesh<> hm(s.c_str());
    Tetmesh<> tm;
    hex_to_tets(hm,tm);
    std::string basename = get_file_path(s,true);
    tm.save((basename+"_tet.mesh").c_str());
    return 0;
}
