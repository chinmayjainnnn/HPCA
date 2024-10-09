// Optimize this function

#include <algorithm>

void singleThread( int input_row, 
                int input_col,
                int *input, 
                int kernel_row, 
                int kernel_col, 
                int *kernel,
                int output_row, 
                int output_col, 
                long long unsigned int *output ) 
{
    
    // Initialize the output array with zeros
    std::fill(output, output + output_row * output_col, 0);

    const int input_row_effective = input_row + 2 * kernel_row;
    const int input_col_effective = input_col + 2 * kernel_col;

    // Unroll the outer loop for output_i
    for (int output_i = 0; output_i < output_row; ++output_i)
    {
        // Pre-calculate the effective input_i using modular arithmetic
        int input_i_base = (output_i * input_row_effective) % input_row;

        // Unroll the outer loop for output_j
        for (int output_j = 0; output_j < output_col; ++output_j)
        {
            long long unsigned int sum = 0;

            // Pre-calculate the effective input_j using modular arithmetic
            int input_j_base = (output_j * input_col_effective) % input_col;

            // Unroll the kernel_i loop
            for (int kernel_i = 0; kernel_i < kernel_row; ++kernel_i)
            {
                int input_i = (input_i_base + 2 * kernel_i) % input_row;

                // Unroll the kernel_j loop
                for (int kernel_j = 0; kernel_j < kernel_col; ++kernel_j)
                {
                    int input_j = (input_j_base + 2 * kernel_j) % input_col;

                    // Accumulate the result using += to avoid repeated array access
                    sum += input[input_i * input_col + input_j] * kernel[kernel_i * kernel_col + kernel_j];
                }
            }

            // Store the final result in the output array
            output[output_i * output_col + output_j] = sum;
                }
            }
        }
}


