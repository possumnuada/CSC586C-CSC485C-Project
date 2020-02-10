
#include <iostream> // std::cout, std::endl
#include <chrono>   // std::chrono
#include <numeric>  // std::accumulate()
#include <algorithm>
#include "../Data/cyclic-data.hpp"
#include "lomb-scargle.hpp"

int main()
{
    double * result; 
    auto const benchmark_trials = 2000u;
    auto const threshold = 500llu;

    auto start_time = std::chrono::system_clock::now();

    for( auto i = 0u; i < benchmark_trials; ++i )
    {
        result = lomb_scargle( input_data,times,0llu,frequencies);
    }

    auto end_time = std::chrono::system_clock::now();
    auto elapsed_time = std::chrono::duration_cast< std::chrono::microseconds >( end_time - start_time );

    for (int i = 0 ; i < sizeof(result)/sizeof(result[0]); i++){
        std::cout << frequencies[i] << " " << result[i] << std::endl;
    }
    
    std::cout << "average time per run: "
              << elapsed_time.count() / static_cast< float >( benchmark_trials )
              << " us" << std::endl;

    return 0;
}