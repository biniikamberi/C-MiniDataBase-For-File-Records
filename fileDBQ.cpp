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
#include <ctime>
struct FileRecord{
std::string fileName;
std::string filePath;
std::string fileType;
long long   fileSize;
std::string dataAdded;


long long getFileSize(std::string path){
    if(path.empty()){
        return -1;
    }
    std::ifstream file(path, std::ios::binary);
    if(!file.is_open()){
        return -1;
    }
    file.seekg(0, std::ios::end);
    return file.tellg();
}

std::string getFileExtension(std::string& filename){
    if(filename.empty()){
        return "ERROR EXTENSION TYPE\n";
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
    <<"#SHOW TABLES -shows all tables in the DataBase\n"
    <<"#SHOW ALL -shows all data to availabe Database,SHOW ALL [tablename]\n"
    <<"#SORT -sorts a table by a field, SORT [tablename] [field(ex, filename,filetype,etc)] [ASC|DESC]\n"
    <<"#VIEW -views a file inside the Database,VIEW [tablename] [filename]\n"
    <<"OPEN -opens a file inside the Database,OPEN [tablename] [filename]\n"
    <<"#COUNT -counts the number of files inside a table,COUNT [tablename]\n"
    <<"EDIT -Edits/Opens a file inside The VSCODE EDITOR,EDIT [tablename] [filename] --MAYBE IN THE FUTURE I WILL UPDATE IT FOR ANY IDE BUT FOR NOW IT'S JUST FOR VSCODE\n"
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
#include <algorithm>
std::string getCurrentDate(){
    std::time_t now = time(0);
    tm* localTime = std::localtime(&now);
    char buffer[11];
    std::strftime(buffer,sizeof(buffer),"%Y-%m-%d",localTime);
    return std::string(buffer);
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
    cout<<"\033[1;32mFSQL_C v1.21\033[0m\n";
#else
    system("clear");
    cout<<"\033[1;32mFSQL_C v1.21\033[0m\n";
#endif    
}

std::string getDefaultContent(const std::string& extension){
    if(extension == "txt")return "New Text File";
    else if(extension == "cpp")return "#include <iostream>\n\nint main(){\n    std::cout << \"Hello, World!\" << std::endl;\n    return 0;\n}\n";
    else if(extension == "py")return "print(\"Hello, World!\")\n";
    else if(extension == "html")return "<!DOCTYPE html>\n<html>\n<head>\n    <title>New HTML File</title>\n</head>\n<body>\n\n</body>\n</html>\n";
    else if(extension == "css")return "/* New CSS File */\nbody {\n    margin: 0;\n    padding: 0;\n}\n";
    else if(extension == "js")return "// New JavaScript File\nconsole.log(\"Hello, World!\");\n";
    else if(extension == "json")return "{\n    \"key\": \"value\"\n}\n";
    else if(extension == "md")return "# New Markdown File\n\nWrite your content here.\n";
    else if(extension == "java")return "public class Main {\n    public static void main(String[] args) {\n        System.out.println(\"Hello, World!\");\n    }\n}\n";
    else if(extension == "c")return "#include <stdio.h>\n\nint main() {\n    printf(\"Hello, World!\\n\");\n    return 0;\n}\n";
    else if(extension == "cs")return "using System;\n\nclass Program {\n    static void Main() {\n        Console.WriteLine(\"Hello, World!\");\n    }\n}\n";
    else if(extension == "rb")return "puts \"Hello, World!\"\n";
    else if(extension == "php")return "<?php\n\necho \"Hello, World!\";\n\n?>\n";
    else if(extension == "xml")return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<root>\n</root>\n";
    else if(extension == "sh")return "#!/bin/bash\n\necho \"Hello, World!\"\n";
    else if(extension == "bat")return "@echo off\n\necho Hello, World!\npause\n";
    else if(extension == "go")return "package main\n\nimport \"fmt\"\n\nfunc main() {\n    fmt.Println(\"Hello, World!\")\n}\n";
    else if(extension == "rs")return "fn main() {\n    println!(\"Hello, World!\");\n}\n";
    else if(extension == "kt")return "fun main() {\n    println(\"Hello, World!\")\n}\n";
    else if(extension == "swift")return "import Foundation\n\nprint(\"Hello, World!\")\n";
    else if(extension == "ts")return "console.log(\"Hello, World!\");\n";
    else if(extension == "dart")return "void main() {\n    print('Hello, World!');\n}\n";
    else if(extension == "lua")return "print(\"Hello, World!\")\n";
    else if(extension == "r")return "cat(\"Hello, World!\\n\")\n";
    else if(extension == "sql")return "-- New SQL File\n-- Write your SQL queries here.\n";
    else if(extension == "bat")return "@echo off\n\necho Hello, World!\npause\n";
    else if(extension == "ps1")return "Write-Host \"Hello, World!\"\n";
    else if(extension == "pl")return "print \"Hello, World!\\n\";\n";
    else if(extension == "asm")return "section .data\n    msg db 'Hello, World!',0\n\nsection .text\n    global _start\n\n_start:\n    mov edx, 13\n    mov ecx, msg\n    mov ebx, 1\n    mov eax, 4\n    int 0x80\n    mov eax, 1\n    int 0x80\n";
    else if(extension == "vbs")return "MsgBox \"Hello, World!\"\n";
    else if(extension == "f90")return "program hello\n    print *, \"Hello, World!\"\nend program hello\n";
    else if(extension == "doc")return "This is a new Word document.\n";
    else if(extension == "docx")return "This is a new Word document.\n";
    else if(extension == "xls")return "This is a new Excel spreadsheet.\n";
    else if(extension == "xlsx")return "This is a new Excel spreadsheet.\n";
    else if(extension == "ppt")return "This is a new PowerPoint presentation.\n";
    else if(extension == "pptx")return "This is a new PowerPoint presentation.\n";
    else if(extension == "odt")return "This is a new OpenDocument text file.\n";
    else if(extension == "ods")return "This is a new OpenDocument spreadsheet file.\n";
    else if(extension == "odp")return "This is a new OpenDocument presentation file.\n";
    else if(extension == "epub")return "This is a new EPUB e-book file.\n";
    else if(extension == "mobi")return "This is a new MOBI e-book file.\n";
    else if(extension == "azw3")return "This is a new AZW3 e-book file.\n";
    else if(extension == "flac")return "This is a new FLAC audio file.\n";
    else if(extension == "mp3")return "This is a new MP3 audio file.\n";
    else if(extension == "wav")return "This is a new WAV audio file.\n";
    else if(extension == "ogg")return "This is a new OGG audio file.\n";
    else if(extension == "mp4")return "This is a new MP4 video file.\n";
    else if(extension == "avi")return "This is a new AVI video file.\n";
    else if(extension == "mkv")return "This is a new MKV video file.\n";
    else if(extension == "mov")return "This is a new MOV video file.\n";
    else if(extension == "wmv")return "This is a new WMV video file.\n";
    else if(extension == "webm")return "This is a new WebM video file.\n";
    else if(extension == "flv")return "This is a new FLV video file.\n";
    else if(extension == "m4v")return "This is a new M4V video file.\n";
    else if(extension == "3gp")return "This is a new 3GP video file.\n";
    else if(extension == "ts")return "This is a new TS video file.\n";
    else if(extension == "vob")return "This is a new VOB video file.\n";
    else if(extension == "iso")return "This is a new ISO disk image file.\n";
    else if(extension == "img")return "This is a new IMG disk image file.\n";
    else if(extension == "bin")return "This is a new BIN binary file.\n";
    else if(extension == "cue")return "This is a new CUE disk image file.\n";
    else if(extension == "mdf")return "This is a new MDF disk image file.\n";
    else if(extension == "mds")return "This is a new MDS disk image file.\n";
    else if(extension == "toast")return "This is a new TOAST disk image file.\n";
    else if(extension == "dmg")return "This is a new DMG disk image file.\n";
    return " ";
}


int main(){
    ClearScreenAuto();
    std::map<std::string, std::vector<FileRecord>> database;
    cout<<"\033[1;32mFSQL_C v1.21\033[0m\n";

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
        else if(commands == "SHOW TABLES" || commands == "show tables" || 
            commands == "SHOW TABLE" || commands == "show table"){
            if(database.empty()){
                cout << "Theres No Table inside the Database!\n";
            } else {
                for(const auto& tablePair : database){
                    cout << "- " << tablePair.first << "\n";
                }
            }
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
            std::string keyword,tablename,filename;
            ss >> keyword >> tablename >> filename;
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }
            std::string storageDir = "storage/" + tablename;
            fs::create_directories(storageDir);
            std::string filePath = storageDir + "/" + filename;
            if(fs::exists(filename)){
                fs::copy_file(filename, filePath, fs::copy_options::overwrite_existing);
                cout << "File " << filename << " already exists in table " << tablename << ". Overwriting.\n";
            }else{
                    FileRecord temp;
                    std::string ext = temp.getFileExtension(filename);
                    std::ofstream outFile(filePath);
                    outFile << getDefaultContent(ext);
            }
            FileRecord newRecord;
            newRecord.fileName = filename;
            newRecord.filePath = filePath;
            newRecord.fileType = newRecord.getFileExtension(filename);
            newRecord.fileSize = newRecord.getFileSize(newRecord.filePath);
            newRecord.dataAdded = getCurrentDate();
            database[tablename].push_back(newRecord);
            cout << "Added " << filename << " to " << tablename << "\n";
        }
        else if(commands.substr(0,4) == "VIEW" || commands.substr(0,4) == "view"){
            std::stringstream ss(commands);
            std::string keyword,tablename,filename;
            ss >> keyword >> tablename >> filename;
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }
            bool found = false;
            std::string trgtPath;
            for(const auto& record: database[tablename]){
                if(record.fileName == filename){
                    trgtPath = record.filePath;
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"FILE NOT FOUND IN TABLE "<<tablename<<"\n";
                continue;
            }
            std::ifstream inFile(trgtPath);
            if(!inFile.is_open()){
                cout<<"FAILED TO OPEN FILE: "<<trgtPath<<"\n";
                continue;
            }
            cout<<"---"<<filename<<"---\n\n";
            std::string line;
            while(std::getline(inFile, line)){
                cout<<line<<"\n";
            }
            inFile.close();
            cout<<"-------------\n";
        }
        else if(commands.substr(0,4) == "SORT" || commands.substr(0,4) == "sort"){
            std::stringstream ss(commands);
            std::string keyword, tablename, by, field,order;
            ss >> keyword >> tablename >> by >> field >> order;
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }
            if(by != "BY" && by != "by"){
                cout<<"INVALID SYNTAX!\n";
                continue;
            }
            auto& table = database[tablename];
            bool desecding = (order == "DESC" || order == "desc");
              std::sort(table.begin(), table.end(), [&](const FileRecord& a, const FileRecord& b) -> bool {
                bool result = false;
                if(field == "FILENAME" || field == "filename"){
                    result = a.fileName < b.fileName;
                }
                else if(field == "FILETYPE" || field == "filetype"){
                    result = a.fileType < b.fileType;
                }
                else if(field == "SIZE" || field == "size"){
                    result = a.fileSize < b.fileSize;
                }
                else if(field == "DATEADDED" || field == "dateadded"){
                    result = a.dataAdded < b.dataAdded;
                }
                return desecding ? !result : result;
              });
               cout << "Sorted table " << tablename << " by " << field << (desecding ? " (descending)" : " (ascending)") << "\n";
    }
        else if(commands.substr(0,11) == "COUNT WHERE" || commands.substr(0,11) == "count where"){
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
            int count = 0;
            for(const auto& record: database[tableName]){
                bool  result = evalCond(record,tokens[0],tokens[1],tokens[2]);
                for(size_t i = 3; i + 3 < tokens.size(); i+=4){
                    bool nextResult = evalCond(record,tokens[i+1],tokens[i+2],tokens[i+3]);
                    if(useAnd) result = result && nextResult;
                    else result = result || nextResult;
                }
                if(result) count++;
            }
            cout << "Count of files in table " << tableName << " matching the condition: " << count << "\n";
        }
        else if(commands.substr(0,5) == "COUNT" || commands.substr(0,5) == "count"){
            std::stringstream ss(commands);
            std::string keyword,tablename;
            ss >> keyword >> tablename;
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }
            cout<<"Number of files in table "<<tablename<<": "<<database[tablename].size()<<"\n";
        }
        else if(commands.substr(0,4) == "OPEN" || commands.substr(0,4) == "open"){
            std::stringstream ss(commands);
            std::string keyword,tablename,filename;
            ss >> keyword >> tablename >> filename;
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }
            bool found = false;
            std::string trgtPath;
            for(const auto& record:  database[tablename]){
                if(record.fileName == filename){
                    trgtPath = record.filePath;
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"FILE NOT FOUND IN TABLE "<<tablename<<"\n";
                continue;
            }
            cout<<"Opening file: "<<filename<<" from table: "<<tablename<<".......\n";
            #ifdef _WIN32
                std::string command = "start \"\" \"" + trgtPath + "\"";
                system(command.c_str());
            #else
                std::string command = "xdg-open \"" + trgtPath + "\"";
                system(command.c_str());
            #endif
            cout<<"Succesfully found and opened file: "<<filename<<" from table: "<<tablename<<"\n";    
        }
        else if(commands.substr(0,4) == "EDIT" || commands.substr(0,4) == "edit"){
            std::stringstream ss(commands);
            std::string keyword,tablename,filename;
            ss >> keyword >> tablename >> filename;
            if(database.find(tablename) == database.end()){
                cout<<"NO SUCH TABLE "<<tablename<<" FOUND!\n";
                continue;
            }

            bool found = false;
            std::string trgtPath;
            for(const auto& record: database[tablename]){
                if(record.fileName == filename){
                    trgtPath = record.filePath;
                    found =true;
                    break;
                }
            }
            if(!found){
                cout<<"FILE NOT FOUND IN TABLE "<<tablename<<"\n";
                continue;
            }
            std::string command = "code \"" + trgtPath + "\"";
            system(command.c_str());
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
        else if(commands.substr(0,12) == "UPDATE WHERE" || commands.substr(0,12) == "update where"){
            std::stringstream ss(commands);
            std::string keyword1, keyword2, tablename;
            ss >> keyword1 >> keyword2 >> tablename;

            if(database.find(tablename) == database.end()){
                cout << "NO SUCH TABLE " << tablename << " FOUND!\n";
                continue;
                }

            std::vector<std::string> allTokens;
            std::string tok;
            while(ss >> tok){
                allTokens.push_back(tok);
            }
        int setIndex = -1;
        for(size_t i = 0; i < allTokens.size(); i++){
            if(allTokens[i] == "SET" || allTokens[i] == "set"){
                setIndex = (int)i;
                break;
                    }
            }
        if(setIndex == -1 || setIndex + 2 >= (int)allTokens.size()){
                cout << "INVALID SYNTAX. Use: UPDATE WHERE <table> <conditions> SET <field> <value>\n";
                continue;
            }

            std::vector<std::string> tokens(allTokens.begin(), allTokens.begin() + setIndex);
            std::string newField = allTokens[setIndex + 1];
            std::string newValue = allTokens[setIndex + 2];

            if(tokens.size() < 3 || (tokens.size() - 3) % 4 != 0){
            cout << "INVALID `WHERE` SYNTAX!\n";
            continue;
            }

        bool useAnd = true;
        for(size_t i = 3; i < tokens.size(); i += 4){
            std::string combinator = tokens[i];
                if(combinator == "AND" || combinator == "and") useAnd = true;
                else if(combinator == "OR" || combinator == "or") useAnd = false;
            }

            auto evalCond = [](const FileRecord& record, const std::string& field, const std::string& op, const std::string& value) -> bool{
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

        auto matchesAll = [&](const FileRecord& record) -> bool {
            bool result = evalCond(record, tokens[0], tokens[1], tokens[2]);
            for(size_t i = 3; i + 3 < tokens.size(); i += 4){
                bool nextResult = evalCond(record, tokens[i+1], tokens[i+2], tokens[i+3]);
                if(useAnd) result = result && nextResult;
                    else result = result || nextResult;
                    }
            return result;
            };

        int updatedCount = 0;
        for(auto& record : database[tablename]){
            if(matchesAll(record)){
                    if(newField == "FILETYPE" || newField == "filetype"){
                        record.fileType = newValue;
                    }
                    else if(newField == "FILENAME" || newField == "filename"){
                        record.fileName = newValue;
                        }
                    else if(newField == "FILEPATH" || newField == "filepath"){
                        record.filePath = newValue;
                        }
                    else{
                    cout << "UNKNOWN FIELD TO SET: " << newField << "\n";
                    continue;
                    }
                    updatedCount++;
                }
            }
        cout << "Updated " << updatedCount << " record(s) in " << tablename << "\n";
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
    
            std::stringstream dirss(dirpath);
            std::string realDirPath;
            dirss >> realDirPath;
            std::vector<std::string> tokens;
            std::string tok;

            while(dirss >> tok){
                tokens.push_back(tok);
            }
            if(!fs::exists(realDirPath) || !fs::is_directory(realDirPath)){
                cout<<"INVALID DIRECTORY PATH: "<<realDirPath<<"\n";
                continue;
            }
            if(tokens.size() < 3 || (tokens.size() - 3) % 4 != 0){
                cout<<"INVALID `WHERE` SYNTAX!\n";
                continue;
            }
            bool useAnd =true;
            for(size_t i = 3; i < tokens.size(); i+=4){
                std::string combinator = tokens[i];
                if(combinator == "AND" || combinator == "and") useAnd = true;
                else if(combinator == "OR" || combinator == "or") useAnd = false;
            }

            auto evalCond = [](const std::string& fname, const std::string& ftype, long long fsize,
                        const std::string& field, const std::string& op, const std::string& value) -> bool{
                            if(field == "FILETYPE" || field == "filetype"){
                                return op == "==" ? (ftype == value) : false;
                            }
                            else if(field == "FILENAME" || field == "filename"){
                                return op == "==" ? (fname == value) : false;
                            }
                            else if(field == "SIZE" || field == "size"){
                                long long v = std::stoll(value);
                                if(op == "==") return fsize == v;
                                else if(op == ">") return fsize > v;
                                else if(op == "<") return fsize < v;
                            }
                            return false;
            };
            unsigned int addedCount = 0;
            for(const auto& entry: fs::directory_iterator(realDirPath)){
                if(!entry.is_regular_file()){
                    continue;
                }
                std::string fname = entry.path().filename().string();
                FileRecord temp;
                std::string ftype = temp.getFileExtension(fname);
                std::string fullPath = entry.path().string();
                long long fsize = temp.getFileSize(fullPath);
                bool result = evalCond(fname, ftype, fsize, tokens[0], tokens[1], tokens[2]);
                for(size_t i = 3; i+3 <tokens.size(); i+=4){
                    bool nextResult = evalCond(fname, ftype, fsize, tokens[i+1], tokens[i+2], tokens[i+3]);
                    if(useAnd) result = result && nextResult;
                    else result = result || nextResult;
                }
                if(result){
                    FileRecord newRecord;
                    newRecord.fileName = fname;
                    newRecord.filePath = entry.path().string();
                    newRecord.fileType = ftype;
                    newRecord.fileSize = fsize;
                    newRecord.dataAdded = getCurrentDate();
                    database[tablename].push_back(newRecord);
                    addedCount++;
            }
        }
        cout<<"Scan and Added " << addedCount << " files to table " << tablename << "\n";
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
                    newRecord.dataAdded = getCurrentDate();
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
