#include <cinolib/meshes/meshes.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nTrimesh Viewer" << std::endl;
        std::cout << "===============" << std::endl;
        std::cout << "Usage: trimesh_viewer [mesh_file]" << std::endl;
        std::cout << "\nLoads and displays a triangle mesh with interactive GUI controls." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/bunny.obj" << std::endl;
        std::cout << "\nControls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        std::cout << "\nSupported formats: OBJ, OFF, STL, HEDRA, MESH, VTU, VTK" << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/bunny.obj";
    DrawableTrimesh<> m(s.c_str());
    GLcanvas gui;
    SurfaceMeshControls<DrawableTrimesh<>> menu(&m, &gui);
    gui.push(&m);
    gui.push(&menu);
    return gui.launch();
}
