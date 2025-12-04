#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace algo {
    inline std::vector<std::string> split(std::string_view s, std::string_view delimiter) {
        if (delimiter.empty()) return { std::string{s} };

        size_t pos_start = 0, pos_end;
        const size_t delim_len = delimiter.size();
        std::vector<std::string> result;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string_view::npos) {
            result.emplace_back(s.substr(pos_start, pos_end - pos_start));
            pos_start = pos_end + delim_len;
        }

        result.emplace_back(s.substr(pos_start));
        return result;
    }
}
