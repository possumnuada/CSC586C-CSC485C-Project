#include <cmath>
#include <vector>

int main() { 
// y - flux
// V - variance 
// t - time
// T - time_offset
// w - frequency
// yavg - flux_average

    // Get data
    // Call compute_normalized_periodogram
    // plot periodogram
}

// Compute flux[i] - flux_avg and time[i] - time_offset for each i once, pass in to this function
// Use one for loop
// Loop unrolling


std::vector<double> compute_normalized_periodogram(std::vector<double> flux, double flux_avg, std::vector<double> time, double time_offset, std::vector<double> frequency, double variance){

    double cos_sum_squared, cos_squared_sum, sin_sum_squared, sin_squared_sum;
    std::vector<double> periodogram(frequency.size());

    for(int w = 0 ; w < frequency.size() ; w++){
        for (int i = 0 ; i < flux.size(); i++){
            cos_sum_squared += (flux[i] - flux_avg) * cos(frequency[w] * (time[i] - time_offset));
        }
        cos_sum_squared = pow(cos_sum_squared, 2);

        for (int i = 0 ; i < flux.size(); i++){
            cos_squared_sum += pow(cos(frequency[w] * (time[i] - time_offset)), 2);
        }

        for (int i = 0 ; i < flux.size(); i++){
            sin_sum_squared += (flux[i] - flux_avg) * cos(frequency[w] * (time[i] - time_offset));
        }
        sin_sum_squared = pow(sin_sum_squared, 2);

        for (int i = 0 ; i < flux.size(); i++){
            sin_squared_sum += pow(cos(frequency[w] * (time[i] - time_offset)), 2);
        }

        periodogram[w] = 1 / (2 * variance) * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
    }

    return periodogram;
}