// Copyright 2023 (Clyde Shtino)
#include "RandWriter.hpp"

RandWriter::RandWriter(string text, int k) : k(k), input(text) {
    srand(time(NULL));

    // Check if text is long enough for k
    if (text.size() < static_cast<size_t>(k)) {
        throw std::logic_error("Input text is too short for the specified k.");
    }
    // looping through all characters in text and alphabetic
    for (unsigned i = 0; i < text.size(); i++) {
        if (std::find(alpha.begin(), alpha.end(), text[i]) == alpha.end()) {
            alpha.push_back(text[i]);
        }
    }
    // calling helper function
    build_Kgram();
}
void RandWriter::build_Kgram() {
    // Clear kgrams map
    kgrams.clear();

    for (unsigned i = 0; i < input.size() - k; i++) {
        std::string kgram = input.substr(i, k);
        char next_char = input[i + k];
        // If kgram is not in kgrams, add it
        if (kgrams.find(kgram) == kgrams.end()) {
            kgrams[kgram] = 0;
        }
        // Increment the count for the next character in the kgram
        kgrams[kgram + next_char]++;
    }
}

int RandWriter::orderK() const {
    return k;
}

int RandWriter::freq(string kgram) const {
    // size not equal to k
    if (kgram.size() != (unsigned)k) {
        throw std::logic_error("kgram is not = k!");
    }
    // in case k is 0
    if (k == 0) {
        return input.size();
    } else {
        return kgrams[kgram];
    }
}

int RandWriter::freq(string kgram, std::function<bool(char)> include_ch) const {
    int count = 0;

    if (kgram.size() != (unsigned)k) {
        throw std::logic_error("kgram is not = k!");
    }

    if (k == 0) {
        for (unsigned i = 0; i < input.size(); i++) {
            if (include_ch(input[i])) {
                count++;
            }
        }
    } else {
        for (char c : alpha) {
            if (include_ch(c)) {
                count += kgrams[kgram + c];
            }
        }
    }

    return count;
}


char RandWriter::kRand(string kgram) {
    // Collect all characters and their frequencies in kgram
    std::vector<std::pair<char, int>> char_freq;
    for (char c : alpha) {
        char_freq.push_back(std::make_pair(c, kgrams[kgram + c]));
    }

    // Shuffle the characters randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(char_freq.begin(), char_freq.end(), gen);

    // Select a random character based on frequencies
    int total_freq = 0;
    for (const auto& entry : char_freq) {
        total_freq += entry.second;
    }

    // Check if total frequency is zero
    if (total_freq == 0) {
        std::cerr << "Freq is zero" << std::endl;
        return -1;
    }

    // Use a uniform distribution for random selection
    std::uniform_int_distribution<int> distrib(0, total_freq - 1);
    int rand_freq = distrib(gen);

    int cumulative_freq = 0;
    // for cumulative frequency calculations
    for (const auto& entry : char_freq) {
        cumulative_freq += entry.second;
        if (rand_freq < cumulative_freq) {
            return entry.first;
        }
    }

    // fail case if kRand encounters an issue
    return -1;
}


string RandWriter::generate(string kgram, int L) {
    if (L < k) {
        throw std::logic_error("L is too small for the specified k.");
    }
    string temp = kgram;
    string out = kgram;
    char ch;

    // loop through kgrams map
    for (int i = 0; i < L - k; i++) {
        // in case of error during kRand call
        try {
            ch = kRand(temp);
            out.push_back(ch);
            temp.erase(temp.begin());
            temp.push_back(ch);
        } catch (const std::exception& e) {
            std::cerr << "Exception in generate: " << e.what() << std::endl;
            std::cerr << "kgram=" << kgram << ", temp=" << temp << std::endl;
        }
    }
    return out;
}


std::ostream& operator<<(std::ostream& out, const RandWriter& writer) {
    // for alphabetic characters
    for (char c : writer.alpha) {
        out << c;
    }

    for (const auto& entry : writer.kgrams) {
        out << entry.first << " " << entry.second << " => ";
        for (char c : writer.alpha) {
            out << entry.first + c << " " << writer.kgrams.at(entry.first + c) << " ";
        }
        out << std::endl;
    }
    return out;
}
