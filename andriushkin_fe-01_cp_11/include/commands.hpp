#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "exec_manager.hpp"

bool CheckVarName(std::string name);

class Command
{
protected:
    std::string comm_name;
public:
    Command();
    Command(std::vector<std::string> tokens);
    virtual ~Command() = 0;
    virtual void Execute(ExecManager &em) = 0;
};

class Exit : public Command
{
public:
    Exit();
    Exit(std::vector<std::string> tokens);
    ~Exit();
    void Execute(ExecManager &em) override;
};

class Create : public Command
{
private:
    std::string name;
public:
    Create(std::string name_);
    Create(std::vector<std::string> tokens);
    ~Create();
    void Execute(ExecManager &em) override;
};

class Insert : public Command
{
private:
    std::string name;
    uint64_t y, x;
public:
    Insert(std::string name_, std::int64_t x_, std::int64_t y_);
    ~Insert();
    void Execute(ExecManager &em) override;
};

class PrintTree : public Command
{
private:
    std::string name;
public:
    PrintTree(std::string name);
    ~PrintTree();
    void Execute(ExecManager &em) override;
};

class Contains : public Command
{
private:
    std::string name;
    uint64_t y, x;
public:
    Contains(std::string name_, std::int64_t x_, std::int64_t y_);
    ~Contains();
    void Execute(ExecManager &em) override;
};

std::shared_ptr<Command> RecognizeComm(std::vector<std::string> tokens);