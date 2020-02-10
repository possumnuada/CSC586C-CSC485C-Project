#include <cmath>

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

double compute_normalized_periodogram(double flux[], double flux_avg, double time[], double time_offset, double variance, double frequency){

    double cos_sum_squared, cos_squared_sum, sin_sum_squared, sin_squared_sum;

    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        cos_sum_squared += (flux[i] - flux_avg) * cos(frequency * (time[i] - time_offset));
    }
    cos_sum_squared = pow(cos_sum_squared, 2);

    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        cos_squared_sum += pow(cos(frequency * (time[i] - time_offset)), 2);
    }

    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        sin_sum_squared += (flux[i] - flux_avg) * cos(frequency * (time[i] - time_offset));
    }
    sin_sum_squared = pow(sin_sum_squared, 2);

    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        sin_squared_sum += pow(cos(frequency * (time[i] - time_offset)), 2);
    }

    return 1 / (2 * variance) * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
}

double * lomb_scargle(double flux[], double time[],double variance, double frequncies[] ){
    double * powers = new double[sizeof(frequncies)/sizeof(frequncies[0])];
    double flux_avg = 0;
    for (int i = 0 ; i < sizeof(flux)/sizeof(flux[0]); i++){
        flux_avg += flux[i];
    }
    flux_avg /= (sizeof(flux)/sizeof(flux[0]));

    for (int i = 0 ; i < sizeof(frequncies)/sizeof(frequncies[0]); i++){
        powers[i] = compute_normalized_periodogram(flux,flux_avg,time,time[0],variance,frequncies[i]);    
    }
    return powers;
}

