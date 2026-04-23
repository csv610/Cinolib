#include <cinolib/meshes/meshes.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/ambient_occlusion.h>
#include <cinolib/profiler.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nAmbient Occlusion" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Usage: ambient_occlusion [mesh_file]" << std::endl;
        std::cout << "\nComputes and visualizes ambient occlusion on a mesh." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/bamboo_pen.obj" << std::endl;
        std::cout << "\nUse the slider to adjust the ambient occlusion intensity." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/bamboo_pen.obj";
    DrawableQuadmesh<> m(s.c_str());

    GLcanvas gui;
    gui.push(&m);

    AO_data data;
    ambient_occlusion(m,data);
    m.updateGL();

    gui.callback_app_controls = [&]()
    {
        if(ImGui::SliderFloat("AO", &m.AO_alpha, 0.f, 1.f))
        {
            m.updateGL();
        }
    };

    return gui.launch();
}
