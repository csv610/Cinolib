#include <cinolib/meshes/meshes.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/volume_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nTetmesh Viewer" << std::endl;
        std::cout << "==============" << std::endl;
        std::cout << "Usage: tetmesh_viewer [mesh_file]" << std::endl;
        std::cout << "\nLoads and displays a tetrahedral mesh with interactive GUI controls." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/sphere.mesh" << std::endl;
        std::cout << "\nControls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        std::cout << "\nSupported formats: MESH, TET, VTU, VTK" << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/sphere.mesh";
    DrawableTetmesh<> m(s.c_str());
    GLcanvas gui;
    VolumeMeshControls<DrawableTetmesh<>> menu(&m, &gui);
    gui.push(&m);
    gui.push(&menu);
    return gui.launch();
}
