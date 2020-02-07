
int main() { 
// y - flux
// V - variance 
// t - time
// T - time_offset
// w - frequncy
// yavg - flux_average
// w - error
// arguments: y V t T w

// Compute y average

// for each w in w
    // P[index] = function for computing P

// plot P

}

int compute_normilized_periodogram(double flux[], double flux_avg, double time[], double time_offset, double error, double varience){
// function for computing P, arguments y, yavg, t, T, w scalar, V

// for each y, t
    // cos_sum_squared += (y-yavg)cosw(t-T)
// sum^2

// for each y, t
    // cos_squared_sum += (cosw(t-T))^2

// for each y, t
    // sin_sum_squared += (y-yavg)sinw(t-T)
// sum^2

// for each y, t
    // sin_squared_sum += (sinw(t-T))^2

// return 1/(2V)(cos_sum_squared/cos_squared_sum + sin_sum_squared/sin_squared_sum)
}