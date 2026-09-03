#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <string>
#include <vector>
#include <map>

struct FileRecord;
void saveDatabase(const std::map<std::string, std::vector<FileRecord>>& database, const std::string& path);
void loadDatabase(std::map<std::string, std::vector<FileRecord>>& database, const std::string& path);

#endif