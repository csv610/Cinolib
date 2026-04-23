#include <cinolib/meshes/meshes.h>
#include <cinolib/export_surface.h>
#include <cinolib/string_utilities.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nExport Surface" << std::endl;
        std::cout << "==============" << std::endl;
        std::cout << "Usage: export_surface -tet|hex|poly filename [-vmap]" << std::endl;
        std::cout << "\nExtracts the boundary surface from a volumetric mesh." << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -tet   Input is a tetrahedral mesh (.mesh, .tet, .vtu, .vtk)" << std::endl;
        std::cout << "  -hex   Input is a hexahedral mesh (.mesh, .vtu, .vtk)" << std::endl;
        std::cout << "  -poly  Input is a polyhedral mesh (.hedra, .mesh, .vtu, .vtk)" << std::endl;
        std::cout << "  -vmap  Export vertex mapping file (volume to surface)" << std::endl;
        std::cout << "\nOutput: surface mesh saved as OBJ file." << std::endl;
        return 0;
    }

    if(argc<3)
    {
        std::cout << "\n\nUsage:\n\texport_surface -tet|hex|poly filename [-vmap]\n\n" << std::endl;;
        return -1;
    }

    std::string filename(argv[2]);
    std::string base_name = get_file_name(filename,false);

    Polygonmesh<> srf;
    std::unordered_map<uint,uint> m2srf,srf2m;

    bool export_map = argc>3 && strcmp(argv[3],"-vmap")==0;

    if(strcmp(argv[1],"-tet")==0)
    {
        Tetmesh<> m(filename.c_str());
        export_surface(m, srf, m2srf, srf2m);
    }
    else if(strcmp(argv[1],"-hex")==0)
    {
        Hexmesh<> m(filename.c_str());
        export_surface(m, srf, m2srf, srf2m);
    }
    else if(strcmp(argv[1],"-poly")==0)
    {
        Polyhedralmesh<> m(filename.c_str());
        export_surface(m, srf, m2srf, srf2m);
    }
    else
    {
        std::cout << "Unknown extension" << std::endl;
        return -1;
    }

    srf.save((base_name + ".obj").c_str());

    if(export_map)
    {
        FILE *f = fopen((base_name + "_srf2vol_vmap.txt").c_str(), "w");
        if(f)
        {
            for(auto v2v : srf2m) fprintf(f,"%d %d\n", v2v.first, v2v.second);
            fclose(f);
        }
    }

    return 0;
}
