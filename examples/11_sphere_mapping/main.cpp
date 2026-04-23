#include <cinolib/meshes/meshes.h>
#include <cinolib/mean_curv_flow.h>
#include <cinolib/profiler.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nSphere Mapping" << std::endl;
        std::cout << "==============" << std::endl;
        std::cout << "Usage: sphere_mapping [mesh_file]" << std::endl;
        std::cout << "\nMaps a surface mesh to a sphere using Mean Curvature Flow." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/bunny.obj" << std::endl;
        std::cout << "\nUse GUI controls to set iterations and time step, then click 'Map to Sphere'." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/bunny.obj";
    DrawableTrimesh<> m(s.c_str());

    GLcanvas gui;
    gui.push(&m);

    Profiler profiler;
    gui.callback_app_controls = [&]()
    {
        static int   n_iter        = 10;
        static float time_step     = 0.005f;
        ImGui::InputInt("Iter.", &n_iter);
        ImGui::InputFloat("t", &time_step);
        if(ImGui::SmallButton("Map to Sphere"))
        {
            profiler.push("Compute MCF");
            MCF(m, (uint)n_iter, (double)time_step);
            profiler.pop();
            m.updateGL();
            gui.refit_scene();
        }
        if(ImGui::SmallButton("Reset"))
        {
            m = DrawableTrimesh<>(s.c_str());
            gui.refit_scene();
        }
    };

    SurfaceMeshControls<DrawableTrimesh<>> menu(&m, &gui);
    gui.push(&menu);

    return gui.launch();
}
