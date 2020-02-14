#include <cmath>
#include <vector>

std::vector<double> lomb_scargle(std::vector<double> flux, std::vector<double> time, std::vector<double> frequency, double variance){

    double cos_sum_squared, cos_squared_sum, sin_sum_squared, sin_squared_sum;
    double flux_avg = std::accumulate( flux.begin(), flux.end(), 0llu)/ flux.size();
    std::vector<double> periodogram(frequency.size());

    double initial_time = time[0];
    for(int i = 0 ; i < time.size() ; i++ ){
        time[i] = time[i] - initial_time;
    }

    for(int i = 0 ; i< flux.size() ; i++){
        flux[i] = flux[i] - flux_avg;
    }

    for(int w = 0 ; w < frequency.size() ; w++){
        cos_sum_squared = 0llu;
        cos_squared_sum = 0llu;
        sin_sum_squared = 0llu;
        sin_squared_sum = 0llu;
        for (int i = 0 ; i < flux.size(); i++){
            double cos_result = cos(2* M_PI *frequency[w] * time[i]);
            double sin_result = sin(2* M_PI *frequency[w] * time[i]);
            cos_sum_squared += flux[i] * cos_result;
            cos_squared_sum += pow(cos_result, 2);
            sin_sum_squared += flux[i] * sin_result;
            sin_squared_sum += pow(sin_result, 2);
        }
        cos_sum_squared = pow(cos_sum_squared, 2);
        sin_sum_squared = pow(sin_sum_squared, 2);

        periodogram.at(w) = 1 / (2 * variance) * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
    }

    return periodogram;
}

