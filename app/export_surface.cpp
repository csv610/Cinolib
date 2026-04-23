#include <cinolib/meshes/meshes.h>
#include <cinolib/export_surface.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<3)
    {
        std::cout << "\nUsage: export_surface -tet|-hex|-poly <input> [-vmap]\n\n"
                  << "Extract boundary surface from volumetric mesh.\n"
                  << "Options:\n"
                  << "  -tet   Tetrahedral mesh (.mesh, .tet, .vtu, .vtk)\n"
                  << "  -hex   Hexahedral mesh (.mesh, .vtu, .vtk)\n"
                  << "  -poly Polyhedral mesh (.hedra, .mesh, .vtu, .vtk)\n"
                  << "  -vmap  Export vertex mapping file\n"
                  << "\nOutput: surface mesh as OBJ file\n"
                  << std::endl;
        return -1;
    }

    std::string filename(argv[2]);
    std::string base_name = get_file_name(filename, false);

    Polygonmesh<> srf;
    std::unordered_map<uint,uint> m2srf, srf2m;

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
        std::cout << "Unknown option: " << argv[1] << std::endl;
        return -1;
    }

    srf.save((base_name + ".obj").c_str());

    if(argc>3 && strcmp(argv[3],"-vmap")==0)
    {
        FILE *f = fopen((base_name + "_srf2vol_vmap.txt").c_str(), "w");
        if(f)
        {
            for(auto &v : srf2m) fprintf(f,"%d %d\n", v.first, v.second);
            fclose(f);
        }
    }

    return 0;
}