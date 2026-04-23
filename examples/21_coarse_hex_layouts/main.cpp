#include <cinolib/meshes/meshes.h>
#include <cinolib/profiler.h>
#include <cinolib/coarse_layout.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/volume_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nCoarse Hex Layouts" << std::endl;
        std::cout << "===================" << std::endl;
        std::cout << "Usage: coarse_hex_layout [mesh_file]" << std::endl;
        std::cout << "\nComputes a coarse hexahedral layout from a hex mesh." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/ellipsoid.mesh" << std::endl;
        std::cout << "\nControls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/ellipsoid.mesh";
    DrawableHexmesh<> m(s.c_str());

    Profiler profiler;
    profiler.push("coarse layout");
    compute_coarse_hex_layout(m);
    profiler.pop();
    m.poly_color_wrt_label();
    m.updateGL();

    GLcanvas gui;
    VolumeMeshControls<DrawableHexmesh<>> menu(&m,&gui);
    gui.push(&m);
    gui.push(&menu);

    return gui.launch();
}
