#include <cinolib/voxelize.h>
#include <cinolib/voxel_grid_to_hexmesh.h>
#include <cinolib/profiler.h>
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/volume_mesh_controls.h>

using namespace cinolib;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main(int argc, char *argv[])
{
    if(argc==2 && std::string(argv[1])=="-h")
    {
        std::cout << "\nVoxelize Function" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Usage: voxelize_function [max_voxels_per_side] [voxel_type]" << std::endl;
        std::cout << "\nVoxelizes an implicit torus function into a hexahedral voxel grid." << std::endl;
        std::cout << "Optional max_voxels_per_side (default: 64)" << std::endl;
        std::cout << "Optional voxel_type: 1=boundary, 2=inside, 3=both (default: 3)" << std::endl;
        std::cout << "\nDisplays the voxelized hexmesh in a GUI." << std::endl;
        std::cout << "Controls: rotate (left click), pan (middle click), zoom (scroll)." << std::endl;
        return 0;
    }

    uint max_voxels_per_side = (argc>1) ? atoi(argv[1]) : 64;
    int  voxel_type = (argc>=2) ? atoi(argv[2]) : VOXEL_BOUNDARY | VOXEL_INSIDE;

    auto torus = [](const vec3d & p)
    {
        double R = 1;
        double r = 0.5;
        return pow(R - sqrt(p[0]*p[0] + p[1]*p[1]),2) + p[2]*p[2] - r*r;
    };

    VoxelGrid g;
    Profiler p;
    p.push("voxelize");
    voxelize(torus, AABB(vec3d(-2,-2,-2),vec3d(2,2,2)), max_voxels_per_side, g);
    p.pop();
    std::cout << "grid dimensions : " << g.dim[0] << " x " << g.dim[1] << " x " << g.dim[2] << std::endl;

    DrawableHexmesh<> h;
    p.push("voxel grid to hexmesh");
    voxel_grid_to_hexmesh(g,h,voxel_type);
    p.pop();
    h.poly_color_wrt_label();
    h.updateGL();

    GLcanvas gui;
    gui.push(&h);
    gui.push(new VolumeMeshControls<DrawableHexmesh<>>(&h,&gui,"voxel grid"));
    return gui.launch();
}
