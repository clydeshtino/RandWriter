// Copyright 2023 (Clyde Shtino)
#ifndef RAND_HPP
#define RAND_HPP
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <utility>
using std::string;
class RandWriter {
 public:
    // constructor
    RandWriter(string text, int k);
    // order K of markov model
    int orderK() const;
    // Number of occurences of kgram in text
    // Throw an exception if kgram is not length k
    int freq(string kgram) const;
    int freq(string kgram, std::function<bool(char)> include_ch) const;
    // Random character following given kgram
    // (throw an exception if kgram is not of length k)
    // (throw an exception if no such kgram)
    char kRand(string kgram);
    // Generate a string of length L characters by simulating a trajectory
    // through the corresponding Markov chain. The first k characters of
    // the newly generated string should be the argument kgram.
    // Throw an excpetion if kgram is not of length k.
    // Assume that L is at least k
    string generate(string kgram, int L);

 private:
    int k;
    string input;
    mutable std::vector<char> alpha;
    mutable std::map<string, int> kgrams;
    friend std::ostream& operator<<(std::ostream& out, const RandWriter& writer);
    void build_Kgram();
};
#endif
