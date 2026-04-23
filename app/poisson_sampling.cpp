#include <cinolib/meshes/meshes.h>
#include <cinolib/Poisson_sampling.h>
#include <cinolib/string_utilities.h>
#include <iostream>

int main(int argc, char **argv)
{
    using namespace cinolib;

    if(argc<2)
    {
        std::cout << "\nUsage: poisson_sampling <n_points> [dimension]\n\n"
                  << "Generate Poisson disk samples.\n"
                  << "N points: target number of samples\n"
                  << "Dimension: 2 or 3 (default: 3)\n"
                  << "\nOutput: OBJ file (poisson_samples.obj)\n"
                  << std::endl;
        return -1;
    }

    uint n_points = atoi(argv[1]);
    uint dim = (argc>=3) ? atoi(argv[2]) : 3;

    std::vector<vec3d> samples;
    float radius = 1.0f / std::sqrt(n_points);

    if(dim == 2)
    {
        std::vector<vec2d> samples_2d;
        Poisson_sampling<2, vec2d>(radius, vec2d(0,0), vec2d(1,1), samples_2d);
        for(auto p : samples_2d) samples.push_back(vec3d(p.x(), p.y(), 0));
    }
    else
    {
        Poisson_sampling<3, vec3d>(radius, vec3d(0,0,0), vec3d(1,1,1), samples);
    }

    std::vector<std::vector<uint>> polys(samples.size());
    Trimesh<>(samples, polys).save("poisson_samples.obj");

    std::cout << "Generated " << samples.size() << " samples" << std::endl;

    return 0;
}