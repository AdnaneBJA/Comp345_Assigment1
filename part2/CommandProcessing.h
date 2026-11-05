// Assignment 2, Part 1: command processor and file command processor adapter.

#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GameEngine.h"

// A command typed by the user (for example "addplayer Alice") and its effect.
class Command {
public:
    Command(std::string text);
    Command(const Command& other);
    ~Command();
    Command& operator=(const Command& other);
    friend std::ostream& operator<<(std::ostream& out, const Command& command);

    void saveEffect(std::string newEffect);
    std::string getCommand() const;
    std::string getEffect() const;

private:
    std::string* command;
    std::string* effect;
};

// Reads commands from the console and saves them in a list of commands.
// The command processor owns its commands and deletes them.
class CommandProcessor {
public:
    CommandProcessor();
    CommandProcessor(const CommandProcessor& other);
    virtual ~CommandProcessor();
    CommandProcessor& operator=(const CommandProcessor& other);
    friend std::ostream& operator<<(std::ostream& out, const CommandProcessor& processor);

    Command* getCommand();
    bool validate(Command* command, GameEngine* engine);
    GameEngine::State nextState(Command* command);

protected:
    virtual std::string readCommand();
    void saveCommand(std::string text);

private:
    std::vector<Command*>* commands;
};

// Reads a text file line by line (the adaptee of the Adapter pattern).
class FileLineReader {
public:
    FileLineReader(std::string fileName);
    FileLineReader(const FileLineReader& other);
    ~FileLineReader();
    FileLineReader& operator=(const FileLineReader& other);
    friend std::ostream& operator<<(std::ostream& out, const FileLineReader& reader);

    bool readLineFromFile(std::string& line);
    bool isOpen() const;

private:
    std::string* fileName;
    std::ifstream* file;
};

// Adapter: a command processor that reads its commands from a file instead of
// the console, by using a FileLineReader.
class FileCommandProcessorAdapter : public CommandProcessor {
public:
    FileCommandProcessorAdapter(std::string fileName);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);
    ~FileCommandProcessorAdapter();
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);
    friend std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter& adapter);

    bool isFileOpen() const;

protected:
    std::string readCommand();

private:
    FileLineReader* flr;
};

#endif