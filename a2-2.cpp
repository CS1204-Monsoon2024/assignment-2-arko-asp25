#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <numeric>
#include <random>

using namespace std;

const int MOD = 50;  // Hash mod value for the co-domain [0, 49]
const int DATA_SIZE = 1000;  // Dataset size
const int PRIME = 100003;  // A large prime number

// Generate a random dataset (e.g., phone numbers, PIN codes, student IDs)
vector<int> generateDataset(int size) {
    vector<int> dataset;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000000, 9999999);  // Random numbers in a range

    for (int i = 0; i < size; ++i) {
        dataset.push_back(dis(gen));  // Generate random phone numbers or PIN codes
    }

    return dataset;
}

// Hash function 1: h(x) = x mod 50
int hashFunction1(int x) {
    return x % MOD;
}

// Hash function 2: h(x) = ((a * x + b) mod p) mod 50
int hashFunction2(int x, int a, int b, int p) {
    return ((a * x + b) % p) % MOD;
}

// Chi-square goodness-of-fit test to evaluate uniformity
double chiSquareTest(const map<int, int>& bucketCounts, int expectedCount) {
    double chiSquare = 0.0;
    for (const auto& pair : bucketCounts) {
        int observed = pair.second;
        chiSquare += pow(observed - expectedCount, 2) / expectedCount;
    }
    return chiSquare;
}

// Pearson correlation coefficient to evaluate independence
double pearsonCorrelation(const vector<int>& dataset, const vector<int>& hashValues) {
    int n = dataset.size();
    double meanX = accumulate(dataset.begin(), dataset.end(), 0.0) / n;
    double meanY = accumulate(hashValues.begin(), hashValues.end(), 0.0) / n;

    double num = 0.0, denomX = 0.0, denomY = 0.0;
    for (int i = 0; i < n; ++i) {
        num += (dataset[i] - meanX) * (hashValues[i] - meanY);
        denomX += pow(dataset[i] - meanX, 2);
        denomY += pow(hashValues[i] - meanY, 2);
    }

    return num / sqrt(denomX * denomY);
}

// Main evaluation function for the hash functions
void evaluateHashFunctions(const vector<int>& dataset) {
    map<int, int> bucketCounts1, bucketCounts2;
    vector<int> hashValues1, hashValues2;

    // Coefficients for hash function 2
    int a = 17, b = 23, p = PRIME;

    // Hash the dataset using the two hash functions and record bucket counts
    for (int x : dataset) {
        int h1 = hashFunction1(x);
        int h2 = hashFunction2(x, a, b, p);

        bucketCounts1[h1]++;
        bucketCounts2[h2]++;

        hashValues1.push_back(h1);
        hashValues2.push_back(h2);
    }

    // Expected count per bucket
    int expectedCount = DATA_SIZE / MOD;

    // Chi-square test for uniformity
    double chiSquare1 = chiSquareTest(bucketCounts1, expectedCount);
    double chiSquare2 = chiSquareTest(bucketCounts2, expectedCount);

    // Pearson correlation for independence
    double correlation1 = pearsonCorrelation(dataset, hashValues1);
    double correlation2 = pearsonCorrelation(dataset, hashValues2);

    // Output results
    cout << "Hash Function 1 (x mod 50):" << endl;
    cout << "  Chi-square: " << chiSquare1 << endl;
    cout << "  Pearson Correlation: " << correlation1 << endl << endl;

    cout << "Hash Function 2 ((a * x + b) mod p mod 50):" << endl;
    cout << "  Chi-square: " << chiSquare2 << endl;
    cout << "  Pearson Correlation: " << correlation2 << endl << endl;
}

int main() {
    // Generate dataset of size 1000 (e.g., phone numbers, PIN codes)
    vector<int> dataset = generateDataset(DATA_SIZE);

    // Evaluate the hash functions
    evaluateHashFunctions(dataset);

    return 0;
}
