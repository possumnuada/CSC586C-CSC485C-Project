
#include <iostream> // std::cout, std::endl
#include <chrono>   // std::chrono
#include <numeric>  // std::accumulate()
#include <algorithm>
#include <vector>
#include "../GPU_Data/cyclic-data.hpp"
// I changed this to .cu to get the correct highlighting
#include "lomb-scargle.cu"

int main()
{

    auto const benchmark_trials = 2000u;

    auto start_time = std::chrono::system_clock::now();

    double periodogram[sizeof(frequencies)/sizeof(frequencies[0])];
    for( auto i = 0u; i < benchmark_trials; ++i )
    {
        lomb_scargle(input_data,times,frequencies,periodogram,.1,sizeof(input_data)/sizeof(input_data[0]),sizeof(frequencies)/sizeof(frequencies[0]));
    }


    auto end_time = std::chrono::system_clock::now();
    auto elapsed_time = std::chrono::duration_cast< std::chrono::microseconds >( end_time - start_time );

    double max = 0;
    int index;
    for (int i = 0; i < sizeof(frequencies)/sizeof(frequencies[0]); i++ ){
        if(periodogram[i] > max) {
            max = periodogram[i];
            index = i;
        }
    }
    std::cout << "max = " << max << "\n";
    std::cout << "index = " << frequencies[index] << "\n";
    std::cout << "average time per run: "
              << elapsed_time.count() / static_cast< float >( benchmark_trials )
              << " us" << std::endl;

    return 0;
}