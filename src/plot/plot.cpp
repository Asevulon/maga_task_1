#include "plot/plot.h"
#include "general/general.h"

#include <fstream>
#include <sstream>
#include "plot.h"
#include <algorithm>
#include <ranges>
#include <cstdint>

using std::ranges::for_each;

std::vector<Point> merge(const std::vector<double> &x, const std::vector<double> &y)
{
    std::vector<Point> res;

    size_t size = std::min(x.size(), y.size());
    res.resize(size);

    for (uint64_t i = 0; i < size; ++i)
    {
        res[i].x = x[i];
        res[i].y = y[i];
    }

    return res;
}

void print_plot_data(const GnuplotParams &p)
{
    std::string data_path = safe_path(p.data_dir, p.title);

    std::ofstream file(data_path);

    size_t max_size = 0;

    for (const auto &line : p.lines)
    {
        file << "\"x_" << line.name << "\" "
             << "\"" << line.name << "\" ";
        if (max_size < line.data.size())
            max_size = line.data.size();
    }
    file << std::endl;

    for (size_t i = 0; i < max_size; ++i)
    {
        for (const auto &line : p.lines)
        {
            file << gnuplot_extract_data_str(line, i) << " ";
        }
        file << std::endl;
    }
    file.close();
}

int draw_plot(const GnuplotParams &p)
{
    print_plot_data(p);
    return exec(p.cmd_line());
}

std::string GnuplotParams::cmd_line() const
{
    string out_name = endline_check(title) + out_ext;

    string data_path = safe_path(data_dir, title);
    string out_path = safe_path(out_dir, out_name);

    std::stringstream line;
    line << gnuplot_line_prefix()
         << gnuplot_param_str("datafile", data_path, " ")
         << gnuplot_param_str("output_file", out_path, " ")
         << gnuplot_param_str("custom_title", title, " ")
         << gnuplot_param("width", width, " ")
         << gnuplot_param("height", height, " ")
         << gnuplot_param_str("x_label", x_label, " ")
         << gnuplot_param_str("y_label", y_label)
         << gnuplot_line_suffix();
    return line.str();
}

GnuplotLine::GnuplotLine(const std::string &name, const std::vector<double> x, const std::vector<double> &y)
    : name(name)
{
    data = merge(x, y);
}
