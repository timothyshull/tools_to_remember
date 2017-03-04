#include <string>

template<class Input_it1, class Input_it2>
bool lexicographical_compare(Input_it1 begin1, Input_it1 end1, Input_it2 begin2, Input_it2 end2)
{
    for (; (begin1 != end1) && (begin2 != end2); ++begin1, (void) ++begin2) {
        if (*begin1 < *begin2) { return true; }
        if (*begin2 < *begin1) { return false; }
    }
    return (begin1 == end1) && (begin2 != end2);
}

// unsafe
bool cstring_compare(const char* a, const char* b)
{
    int i;
    for (i = 0; a[i] == b[i]; ++i) {
        if (a[i] == '\0') { return 0; }
    }
    return a[i] - b[i];
}

// unsafe
bool cstring_ptr_compare(const char* a, const char* b)
{
    while (*a++ == *b++) {
        if (*(a - 1) == '\0') {
            return 0;
        }
    }
    return *(a - 1) - *(b - 1);
}

bool string_it_compare(const std::string& str1, const std::string& str2)
{
    auto begin1 = str1.begin();
    auto begin2 = str2.begin();
    auto end1 = str1.end();
    auto end2 = str2.end();
    for (; (begin1 != end1) && (begin2 != end2); ++begin1, ++begin2) {
        if (*begin1 < *begin2) { return true; }
        if (*begin2 < *begin1) { return false; }
    }
    return (begin1 == end1) && (begin2 != end2);
}

bool string_compare(const std::string& str1, const std::string& str2)
{
    auto size1 = str1.size();
    auto size2 = str2.size();
    auto min_size = std::min(size1, size2);

    int i;
    for (i = 0; i < min_size; ++i) {
        if (str1[i] < str2[i]) { return true; }
        if (str2[i] < str1[i]) { return false; }
    }
    return size1 < size2;
}
