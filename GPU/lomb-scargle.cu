#include <cmath>
#include <vector>

int const blocksize = 512;

void lomb_scargle(double *flux, double *time, double *frequency, double *periodogram, double variance){

    int sample_size = sizeof(flux)/sizeof(flux[0]);
    int num_frequencies = sizeof(frequency)/sizeof(frequency[0]);

    double flux_total = 0;
    for(int i = 0; i<sample_size ; i++){
        flux_total += flux[i];
    }
    double flux_avg = flux_total/sample_size;
    
    double initial_time = time[0];
    for(int i = 0 ; i < sample_size ; i++){
        time[i] -= initial_time;
    }

    for(int i = 0 ; i< sample_size ; i++){
        flux[i] -= flux_avg;
    }

    // Allocate memory on GPU
    double *dev_time, *dev_flux, *dev_frequency, *dev_periodogram;

    cudaMalloc( (void **) &dev_time, sample_size);
    cudaMalloc( (void **) &dev_flux, sample_size);
    cudaMalloc( (void **) &dev_frequency, num_frequencies);
    cudaMalloc( (void **) &dev_periodogram, num_frequencies);


    cudaMemcpy( dev_time, time, sample_size, cudaMemcpyHostToDevice );
    cudaMemcpy( dev_flux, flux, sample_size, cudaMemcpyHostToDevice );
    cudaMemcpy( dev_frequency, frequency, sample_size, cudaMemcpyHostToDevice );

    double one_over_2variance = 1 / (2 * variance);

    auto const num_blocks = ceil(num_frequencies/ static_cast< float >(blocksize));

    periodogram_frequency<<< num_blocks, blocksize >>>(dev_time, dev_flux, dev_frequency, dev_periodogram, one_over_2variance, sample_size, num_frequencies);

    cudaMemcpy( periodogram, dev_periodogram, sample_size, cudaMemcpyDeviceToHost );
}


__global__
void periodogram_frequency(float *flux, float *time, float *frequency, float *periodogram, float one_over_2variance, size_t sample_size, size_t num_frequencies){
    // Calculate frequency index
    int const w = threadIdx.x + blockIdx.x * blockDim.x;

    if ( w < num_frequencies) {    
        double cos_sum_squared = 0llu, cos_squared_sum = 0llu, sin_sum_squared = 0llu, sin_squared_sum = 0llu;
        // Not sure if we can do this, maybe we have to use cudaMalloc and pass in?
        double time2[sample_size], sins[sample_size], coss[sample_size];
        double frequency_2_pi = 2 * M_PI * frequency[w];

        for(int i = 0; i < sample_size ; i++){
            time2[i] = frequency_2_pi * time[i];
        }
        for (int i = 0 ; i < sample_size ; i++){
            coss[i] = cos(time2[i]);
        }
        for (int i = 0 ; i < sample_size ; i++){
            sins[i] = sin(time2[i]);
        }
        for(int i = 0; i< sample_size;i++){
            cos_sum_squared += flux[i] * coss[i];
            cos_squared_sum += coss[i] * coss[i];
            sin_sum_squared += flux[i] * sins[i];
            sin_squared_sum += sins[i] * sins[i];
        }
        cos_sum_squared = cos_sum_squared * cos_sum_squared;
        sin_sum_squared = sin_sum_squared * sin_sum_squared;

        periodogram[w] = one_over_2variance * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
    }
}

