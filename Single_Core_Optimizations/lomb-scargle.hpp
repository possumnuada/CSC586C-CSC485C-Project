#include <cmath>
#include <vector>

std::vector<double> lomb_scargle(std::vector<double> flux, std::vector<double> time, std::vector<double> frequency, double variance){

    int sample_size = flux.size();
    // double cos_sum_squared[4], cos_squared_sum[4], sin_sum_squared[4], sin_squared_sum[4];
    double flux_avg = std::accumulate( flux.begin(), flux.end(), 0llu)/ sample_size;
    std::vector<double> periodogram(frequency.size());

    double initial_time = time[0];
    for(int i = 0 ; i < sample_size ; i++ ){
        time[i] = time[i] - initial_time;
    }

    for(int i = 0 ; i< sample_size ; i++){
        flux[i] = flux[i] - flux_avg;
    }

    for(int w = 0 ; w < frequency.size() ; w++){
        double cos_sum_squared[4] = {0.0, 0.0, 0.0, 0.0};
        double cos_squared_sum[4] = {0.0, 0.0, 0.0, 0.0};
        double sin_sum_squared[4] = {0.0, 0.0, 0.0, 0.0};
        double sin_squared_sum[4] = {0.0, 0.0, 0.0, 0.0};
        double frequency_2_pi = 2 * M_PI * frequency[w];
        int num_unrolls = 2;
        for (int i = 0 ; i < sample_size ; i+=num_unrolls){
            double cos_result = cos(frequency_2_pi * time[i]);
            double sin_result = sin(frequency_2_pi * time[i]);
            cos_sum_squared[0] += flux[i] * cos_result;
            cos_squared_sum[0] += cos_result * cos_result;
            sin_sum_squared[0] += flux[i] * sin_result;
            sin_squared_sum[0] += sin_result * sin_result;
            
            double cos_result2 = cos(frequency_2_pi * time[i + 1]);
            double sin_result2 = sin(frequency_2_pi * time[i + 1]);
            cos_sum_squared[1] += flux[i + 1] * cos_result2;
            cos_squared_sum[1] += cos_result2 * cos_result2;
            sin_sum_squared[1] += flux[i + 1] * sin_result2;
            sin_squared_sum[1] += sin_result2 * sin_result2;

            // double cos_result3 = cos(frequency_2_pi * time[i + 2]);
            // double sin_result3 = sin(frequency_2_pi * time[i + 2]);
            // cos_sum_squared += flux[i + 2] * cos_result3;
            // cos_squared_sum += cos_result3 * cos_result3;
            // sin_sum_squared += flux[i + 2] * sin_result3;
            // sin_squared_sum += sin_result3 * sin_result3;
            
            // double cos_result4 = cos(frequency_2_pi * time[i + 3]);
            // double sin_result4 = sin(frequency_2_pi * time[i + 3]);
            // cos_sum_squared += flux[i + 3] * cos_result4;
            // cos_squared_sum += cos_result4 * cos_result4;
            // sin_sum_squared += flux[i + 3] * sin_result4;
            // sin_squared_sum += sin_result4 * sin_result4;
        }

        double cos_sum_squared_total =  (cos_sum_squared[0] + cos_sum_squared[1]) * (cos_sum_squared[0] + cos_sum_squared[1]);
        double sin_sum_squared_total = (sin_sum_squared[0] + sin_sum_squared[1]) * (sin_sum_squared[0] + sin_sum_squared[1]);

        periodogram.at(w) = 1 / (2 * variance) * (cos_sum_squared_total/(cos_squared_sum[0] + cos_squared_sum[1]) + sin_sum_squared_total/(sin_squared_sum[0] + sin_squared_sum[1]));
    }

    return periodogram;
}

