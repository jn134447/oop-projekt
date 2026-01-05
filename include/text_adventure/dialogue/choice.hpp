#ifndef CHOICE_H
#define CHOICE_H
#pragma once

#include <string>
class Choice
{
    std::string text;
    std::string targetNodeId;

public:
    Choice(std::string text, std::string targetNodeId);
    const std::string &GetText() const;
    const std::string &GetTargetNodeId() const;
};

#endif