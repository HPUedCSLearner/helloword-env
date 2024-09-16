#include <iostream>
#include <vector>
#include <chrono> // 用于计时

// 普通的减法操作
void subtract_value(std::vector<float>& arr, float value_to_subtract) {
    size_t array_size = arr.size();
    for (size_t i = 0; i < array_size; ++i) {
        arr[i] -= value_to_subtract;
    }
}

// 使用循环展开优化的减法操作
void subtract_value_unrolled_4(std::vector<float>& arr, float value_to_subtract) {
    size_t array_size = arr.size();
    size_t i = 0;

    // 每次处理 4 个元素
    for (; i + 3 < array_size; i += 4) {
        arr[i] -= value_to_subtract;
        arr[i + 1] -= value_to_subtract;
        arr[i + 2] -= value_to_subtract;
        arr[i + 3] -= value_to_subtract;
    }

    // 处理剩余的元素
    for (; i < array_size; ++i) {
        arr[i] -= value_to_subtract;
    }
}



// 使用循环展开优化的减法操作
void subtract_value_unrolled_8(std::vector<float>& arr, float value_to_subtract) {
    size_t array_size = arr.size();
    size_t i = 0;
    size_t stride = 8;

    // 每次处理 4 个元素
    for (; i + stride - 1 < array_size; i += stride) {
        arr[i] -= value_to_subtract;
        arr[i + 1] -= value_to_subtract;
        arr[i + 2] -= value_to_subtract;
        arr[i + 3] -= value_to_subtract;
        arr[i + 4] -= value_to_subtract;
        arr[i + 5] -= value_to_subtract;
        arr[i + 6] -= value_to_subtract;
        arr[i + 7] -= value_to_subtract;
    }

    // 处理剩余的元素
    for (; i < array_size; ++i) {
        arr[i] -= value_to_subtract;
    }
}

// 使用循环展开优化的减法操作
void subtract_value_unrolled_16(std::vector<float>& arr, float value_to_subtract) {
    size_t array_size = arr.size();
    size_t i = 0;
    size_t stride = 16;

    // 每次处理 4 个元素
    for (; i + stride - 1 < array_size; i += stride) {
        arr[i] -= value_to_subtract;
        arr[i + 1] -= value_to_subtract;
        arr[i + 2] -= value_to_subtract;
        arr[i + 3] -= value_to_subtract;
        arr[i + 4] -= value_to_subtract;
        arr[i + 5] -= value_to_subtract;
        arr[i + 6] -= value_to_subtract;
        arr[i + 8] -= value_to_subtract;
        arr[i + 9] -= value_to_subtract;
        arr[i + 10] -= value_to_subtract;
        arr[i + 11] -= value_to_subtract;
        arr[i + 12] -= value_to_subtract;
        arr[i + 13] -= value_to_subtract;
        arr[i + 14] -= value_to_subtract;
        arr[i + 15] -= value_to_subtract;
    }

    // 处理剩余的元素
    for (; i < array_size; ++i) {
        arr[i] -= value_to_subtract;
    }
}


// 使用循环展开优化的减法操作
void subtract_value_unrolled_32(std::vector<float>& arr, float value_to_subtract) {
    size_t array_size = arr.size();
    size_t i = 0;
    size_t stride = 32;

    // 每次处理 4 个元素
    for (; i + stride - 1 < array_size; i += stride) {
        arr[i] -= value_to_subtract;
        arr[i + 1] -= value_to_subtract;
        arr[i + 2] -= value_to_subtract;
        arr[i + 3] -= value_to_subtract;
        arr[i + 4] -= value_to_subtract;
        arr[i + 5] -= value_to_subtract;
        arr[i + 6] -= value_to_subtract;
        arr[i + 8] -= value_to_subtract;
        arr[i + 9] -= value_to_subtract;
        arr[i + 10] -= value_to_subtract;
        arr[i + 11] -= value_to_subtract;
        arr[i + 12] -= value_to_subtract;
        arr[i + 13] -= value_to_subtract;
        arr[i + 14] -= value_to_subtract;
        arr[i + 15] -= value_to_subtract;
        arr[i + 16] -= value_to_subtract;
        arr[i + 17] -= value_to_subtract;
        arr[i + 18] -= value_to_subtract;
        arr[i + 19] -= value_to_subtract;
        arr[i + 20] -= value_to_subtract;
        arr[i + 21] -= value_to_subtract;
        arr[i + 22] -= value_to_subtract;
        arr[i + 23] -= value_to_subtract;
        arr[i + 24] -= value_to_subtract;
        arr[i + 25] -= value_to_subtract;
        arr[i + 26] -= value_to_subtract;
        arr[i + 27] -= value_to_subtract;
        arr[i + 28] -= value_to_subtract;
        arr[i + 29] -= value_to_subtract;
        arr[i + 30] -= value_to_subtract;
        arr[i + 31] -= value_to_subtract;
    }

    // 处理剩余的元素
    for (; i < array_size; ++i) {
        arr[i] -= value_to_subtract;
    }
}


// 计时函数
template <typename Func>
double measure_time(Func func, std::vector<float>& arr, float value_to_subtract) {
    auto start = std::chrono::high_resolution_clock::now(); // 记录开始时间
    func(arr, value_to_subtract); // 执行函数
    auto end = std::chrono::high_resolution_clock::now();   // 记录结束时间
    std::chrono::duration<double> elapsed = end - start;    // 计算耗时
    return elapsed.count();
}

int main() {
    const size_t array_size = 1e7; // 数组大小，可以调整
    std::vector<float> arr1(array_size, 1.0f); // 初始化数组1
    std::vector<float> arr2 = arr1; // 复制一份数组2
    float value_to_subtract = 0.5f;

    // 计时普通的减法操作
    double time_normal = measure_time(subtract_value, arr1, value_to_subtract);
    std::cout << "Normal loop time: " << time_normal << " seconds" << std::endl;

    // 计时循环展开的减法操作
    double time_unrolled_4 = measure_time(subtract_value_unrolled_4, arr2, value_to_subtract);
    std::cout << "Unrolled loop time: " << time_unrolled_4 << " seconds" << std::endl;

    // 计时循环展开的减法操作
    double time_unrolled_8 = measure_time(subtract_value_unrolled_8, arr2, value_to_subtract);
    std::cout << "Unrolled loop time: " << time_unrolled_8 << " seconds" << std::endl;

    // 计时循环展开的减法操作
    double time_unrolled_16 = measure_time(subtract_value_unrolled_16, arr2, value_to_subtract);
    std::cout << "Unrolled loop time: " << time_unrolled_16 << " seconds" << std::endl;

    // 计时循环展开的减法操作
    double time_unrolled_32 = measure_time(subtract_value_unrolled_32, arr2, value_to_subtract);
    std::cout << "Unrolled loop time: " << time_unrolled_32 << " seconds" << std::endl;

    // 计算加速比
    double speedup = time_normal / time_unrolled_4;
    std::cout << "Unroll 4 Speedup: " << speedup << std::endl;
    
    // 计算加速比
    speedup = time_normal / time_unrolled_8;
    std::cout << "Unroll 8 Speedup: " << speedup << std::endl;


    // 计算加速比
    speedup = time_normal / time_unrolled_16;
    std::cout << "Unroll 16 Speedup: " << speedup << std::endl;


    // 计算加速比
    speedup = time_normal / time_unrolled_32;
    std::cout << "Unroll 32 Speedup: " << speedup << std::endl;

    

    return 0;
}
