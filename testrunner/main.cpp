#include "../tasks/ATeam.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <iomanip>

namespace Color {
    enum Code {
        FG_CYAN = 36,
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_ORANGE = 208,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

Color::Modifier cyan(Color::FG_CYAN);
Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier orange(Color::FG_ORANGE);
Color::Modifier def(Color::FG_DEFAULT);

namespace jhelper {

    struct Test {
        std::string input;
        std::string output;
        bool active;
        bool has_output;
    };

    bool check(const std::string& expected, const std::string& actual) {
        auto trim = [](std::string& str) {
            while (!str.empty() && isspace(*--str.end()))
                str.erase(--str.end());
        };
        std::string trimmedExpected = expected;
        std::string trimmedActual = actual;
        trim(trimmedExpected);
        trim(trimmedActual);
        return trimmedExpected == trimmedActual;
    }

    void printDifference(const std::string& expected, const std::string& actual) {
        std::istringstream expectedStream(expected);
        std::istringstream actualStream(actual);
        std::string expectedLine, actualLine;

        const int width = 15;

        std::vector<std::string> expectedLines;
        std::vector<std::string> actualLines;

        while (std::getline(expectedStream, expectedLine)) {
            expectedLines.push_back(expectedLine);
        }

        while (std::getline(actualStream, actualLine)) {
            actualLines.push_back(actualLine);
        }

        size_t maxLines = std::max(expectedLines.size(), actualLines.size());

        std::cout << std::left << std::setw(width) << "Expected" << " | " << "Actual" << std::endl;
        std::cout << std::string(width + 10, '-') << std::endl;

        for (size_t i = 0; i < maxLines; ++i) {
            std::string expLine = (i < expectedLines.size()) ? expectedLines[i] : "";
            std::string actLine = (i < actualLines.size()) ? actualLines[i] : "";

            std::cout << std::left << std::setw(width);
            if (!expLine.empty()) {
                std::cout << expLine;
            } else {
                std::cout << std::setw(width) << " ";
            }

            std::cout << " | ";
            if (!actLine.empty()) {
                if (expLine != actLine) {
                    std::cout << red << std::setw(width) << actLine << def;
                } else {
                    std::cout << std::setw(width) << actLine;
                }
            } else {
                std::cout << std::setw(width) << " ";
            }
            std::cout << std::endl;
        }
    }

} // namespace jhelper

void runTests(std::vector<jhelper::Test>& tests) {
    bool allOK = true;
    int testID = 0;
    std::cout << std::fixed;
    double maxTime = 0.0;

    for (const jhelper::Test& test : tests) {
        std::cout << cyan << "Test #" << ++testID << std::endl;
        std::cout << cyan << "Input: \n" << test.input << std::endl;
        if (test.has_output) {
            std::cout << cyan << "Expected output: \n" << test.output << std::endl;
        } else {
            std::cout << cyan << "Expected output: \n" << "N/A" << std::endl;
        }

        if (test.active) {
            std::streambuf* cinbuf = std::cin.rdbuf();
            std::streambuf* coutbuf = std::cout.rdbuf();

            std::istringstream in(test.input);
            std::ostringstream out;

            std::cin.rdbuf(in.rdbuf());
            std::cout.rdbuf(out.rdbuf());

            std::clock_t start = std::clock();
            ATeam solver;
            solver.solve();

            std::clock_t finish = std::clock();
            double currentTime = double(finish - start) / CLOCKS_PER_SEC;
            maxTime = std::max(currentTime, maxTime);

            std::cin.rdbuf(cinbuf);
            std::cout.rdbuf(coutbuf);

            std::cout << cyan << "Actual output: \n" << out.str() << std::endl;

            if (test.has_output) {
                bool result = jhelper::check(test.output, out.str());
                allOK = allOK && result;
                if (!result) {
                    std::cout << yellow << "Differences:\n" << def;
                    jhelper::printDifference(test.output, out.str());
                }
                std::cout << (result ? green : red) << "Result: " << (result ? "OK" : "Wrong answer") << def << std::endl;
            } else {
                std::cout << yellow << "Result: " << "N/A" << def << std::endl;
            }
            std::cout << "Time: " << currentTime << std::endl;
        } else {
            std::cout << "SKIPPED\n";
        }

        std::cout << std::endl;
    }

    if (allOK) {
        std::cout << green << "All OK" << def << std::endl;
    } else {
        std::cout << yellow << "Some cases failed" << def << std::endl;
    }

    std::cout << "Maximal time: " << maxTime << "s." << std::endl;
}

int main() {
    std::vector<jhelper::Test> tests = {
            {"3\n1 1 0\n1 1 1\n1 0 0\n", "2\n", true, true},{"2\n1 0 0\n0 1 1\n", "1\n", true, true},
    };

    // Primeira rodada de testes
    runTests(tests);

    char continueTesting;
    do {
        jhelper::Test newTest;

        std::cout << "Enter the input for the test case (type 'end' on a single line to finish):\n";
        std::string testInput;
        std::string line;
        while (std::getline(std::cin, line) && line != "end") {
            testInput += line + "\n";
        }

        // Remove the last newline, if present
        if (!testInput.empty() && testInput.back() == '\n') {
            testInput.pop_back();
        }
        newTest.input = testInput;

        std::cout << "Enter the expected output (type 'end' on a single line to finish):\n";
        std::string expectedOutput;
        while (std::getline(std::cin, line) && line != "end") {
            expectedOutput += line + "\n";
        }

        // Remove the last newline, if present
        if (!expectedOutput.empty() && expectedOutput.back() == '\n') {
            expectedOutput.pop_back();
        }
        newTest.output = expectedOutput;

        newTest.active = true;
        newTest.has_output = true;
        tests.push_back(newTest);

        std::cout << "\n--- Re-executing all tests. ---\n" << std::endl;
        runTests(tests);

        std::cout << "Would you like to add another test case? (y/n):";
        std::cin >> continueTesting;
        std::cin.ignore(); // Clears the input buffer

    } while (continueTesting == 'y' || continueTesting == 'Y');

    return 0;
}




