//Inspired DataBase Queries like SQL,but in C++17
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <filesystem>

#include "SaveFile.h"
using std::cout;
using std::cin;
namespace  fs = std::filesystem; //short alias

struct FileRecord{
std::string fileName;
std::string filePath;
std::string fileType;
long long   fileSize;
std::string dataAdded;

long long getFileSize(std::string path){
    if(path.empty()){
        throw std::invalid_argument("FILE NOT FOUND");    
    }
    std::ifstream file(path);
    if(!file.is_open()){
        //FIX IT LATER  AT THE END  WITH STD::RUNTIME 
    }
    file.seekg(0, std::ios::end);
    return file.tellg();
}
std::string getFileExtension(std::string& filename){
    if(filename.empty()){
        throw std::invalid_argument("FILE NOT FOUND");
    }
    size_t dotPos = filename.find_last_of(".");
    if(dotPos == std::string::npos){
        return "unknown";
    }
    return filename.substr(dotPos + 1);
}

};
void displayFileDataBase(const FileRecord& record){
    cout<<"File Name: "<<record.fileName<<"\n"
    <<"File Path: "<<record.filePath<<"\n"
    <<"File Type: "<<record.fileType<<"\n"
    <<"Size: "<<record.fileSize<<"Bytes\n"
    <<"Date Added: "<<record.dataAdded<<"\n";
}
void addDataToFileDataBase(std::vector<FileRecord>& FILEDB, const FileRecord& record){
    FILEDB.push_back(record);
}
void help(){
    cout<<"|\n"
    <<"#CREATE TABLE -create a table [any-name] of File Database\n"
    <<"#ADD -adds a file to Database,ADD [tablename] [_____.(musthaveExtension)]\n"
    <<"#SHOW ALL -shows all data to availabe Database,SHOW ALL [tablename]\n"
    <<"#FIND && |FIND WHERE -Find if a file is in Database,Can be used Very Flexilibile like an if Statement\nFIND WHERE [tablename] [field(ex, filename,filetype,etc) [operation] [value(MUST  BE INT)]]\n"
    <<"#EXIT SAVE -Saves The Data in a .txt file extension\n"
    <<"---ADDITIONAL COMMANDS CAN BE USED OR|AND TO COMBINE MULTIPLE CONDITIONS---\n"
    <<"#DELETE && |DELETE WHERE -deletes a file inside the Database,Can be used Very Flexilibile like an if Statement\nDELETE WHERE [tablename] [field(ex, filename,filetype,etc) [operation] [value(MUST  BE INT)]]\n"
    <<"#UPDATE -updates a file inside the Database,UPDATE [tablename] [filename] [field(ex, filename,filetype,etc)] [newvalue]\n"
    <<"#REMOVE TABLE -removes a table from the Database,REMOVE TABLE [tablename]\n"
    <<"#SCAN -scans a directory and adds all files to the Database,SCAN [tablename] [directorypath]\n";

    cout<<"\nEXIT -exits the progam without saving\n"
        <<"CLEAR|cls -clears the screen\n";
}

void saveDataBase(const std::map<std::string, std::vector<FileRecord>>& database,const std::string& path){
    std::ofstream outFile(path);
    for(const auto& tablePair: database){
        outFile<<"[TABLE]"<< tablePair.first<<"\n";
        for(const auto& rec: tablePair.second){
            outFile<<rec.fileName<<"|"
            <<rec.filePath<<"|"
            <<rec.fileType<<"|"
            <<rec.fileSize<<"|"
            <<rec.dataAdded<<"\n";
        }
    }
}
void loadFromDataBase(std::map<std::string,std::vector<FileRecord>>& database, std::string path){
std::ifstream inFile(path);
if(!inFile.is_open()){
 return;
}

std::string line, currentTable;
while(std::getline(inFile, line)){
    if(line.substr(0,7) == "[TABLE]"){
        currentTable = line.substr(7);
        database[currentTable] = std::vector<FileRecord>{};
    }
    else if(!line.empty()){
        std::stringstream  ss(line);
        std::string field;
        FileRecord  record;
        std::getline(ss,record.fileName,'|');
        std::getline(ss,record.filePath,'|');
        std::getline(ss,record.fileType,'|');
        std::getline(ss,field,'|');
        record.fileSize = std::stoll(field);
        std::getline(ss,record.dataAdded,'|');
        
        database[currentTable].push_back(record);
    }
}
}

void ClearScreenAuto(){
#ifdef _WIN32    
    system("cls");
#else
    system("clear");
#endif    
}
void ClearScreenBT(){
#ifdef _WIN32    
    system("cls");
    cout<<"\033[1;32mMiniDataC v1.0\033[0m\n";
#else
    system("clear");
    cout<<"\033[1;32mMiniDataC v1.0\033[0m\n";
#endif    
}

int main(){
    ClearScreenAuto();
    std::map<std::string, std::vector<FileRecord>> database;
    cout<<"\033[1;32mMiniDataC v1.0\033[0m\n";

    database["files"] = std::vector<FileRecord>{};
    loadFromDataBase(database,"database.txt");
    /* HARDCODED EXAMPLE[NOT NEEDED ANYMORE -Just for visualization of the back curtains behind the Database]
    FileRecord f1;
    f1.fileName = "example.txt";
    f1.filePath = "C:\\Users\\User\\Documents\\example.txt";
    f1.fileType = "txt";
    f1.fileSize = f1.getFileSize(f1.filePath);
    f1.dataAdded = "2023-10-01";
    database["files"].push_back(f1);

    FileRecord f2;
    f2.fileName = "img.png";
    f2.filePath = "C:\\Users\\User\\Pictures\\img.png";
    f2.fileType = "png";
    f2.fileSize = f2.getFileSize(f2.filePath);
    f2.dataAdded = "2024-30-01";
    database["files"].push_back(f2);

    FileRecord f3;
    f3.fileName = "doc.pdf";
    f3.filePath = "C:\\Users\\User\\Documents\\doc.pdf";
    f3.fileType = "pdf";
    f3.fileSize = f3.getFileSize(f3.filePath);
    f3.dataAdded = "2024-01-01";
    database["files"].push_back(f3);

    FileRecord f4;
    f4.fileName = "anotherImg.png";
    f4.filePath = "C:\\Users\\User\\Documents\\anotherImg.png";
    f4.fileType = "png";
    f4.fileSize = f4.getFileSize(f4.filePath);
    f4.dataAdded = "2024-01-01";
    database["files"].push_back(f4);
*/
    std::string commands;
    while(true){
        std::getline(cin, commands);
        if(commands.empty() || commands == " "){
            continue;
        }
       else if(commands == "HELP" || commands == "help"){
            help();
        }
        else if(commands.substr(0,9) == "EXIT SAVE" || commands.substr(0,9) == "exit save"){
            saveDataBase(database, "database.txt");
            break;
        }
         else if(commands == "EXIT" || commands == "exit"){
            break;
        }
        else if(commands == "clear" || commands == "cls" || commands == "CLS" || commands == "CLEAR"){
            ClearScreenBT();
        }
        else if(commands.substr(0,12) == "CREATE TABLE" || commands.substr(0,12) == "create table"){
            std::stringstream ss(commands);
            std::string keyword1, keyword2, tableName;
            ss >> keyword1 >> keyword2 >> tableName;

            if(database.find(tableName) != database.end()){
                cout << "Table already exists: " << tableName << "\n";
            } else {
                database[tableName] = std::vector<FileRecord>{};
                cout << "Created table: " << tableName << "\n";
            }
        }
        else if(commands.substr(0,8) == "SHOW ALL" || commands.substr(0,8) == "show all"){
            std::stringstream ss(commands);
            std::string keyword1, keyword2, tableName;
            ss >> keyword1 >> keyword2 >> tableName;

            if(database.find(tableName) == database.end()){
                cout << "No such table: " << tableName << "\n";
            }   else {                
                for(const auto& record : database[tableName]){
                    displayFileDataBase(record);
                    cout << "\n";
                 }
            }
        }

        else if(commands.substr(0, 3) == "ADD" || commands.substr(0,3) == "add"){
            std::stringstream ss(commands);
            std::string keyword, tableName, filename;
            ss >> keyword >> tableName >> filename;

            if(database.find(tableName) == database.end()){
                cout << "No such table: " << tableName << "\n";
            } else {
                FileRecord newRecord;
                newRecord.fileName = filename;
                newRecord.filePath = filename;
                newRecord.fileType = newRecord.getFileExtension(filename);
                newRecord.fileSize = newRecord.getFileSize(newRecord.filePath);
                newRecord.dataAdded = "2024-01-01";
                database[tableName].push_back(newRecord);
                cout << "Added " << filename << " to " << tableName << "\n";
            }
        }
        else if(commands.substr(0,10) == "FIND WHERE" || commands.substr(0,10) == "find where"){
            std::stringstream ss(commands);
            std::string keyword1, keyword2, tableName;
            ss >> keyword1 >> keyword2 >> tableName;

            if(database.find(tableName) == database.end()){
                cout << "No such table: " << tableName << "\n";
                continue;
            }

            std::vector<std::string> tokens;
            std::string tok;
            while(ss >> tok){
                tokens.push_back(tok);
            }
            if(tokens.size() < 3 || (tokens.size() - 3) % 4 != 0){
                cout <<"INVALID `WHERE` SYNTAX\n";
                continue;
            }
            bool useAnd = true;
            for(size_t i = 3; i < tokens.size(); i+=4){
                std::string combinator = tokens[i];
                if(combinator == "AND" || combinator == "and") useAnd = true;
                else if(combinator == "OR" || combinator == "or") useAnd = false;
            }
            auto evalCond = [&](const FileRecord& record,const std::string& field
            ,const std::string& op, std::string& value) -> bool{
                if(field == "FILETYPE" || field == "filetype"){
                    return op == "==" ? (record.fileType == value) : false;
                }
                else if(field == "FILENAME" ||field == "filename"){
                    return op == "==" ? (record.fileName == value) : false;
                }
                else if(field == "SIZE" || field == "size"){
                    long long v = std::stoll(value);
                    if(op == "==") return record.fileSize == v;
                    else if(op == ">") return record.fileSize > v;
                    else if(op == "<") return record.fileSize < v;
                }
                return false;
            };
            bool found = false;
            for(const auto& record: database[tableName]){
                bool  result = evalCond(record,tokens[0],tokens[1],tokens[2]);
                for(size_t i = 3; i + 3 < tokens.size(); i+=4){
                    bool nextResult = evalCond(record,tokens[i+1],tokens[i+2],tokens[i+3]);
                    if(useAnd) result = result && nextResult;
                    else result = result || nextResult;
                }
                if(result){
                    displayFileDataBase(record);
                    found = true;
                }
            }
            if(!found){cout<<"NO FILE FOUND!\n";}
        }
        else if(commands.substr(0,4) == "FIND" || commands.substr(0,4) == "find"){
            std::stringstream ss(commands);
            std::string keyword, tableName, filename;
            ss >> keyword >> tableName >> filename;
            
            if(database.find(tableName) == database.end()){
                cout << "No such table: " << tableName << "\n";
                continue;
            }
            bool found = false;
            for(const auto& record : database[tableName]){
                if(record.fileName == filename){
                    displayFileDataBase(record);
                    found = true;
                    break;
                }
            }
            if(!found){
                cout << "File not found.\n";
            }
        }
        else if(commands.substr(0,12) == "DELETE WHERE" || commands.substr(0,12) == "delete where"){
            std::stringstream ss(commands);
            std::string keyword1, keyword2, tablename;
            ss >> keyword1 >> keyword2 >> tablename;
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }
            std::vector<std::string> tokens;
            std::string tok;
            while(ss >> tok){
                tokens.push_back(tok);
            }
            if(tokens.size() < 3 || (tokens.size() - 3) % 4 != 0){
                cout<<"INVALID `WHERE` SYNTAX!\n";
                continue;
            }
            bool useAnd = true;
            for(size_t i = 3; i < tokens.size(); i+=4){
                std::string combinator = tokens[i];
                if(combinator == "AND" || combinator == "and") useAnd = true;
                else if(combinator == "OR" || combinator == "or") useAnd = false;
            }
            auto evalCond = [&](const FileRecord& record,const std::string& field,
            const std::string& op, std::string& value) -> bool{
                if(field == "FILETYPE" || field == "filetype"){
                    return op == "==" ? (record.fileType == value) : false;   
                }
               else if(field == "FILENAME" || field == "filename"){
                    return op == "==" ? (record.fileName == value) : false;
                }
               else if(field == "SIZE" || field == "size"){
                    long long v = std::stoll(value);
                    if(op == "==") return record.fileSize == v;
                    else if(op == ">") return record.fileSize > v;
                    else if(op == "<") return record.fileSize < v;
               }
               return false;
            };
        //helper for the lamba function
        auto matchesALL = [&](const FileRecord& record) -> bool{
            bool result = evalCond(record,tokens[0],tokens[1],tokens[2]);
            for(size_t i = 3; i + 3 < tokens.size(); i+=4){
                bool nextResult = evalCond(record,tokens[i+1],tokens[i+2],tokens[i+3]);
                if(useAnd) result = result && nextResult;
                else result = result || nextResult;
            }
            return result;
        };
        auto& table = database[tablename];
        int matchCount = 0;
        for(const auto& record: table){
            if(matchesALL(record)){matchCount++;}
        }
        if(matchCount == 0){
            cout<<"NO RECORDS MATCHED!\n";
            continue;
        }
        cout<<"FOUND "<<matchCount<<" MATCHING RECORDS\nARE YOU SURE U WANT TO DELETE  THEM? (y/n)";
        char confirm;
        cin>>confirm;
        if(confirm == 'y' || confirm == 'Y'){
        int deletedCount = 0;
        for(auto it = table.begin(); it != table.end();){
            if(matchesALL(*it)){
                it = table.erase(it);
                deletedCount++;
            } else {
                ++it;
            }
        }
    }
    else{cout<<"DELETION CANCELLED\n";
        continue;}
}
        else if(commands.substr(0,6) == "DELETE" || commands.substr(0,6) == "delete"){
            std::stringstream ss(commands);
            std::string keyword, tableName, filename;
            ss >> keyword >> tableName >> filename;

            if(database.find(tableName) == database.end()){
                cout << "No such table: " << tableName << "\n";
                continue;
            }

            bool found = false;
            auto& table = database[tableName];
            for(auto it = table.begin(); it != table.end(); ++it){
                if(it->fileName == filename){
                    table.erase(it);
                    found = true;
                    cout << "DELETED: " << filename << "\n";
                    break;
                }
            }
            if(!found){
                cout << "FILE NOT FOUND\n";
            }
        }
        else if(commands.substr(0,6) == "UPDATE" || commands.substr(0,6) == "update"){
            std::stringstream ss(commands);
            std::string keyword,tablename,filename,field,newvalue;
            ss >> keyword >> tablename >>  filename >> field >> newvalue;

            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<< tablename <<"FOUND!\n";
                continue;
            }
            bool found = false;
            for(auto& record: database[tablename]){
            if(record.fileName == filename){
            found = true;
                    if(field == "FILETYPE" || field == "filetype"){
                    record.fileType = newvalue;
                       }
                    else if(field == "FILEPATH" || field == "filepath"){
                    record.filePath = newvalue;
                        }
                    else if(field == "FILENAME" || field == "filename"){
                    record.fileName = newvalue;
                        }
                else{
                    cout << "UNKOWN FIELDTYPE: " << field << "\n";
                    found = false;
                    break;
                    }
                    cout << "UPDATED " << filename << " from " << field << " to " << newvalue << "\n";
                    break;
                }
            }
            if(!found){
            cout << "NO RECORD FOUND OR INVALID FIELD TYPE!\n";
            }
        }
        else if(commands.substr(0,12) =="REMOVE TABLE" || commands.substr(0,12) == "remove table"){
            std::stringstream ss(commands);
            std::string keyword, keyword2,tablename;
            ss >> keyword >> keyword2 >> tablename;
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue; 
            }           
            auto nowit = database.find(tablename);
            char ch;
            cout<<"ARE YOU SURE U WANT TO DELETE "<<tablename<<" (Y/N):";
            cin>>ch;
            if(ch == 'y' || ch == 'Y'){
                database.erase(nowit);
            }else{
                continue;
            }
        }
        //prob scan where
        else if(commands.substr(0,10) == "SCAN WHERE" || commands.substr(0,10) == "scan where"){
            std::stringstream ss(commands);
            std::string keyword1, keyword2, tablename, dirpath;
            ss >> keyword1 >> keyword2 >> tablename;
            std::getline(ss, dirpath);
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }
            if(!dirpath.empty() && dirpath[0] == ' '){
                dirpath = dirpath.substr(1);
            }
            if(!fs::exists(dirpath) || !fs::is_directory(dirpath)){
                cout<<"INVALID DIRECTORY PATH: "<<dirpath<<"\n";
                continue;
            }//Implementing the scan where logic is
            std::vector<std::string> tokens;
            std::string tok;
            while(ss >> tok){
                tokens.push_back(tok);
            }
            bool useAnd = true;
            if(tokens.size() >= 3 && (tokens.size() - 3) % 4 == 0){
                for(size_t i = 3;i < tokens.size(); i+=4){
                    std::string combinator = tokens[i];
                    if(combinator == "AND" || combinator == "and") useAnd = true;
                    else if(combinator == "OR" || combinator == "or") useAnd =false;
                }
            }//working on this
        }
        else if(commands.substr(0,4) == "SCAN" || commands.substr(0,4) == "scan"){
            std::stringstream ss(commands);
            std::string keyword,tablename,dirpath;
            ss >> keyword >> tablename;
            std::getline(ss,dirpath);
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }
            if(!dirpath.empty() && dirpath[0] == ' '){
                dirpath = dirpath.substr(1);
            }
            if(!fs::exists(dirpath) || !fs::is_directory(dirpath)){
                cout<<"INVALID DIRECTORY PATH: "<<dirpath<<"\n";
                continue;
            }
            int addedCount = 0;
            for(const auto& entry: fs::directory_iterator(dirpath)){
                if(entry.is_regular_file()){
                    FileRecord newRecord;
                    newRecord.fileName = entry.path().filename().string();
                    newRecord.filePath = entry.path().string();
                    newRecord.fileType = newRecord.getFileExtension(newRecord.fileName);
                    newRecord.fileSize = newRecord.getFileSize(newRecord.filePath);
                    newRecord.dataAdded = "2024-01-01";
                    database[tablename].push_back(newRecord);
                    addedCount++;
                }
            }
            cout << "Scan and Added " << addedCount << " files to table " << tablename << "\n";
        }
        else{
            cout << "ERROR SYNTAX or COMMAND NOT FOUND\n";
        }
    }
    return 0;
}