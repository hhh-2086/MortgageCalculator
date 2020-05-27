#include "widget.h"
#include "ui_widget.h"
#include<QComboBox>
#include<QDebug>
#include<QPushButton>
#include<math.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{  
    ui->setupUi(this);

    //贷款类别商业贷款，公积金贷款所需信息:

    ui->comboBox_1->addItem("商业贷款");
    ui->comboBox_1->addItem("公积金贷款");
    ui->comboBox_1->addItem("组合型贷款");

    //计算方式
    ui->comboBox_1_2->addItem("根据面积、单位计算");
    ui->comboBox_1_2->addItem("根据贷款总额计算");

    //房屋单价与面积提示信息
    ui->lineEdit_3->setPlaceholderText("请输入房屋面积（平方米）如未填,则以0计算");
    ui->lineEdit_2->setPlaceholderText("请输入房屋单价（元/平米）如未填,则以0计算");

    //按揭成数
    QStringList a = {"2 成","2.5成","3 成","3.5成","4 成","4.5成","5 成","5.5成","6 成","6.5成","7 成","7.5成","8 成"};
    ui->comboBox_1_5->addItems(a);

    //按揭年数
    QStringList b = {"1年(12期)","2年(24期)","3年(36期)","4年(48期)","5年(60期)", "6年(72期)", "7年(84期)","8年(96期)","9年(108期)",
                     "10年(120期)","11年(132期)","12年(144期)","13年(156期)","14年(168期)","15年(180期)","16年(192期)","17年(204期)",
                     "18年(216期)","19年(228期)","20年(240期)","21年(252期)","22年(264期)","23年(276期)","24年(288期)","25年(300期)",};
    ui->comboBox_1_7->addItems(b);

    //贷款利率
    QStringList c = {"20年3月20日贷款市场报价利率（LPR）","19年9月20日贷款市场报价利率（LPR）","15年10月24日利率上限（1.1倍）","15年10月24日利率上限（1.05倍）",
                     "15年10月24日利率下限（85折）", "15年10月24日利率下限（7折）", "15年10月24日基准利率", "15年8月26日利率上限(1.1倍）", "15年8月26日利率下限（85折）",
                     "15年8月26日利率下限（7折）","15年8月26日基准利率","15年6月28日利率上限(1.1倍）","15年6月28日利率下限（85折）","15年6月28日利率下限（7折）",
                     "15年6月11日基准利率","15年5月11日利率上限(1.1倍）", "15年5月11日利率下限（85折）",  "15年5月11日利率下限（7折）",  "15年5月1日基准利率",
                     "15年3月1日利率上限(1.1倍）","15年3月1日利率下限（85折）","15年3月1日利率下限（7折）","15年3月1日基准利率","14年11月22日利率上限(1.1倍）",
                     "14年11月22日利率下限（85折）","14年11月22日利率下限（7折）","14年11月22日基准利率","12年7月6日利率上限(1.1倍）","12年7月6日利率下限（85折）",
                     "12年7月6日利率下限（7折）","12年7月6日基准利率","12年6月8日利率上限(1.1倍）","12年6月8日利率下限（85折）","12年6月8日利率下限（7折）",
                     "12年6月8日基准利率"
                     };
    ui->comboBox_1_6->addItems(c);
    ui->lineEdit->setText(QString::number(4.75,'f',2));//首界面关于利率默认值

    //贷款总额提示信息
    ui->lineEdit_8->setPlaceholderText("请输入贷款总额（万）如未填,则以0计算");


    //以下为组合型贷款页面所需信息:
    //商业贷款额提示信息
    ui->lineEdit_4->setPlaceholderText("请输入商业贷款额（万）如未填,则以0计算");
    //商业利率
    ui->comboBox2_2->addItems(c);

    //公积金输入提示信息
    ui->lineEdit_6->setPlaceholderText("请输入公积金贷款额(万)如未填,则以0计算");
    //公积金利率
    ui->comboBox_2->addItems(c);

    //按揭年数
    ui->comboBox_3->addItems(b);

    //借鉴的利率，用户可以自行更改
    double rate[] = {4.75,4.85,5.39,5.15,4.17,3.43,4.9, 5.67, 4.38, 3.61,5.15,5.94,4.59,
                  3.78,5.4,6.22,4.8,3.96,5.65,6.49,5.01,4.13,5.9,6.7,5.2,4.3,6.15,7.21,5.57,
                  4.59,6.55, 7.48, 5.78, 4.76, 6.8};

    double rate2[] = {3.25,3.25,3.57,3.41,2.76,2.28,3.25,3.57,2.76,2.28,3.25,3.85,2.98,
                      2.45,3.5,4.13,3.19,2.63,3.75,4.4,3.4,2.8,4,4.25,4.25,4.25,4.25,
                      4.5,4.5,4.5,4.5,4.7,4.7,4.7,4.7};

    //实现三种基金页面转换：
    //变化页面时，需要注意某些默认值
    //切换到其他界面时，切换后做做清空处理
    ui->stackedWidget->setCurrentIndex(0);
    ui->radioButton_2->setChecked(true);
    void(QComboBox:: *p)(int) = &QComboBox::currentIndexChanged;

    connect(ui->comboBox_1,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](){ui->clearButton->clicked(true);});
    connect(ui->comboBox_1,p,[=](){
        QString data = ui->comboBox_1->currentText();
        if(data=="组合型贷款")
        {
        ui->lineEdit_5->setText(QString::number(4.75));
        ui->lineEdit_7->setText(QString::number(3.25));
        ui->stackedWidget->setCurrentIndex(1);
        }   
        else if(data == "商业贷款")
        {
        ui->lineEdit->setText(QString::number(4.75));
        ui->stackedWidget->setCurrentIndex(0);
        }
        else
        {
         ui->lineEdit->setText(QString::number(3.25));
         ui->stackedWidget->setCurrentIndex(0);
        }
        });


    //关于计算方式的页面转换
    connect(ui->comboBox_1_2,p,[=](){
        int data2 = ui->comboBox_1_2->currentIndex();
        if(data2==0)
        {ui->stackedWidget_1_2->setCurrentIndex(0);
         ui->textBrowser->clear();
        }
        else
        {ui->stackedWidget_1_2->setCurrentIndex(1);
         ui->textBrowser->clear();
        }
    });


    //利率值在页面上的的显示

    //前两种贷款:
    connect(ui->comboBox_1_6,p,[=](){
        int i = ui->comboBox_1->currentIndex();
        int j = ui->comboBox_1_6->currentIndex();
        if(i==0)ui->lineEdit->setText(QString::number(rate[j],'f',2));
        else ui->lineEdit->setText(QString::number(rate2[j],'f',2));
    });

    //组合型贷款
    connect(ui->comboBox2_2,p,[=](){
      int j = ui->comboBox2_2->currentIndex();
      ui->lineEdit_5->setText(QString::number(rate[j],'f',2));
    });
    connect(ui->comboBox_2,p,[=](){
        int j = ui->comboBox_2->currentIndex();
        ui->lineEdit_7->setText(QString::number(rate2[j],'f',2));
    });


    //对用“清空重填”按钮的作用;

    void (QAbstractButton:: *p2)(bool) = &QAbstractButton::clicked;

   connect(ui->clearButton,p2,[=](){
    ui->lineEdit_3->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_8->clear();
    ui->comboBox_1_2->setCurrentIndex(0);
    ui->comboBox_1_5->setCurrentIndex(0);
    ui->comboBox_1_6->setCurrentIndex(0);
    ui->comboBox_1_7->setCurrentIndex(0);
    ui->radioButton_2->setChecked(true);
    ui->lineEdit_4->clear();
    ui->comboBox2_2->setCurrentIndex(0);
    ui->lineEdit_6->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->radioButton_4->setChecked(true);
    ui->textBrowser->clear();
    });


    //关于输入信息，需要限制字数,以及限制输入的符号样式：
    ui->lineEdit_2->setMaxLength(6);
    ui->lineEdit_2->setValidator(new QDoubleValidator(0,9999,2,this));
    ui->lineEdit_3->setMaxLength(4);
    ui->lineEdit_3->setValidator(new QDoubleValidator(0,999999,2,this));
    ui->lineEdit_8->setMaxLength(10);
    ui->lineEdit_8->setValidator(new QDoubleValidator(0,9999999999,2,this));
    ui->lineEdit_4->setMaxLength(6);
    ui->lineEdit_4->setValidator(new QDoubleValidator(0,999999,2,this));
    ui->lineEdit_6->setMaxLength(6);
    ui->lineEdit_6->setValidator(new QDoubleValidator(0,999999,2,this));

    //信息完整后，开始计算
    connect(ui->startButton,p2,[=](){
        ui->textBrowser->clear();//清空以前的内容

        if(ui->stackedWidget->currentIndex()==0)//商业贷款或公积金贷款
        {
            //贷款总额,单位是元
            double loans = 0;
            int flag = 1;
            if((ui->lineEdit->text()=="")||ui->lineEdit_2->text()==""||ui->lineEdit_3->text()=="")flag =0;

            if(ui->comboBox_1_2->currentIndex()==0&&flag)//根据面积、单价计算
            {
                //房屋面积
                double area = (ui->lineEdit_3->text()).toDouble();
                //房屋单价
                double price = (ui->lineEdit_2->text()).toDouble();
                //按揭成数，即贷款占房款的总额度
                double radio = ((ui->comboBox_1_5->currentIndex())*0.5+2)*0.1;

                loans = (area*price) *radio;
                //首付:
                double initial = area*price - loans;
                //先显示在结果中
                ui->textBrowser->append("首付:\n"+QString::number(initial,'f',2)+"  元");//规定 以‘f’显示，就不会出现1e+10这种情况

            }

            else
            //根据贷款总额计算
                loans =( (ui->lineEdit_8->text()).toDouble() )*10000;

            //贷款总额:
            ui->textBrowser->append("贷款总额:\n"+QString::number(loans,'f',2)+"  元");



            //还款月数：
            int month = (ui->comboBox_1_7->currentIndex()+1)*12;

            //利率：
            double rate_mon = ( (ui->lineEdit->text()).toDouble())*0.01/12;//此处不用区别商业贷款和公积金贷款

            //区分等额本息和等额本金:

            //如果是等额本息：
            if(ui->radioButton_1->isChecked())
            {//每月还款金额:
            double extra = (loans *rate_mon*pow(1+rate_mon,month))/(pow(1+rate_mon,month) -1);

            ui->textBrowser->append("每月月供:\n"+QString::number(extra,'f',2)+"  元");
            double all = extra*month;
            double allExtra = all-loans;
            //显示支付利息和还款总额
            ui->textBrowser->append("支付利息:\n"+QString::number(allExtra,'f',2)+"  元");
            ui->textBrowser->append("还款总额:\n"+QString::number(all,'f',2)+"  元");

            }

            else//等额本金
            {//首月月供
             double extra = (loans/month)+(loans*rate_mon);
             ui->textBrowser->append("首月月供:\n"+QString::number(extra,'f',2)+"  元");

             //逐月递减 = 每月固定归还的本金*月利率
             double differ = (loans/month)*rate_mon;
             ui->textBrowser->append("每月递减:\n"+QString::number(differ,'f',2)+" 元");

             //等差数列计算还款总额:
             double all = month*extra-month*(month-1)*differ/2;
             double allExtra = all-loans;
             ui->textBrowser->append("支付利息:\n"+QString::number(allExtra,'f',2));
             ui->textBrowser->append("还款总额:\n"+QString::number(all,'f',2));
            }

            ui->textBrowser->append("还款月数:\n"+QString::number(month)+"  月");
        }



        else//组合型贷款
        {//对应相关信息
           //商业贷款额
         double loans1 = ((ui->lineEdit_4->text()).toDouble())*10000;
         //商业利率
         double rate1_month =  ( (ui->lineEdit_5->text()).toDouble())*0.01/12;
         //公积金贷款额
         double loans2 = ((ui->lineEdit_6->text()).toDouble())*10000;
         //公积金利率
         double rate2_month = ( (ui->lineEdit_7->text()).toDouble())*0.01/12;
         //按揭年数
        int month = (ui->comboBox_3->currentIndex()+1)*12;

        //显示贷款总额:
        ui->textBrowser->append("贷款总额:\n"+QString::number(loans1+loans2,'f',2));

        //等额本息：
        if(ui->radioButton_4->isChecked())
        {//每月还款金额：
          double extra = (loans1*rate1_month*pow(1+rate1_month,month))/(pow(1+rate1_month,month)-1)
                        +(loans2*rate2_month*pow(1+rate2_month,month))/(pow(1+rate2_month,month)-1);
          ui->textBrowser->append("每月月供:\n"+QString::number(extra,'f',2)+"  元");

          double all = extra*month;
          double allExtra = all-loans1-loans2;
          //显示支付利息和还款总额：
          ui->textBrowser->append("支付利息:\n"+QString::number(allExtra,'f',2)+"  元");
          ui->textBrowser->append("还款总额:\n"+QString::number(all,'f',2)+"  元");

        }


        //等额本金
        else
        {//首月月供
         double extra = (loans1/month)+(loans1*rate1_month)
                      + (loans2/month)+(loans2*rate2_month);
         ui->textBrowser->append("首月月供:\n"+QString::number(extra,'f',2)+"  元");
         //逐月递减：
         double differ = (loans1/month)*rate1_month
                       + (loans2/month)*rate2_month;
         ui->textBrowser->append("每月递减:\n"+QString::number(differ,'f',2)+"  元");

         //还款总额和支付利息：
         double all = month*extra-(month-1)*month*differ/2;
         double allExtra = all-loans1-loans2;
         ui->textBrowser->append("支付利息:\n"+QString::number(allExtra,'f',2)+"  元");
         ui->textBrowser->append("还款总额:\n"+QString::number(all,'f',2)+"  元");

        }

        //最后显示还款月数
        ui->textBrowser->append("还款月数:\n"+QString::number(month)+"  月");

        }

 });

}
Widget::~Widget()
{
    delete ui;
}

