#include <cmath>
#include <vector>
#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/functional.h>
#include <thrust/transform.h>

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

__global__
void calcAvg(double *flux, double *result, size_t size){
    int const w = threadIdx.x + blockIdx.x * blockDim.x;
    *result += flux[w];

}

void lomb_scargle(double *flux, double *time, double *frequency, double *periodogram, double variance, size_t sample_size, size_t num_frequencies){

    double *dev_frequency, *dev_periodogram;
    thrust::device_vector<double> time2(time,time+sample_size);
    thrust::device_vector<double> flux2(flux,flux+sample_size);
 
    cudaMalloc( (void **) &dev_frequency, num_frequencies * sizeof(double));
    cudaMalloc( (void **) &dev_periodogram, num_frequencies * sizeof(double));

    cudaMemcpy( dev_frequency, frequency, num_frequencies * sizeof(double), cudaMemcpyHostToDevice );

    
    double flux_avg = thrust::reduce(flux2.begin(), flux2.end())/sample_size;
    using namespace thrust::placeholders;
    thrust::transform(flux2.begin(), flux2.end(), flux2.begin(), _1 - flux_avg); 
    thrust::transform(time2.begin(), time2.end(), time2.begin(), _1 - time[0]); 

    double one_over_2variance = 1 / (2 * variance);
    auto const num_blocks = ceil(num_frequencies/ static_cast< float >(blocksize));

    periodogram_frequency<<< num_blocks, blocksize >>>(thrust::raw_pointer_cast(time2.data()), thrust::raw_pointer_cast(flux2.data()), dev_frequency, dev_periodogram, one_over_2variance, sample_size, num_frequencies);
    
    //Cuda fails silently, need this to see errors
    cudaError_t err2 = cudaGetLastError();
    if (err2 != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err2));
    cudaMemcpy( periodogram, dev_periodogram, num_frequencies * sizeof(double), cudaMemcpyDeviceToHost );

    cudaFree(dev_frequency);
    cudaFree(dev_periodogram);
}

