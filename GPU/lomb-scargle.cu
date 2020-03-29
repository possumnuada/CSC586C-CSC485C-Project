#include <cmath>
#include <vector>

int const blocksize = 512;


__global__
void periodogram_frequency( double *time, double *flux, double *frequency, double *periodogram, double one_over_2variance, size_t sample_size, size_t num_frequencies){
    // Calculate frequency index

    //One thing, printf works from the kernel but only up to a certain length then it just doesn't print anymore. Learnt that the hard way...
    int const w = threadIdx.x + blockIdx.x * blockDim.x;
    if ( w < num_frequencies) { 
       
        double cos_sum_squared = 0llu, cos_squared_sum = 0llu, sin_sum_squared = 0llu, sin_squared_sum = 0llu;
       
        
        double frequency_2 = 2 * frequency[w];
   
        //A potential way forward might be to split the frequencies across blocks and this across threads? I had to remove the temp arrays as there wasn't enough memory
        //Also not really sure we need them anymore as they were mainly for vectorization
        for(int i = 0; i< sample_size;i++){
            double coscal;
            double sincal;
            sincospi(frequency_2 * time[i],&sincal,&coscal);
            cos_sum_squared = fma(flux[i],coscal,cos_sum_squared);
            cos_squared_sum = fma(coscal, coscal,cos_squared_sum);
            sin_sum_squared = fma(flux[i], sincal,sin_sum_squared);
            sin_squared_sum = fma(sincal, sincal,sin_squared_sum);
        }
        cos_sum_squared = cos_sum_squared * cos_sum_squared;
        sin_sum_squared = sin_sum_squared * sin_sum_squared;

        periodogram[w] = one_over_2variance * (cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum);
    }
}

void lomb_scargle(double *flux, double *time, double *frequency, double *periodogram, double variance, size_t sample_size, size_t num_frequencies){

    double *time2 = new double[sample_size];
    double *flux2 = new double[sample_size];
    
    double flux_total = 0llu;
    for(int i = 0; i<sample_size ; i++){
        flux_total =  flux_total + flux[i];
    }

    double flux_avg = flux_total/sample_size;
    
    double initial_time = time[0];
    for(int i = 0 ; i < sample_size ; i++){
        time2[i] = time[i] - initial_time;
        flux2[i] = flux[i] - flux_avg;
    }

    double *dev_time, *dev_flux, *dev_frequency, *dev_periodogram;

    cudaMalloc( (void **) &dev_time, sample_size * sizeof(double));
    cudaMalloc( (void **) &dev_flux, sample_size * sizeof(double));
    cudaMalloc( (void **) &dev_frequency, num_frequencies * sizeof(double));
    cudaMalloc( (void **) &dev_periodogram, num_frequencies * sizeof(double));


    cudaMemcpy( dev_time, time2, sample_size * sizeof(double), cudaMemcpyHostToDevice );
    cudaMemcpy( dev_flux, flux2, sample_size * sizeof(double), cudaMemcpyHostToDevice );
    cudaMemcpy( dev_frequency, frequency, num_frequencies * sizeof(double), cudaMemcpyHostToDevice );

    double one_over_2variance = 1 / (2 * variance);

    auto const num_blocks = ceil(num_frequencies/ static_cast< float >(blocksize));

    periodogram_frequency<<< num_blocks, blocksize >>>(dev_time, dev_flux, dev_frequency, dev_periodogram, one_over_2variance, sample_size, num_frequencies);
    
    //Cuda fails silently, need this to see errors
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err));
    cudaMemcpy( periodogram, dev_periodogram, num_frequencies * sizeof(double), cudaMemcpyDeviceToHost );
}

