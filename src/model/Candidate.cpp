
// model/Candidate.cpp
#include "Candidate.h"

Candidate::Candidate() 
    : candidate_id(""), name(""), email(""), phone("") {}

Candidate::Candidate(std::string id, std::string name, std::string email, std::string phone)
    : candidate_id(id), name(name), email(email), phone(phone) {}
