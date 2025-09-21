#pragma once

#include <string>
#include <vector>

struct Point
{
    double x = 0;
    double y = 0;
};

class GnuplotParams
{
public:
    using string = std::string;
    string data_dir = "data/";
    string out_dir = "plot/";
    string title = "title";
    string width = "800";
    string height = "600";
    string x_label = "X";
    string y_label = "Y";
    string data_ext = ".txt";
    string out_ext = ".png";

    std::string cmd_line() const;
};

std::vector<Point> merge(const std::vector<double> &x, const std::vector<double> &y);

void print_plot_data(const std::vector<Point> &src, const GnuplotParams &p);
int draw_plot(const std::vector<Point> &src, const GnuplotParams &p);
int draw_plot(const std::vector<double> &x, const std::vector<double> &y, const GnuplotParams &p);

inline std::string safe_path(const std::string head, const std::string tail)
{
    return head + ((head.back() == '/') ? "" : "/") + tail;
}
inline std::string gnuplot_param(const std::string name, const std::string val, const std::string endline = "")
{
    return name + "=" + val + ";" + endline;
}
inline std::string gnuplot_param_str(const std::string name, const std::string val, const std::string endline = "")
{
    return name + "='" + val + "';" + endline;
}