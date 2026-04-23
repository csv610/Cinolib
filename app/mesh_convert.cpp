#include <cinolib/io/read_write.h>
#include <cinolib/string_utilities.h>
#include <cinolib/stl_container_utilities.h>
#include <cinolib/meshes/trimesh.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc!=3)
    {
        std::cout << "\nUsage: mesh_convert input output\n\n"
                  << "Convert between mesh formats.\n"
                  << "Supported: OBJ, OFF, STL, MESH, TET, HEDRA, VTU, VTK\n"
                  << std::endl;
        return -1;
    }

    std::vector<vec3d>             verts;
    std::vector<std::vector<uint>> faces;
    std::vector<std::vector<uint>> polys;
    std::vector<std::vector<bool>> winding;

    std::string ext = get_file_extension(argv[1]);

    if(ext=="OBJ" || ext=="obj") read_OBJ(argv[1], verts, polys);
    else if(ext=="OFF" || ext=="off") read_OFF(argv[1], verts, polys);
    else if(ext=="STL" || ext=="stl") {
        std::vector<uint> tris;
        read_STL(argv[1], verts, tris);
        polys = polys_from_serialized_vids(tris,3);
    }
    else if(ext=="MESH" || ext=="mesh") read_MESH(argv[1], verts, polys);
    else if(ext=="TET" || ext=="tet") read_TET(argv[1], verts, polys);
    else if(ext=="VTU" || ext=="vtu") read_VTU(argv[1], verts, polys);
    else if(ext=="VTK" || ext=="vtk") read_VTK(argv[1], verts, polys);
    else if(ext=="HEDRA" || ext=="hedra") read_HEDRA(argv[1], verts, faces, polys, winding);
    else {
        std::cout << "Unknown input format: " << ext << std::endl;
        return -1;
    }

    ext = get_file_extension(argv[2]);

    if(ext=="OBJ" || ext=="obj") write_OBJ(argv[2], serialized_xyz_from_vec3d(verts), polys);
    else if(ext=="OFF" || ext=="off") write_OFF(argv[2], serialized_xyz_from_vec3d(verts), polys);
    else if(ext=="STL" || ext=="stl") {
        Trimesh<> tmp(verts,polys);
        tmp.save(argv[2]);
    }
    else if(ext=="MESH" || ext=="mesh") write_MESH(argv[2], verts, polys);
    else if(ext=="TET" || ext=="tet") write_TET(argv[2], verts, polys);
    else if(ext=="VTU" || ext=="vtu") write_VTU(argv[2], verts, polys);
    else if(ext=="VTK" || ext=="vtk") write_VTK(argv[2], verts, polys);
    else if(ext=="NODE" || ext=="node" || ext=="ELE" || ext=="ele") {
        write_NODE_ELE(get_file_name(argv[2], false).c_str(), verts, polys);
    }
    else {
        std::cout << "Unknown output format: " << ext << std::endl;
        return -1;
    }

    return 0;
}