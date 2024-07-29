#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

std::string runProgram(const std::string &inputFile) {
    std::string command = "./ip_filter < " + inputFile + " > output.txt";
    system(command.c_str());

    std::ifstream outfile("output.txt");
    std::string output((std::istreambuf_iterator<char>(outfile)), std::istreambuf_iterator<char>());
    outfile.close();

    return output;
}

TEST(IpFilterTest, ReverseLexicographically) {
    std::string input = "1.1.1.1\n2.2.2.2\n1.0.0.0\n";
    std::ofstream infile("input1.tsv");
    infile << input;
    infile.close();
    
    std::string expected_output = "Reverse lexicographically:\n2.2.2.2\n1.1.1.1\n1.0.0.0\n";
    std::string output = runProgram("input1.tsv");
    EXPECT_NE(output.find(expected_output), std::string::npos);
}

TEST(IpFilterTest, FilterByFirstByte) {
    std::string input = "1.1.1.1\n2.2.2.2\n1.0.0.0\n";
    std::ofstream infile("input2.tsv");
    infile << input;
    infile.close();
    
    std::string expected_output = "ip = filter(1)\n1.1.1.1\n1.0.0.0\n";
    std::string output = runProgram("input2.tsv");
    EXPECT_NE(output.find(expected_output), std::string::npos);
}

TEST(IpFilterTest, FilterByFirstAndSecondBytes) {
    std::string input = "46.70.225.39\n46.70.147.26\n46.70.113.73\n46.70.29.76\n";
    std::ofstream infile("input3.tsv");
    infile << input;
    infile.close();
    
    std::string expected_output = "ip = filter(46, 70)\n46.70.225.39\n46.70.147.26\n46.70.113.73\n46.70.29.76\n";
    std::string output = runProgram("input3.tsv");
    EXPECT_NE(output.find(expected_output), std::string::npos);
}

TEST(IpFilterTest, FilterAnyByte) {
    std::string input = "46.70.225.39\n186.204.34.46\n185.46.86.132\n";
    std::ofstream infile("input4.tsv");
    infile << input;
    infile.close();
    
    std::string expected_output = "ip = filter_any(46)\n186.204.34.46\n185.46.86.132\n46.70.225.39\n";
    std::string output = runProgram("input4.tsv");
    EXPECT_NE(output.find(expected_output), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}