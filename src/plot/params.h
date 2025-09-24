#pragma once

#include "config/config.h"
#include "plot/types.h"

class GnuplotParams
{
public:
    using string = std::string;
    string data_dir = "data/";
    string out_dir = "plot/";
    string title = "title";
    string width = "1280";
    string height = "900";
    string x_label = "X";
    string y_label = "Y";
    string out_ext = ".png";

    virtual std::string cmd_line() const;
};

class GnuplotLineParams : public GnuplotParams
{
protected:
    std::vector<string> collect_names() const;

public:
    std::vector<GnuplotLine> lines;
    std::string cmd_line() const override;
};