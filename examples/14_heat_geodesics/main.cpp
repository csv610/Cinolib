#include <cinolib/meshes/meshes.h>
#include <cinolib/geodesics.h>
#include <cinolib/profiler.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nHeat Geodesics" << std::endl;
        std::cout << "==============" << std::endl;
        std::cout << "Usage: heat_geodesics [mesh_file]" << std::endl;
        std::cout << "\nComputes geodesic distances from user-selected seed vertices." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/bunny.obj" << std::endl;
        std::cout << "\nControls: CMD+CLICK to add geodesic source. Reset button clears sources." << std::endl;
        std::cout << "Other controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/bunny.obj";
    DrawableTrimesh<> m(s.c_str());
    m.show_wireframe(false);

    GLcanvas gui;
    SurfaceMeshControls<DrawableTrimesh<>> menu(&m, &gui);
    gui.push(&m);
    gui.push(&menu);

    // position heat sources with CMD + left click
    Profiler profiler;
    std::vector<uint> sources;
    GeodesicsCache prefactored_matrices;
    gui.callback_mouse_left_click = [&](int modifiers) -> bool
    {
        if(modifiers & GLFW_MOD_SUPER)
        {
            vec3d p;
            vec2d click = gui.cursor_pos();
            if(gui.unproject(click, p)) // transform click in a 3d point
            {
                uint vid = m.pick_vert(p);
                sources.push_back(vid);
                profiler.push("compute_geodesics");
                compute_geodesics_amortized(m, prefactored_matrices, sources).copy_to_mesh(m);
                profiler.pop();
                m.show_texture1D(TEXTURE_1D_HSV_W_ISOLINES);
            }
        }
        return false;
    };

    gui.callback_app_controls = [&]()
    {
        if(ImGui::SmallButton("Reset"))
        {
            // reset heat sources
            sources.clear();
            m.show_vert_color();
        }
    };

    return gui.launch();
}
