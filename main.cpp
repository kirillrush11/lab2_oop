#include <iostream>
#include "vector.hpp"

void print_test_header(const std::string& title) {
    std::cout << " \n" << title << ":\n";
}

int main() {
    print_test_header("Constructor Tests");
    m_vector<int> empty_vec;
    std::cout << "Empty vector: " << empty_vec << ", length: " << empty_vec.get_length() << "\n";

    m_vector<int> sized_vec(3);
    std::cout << "Sized vector (3): " << sized_vec << ", length: " << sized_vec.get_length() << "\n";

    m_vector<int> init_list_vec = {1, 2, 3, 4, 5};
    std::cout << "Initializer list vector: " << init_list_vec << ", length: " << init_list_vec.get_length() << "\n";

    print_test_header("Element Access Tests");
    std::cout << "Original vector: " << init_list_vec << "\n";
    init_list_vec.set_elem(0, 100);
    init_list_vec[1] = 200;
    std::cout << "After modifications: " << init_list_vec << "\n";

    try {
        init_list_vec.set_elem(10, 50);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    print_test_header("Vector Operations Tests");
    m_vector<int> vec1 = {1, 2, 3};
    m_vector<int> vec2 = {4, 5, 6};

    std::cout << "vec1: " << vec1 << "\n";
    std::cout << "vec2: " << vec2 << "\n";

    m_vector<int> sum_vec = vec1 + vec2;
    std::cout << "Sum (vec1 + vec2): " << sum_vec << "\n";

    m_vector<int> diff_vec = vec1 - vec2;
    std::cout << "Difference (vec1 - vec2): " << diff_vec << "\n";

    m_vector<int> scaled_vec = vec1 * 2;
    std::cout << "Scaled (vec1 * 2): " << scaled_vec << "\n";

    m_vector<int> divided_vec = vec2 / 2;
    std::cout << "Divided (vec2 / 2): " << divided_vec << "\n";

    try {
        m_vector<int> bad_div = vec1 / 0;
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught division exception: " << e.what() << "\n";
    }

    print_test_header("Comparison Tests");
    m_vector<int> vec3 = {1, 2, 3};
    std::cout << "vec1: " << vec1 << "\n";
    std::cout << "vec3: " << vec3 << "\n";
    std::cout << "vec1 == vec3: " << (vec1 == vec3 ? "true" : "false") << "\n";
    std::cout << "vec1 != vec2: " << (vec1 != vec2 ? "true" : "false") << "\n";

    print_test_header("Iterator Tests");
    std::cout << "Using iterators: ";
    for (auto it = vec1.iterator_begin(); it != vec1.iterator_end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    print_test_header("Array Conversion Test");
    int* arr = init_list_vec.to_array();
    std::cout << "Array: [";
    for (size_t i = 0; i < init_list_vec.get_length(); ++i) {
        if (i != 0) std::cout << ", ";
        std::cout << arr[i];
    }
    std::cout << "]\n";
    delete[] arr;

    print_test_header("Move Semantics Test");
    m_vector<int> moved_vec = std::move(init_list_vec);
    std::cout << "Moved vector: " << moved_vec << "\n";
    std::cout << "Original vector after move: " << init_list_vec << "\n";

    return 0;
}
