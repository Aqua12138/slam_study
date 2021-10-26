//
// Created by zhx on 2021/10/26.
//

#include "Sophus_study.h"
Sophus_basic_study::Sophus_basic_study() {
    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d(0, 0, 1)).toRotationMatrix();
    Eigen::Vector3d v(0, 0, M_PI / 2);
    Eigen::Quaterniond q(R);
    Sophus::SO3<double> SO3_R(R);//可以直接从旋转矩阵进行构造
    //Sophus::SO3<double> SO3_v();//也可以通过旋转向量进行构造，t has some mistakes
    Sophus::SO3<double> SO3_q(q);//也可以通过四元数进行构造
    cout << "SO(3) from matrix:\n" << SO3_R.matrix() << endl;//输出李群对应的矩阵
    cout << "SO(3) from orientation:\n" << SO3_q.matrix() << endl;//输出李群对应的矩阵

    //使用对数映射获得它的李代数
    Eigen::Vector3d so3 = SO3_R.log();
    cout << "so3 = " << so3.transpose() << endl;

    //hat为向量到反对称矩阵
    Eigen::Matrix3d so3_hat = Sophus::SO3<double>::hat(so3);
    cout << "so3 hat=" << so3_hat << endl;
    //相对的，vee为反对称到向量
    Eigen::Vector3d v_vee = Sophus::SO3<double>::vee(so3_hat);
    cout << "s03 hat vee=" << v_vee.transpose() << endl;

    //增加扰动模型的更新
    Eigen::Vector3d update_so3(1e-4, 0, 0);//假设更新量有这么多
    Sophus::SO3d SO3_update = Sophus::SO3d::exp(update_so3) * SO3_R;//左乘更新
    cout << "SO3_updated = \n" << SO3_update.matrix() << endl;

/*******************************/
    //SE（3）操作
    Eigen::Vector3d t(1, 0, 0); //沿着x轴平移1
    Sophus::SE3<double> SE3_Rt(R, t);//从R，t构造SE（3）
    Sophus::SE3<double> SE3_qt(q, t);//从q，t构造SE（3）
    cout << "SE(3) from matrix:\n" << SE3_Rt.matrix() << endl;//输出李群对应的矩阵
    cout << "SE(3) from orientation:\n" << SE3_qt.matrix() << endl;//输出李群对应的矩阵

    //李代数se（3）是一个6维向量,使用typedef为类起别名
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log();//获取李代数
    cout << "se3 =" << se3.transpose() << endl;//三维是位置，后三维是角度
    //hat和vee操作
    Eigen::Matrix4d se3_hat = Sophus::SE3d::hat(se3);
    Vector6d se3_vee = Sophus::SE3d::vee(se3_hat);
    cout << "se3_hat = \n" << se3_hat << endl;
    cout << "se3_hat = \n" << se3_vee.transpose() << endl;

    //upate
    Vector6d updated_se3;//更新量
    updated_se3.setZero();
    updated_se3(0, 0) = 1e-4;
    Sophus::SE3d SE3_updated = Sophus::SE3d::exp(updated_se3) * SE3_Rt;
    cout << "SE3 updated = \n" << endl << SE3_updated.matrix() << endl;
}