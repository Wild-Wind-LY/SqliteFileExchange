/**
 * @file FileDataManager.hpp
 * @author liuyan (liuyan@qq.com)
 * @brief 文件数据管理类
 * @version 0.1
 * @date 2025-04-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "spdlog/spdlog.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct FileItemData {
  int num;
  std::string question;
  std::string answer;
};

class FileDataManager {

public:
  explicit FileDataManager(const std::string &filePath) : filePath(filePath) {
    // 加载文件数据
    loadFileData();
  }

  /**
   * @brief 加载文件数据
   *
   */
  void loadFileData() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
      spdlog::error("Error opening file: {}", filePath);
      return;
    }

    fileDataList.clear();
    std::string line{};
    while (std::getline(file, line)) {
      FileItemData item{};
      size_t pos1 = line.find('#');
      size_t pos2 = line.find('#', pos1 + 1);

      if (pos1 != std::string::npos && pos2 != std::string::npos) {
        item.num = std::stoi(line.substr(0, pos1));
        item.question = line.substr(pos1 + 1, pos2 - pos1 - 1);
        item.answer = line.substr(pos2 + 1);
        fileDataList.push_back(item);
      }
    }
    file.close();

    spdlog::info("Loaded {} items from file: {}", fileDataList.size(),
                 filePath);
  }

  /**
   * @brief 设置加载文件的路径
   *
   * @param newFilePath
   */
  auto setFilePath(const std::string &newFilePath) -> void {
    filePath = newFilePath;
  }

  /**
   * @brief 重新加载文件数据，如果输入了文件路径， 则重新加载该路径的文件数据
   *
   * @param filePath
   */
  auto reloadFileData(const std::string &filePath = "") -> void {
    if (!filePath.empty()) {
      setFilePath(filePath);
    }
    loadFileData();
  }

  /**
   * @brief 获取文件数据列表
   *
   * @return const std::vector<FileItemData>&
   */
  auto getFileDataList() const -> const std::vector<FileItemData> & {
    return fileDataList;
  }

private:
  std::vector<FileItemData> fileDataList;
  std::string filePath;
};
