#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <ctime>

using namespace std;

// Function for Hash1: h(x) = x mod 50
int hash1(int x) {
    return x % 50;
}

// Function for Hash2: h(x) = ((ax + b) mod p) mod 50
int hash2(int x, int a, int b, int p) {
    return ((a * x + b) % p) % 50;
}

// Function to evaluate the uniformity of hash values
void evaluate_uniformity(const vector<int>& hash_values) {
    unordered_map<int, int> freq;
    for (int val : hash_values) {
        freq[val]++;
    }
    
    cout << "Hash Value Frequency Distribution:" << endl;
    for (auto& entry : freq) {
        cout << "Value " << entry.first << " -> Frequency: " << entry.second << endl;
    }
}

// Function to generate a random dataset of 10-digit phone numbers
vector<long long> generate_phone_numbers(int size) {
    vector<long long> dataset;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(1000000000LL, 9999999999LL); // 10-digit numbers

    for (int i = 0; i < size; i++) {
        dataset.push_back(dis(gen));
    }

    return dataset;
}

int main() {
    const int dataset_size = 1000;
    const int p = 100003;  // A large prime number
    const int a = 12345;   // Random a
    const int b = 67890;   // Random b

    // Curate dataset of 10-digit phone numbers
    vector<long long> dataset = generate_phone_numbers(dataset_size);

    // Store hash results
    vector<int> hash1_values, hash2_values;

    // Apply both hash functions
    for (long long x : dataset) {
        hash1_values.push_back(hash1(x));
        hash2_values.push_back(hash2(x, a, b, p));
    }

    // Evaluate uniformity
    cout << "Evaluating Uniformity for Hash1 (x mod 50):" << endl;
    evaluate_uniformity(hash1_values);

    cout << "\nEvaluating Uniformity for Hash2 ((ax + b) mod p) mod 50:" << endl;
    evaluate_uniformity(hash2_values);

    return 0;
}