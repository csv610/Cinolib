#include <cinolib/meshes/meshes.h>
#include <cinolib/geodesics.h>
#include <cinolib/profiler.h>
#include <cinolib/drawable_isosurface.h>
#include <cinolib/gl/glcanvas.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nIso Surfaces" << std::endl;
        std::cout << "============" << std::endl;
        std::cout << "Usage: iso_surfaces [mesh_file]" << std::endl;
        std::cout << "\nDisplays iso-surfaces in a volumetric mesh with a scalar field." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/sphere.mesh" << std::endl;
        std::cout << "\nUse sliders to adjust the iso-value and slice plane." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    GLcanvas gui;

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/sphere.mesh";
    DrawableTetmesh<> m(s.c_str());
    compute_geodesics(m, {0, 10}, COTANGENT).copy_to_mesh(m); // generate some scalar field
    m.show_in_texture1D(TEXTURE_1D_HSV_W_ISOLINES);
    m.show_out_texture1D(TEXTURE_1D_HSV_W_ISOLINES);
    gui.push(&m);

    MeshSlicer ss;
    ss.Z_thresh = 0.5f;
    ss.slice(m);
    m.updateGL();

    float iso_val = 0.5f;
    DrawableIsosurface<> iso(m, iso_val);
    gui.push(&iso, false);

    Profiler profiler;
    gui.callback_app_controls = [&]()
    {
        if(ImGui::SliderFloat("iso", &iso_val, 0.f, 1.f))
        {
            iso = DrawableIsosurface<>(m,iso_val);
        }
        if(ImGui::SliderFloat("slice", &ss.Z_thresh, 0.f, 1.f))
        {
            ss.slice(m);
            m.updateGL();
        }
        if(ImGui::SmallButton("Tessellate"))
        {
            profiler.push("tessellate iso-surface");
            iso.tessellate(m);
            profiler.pop();
            ss.slice(m);
            m.updateGL();
        }
    };

    return gui.launch();
}
