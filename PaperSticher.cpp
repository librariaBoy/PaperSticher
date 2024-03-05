#include "PaperSticher.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>  // �������ڴ���˳���ͷ�ļ�
#include <random>     // ���������������ͷ�ļ�

using namespace cv;
using namespace std;

class Picture
{
    int*** image_data;//ͼ������
    string location;//ĿǰͼƬ�Ĵ洢��ַ
    int NO;//Ŀǰ�����ͼƬ�ļ����
    int MIN;//�ļ�������ֽƬ��
public:
    string save_palce;//ͼƬ�洢��ַ
    Picture();
    Picture(string location, int NO, int MIN);
    void init();
    void get_img(Mat& image, int i, int* rows, int* cols, string location);//��ȡͼ��
    int col_sum(int*** image_data, int no1, int no2, int rows, int cols, int judge);//����߽��ľ���ֵ�ĺ�
    void stich_image(int** match, int first, Mat result, int NO, string location);//ͼ������Զ�ƴ��
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


//��������
Picture::Picture()
{
    cout << "�������ļ���ַ��";
    cin >> location;
    cout << "�������ļ���ţ�";
    cin >> NO;
    cout << "�������ļ�����ֽƬ����";
    cin >> MIN;

    //��̬������ά����
    image_data = new int** [MIN];
    cout << image_data << endl;
}

Picture::Picture(string location, int NO, int MIN)
{
    this->location = location;
    this->NO = NO;
    this->MIN = MIN;
    //��̬������ά����
    image_data = new int** [MIN];
}

void Picture::init()
{
    Mat image;
    int rows = 0, cols = 0; //����������

    //��̬������ά����
    //int*** image_data = new int** [MIN];
    for (int i = 0; i < MIN; i++)
    {
        get_img(image, i, &rows, &cols, location);
    }

    cout << "��ȡ���!\n";
    waitKey(0);
    //system("pause");

    //���ԣ��Ƿ�ɹ�����
    /*
    cout << "������Եľ�������������" << endl;
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

    int right, left;//���ұ߽���к�
    //�ұ߽�ƥ���
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
    //��߽�ƥ���
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

    //�ҳ���һ�������һ��
    int first, last;

    //���ԣ���ʾƥ���
    //cout << "��ƥ��" << endl;
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
    cout << "��ƥ��" << endl;
    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < MIN; j++)
        {
            cout << left_match[i][j] << " \t";
        }
        cout << endl;
    }
    */

    //Ѱ��ÿһ��ͼƬ������ƥ��
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

    //��ʾ���ƥ��
    /*
    cout << "���ƥ��:" << endl;
    for (int i = 0; i < MIN; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            cout << match[i][0] << "\t" << match[i][1] << endl;
        }
    }

    cout << "first = " << first << endl; //չʾ��һ��λ��
    */

    //�ͷ��ڴ�
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

    //�Զ�ƴ��
    Mat result;
    stich_image(match, first, result, NO, location);

    //�ͷ�image_data
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
    ss << i;		//��intת����string
    ss >> str;

    image_name = image_name + str;	//ͼ���ļ���
    image_name = location + image_name + ".bmp";


    //��ȡͼƬ���ҽ�ͼ��ҶȻ�
    cout << "���ڶ�ȡ: " << image_name << endl;
    image = imread(image_name, IMREAD_GRAYSCALE);

    //����Ƿ�������ȡ��ͼƬ
    if (image.data == 0)
    {
        cout << "[error]û��ͼƬ!\n";
        system("pause");
    }

    //��ȡMat�к���
    int row = image.rows;
    int col = image.cols;
    cout << "rows = " << row << endl;
    cout << "cols = " << col << endl;

    //��������������Ϣ��������
    *rows = row;
    *cols = col;

    //��̬������ά�����µĶ�ά�����һά����
    image_data[i] = new int* [row];
    for (int j = 0; j < row; j++)
    {
        image_data[i][j] = new int[col];
    }

    //��image�е�ֵд��image_data������ʵ�ֶ�ֵ��
    for (int j = 0; j < row; j++)
    {
        for (int k = 0; k < col; k++)
        {
            if (image.at<uchar>(j, k) == 255)
            {
                image_data[i][j][k] = 1;    //��ɫ��ֵΪ1
            }
            else image_data[i][j][k] = 0;     //��ɫ����������ֵΪ0
        }
    }
}	//��ȡͼ��

int Picture::col_sum(int*** image_data, int no1, int no2, int rows, int cols, int judge)
{
    int sum = 0;
    int col_1 = 0, col_2 = 0;

    //judge=1��ƥ�䣬judge=0��ƥ��
    (judge == 1) ? (col_1 = cols - 1, col_2 = 0) : (col_1 = 0, col_2 = cols - 1);

    for (int i = 0; i < rows; i++)
    {
        sum += abs(image_data[no1][i][col_1] - image_data[no2][i][col_2]);
    }
    return sum;
} //����߽��ľ���ֵ�ĺ�

void Picture::stich_image(int** match, int first, Mat result, int NO, string location)
{
    Mat image;
    vector<Mat> imgs;
    int no;

    //��ȡͼ��
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

        ss << no;		//��intת����string
        ss >> str;

        image_name = image_name + str;	//ͼ���ļ���
        image_name = location + image_name + ".bmp";
        image = imread(image_name);
        //resize(image, image, Size())
        imgs.push_back(image);
    }

    hconcat(imgs, result);
    //string img_name;
    save_palce = "C:/Users/�����|/Desktop/��ֽƬƴ��/result_" + to_string(NO) + ".png";
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
    // ��ȡͼƬ
    Mat image = imread(image_name);

    if (image.empty()) {
        cerr << "Could not read the image" << endl;
        return 1;
    }

    // ��ȡͼƬ�ĸ߶ȺͿ��
    int height = image.rows;
    int width = image.cols;

    // ����Ҫ�и�ķ���
    int num_slices = num;  // ����Ҫ��ͼƬ�����и�� 5 ��

    // ����ÿ�ݵĸ߶�
    int slice_width = width / num_slices;

    // ����Ҫ�����ͼƬ����
    std::vector<int> indices(num_slices);
    for (int i = 0; i < num_slices; i++) {
        indices[i] = i;
    }

    // ʹ�����������������˳��
    random_device rd;
    mt19937 g(rd());
    shuffle(indices.begin(), indices.end(), g);

    // �и�ͼƬ������
    for (int i = 0; i < num_slices; i++) {
        int index = indices[i];  // ��ȡ���Һ������
        int start_col = i * slice_width;
        int end_col = (i + 1) * slice_width;

        // �и�ͼƬ
        Rect roi(start_col, 0, end_col - start_col, height);
        Mat croppedImage = image(roi);

        // ���ɱ����ļ���·��
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

        // �����и���ͼƬ
        bool result = imwrite(outputFilename, croppedImage);

        if (result) {
            std::cout << "Image " << i << " �ѳɹ����ò�����" << endl;
        }
        else {
            std::cerr << "Error saving the cropped image " << i << endl;
        }
    }
    cout << "���ñ������" << endl;
    return 1;
}
