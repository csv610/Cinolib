#include <cinolib/meshes/meshes.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>
#include <cinolib/3d_printing/drawable_sliced_object.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nSliced CLI Loader" << std::endl;
        std::cout << "================" << std::endl;
        std::cout << "Usage: sliced_cli_loader [cli_file] [hatch_spacing]" << std::endl;
        std::cout << "\nLoads and displays a sliced .cli file for 3D printing visualization." << std::endl;
        std::cout << "If no files provided, defaults to: " << DATA_PATH << "/T_supported.cli" << std::endl;
        std::cout << "Default hatch spacing: 0.01" << std::endl;
        std::cout << "\nControls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc>1) ? std::string(argv[1]) : std::string(DATA_PATH) + "/T_supported.cli";
    double hatch  = (argc>2) ? atof(argv[2]) : 0.01;

    std::cout << "load " << s << std::endl;
    std::cout << "hatch is: " << hatch << std::endl;

    DrawableSlicedObj<> obj(s.c_str(), hatch);

    GLcanvas gui;
    SurfaceMeshControls<DrawableSlicedObj<>> menu(&obj, &gui);
    gui.push(&obj);
    gui.push(&menu);

    return gui.launch();
}
