#include <iostream>
#include <vector>
#include <chrono> // 用于计时
#include <memory>
#include <xmmintrin.h> // SSE 指令头文件
#include <cstdlib>     // std::aligned_alloc

// 普通的减法操作
void subtract_value(float* arr, size_t array_size, float value_to_subtract) {
    for (size_t i = 0; i < array_size; ++i) {
        arr[i] -= value_to_subtract;
    }
}

// 使用循环展开优化的减法操作
void subtract_value_unrolled_16(float* arr, size_t array_size, float value_to_subtract) {
    size_t i = 0;
    size_t stride = 16;

    // 每次处理 16 个元素
    for (; i + stride - 1 < array_size; i += stride) {
        arr[i] -= value_to_subtract;
        arr[i + 1] -= value_to_subtract;
        arr[i + 2] -= value_to_subtract;
        arr[i + 3] -= value_to_subtract;
        arr[i + 4] -= value_to_subtract;
        arr[i + 5] -= value_to_subtract;
        arr[i + 6] -= value_to_subtract;
        arr[i + 7] -= value_to_subtract;
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

// _mm_load_ps vs _mm_loadu_ps
// 使用 SSE 加速的减法操作，每次处理 32 个浮点数
void subtract_value_sse_32_f(float* arr, size_t array_size, float value_to_subtract) {
    size_t i = 0;
    __m128 vec_sub = _mm_set1_ps(value_to_subtract);

    for (; i + 31 < array_size; i += 32) {
        __m128 vec_data0 = _mm_load_ps(&arr[i]);
        __m128 vec_data1 = _mm_load_ps(&arr[i + 4]);
        __m128 vec_data2 = _mm_load_ps(&arr[i + 8]);
        __m128 vec_data3 = _mm_load_ps(&arr[i + 12]);
        __m128 vec_data4 = _mm_load_ps(&arr[i + 16]);
        __m128 vec_data5 = _mm_load_ps(&arr[i + 20]);
        __m128 vec_data6 = _mm_load_ps(&arr[i + 24]);
        __m128 vec_data7 = _mm_load_ps(&arr[i + 28]);

        vec_data0 = _mm_sub_ps(vec_data0, vec_sub);
        vec_data1 = _mm_sub_ps(vec_data1, vec_sub);
        vec_data2 = _mm_sub_ps(vec_data2, vec_sub);
        vec_data3 = _mm_sub_ps(vec_data3, vec_sub);
        vec_data4 = _mm_sub_ps(vec_data4, vec_sub);
        vec_data5 = _mm_sub_ps(vec_data5, vec_sub);
        vec_data6 = _mm_sub_ps(vec_data6, vec_sub);
        vec_data7 = _mm_sub_ps(vec_data7, vec_sub);

        _mm_store_ps(&arr[i], vec_data0);
        _mm_store_ps(&arr[i + 4], vec_data1);
        _mm_store_ps(&arr[i + 8], vec_data2);
        _mm_store_ps(&arr[i + 12], vec_data3);
        _mm_store_ps(&arr[i + 16], vec_data4);
        _mm_store_ps(&arr[i + 20], vec_data5);
        _mm_store_ps(&arr[i + 24], vec_data6);
        _mm_store_ps(&arr[i + 28], vec_data7);
    }

    // 处理剩余的元素
    for (; i < array_size; ++i) {
        arr[i] -= value_to_subtract;
    }
}


void subtract_value_sse_32_f_prefetch(float* arr, size_t array_size, float value_to_subtract) {
    size_t i = 0;
    __m128 vec_sub = _mm_set1_ps(value_to_subtract);

    // 预取步长，假设每次预取 32 个浮点数
    size_t prefetch_distance = 128; // 根据 L1 缓存大小以及数组大小来调整这个值

    for (; i + 31 < array_size; i += 32) {
        // 预取未来的内存块到缓存，使用 `_mm_prefetch`
        if (i + prefetch_distance < array_size) {
            // 使用 _MM_HINT_T0 表示预取到 L1 缓存
            _mm_prefetch(reinterpret_cast<const char*>(&arr[i + prefetch_distance]), _MM_HINT_T0);
        }

        // 加载 32 个浮点数到 8 个 SSE 寄存器中
        __m128 vec_data0 = _mm_load_ps(&arr[i]);
        __m128 vec_data1 = _mm_load_ps(&arr[i + 4]);
        __m128 vec_data2 = _mm_load_ps(&arr[i + 8]);
        __m128 vec_data3 = _mm_load_ps(&arr[i + 12]);
        __m128 vec_data4 = _mm_load_ps(&arr[i + 16]);
        __m128 vec_data5 = _mm_load_ps(&arr[i + 20]);
        __m128 vec_data6 = _mm_load_ps(&arr[i + 24]);
        __m128 vec_data7 = _mm_load_ps(&arr[i + 28]);

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
        _mm_store_ps(&arr[i], vec_data0);
        _mm_store_ps(&arr[i + 4], vec_data1);
        _mm_store_ps(&arr[i + 8], vec_data2);
        _mm_store_ps(&arr[i + 12], vec_data3);
        _mm_store_ps(&arr[i + 16], vec_data4);
        _mm_store_ps(&arr[i + 20], vec_data5);
        _mm_store_ps(&arr[i + 24], vec_data6);
        _mm_store_ps(&arr[i + 28], vec_data7);
    }

    // 处理剩余的元素
    for (; i < array_size; ++i) {
        arr[i] -= value_to_subtract;
    }
}

// 计时函数
template <typename Func>
double measure_time(Func func, float* arr, size_t array_size, float value_to_subtract) {
    auto start = std::chrono::high_resolution_clock::now();
    func(arr, array_size, value_to_subtract);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    const size_t array_size = 1e7;

    // 使用 aligned_alloc 分配内存对齐的数组
    float* arr1 = static_cast<float*>(std::aligned_alloc(16, array_size * sizeof(float)));
    float* arr2 = static_cast<float*>(std::aligned_alloc(16, array_size * sizeof(float)));

    // 初始化数组
    std::fill(arr1, arr1 + array_size, 1.0f);
    std::copy(arr1, arr1 + array_size, arr2);

    float value_to_subtract = 0.5f;

    // 计时普通的减法操作
    double time_normal = measure_time(subtract_value, arr1, array_size, value_to_subtract);
    std::cout << "Normal loop time: " << time_normal << " seconds" << std::endl;

    // 计时循环展开的减法操作
    double time_unrolled_16 = measure_time(subtract_value_unrolled_16, arr1, array_size, value_to_subtract);
    std::cout << "Unrolled loop time: " << time_unrolled_16 << " seconds" << std::endl;

    // 计时 SSE 的减法操作
    double time_sse = measure_time(subtract_value_sse_32_f, arr2, array_size, value_to_subtract);
    std::cout << "SSE loop time: " << time_sse << " seconds" << std::endl;

    // 计时 SSE 的减法操作
    double time_sse_prefetch = measure_time(subtract_value_sse_32_f_prefetch, arr2, array_size, value_to_subtract);
    std::cout << "subtract_value_sse_32_f_prefetch time: " << time_sse << " seconds" << std::endl;

    // 计算加速比
    std::cout << "SSE Speedup: " << time_normal / time_sse << std::endl;

    // 计算加速比
    std::cout << "subtract_value_sse_32_f_prefetch Speedup: " << time_normal / time_sse_prefetch << std::endl;

    // 释放对齐内存
    std::free(arr1);
    std::free(arr2);

    return 0;
}
