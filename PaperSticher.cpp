#include "PaperSticher.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>  // 包含用于打乱顺序的头文件
#include <random>     // 包含随机数生成器头文件

using namespace cv;
using namespace std;

class Picture
{
    int*** image_data;//图像数据
    string location;//目前图片的存储地址
    int NO;//目前处理的图片文件编号
    int MIN;//文件夹中碎纸片数
public:
    string save_palce;//图片存储地址
    Picture();
    Picture(string location, int NO, int MIN);
    void init();
    void get_img(Mat& image, int i, int* rows, int* cols, string location);//获取图像
    int col_sum(int*** image_data, int no1, int no2, int rows, int cols, int judge);//计算边界差的绝对值的和
    void stich_image(int** match, int first, Mat result, int NO, string location);//图像横向自动拼接
    ~Picture();
};

class Cut
{
    string image_name;
    string path_to_save;
    int num;
public:
    Cut(string str1, string str2, int n) :image_name(str1), path_to_save(str2), num(n) {}
    int Init();
};

PaperSticher::PaperSticher(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

PaperSticher::~PaperSticher()
{}

void PaperSticher::on_stich_btn_clicked()
{
    string loc = ui.address->text().toStdString();
    int pic_num = ui.pic_num->text().toInt();
    int NO = ui.file_NO->text().toInt();
    Picture pic(loc, NO, pic_num);
    pic.init();
}


//函数定义
Picture::Picture()
{
    cout << "请输入文件地址：";
    cin >> location;
    cout << "请输入文件编号：";
    cin >> NO;
    cout << "请输入文件中碎纸片个数";
    cin >> MIN;

    //动态创建三维数组
    image_data = new int** [MIN];
    cout << image_data << endl;
}

Picture::Picture(string location, int NO, int MIN)
{
    this->location = location;
    this->NO = NO;
    this->MIN = MIN;
    //动态创建三维数组
    image_data = new int** [MIN];
}

void Picture::init()
{
    Mat image;
    int rows = 0, cols = 0; //行数和列数

    //动态创建三维数组
    //int*** image_data = new int** [MIN];
    for (int i = 0; i < MIN; i++)
    {
        get_img(image, i, &rows, &cols, location);
    }

    cout << "读取完毕!\n";
    waitKey(0);
    //system("pause");

    //测试：是否成功储存
    /*
    cout << "输入测试的矩阵行数和列数" << endl;
    int row, col;
    cin >> row >> col;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << image_data[2][i][j] << ' ';
        }
        cout << endl;
    }
    */

    int right, left;//左右边界的列号
    //右边界匹配度
    int** right_match = new int* [MIN];

    for (int i = 0; i < MIN; i++)
    {
        right_match[i] = new int[MIN];
    }

    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < MIN; j++)
        {
            right_match[i][j] = col_sum(image_data, i, j, rows, cols, 1);
            //cout << right_match[i][j] << endl;
        }
    }
    //左边界匹配度
    int** left_match = new int* [MIN];

    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < MIN; j++)
        {
            left_match[i] = new int[MIN];
        }
    }

    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < MIN; j++)
        {
            left_match[i][j] = col_sum(image_data, i, j, rows, cols, 0);
        }
    }

    //找出第一个和最后一个
    int first, last;

    //测试：显示匹配度
    //cout << "右匹配" << endl;
    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < MIN; j++)
        {
            //cout << right_match[i][j] << " \t ";
            if (right_match[i][j] == 0)
            {
                last = i;
                first = j;
            }
        }
        //cout << endl;
    }
    /*
    cout << endl;
    cout << "左匹配" << endl;
    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < MIN; j++)
        {
            cout << left_match[i][j] << " \t";
        }
        cout << endl;
    }
    */

    //寻找每一张图片的最优匹配
    //int match[MIN][2];
    int** match = new int* [MIN];
    for (int i = 0; i < MIN; i++)
    {
        match[i] = new int[2];
    }


    for (int i = 0; i < MIN; i++)
    {
        int min_left = left_match[i][0];
        int min_left_pos = 0;
        int min_right = right_match[i][0];
        int min_right_pos = 0;

        for (int j = 1; j < MIN; j++)
        {
            if (left_match[i][j] < min_left)
            {
                min_left_pos = j;
                min_left = left_match[i][j];
            }
            if (right_match[i][j] < min_right)
            {
                min_right_pos = j;
                min_right = right_match[i][j];
            }
        }

        match[i][0] = min_left_pos;
        match[i][1] = min_right_pos;
    }

    //显示最佳匹配
    /*
    cout << "最佳匹配:" << endl;
    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            cout << match[i][0] << "\t" << match[i][1] << endl;
        }
    }

    cout << "first = " << first << endl; //展示第一个位置
    */

    //释放内存
    for (int i = 0; i < MIN; i++)
    {
        delete[]right_match[i];
    }
    delete[]right_match;

    for (int i = 0; i < MIN; i++)
    {
        delete[]left_match[i];
    }
    delete[]left_match;

    //自动拼接
    Mat result;
    stich_image(match, first, result, NO, location);

    //释放image_data
    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            delete[]image_data[i][j];
        }
        delete[]image_data[i];
    }
}

void Picture::get_img(Mat& image, int i, int* rows, int* cols, string location)
{
    string image_name;

    if (i < 10)
    {
        image_name = "00";
    }
    else if (i < 100)
    {
        image_name = "0";
    }
    else
    {
        image_name = "";
    }

    stringstream ss;
    string str;
    ss << i;		//将int转换成string
    ss >> str;

    image_name = image_name + str;	//图像文件名
    image_name = location + image_name + ".bmp";


    //读取图片并且将图像灰度化
    cout << "正在读取: " << image_name << endl;
    image = imread(image_name, IMREAD_GRAYSCALE);

    //检查是否正常读取到图片
    if (image.data == 0)
    {
        cout << "[error]没有图片!\n";
        system("pause");
    }

    //获取Mat行和列
    int row = image.rows;
    int col = image.cols;
    cout << "rows = " << row << endl;
    cout << "cols = " << col << endl;

    //将行数和列数信息带出函数
    *rows = row;
    *cols = col;

    //动态生成三维数组下的二维数组和一维数组
    image_data[i] = new int* [row];
    for (int j = 0; j < row; j++)
    {
        image_data[i][j] = new int[col];
    }

    //将image中的值写入image_data，并且实现二值化
    for (int j = 0; j < row; j++)
    {
        for (int k = 0; k < col; k++)
        {
            if (image.at<uchar>(j, k) == 255)
            {
                image_data[i][j][k] = 1;    //白色赋值为1
            }
            else image_data[i][j][k] = 0;     //黑色（其他）赋值为0
        }
    }
}	//获取图像

int Picture::col_sum(int*** image_data, int no1, int no2, int rows, int cols, int judge)
{
    int sum = 0;
    int col_1 = 0, col_2 = 0;

    //judge=1右匹配，judge=0左匹配
    (judge == 1) ? (col_1 = cols - 1, col_2 = 0) : (col_1 = 0, col_2 = cols - 1);

    for (int i = 0; i < rows; i++)
    {
        sum += abs(image_data[no1][i][col_1] - image_data[no2][i][col_2]);
    }
    return sum;
} //计算边界差的绝对值的和

void Picture::stich_image(int** match, int first, Mat result, int NO, string location)
{
    Mat image;
    vector<Mat> imgs;
    int no;

    //读取图像
    for (int i = 0; i < MIN; i++)
    {
        if (i == 0)
        {
            no = first;
        }
        else
        {
            for (int j = 0; j < MIN; j++)
            {
                if (match[j][0] == no)
                {
                    no = j;
                    break;
                }
            }
        }

        string image_name;
        stringstream ss;
        string str;

        if (no < 10)
        {
            image_name = "00";
        }
        else
        {
            image_name = "0";
        }

        ss << no;		//将int转换成string
        ss >> str;

        image_name = image_name + str;	//图像文件名
        image_name = location + image_name + ".bmp";
        image = imread(image_name);
        //resize(image, image, Size())
        imgs.push_back(image);
    }

    hconcat(imgs, result);
    //string img_name;
    save_palce = "C:/Users/王崟珅/Desktop/碎纸片拼接/result_" + to_string(NO) + ".png";
    imwrite(save_palce, result);

    namedWindow("Result_" + to_string(NO), WINDOW_NORMAL);
    imshow("Result_" + to_string(NO), result);
    waitKey(0);
}

Picture::~Picture()
{
    delete image_data;
}

int Cut::Init()
{
    // 读取图片
    Mat image = imread(image_name);

    if (image.empty()) {
        cerr << "Could not read the image" << endl;
        return 1;
    }

    // 获取图片的高度和宽度
    int height = image.rows;
    int width = image.cols;

    // 定义要切割的份数
    int num_slices = num;  // 假设要将图片纵向切割成 5 份

    // 计算每份的高度
    int slice_width = width / num_slices;

    // 创建要保存的图片索引
    std::vector<int> indices(num_slices);
    for (int i = 0; i < num_slices; i++) {
        indices[i] = i;
    }

    // 使用随机数生成器打乱顺序
    random_device rd;
    mt19937 g(rd());
    shuffle(indices.begin(), indices.end(), g);

    // 切割图片并保存
    for (int i = 0; i < num_slices; i++) {
        int index = indices[i];  // 获取打乱后的索引
        int start_col = i * slice_width;
        int end_col = (i + 1) * slice_width;

        // 切割图片
        Rect roi(start_col, 0, end_col - start_col, height);
        Mat croppedImage = image(roi);

        // 生成保存文件的路径
        string str;
        if (i < 10)
        {
            str = "00";
        }
        else if (i < 100)
        {
            str = "0";
        }
        else
        {
            str = "";
        }
        string outputFilename = path_to_save + '/' + str + to_string(index) + ".bmp";

        // 保存切割后的图片
        bool result = imwrite(outputFilename, croppedImage);

        if (result) {
            std::cout << "Image " << i << " 已成功剪裁并保存" << endl;
        }
        else {
            std::cerr << "Error saving the cropped image " << i << endl;
        }
    }
    cout << "剪裁保存完成" << endl;
    return 1;
}
