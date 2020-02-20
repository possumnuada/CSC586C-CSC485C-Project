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
        double cos_sum_squared[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
        double cos_squared_sum[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
        double sin_sum_squared[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
        double sin_squared_sum[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
        double frequency_2_pi = 2 * M_PI * frequency[w];
        int num_unrolls = 5;
        for (int i = 0 ; i < sample_size ; i+=num_unrolls){
            double frequency_2_pi_time1 = frequency_2_pi * time[i];
            double cos_result1 = cos(frequency_2_pi_time1);
            double sin_result1 = sin(frequency_2_pi_time1);
            cos_sum_squared[0] += flux[i] * cos_result1;
            cos_squared_sum[0] += cos_result1 * cos_result1;
            sin_sum_squared[0] += flux[i] * sin_result1;
            sin_squared_sum[0] += sin_result1 * sin_result1;
            
            double frequency_2_pi_time2 = frequency_2_pi * time[i + 1];
            double cos_result2 = cos(frequency_2_pi_time2);
            double sin_result2 = sin(frequency_2_pi_time2);
            cos_sum_squared[1] += flux[i + 1] * cos_result2;
            cos_squared_sum[1] += cos_result2 * cos_result2;
            sin_sum_squared[1] += flux[i + 1] * sin_result2;
            sin_squared_sum[1] += sin_result2 * sin_result2;

            double frequency_2_pi_time3 = frequency_2_pi * time[i + 2];
            double cos_result3 = cos(frequency_2_pi_time3);
            double sin_result3 = sin(frequency_2_pi_time3);
            cos_sum_squared[2] += flux[i + 2] * cos_result3;
            cos_squared_sum[2] += cos_result3 * cos_result3;
            sin_sum_squared[2] += flux[i + 2] * sin_result3;
            sin_squared_sum[2] += sin_result3 * sin_result3;

            double frequency_2_pi_time4 = frequency_2_pi * time[i + 3];
            double cos_result4 = cos(frequency_2_pi_time4);
            double sin_result4 = sin(frequency_2_pi_time4);
            cos_sum_squared[3] += flux[i + 3] * cos_result4;
            cos_squared_sum[3] += cos_result4 * cos_result4;
            sin_sum_squared[3] += flux[i + 3] * sin_result4;
            sin_squared_sum[3] += sin_result4 * sin_result4;

            double frequency_2_pi_time5 = frequency_2_pi * time[i + 4];
            double cos_result5 = cos(frequency_2_pi_time5);
            double sin_result5 = sin(frequency_2_pi_time5);
            cos_sum_squared[4] += flux[i + 4] * cos_result5;
            cos_squared_sum[4] += cos_result5 * cos_result5;
            sin_sum_squared[4] += flux[i + 4] * sin_result5;
            sin_squared_sum[4] += sin_result5 * sin_result5;
        }

        double cos_sum_squared_total = std::accumulate(cos_sum_squared, cos_sum_squared + num_unrolls, 0.0);
        double cos_squared_sum_total = std::accumulate(cos_squared_sum, cos_squared_sum + num_unrolls, 0.0);
        double sin_sum_squared_total = std::accumulate(sin_sum_squared, sin_sum_squared + num_unrolls, 0.0);
        double sin_squared_sum_total = std::accumulate(sin_squared_sum, sin_squared_sum + num_unrolls, 0.0);

        cos_sum_squared_total = cos_sum_squared_total * cos_sum_squared_total;
        sin_sum_squared_total = sin_sum_squared_total * sin_sum_squared_total;

        periodogram.at(w) = 1 / (2 * variance) * (cos_sum_squared_total/cos_squared_sum_total + sin_sum_squared_total/sin_squared_sum_total);
    }

    return periodogram;
}

