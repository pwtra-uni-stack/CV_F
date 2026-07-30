
// model/CV.h
#ifndef CV_H
#define CV_H

#include <string>
#include <vector>
#include "Candidate.h"

class CV {
public:
    std::string id;
    Candidate* candidate;
    std::vector<std::string> skills;
    int experienceYears;
    std::string education;
    std::string raw_text;
    int score;

    CV();
    CV(std::string id, Candidate* cand, std::vector<std::string> sk, 
       int exp, std::string edu, std::string raw = "", int score = 0);
    
    ~CV();

    // Ngăn chặn copy bằng pointer để tránh lỗi giải phóng bộ nhớ 2 lần (Double Free)
    CV(const CV&) = delete;
    CV& operator=(const CV&) = delete;
};

#endif // CV_H
