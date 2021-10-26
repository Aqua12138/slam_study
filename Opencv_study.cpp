//
// Created by zhx on 2021/10/26.
//

#include "Opencv_study.h"
Opencv_study::Opencv_study() {
////////////////////读取图像//////////////////////////

    //读取指定路径下的图像
    Mat image;
    image = imread ("/home/zhx/下载/sea.jpg");
    //获取图片的一些信息
    cout<<"图像宽度为:"<<image.cols<<",高为"<<image.rows<<"图像的通道数为:"<<image.channels()<<endl;
    //显示图像
    imshow("input",image);
    //暂停程序，登台一个按键进行输出
    waitKey(0);
    //调用窗口
    destroyAllWindows();
    //判断 image的类型
    if (image.type()!=CV_8UC1 && image.type() != CV_8UC3)
    {
        //图像类型不符合要求
        cout<<"请输入一张彩色或者灰度图"<<endl;
    }


/////////////////遍历图像/////////////////////

    //遍历图像，请注意以下的遍历方式亦可用于随机访问
    //使用std:;chromo 来给算法计时
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();//获得现在的时间
    for (size_t y=0;y<image.rows;y++)
    {
        unsigned char* row_ptr = image.ptr<unsigned char>(y);//row_ptr是y行的头指针
        for(size_t x=0;x<image.cols;x++)
        {
            //访问位于x,y处像素
            //用cv::Mat::ptr 获取图像的指针
            //unsigned char* row_ptr = image.ptr<unsigned char>(y);//row_ptr是y行的头指针
            unsigned char* data_ptr = &row_ptr[x*image.channels()];//data_ptr指向待访问的像素数据
            //输出该像素的每个通道，如果是灰度图就只有一个通道
            for (int c = 0;c!=image.channels(); c++) {
                unsigned char data = data_ptr[c];//data为 I（x,y）第c个通道的值
            }
        }
    }
    chrono::steady_clock::time_point  t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
    cout<<"遍历图像用时:"<<time_used.count()<<endl;


////////////拷贝/////////////////
}
