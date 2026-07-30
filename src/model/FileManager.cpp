
// service/FileManager.cpp
#include "FileManager.h"
#include "../parser/PdfParser.h"
#include "../parser/DocxParser.h"
#include "../utils/Logger.h"
#include "../utils/Utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

std::string FileManager::readFileContent(const std::string& filePath) {
    if (filePath.empty()) {
        Logger::getInstance().log(LogLevel::WARNING, "Đường dẫn file rỗng.");
        return "";
    }

    // Lấy đuôi file để gọi Parser tương ứng
    std::string ext = "";
    size_t dotPos = filePath.find_last_of(".");
    if (dotPos != std::string::npos) {
        ext = filePath.substr(dotPos);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    }

    // Gọi Real Parsers thay vì dùng Mock
    if (ext == ".pdf") {
        PdfParser pdfParser;
        return pdfParser.parse(filePath);
    } else if (ext == ".docx" || ext == ".doc") {
        DocxParser docxParser;
        return docxParser.parse(filePath);
    } else {
        // Mặc định đọc file văn bản thông thường (.txt)
        std::ifstream file(filePath);
        if (!file.is_open()) {
            Logger::getInstance().log(LogLevel::ERROR, "Không thể mở file: " + filePath);
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
}

CV* FileManager::parseCVText(const std::string& raw_text, int cv_id) {
    // 1. Validation: Kiểm tra dữ liệu đầu vào rỗng
    if (raw_text.empty()) {
        Logger::getInstance().log(LogLevel::WARNING, "Dữ liệu raw_text rỗng, không thể parse CV.");
        return nullptr;
    }

    std::string name = "";
    std::string email = "";
    std::string phone = "";
    std::string education = "Dai hoc";
    int exp_years = 0;
    std::vector<std::string> foundSkills;

    // 2. Trích xuất thông tin cơ bản từ raw_text
    std::stringstream ss(raw_text);
    std::string line;
    
    while (std::getline(ss, line)) {
        line = Utils::trim(line);
        if (line.empty()) continue;

        // Trích xuất Email (chứa ký tự '@')
        if (email.empty() && line.find("@") != std::string::npos) {
            std::vector<std::string> words = Utils::split(line, ' ');
            for (const auto& word : words) {
                if (word.find("@") != std::string::npos) {
                    email = word;
                    break;
                }
            }
        }

        // Trích xuất Tên (dòng đầu tiên có chứa chữ)
        if (name.empty() && line.find("Email:") == std::string::npos && line.find("Phone:") == std::string::npos) {
            name = line;
        }

        // Trích xuất kỹ năng cơ bản
        std::string lowerLine = line;
        std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);
        
        std::vector<std::string> targetSkills = {"c++", "python", "java", "sql", "html", "css", "javascript", "react"};
        for (const auto& skill : targetSkills) {
            if (lowerLine.find(skill) != std::string::npos) {
                if (std::find(foundSkills.begin(), foundSkills.end(), skill) == foundSkills.end()) {
                    foundSkills.push_back(skill);
                }
            }
        }
    }

    // 3. Validation: Đảm bảo không bị rỗng các trường quan trọng
    if (name.empty()) {
        Logger::getInstance().log(LogLevel::WARNING, "Không trích xuất được tên ứng viên. Gán mặc định.");
        name = "Unknown Candidate";
    }

    std::string str_id = "CV_" + std::to_string(cv_id);
    std::string cand_id = "CAND_" + std::to_string(cv_id);

    // 4. Khởi tạo đối tượng Candidate và CV (Con trỏ thô theo phong cách ban đầu)
    Candidate* cand = new Candidate(cand_id, name, email, phone);
    CV* newCV = new CV(str_id, cand, foundSkills, exp_years, education, raw_text, 0);

    return newCV;
}

bool FileManager::saveCVListToFile(const std::string& filePath, const std::vector<CV*>& cvList) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        Logger::getInstance().log(LogLevel::ERROR, "Không thể mở file để ghi: " + filePath);
        return false;
    }

    for (CV* cv : cvList) {
        if (cv != nullptr && cv->candidate != nullptr) {
            file << cv->id << "|"
                 << cv->candidate->name << "|"
                 << cv->candidate->email << "|"
                 << cv->experienceYears << "|"
                 << cv->education << "\n";
        }
    }

    file.close();
    return true;
}

std::vector<CV*> FileManager::loadCVListFromFile(const std::string& filePath) {
    std::vector<CV*> result;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::getInstance().log(LogLevel::WARNING, "Không tìm thấy file lưu trữ: " + filePath);
        return result;
    }

    std::string line;
    int index = 1;
    while (std::getline(file, line)) {
        line = Utils::trim(line);
        if (line.empty()) continue;

        std::vector<std::string> parts = Utils::split(line, '|');
        if (parts.size() >= 5) {
            std::string cv_id = parts[0];
            std::string name = parts[1];
            std::string email = parts[2];
            int exp = std::stoi(parts[3]);
            std::string edu = parts[4];

            Candidate* cand = new Candidate("CAND_" + std::to_string(index), name, email, "");
            CV* cv = new CV(cv_id, cand, {}, exp, edu, "", 0);
            result.push_back(cv);
            index++;
        }
    }

    file.close();
    return result;
}
