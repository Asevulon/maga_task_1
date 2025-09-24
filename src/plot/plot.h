#pragma once

#include "plot/params.h"

std::vector<Point> merge(const std::vector<double> &x, const std::vector<double> &y);

void print_plot_data(const std::vector<Point> &src, const GnuplotParams &p);
void print_plot_data(const std::vector<Point> &src, const std::string &path);

int draw_plot(const std::vector<Point> &src, const GnuplotParams &p);
int draw_plot(const std::vector<double> &x, const std::vector<double> &y, const GnuplotParams &p);
int draw_plot(const GnuplotLineParams &p);

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
template <typename ContainerType>
inline std::string gnuplot_long_param_str(const std::string name, ContainerType &&src, std::string endline = "")
{
    std::string result = name + "='";
    for (auto &item : src)
        result += item + ' ';
    result.back() = '\'';
    return result + ";" + endline;
}

constexpr inline const char *gnuplot_line_prefix()
{
    return "gnuplot -e \"";
}
constexpr inline const char *gnuplot_line_suffix()
{
    return "\" plot_template.gp";
}