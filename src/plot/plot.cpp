#include "plot/plot.h"
#include "general/general.h"

#include <fstream>
#include <sstream>

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

void print_plot_data(const std::vector<Point> &src, const GnuplotParams &p)
{
    auto path = safe_path(p.data_dir, p.title + p.data_ext);
    std::ofstream file(path);
    for (auto &p : src)
        file << p.x << ' ' << p.y << std::endl;
    file.close();
}

int draw_plot(const std::vector<Point> &src, const GnuplotParams &p)
{
    print_plot_data(src, p);
    return exec(p.cmd_line());
}
int draw_plot(const std::vector<double> &x, const std::vector<double> &y, const GnuplotParams &p)
{
    auto merged = merge(x, y);
    return draw_plot(merged, p);
}

std::string GnuplotParams::cmd_line() const
{
    string data_name = title + data_ext;
    string out_name = title + out_ext;

    string data_path = safe_path(data_dir, data_name);
    string out_path = safe_path(out_dir, out_name);

    std::stringstream line;
    line << "gnuplot -e \""
         << gnuplot_param_str("datafile", data_path, " ")
         << gnuplot_param_str("output_file", out_path, " ")
         << gnuplot_param_str("custom_title", title, " ")
         << gnuplot_param("width", width, " ")
         << gnuplot_param("height", height, " ")
         << gnuplot_param_str("x_label", x_label, " ")
         << gnuplot_param_str("y_label", y_label)
         << "\" plot_template.gp";
    return line.str();
}
