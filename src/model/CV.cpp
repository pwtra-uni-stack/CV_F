
// model/CV.cpp
#include "CV.h"

CV::CV() 
    : id(""), candidate(nullptr), experienceYears(0), education(""), raw_text(""), score(0) {}

CV::CV(std::string id, Candidate* cand, std::vector<std::string> sk, 
       int exp, std::string edu, std::string raw, int score)
    : id(id), candidate(cand), skills(sk), experienceYears(exp), 
      education(edu), raw_text(raw), score(score) {}

CV::~CV() {
    if (candidate != nullptr) {
        delete candidate;
        candidate = nullptr;
    }
}
