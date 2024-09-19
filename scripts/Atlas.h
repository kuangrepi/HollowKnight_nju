#include <vector>
#include <graphics.h>
#include <cstdio>


class Atlas {
private:
    std::vector<IMAGE> img_list;

public:
    Atlas() = default;
    ~Atlas() = default;

    void load_from_file(LPCTSTR path_template, int num);//num 表示图片数量

    void clear();

    int get_size();

    IMAGE* get_image(int idx); // 用这个获得实际渲染的图片

    void add_image(const IMAGE& img);

};


