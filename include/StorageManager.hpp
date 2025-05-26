/**
 * @file StorageManager.hpp
 * @author liuyan (liuyan@qq.com)
 * @brief sqlite3 存储数据管理类
 * @version 0.1
 * @date 2025-04-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "spdlog/spdlog.h"
#include "sqlite_orm/sqlite_orm.h"
#include <iostream>
#include <memory>

struct QA {
  std::string question;
  std::string answer;
};

class StorageManager {
public:
  /**
   * @brief Construct a new Storage Manager object
   *
   * @param dbPath
   */
  explicit StorageManager(const std::string &dbPath)
      : storage(std::make_shared<Storage>(initStorage(dbPath))) {
    storage->open_forever();
    storage->sync_schema();
    spdlog::info("Opening storage...");
  }

  ~StorageManager() { spdlog::info("Closing storage..."); }

  void insertQA(const QA &qa) const { storage->replace(qa); }

  std::vector<QA> getAll() const { return storage->get_all<QA>(); }

  void updateQA(const QA &qa) const { storage->update(qa); }




private:
  using Storage = decltype(sqlite_orm::make_storage(
      "",
      sqlite_orm::make_table("qa",
                             sqlite_orm::make_column("question", &QA::question,
                                                     sqlite_orm::primary_key()),
                             sqlite_orm::make_column("answer", &QA::answer))));

  std::shared_ptr<Storage> storage;

  static Storage initStorage(const std::string &path) {
    using namespace sqlite_orm;
    return make_storage(
        path,
        make_table("qa", make_column("question", &QA::question, primary_key()),
                   make_column("answer", &QA::answer)));
  }
};
