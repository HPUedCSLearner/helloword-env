#include <iostream>
#include <vector>
#include <chrono> // 用于计时

#include <memory>
#include <xmmintrin.h> // SSE 指令头文件

// 普通的减法操作
void subtract_value(std::vector<float>& arr, float value_to_subtract) {
    size_t array_size = arr.size();
    for (size_t i = 0; i < array_size; ++i) {
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

// 使用 SSE 加速的减法操作，每次处理 32 个浮点数
void subtract_value_sse_32_f(std::vector<float>& arr, float value_to_subtract) {
    size_t array_size = arr.size();
    size_t i = 0;

    // 创建一个包含 4 个 value_to_subtract 的向量
    __m128 vec_sub = _mm_set1_ps(value_to_subtract);

    // 每次处理 32 个元素（8 次 4 元素处理）
    for (; i + 31 < array_size; i += 32) {
        // 加载 32 个浮点数到 8 个 SSE 寄存器中
        __m128 vec_data0 = _mm_loadu_ps(&arr[i]);
        __m128 vec_data1 = _mm_loadu_ps(&arr[i + 4]);
        __m128 vec_data2 = _mm_loadu_ps(&arr[i + 8]);
        __m128 vec_data3 = _mm_loadu_ps(&arr[i + 12]);
        __m128 vec_data4 = _mm_loadu_ps(&arr[i + 16]);
        __m128 vec_data5 = _mm_loadu_ps(&arr[i + 20]);
        __m128 vec_data6 = _mm_loadu_ps(&arr[i + 24]);
        __m128 vec_data7 = _mm_loadu_ps(&arr[i + 28]);

        // 执行减法操作
        vec_data0 = _mm_sub_ps(vec_data0, vec_sub);
        vec_data1 = _mm_sub_ps(vec_data1, vec_sub);
        vec_data2 = _mm_sub_ps(vec_data2, vec_sub);
        vec_data3 = _mm_sub_ps(vec_data3, vec_sub);
        vec_data4 = _mm_sub_ps(vec_data4, vec_sub);
        vec_data5 = _mm_sub_ps(vec_data5, vec_sub);
        vec_data6 = _mm_sub_ps(vec_data6, vec_sub);
        vec_data7 = _mm_sub_ps(vec_data7, vec_sub);

        // 将结果存储回数组
        _mm_storeu_ps(&arr[i], vec_data0);
        _mm_storeu_ps(&arr[i + 4], vec_data1);
        _mm_storeu_ps(&arr[i + 8], vec_data2);
        _mm_storeu_ps(&arr[i + 12], vec_data3);
        _mm_storeu_ps(&arr[i + 16], vec_data4);
        _mm_storeu_ps(&arr[i + 20], vec_data5);
        _mm_storeu_ps(&arr[i + 24], vec_data6);
        _mm_storeu_ps(&arr[i + 28], vec_data7);
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
    // std::vector<float, aligned_alloc<float, 16>> arr1(array_size, 1.0f); // 初始化数组1
    std::vector<float> arr2 = arr1; // 复制一份数组2
    float value_to_subtract = 0.5f;

    // 计时普通的减法操作
    double time_normal = measure_time(subtract_value, arr1, value_to_subtract);
    std::cout << "Normal loop time: " << time_normal << " seconds" << std::endl;

    // 计时循环展开的减法操作
    double time_unrolled_16 = measure_time(subtract_value_unrolled_16, arr2, value_to_subtract);
    std::cout << "Unrolled loop time: " << time_unrolled_16 << " seconds" << std::endl;

    // 计时循环展开的减法操作
    double time_unrolled_32 = measure_time(subtract_value_unrolled_32, arr2, value_to_subtract);
    std::cout << "Unrolled loop time: " << time_unrolled_32 << " seconds" << std::endl;
    // 计时循环展开的减法操作
    double time_subtract_value_sse_32_f_f = measure_time(subtract_value_sse_32_f, arr2, value_to_subtract);
    std::cout << "Unrolled loop + sse_32_f time: " << time_subtract_value_sse_32_f_f << " seconds" << std::endl;



    // 计算加速比
    double speedup = time_normal / time_unrolled_16;
    std::cout << "Unroll 16 Speedup: " << speedup << std::endl;


    // 计算加速比
    speedup = time_normal / time_unrolled_32;
    std::cout << "Unroll 32 Speedup: " << speedup << std::endl;


    // 计算加速比
    speedup = time_normal / time_subtract_value_sse_32_f_f;
    std::cout << "Unroll 32 + SSE Speedup: " << speedup << std::endl;

    

    return 0;
}
