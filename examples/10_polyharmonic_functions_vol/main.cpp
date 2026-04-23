#include <cinolib/meshes/meshes.h>
#include <cinolib/harmonic_map.h>
#include <cinolib/profiler.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/volume_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nPolyharmonic Functions (Volume)" << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "Usage: polyharmonic_functions_vol [mesh_file]" << std::endl;
        std::cout << "\nComputes polyharmonic functions on volumetric meshes." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/sphere.mesh" << std::endl;
        std::cout << "\nUse the GUI to set harmonic order and compute the field." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/sphere.mesh";
    DrawableTetmesh<> m(s.c_str());
    GLcanvas gui;
    VolumeMeshControls<DrawableTetmesh<>> menu(&m, &gui);
    gui.push(&m);
    gui.push(&menu);

    // visual controls to setup the level of harmonicity (1,2,...)
    // and to compute and reset the field
    Profiler profiler;
    gui.callback_app_controls = [&]()
    {
        static int n_harmonic = 1;
        ImGui::InputInt("Harmonic n", &n_harmonic);
        if(ImGui::SmallButton("Compute Field"))
        {
            std::map<uint,double> bc = {{0,0.0}, {999,1.0}}; // Dirichlet boundary conditions
            profiler.push("harmonic_map");
            harmonic_map(m, bc, (uint)n_harmonic, COTANGENT).copy_to_mesh(m);
            profiler.pop();
            m.show_in_texture1D (TEXTURE_1D_PARULA_W_ISOLINES);
            m.show_out_texture1D(TEXTURE_1D_PARULA_W_ISOLINES);
        }
    };

    return gui.launch();
}
