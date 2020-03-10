#include <cmath>
#include <vector>
#include <omp.h>

std::vector<double> lomb_scargle(std::vector<double> flux, std::vector<double> time, std::vector<double> frequency, double variance){

    int sample_size = flux.size();
    int num_frequencies = frequency.size();
    double cos_sum_squared, cos_squared_sum, sin_sum_squared, sin_squared_sum;
    double flux_avg = std::accumulate( flux.begin(), flux.end(), 0llu)/ sample_size;
    std::vector<double> periodogram(frequency.size());
    std::vector<double> time2(sample_size * omp_get_max_threads());
    std::vector<double> sins(sample_size * omp_get_max_threads());
    std::vector<double> coss(sample_size * omp_get_max_threads());

    double initial_time = time[0];
    double one_over_2variance = 1 / (2 * variance);
    for(int i = 0 ; i < sample_size ; i++){
        time[i] -= initial_time;
    }

    for(int i = 0 ; i< sample_size ; i++){
        flux[i] -= flux_avg;
    }

    #pragma omp parallel for 
    for(int w = 0 ; w < num_frequencies ; w++){
        
        int offset = omp_get_thread_num() * sample_size;
        cos_sum_squared = 0llu;
        cos_squared_sum = 0llu;
        sin_sum_squared = 0llu;
        sin_squared_sum = 0llu;
        double frequency_2_pi = 2 * M_PI * frequency[w];
        
        for(int i = offset; i < (offset + sample_size);i++){
            time2[i] = frequency_2_pi * time[i-offset];
        }

        for (int i = offset ; i < (offset + sample_size) ; i++){
            coss[i] = cos(time2[i]);
        }

        for (int i = offset ; i < (offset + sample_size) ; i++){
            sins[i] = sin(time2[i]);
        }
    
        for(int i = 0; i< sample_size;i++){
            int j = i +offset;
            cos_sum_squared += flux[i] * coss[j];
            cos_squared_sum += coss[j] * coss[j];
            sin_sum_squared += flux[i] * sins[j];
            sin_squared_sum += sins[j] * sins[j];
        }
        cos_sum_squared = cos_sum_squared * cos_sum_squared;
        sin_sum_squared = sin_sum_squared * sin_sum_squared;

        periodogram[w] = one_over_2variance * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
    }

    return periodogram;
}

