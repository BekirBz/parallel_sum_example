//
//  main.cpp
//  
//
//  Created by Bekir Bozoklar on 27.04.2025.
//

#include <iostream>
#include <vector>
#include <thread>  // Thread'ler için
#include <chrono>  // Zaman ölçümü için

// Thread fonksiyonu: kendi bölümündeki toplamı hesaplar
void partial_sum(const std::vector<int>& data, size_t start, size_t end, long long& result) {
    long long sum = 0;
    for (size_t i = start; i < end; ++i) {
        sum += data[i];
    }
    result = sum; // Sonucu referansla döndür
}

int main() {
    const size_t DATA_SIZE = 100'000'000; // 100 milyon eleman
    const size_t NUM_THREADS = 4;          // 4 thread kullanacağız

    std::vector<int> data(DATA_SIZE, 1);   // Bütün elemanlar 1

    // --- Single-threaded Toplama ---

    auto start_single = std::chrono::high_resolution_clock::now();

    long long total_sum_single = 0;
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        total_sum_single += data[i];
    }

    auto end_single = std::chrono::high_resolution_clock::now();
    auto duration_single = std::chrono::duration_cast<std::chrono::milliseconds>(end_single - start_single);

    std::cout << "Single-threaded Sum: " << total_sum_single << std::endl;
    std::cout << "Single-threaded Execution Time: " << duration_single.count() << " milliseconds" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    // --- Multi-threaded Toplama ---

    std::vector<long long> partial_sums(NUM_THREADS, 0);
    std::vector<std::thread> threads;
    size_t chunk_size = DATA_SIZE / NUM_THREADS;

    auto start_multi = std::chrono::high_resolution_clock::now();

    // Thread'leri başlat
    for (size_t i = 0; i < NUM_THREADS; ++i) {
        size_t start_idx = i * chunk_size;
        size_t end_idx = (i == NUM_THREADS - 1) ? DATA_SIZE : (i + 1) * chunk_size;
        threads.emplace_back(partial_sum, std::cref(data), start_idx, end_idx, std::ref(partial_sums[i]));
    }

    // Bütün thread'lerin bitmesini bekle
    for (auto& t : threads) {
        t.join();
    }

    // Kısmi toplamları birleştir
    long long total_sum_multi = 0;
    for (const auto& part : partial_sums) {
        total_sum_multi += part;
    }

    auto end_multi = std::chrono::high_resolution_clock::now();
    auto duration_multi = std::chrono::duration_cast<std::chrono::milliseconds>(end_multi - start_multi);

    std::cout << "Multi-threaded Sum: " << total_sum_multi << std::endl;
    std::cout << "Multi-threaded Execution Time: " << duration_multi.count() << " milliseconds" << std::endl;

    return 0;
}
