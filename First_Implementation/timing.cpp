
#include <iostream> // std::cout, std::endl
#include <chrono>   // std::chrono
#include <numeric>  // std::accumulate()
#include <algorithm>
#include <vector>
#include "../Data/cyclic-data.hpp"
#include "lomb-scargle.hpp"

int main()
{
    std::vector<double> result; 
    auto const benchmark_trials = 2000u;
    auto const threshold = 500llu;

    auto start_time = std::chrono::system_clock::now();

    for( auto i = 0u; i < benchmark_trials; ++i )
    {
        result = lomb_scargle( input_data,times,frequencies,.1);
    }

    auto end_time = std::chrono::system_clock::now();
    auto elapsed_time = std::chrono::duration_cast< std::chrono::microseconds >( end_time - start_time );

    for (int i = 0 ; i < result.size(); i++){
        std::cout << frequencies.at(i) << " " << result.at(i) << std::endl;
    }
    double max = *max_element(std::begin(result), std::end(result));
    std::cout << "max = " << max << "\n";
    std::cout << "average time per run: "
              << elapsed_time.count() / static_cast< float >( benchmark_trials )
              << " us" << std::endl;

    return 0;
}