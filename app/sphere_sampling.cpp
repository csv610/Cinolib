#include <cinolib/sphere_coverage.h>
#include <cinolib/meshes/meshes.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: sphere_sampling <n_points> [output]\n\n"
                  << "Generate uniform samples on a sphere.\n"
                  << "N points: number of sample points (default: 1000)\n"
                  << "Output: OBJ file (default: sphere_samples.obj)\n"
                  << std::endl;
        return -1;
    }

    uint n_points = (argc>=2) ? atoi(argv[1]) : 1000;
    std::string output = (argc>=3) ? argv[2] : "sphere_samples.obj";

    std::vector<vec3d> samples;
    sphere_coverage(n_points, samples);

    std::vector<std::vector<uint>> polys(samples.size());
    Trimesh<>(samples, polys).save(output.c_str());

    std::cout << "Saved " << n_points << " samples to " << output << std::endl;

    return 0;
}