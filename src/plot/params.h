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
    string width = "2560";
    string height = "800";
    string x_label = "X";
    string y_label = "Y";
    string out_ext = ".png";

    std::vector<GnuplotLine> lines;

    virtual std::string cmd_line() const;
};