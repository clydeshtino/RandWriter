// Copyright 2023 (Clyde Shtino)
#define BOOST_TEST_MODULE Rand_Test
#define BOOST_TEST_DYN_LINK
#include "RandWriter.hpp"
#include <boost/test/included/unit_test.hpp>
// for valid input
BOOST_AUTO_TEST_CASE(test_constructor_valid) {
    std::string input = "gagggagaggcgagaaa";
    BOOST_REQUIRE_NO_THROW(RandWriter writer(input, 2));
}
// bad input
BOOST_AUTO_TEST_CASE(test_constructor_invalid) {
    string input = "";
    BOOST_CHECK_THROW(RandWriter writer(input, 2), std::logic_error);
}

// ensuring K is set to user input
BOOST_AUTO_TEST_CASE(test_orderK) {
    RandWriter rw("Order K", 3);
    BOOST_CHECK_EQUAL(rw.orderK(), 3);
}
// testing with valid input
BOOST_AUTO_TEST_CASE(test_generate_valid) {
    RandWriter rw("This is a test", 2);
    std::string generatedText = rw.generate("Th", 5);
    BOOST_CHECK_EQUAL(generatedText.size(), 5);
}
// testing with invalid input and ensures exception is thrown
BOOST_AUTO_TEST_CASE(test_generate_invalid_L) {
    RandWriter rw("This is a test", 2);
    try {
        BOOST_CHECK_THROW(rw.generate("Th", 1), std::logic_error);
    } catch (const std::logic_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        throw;
    }
}
// testing with a kgram that is not in input
BOOST_AUTO_TEST_CASE(test_freq_kgram_not_present) {
    RandWriter rw("This is a test", 2);
    int actualFreq = rw.freq("ZZ");
    BOOST_REQUIRE_EQUAL(actualFreq, 0);
}
// testing with valid freq
BOOST_AUTO_TEST_CASE(test_freq_valid) {
    RandWriter rw("This is a test", 2);

    // Using lambda to count chars
    auto include_ch = [](char c) {
        return c == 'i' || c == 's';
    };
    int actualFreq = rw.freq("Th", include_ch);
    int expectedFreq = 1;
    BOOST_CHECK_EQUAL(actualFreq, expectedFreq);
}
// invalid kgram size test
BOOST_AUTO_TEST_CASE(test_freq_invalid_kgram_size) {
    RandWriter rw("This is a test", 2);
    try {
        BOOST_CHECK_THROW(rw.freq("This", [](char c) { return true; }), std::logic_error);
    } catch (const std::logic_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        throw;
    }
}
