#include <cinolib/meshes/meshes.h>
#include <cinolib/coarse_layout.h>
#include <cinolib/profiler.h>
#include <cinolib/drawable_sphere.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nCoarse Quad Layouts" << std::endl;
        std::cout << "====================" << std::endl;
        std::cout << "Usage: coarse_quad_layout [mesh_file]" << std::endl;
        std::cout << "\nComputes a coarse quad layout from a quad mesh using singularity analysis." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/cubespikes.obj" << std::endl;
        std::cout << "\nSingular vertices are shown as spheres." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/cubespikes.obj";
    DrawableQuadmesh<> m(s.c_str());

    Profiler profiler;
    profiler.push("coarse layout");
    compute_coarse_quad_layout(m);
    profiler.pop();
    m.poly_color_wrt_label();
    m.show_marked_edge_color(Color::BLACK());
    m.show_marked_edge_width(5);
    m.updateGL();

    GLcanvas gui;
    SurfaceMeshControls<DrawableQuadmesh<>> controls(&m, &gui);
    gui.push(&m);
    gui.push(&controls);

    float radius = float(m.bbox().diag()) * 0.01f;
    for(uint vid=0; vid<m.num_verts(); ++vid)
    {
        if(m.vert_is_singular(vid)) gui.push(new DrawableSphere(m.vert(vid), radius),false);
    }

    return gui.launch();
}
