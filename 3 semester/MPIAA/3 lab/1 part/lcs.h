#pragma once

#include <string>

// Find the longest common subsequence of two strings.
std::string lcs(const std::string &first, const std::string &second);
std::string lcs_rec_search(const std::string& first, const std::string& second);