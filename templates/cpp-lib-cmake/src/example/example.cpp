#include <example/example.h>

namespace example {
unsigned int fibonacci(unsigned int n) {
    unsigned int a = 0;
    unsigned int b = 1;

    for (unsigned int i = 0; i != n; ++i) {
        const auto c = a + b;

        a = b;
        b = c;
    }

    return a;
}
}  // namespace example
