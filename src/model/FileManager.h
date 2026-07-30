
// service/FileManager.h
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "../model/CV.h"

class FileManager {
public:
    FileManager() = default;
    ~FileManager() = default;

    // Đọc nội dung thô từ file PDF/DOCX/TXT dựa vào đuôi file
    std::string readFileContent(const std::string& filePath);

    // Parse chuỗi text thô thành đối tượng CV (có validation)
    CV* parseCVText(const std::string& raw_text, int cv_id);

    // Lưu/Tải dữ liệu danh sách CV ra file cấu hình
    bool saveCVListToFile(const std::string& filePath, const std::vector<CV*>& cvList);
    std::vector<CV*> loadCVListFromFile(const std::string& filePath);
};

#endif // FILEMANAGER_H
