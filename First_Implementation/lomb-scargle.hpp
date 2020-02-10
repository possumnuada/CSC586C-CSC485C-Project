#include <cmath>
#include <vector>

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


std::vector<double> lomb_scargle(std::vector<double> flux, std::vector<double> time, std::vector<double> frequency, double variance){

    double cos_sum_squared, cos_squared_sum, sin_sum_squared, sin_squared_sum;
    double flux_avg = std::accumulate( flux.begin(), flux.end(), 0llu)/ flux.size();
    std::vector<double> periodogram(frequency.size());

    for(int w = 0 ; w < frequency.size() ; w++){
        cos_sum_squared = 0llu;
        cos_squared_sum = 0llu;
        sin_sum_squared = 0llu;
        sin_squared_sum = 0llu;
        for (int i = 0 ; i < flux.size(); i++){
            cos_sum_squared += (flux[i] - flux_avg) * cos(2* M_PI *frequency[w] * (time[i] - time[0]));
        }
        cos_sum_squared = pow(cos_sum_squared, 2);
        

        for (int i = 0 ; i < flux.size(); i++){
            cos_squared_sum += pow(cos(2* M_PI *frequency[w] * (time[i] - time[0])), 2);
        }
        

        for (int i = 0 ; i < flux.size(); i++){
            sin_sum_squared += (flux[i] - flux_avg) * cos(2* M_PI *frequency[w] * (time[i] - time[0]));
        }
        sin_sum_squared = pow(sin_sum_squared, 2);
       

        for (int i = 0 ; i < flux.size(); i++){
            sin_squared_sum += pow(cos(2* M_PI *frequency[w] * (time[i] - time[0])), 2);
        }
        
        periodogram.at(w) = 1 / (2 * variance) * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
    }

    return periodogram;
}

