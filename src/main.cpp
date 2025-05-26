#include "FileDataManager.hpp"
#include "StorageManager.hpp"
#include "spdlog/spdlog.h"
#include <range/v3/view/zip.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/all.hpp>

#include <iostream>

int main(int, char **) {
  spdlog::set_level(spdlog::level::trace); // Set global log level to info
  spdlog::info("Hello, from SqliteFileExchange!");

  StorageManager storageManager("Questions.db");
  auto tryInsert = [&](const QA &qa) {
    try {
      storageManager.insertQA(qa);
    } catch (const std::exception &e) {
      spdlog::error("Insert failed for question '{}': {}", qa.question,
                    e.what());
    }
  };
  FileDataManager fileDataManager("Question.txt");


  const auto& list = fileDataManager.getFileDataList();
  for (auto&& [index, item] : ranges::views::zip(ranges::views::iota(0), list)) {
      spdlog::info("下标 {}: 题目 = {} 答案 = {}", index, item.question, item.answer);
      tryInsert({item.question, item.answer});
  }

  // tryInsert({"这是题目1", "这是答案1"});
  // tryInsert({"这是题目2", "这是答案2"});
  // tryInsert({"这是题目3", "这是答案3"});

  try {
    // auto data = storageManager.getAll();
    // for (const auto &qa : data) {
    //   spdlog::info("Question: {}, Answer: {}", qa.question, qa.answer);
    // }


  } catch (const std::exception &e) {
    spdlog::error("Query failed: {}", e.what());
  }

  return 0;
}
