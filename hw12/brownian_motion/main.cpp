#include <vector>
#include <random>
#include <chrono>
#include <thread>

#include "particle.h"
#include "system.h"


using particle_t = std::shared_ptr < Particle >;


int main(){

    const auto H = 800U;
    const auto W = 800U;

    const auto cell_size = 40U;

    const auto N = 600U;

    const auto r = 2.0f;

    sf::Vector2f min_point(  0.0f,   0.0f);
    sf::Vector2f max_point(W*1.0f, H*1.0f);

    auto central_pos = (min_point + max_point) * 0.5f;

    std::vector < particle_t > particles;

    for (int i = 0; i < N; ++i) {
        particles.emplace_back(std::make_shared < Particle > (central_pos, r));
    }

    std::vector< std::vector< unsigned int >> cells(H / cell_size, std::vector<unsigned int> (W / cell_size));


    std::random_device rd;
    std::mt19937 gen(rd());


    System system(min_point, max_point, particles, cells, r, cell_size, gen);

    system.run();

    return 0;
}
