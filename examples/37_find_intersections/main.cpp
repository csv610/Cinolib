#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>
#include <cinolib/meshes/meshes.h>
#include <cinolib/find_intersections.h>
#include <cinolib/profiler.h>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nFind Intersections" << std::endl;
        std::cout << "===================" << std::endl;
        std::cout << "Usage: find_intersections [mesh_file]" << std::endl;
        std::cout << "\nDetects self-intersections in a triangle mesh." << std::endl;
        std::cout << "If no mesh file is provided, defaults to: " << DATA_PATH << "/two_spheres.obj" << std::endl;
        std::cout << "\nIntersecting triangles are highlighted in red." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/two_spheres.obj";
    DrawableTrimesh<> m(s.c_str());

    Profiler p;
    p.push("Find intersections");
    std::set<ipair> inters;
    find_intersections(m, inters);
    p.pop();

    std::cout << "\n" << inters.size() << " pairs of intersecting triangles were found\n" << std::endl;
    for(const auto & i : inters)
    {
        m.poly_data(i.first ).color = Color::RED();
        m.poly_data(i.second).color = Color::RED();

        m.poly_data(i.first ).flags[MARKED] = true;
        m.poly_data(i.second).flags[MARKED] = true;
    }
    m.updateGL();

    GLcanvas gui;
    SurfaceMeshControls<DrawableTrimesh<>> menu(&m,&gui);
    gui.push(&m);
    gui.push(&menu);
    return gui.launch();
}
