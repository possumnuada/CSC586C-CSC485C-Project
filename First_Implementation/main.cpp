#include <cmath>

int main() { 
// y - flux
// V - variance 
// t - time
// T - time_offset
// w - frequncy
// yavg - flux_average
// arguments: y V t T w

// Compute y average

// for each w in w
    // P[index] = function for computing P

// plot P

}

int compute_normalized_periodogram(double flux[], double flux_avg, double time[], double time_offset, double variance){

    double cos_sum_squared, cos_squared_sum, sin_sum_squared, sin_squared_sum;

    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        cos_sum_squared += (flux[i] - flux_avg) * cos(variance * (time[i] - time_offset));
    }
    cos_sum_squared = pow(cos_sum_squared, 2);

    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        cos_squared_sum += pow(cos(variance * (time[i] - time_offset)), 2);
    }

    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        sin_sum_squared += (flux[i] - flux_avg) * cos(variance * (time[i] - time_offset));
    }
    sin_sum_squared = pow(sin_sum_squared, 2);

    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        sin_squared_sum += pow(cos(variance * (time[i] - time_offset)), 2);
    }

    return 1 / (2 * variance) * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum)
}