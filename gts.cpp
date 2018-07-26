#include "gts.h"


GTS::GTS(QObject *parent) : QObject(parent)
{
    this->moveToThread(new QThread());

    connect(this->thread(),&QThread::started,this,&GTS::process_start);

    this->thread()->start();
}

GTS::~GTS()
{
    this->thread()->quit();
}

void GTS::setIp(QString ip)
{
    ip_addr = ip;
}

void GTS::setN9000(N9000A *get_N9000)
{
    N9000 = get_N9000;
}

void GTS::process_start()
{
    m_pUdpSocket = new QUdpSocket();

    listProverka.clear();
    for(int i=0;i < 15;i++)
    {
        listProverka.append(true);
    }

}

void GTS::updateProverkiListCheck(QList<bool> list)
{
        listProverka.clear();
        for(int i=0 ; i < list.count();i++)
        {
            listProverka.append(list.value(i));
        }

}




void GTS::write(int status_izl, int att, int freq_prd, int uhf_prd,int dopler_prd, int freq_prm, int uhf_prm, int dopler_prm, int freq_dds, int ampl_i, int ampl_q ,int ph_i ,int ph_q, int offset_i, int offset_q)
{
    QByteArray arrBlock;
    arrBlock.clear();

    QString str;
    str.clear();

    if (ampl_i < 0) ampl_i = ~(-ampl_i) + 1;
    if (ampl_q < 0) ampl_q = ~(-ampl_q) + 1;

    if (offset_i < 0) offset_i = ~(-offset_i) + 1;
    if (offset_q < 0) offset_q = ~(-offset_q) + 1;


    /// status_izl - 1
    /// att - 0
    /// freq_prd - floor(x-950)*100) , где x - желаемая частота шагать по 10 МГЦ
    /// uhf_prd - 0
    /// dopler_prd - 0
    /// freq_prm - floor(x-950)*100) , где x - желаемая частота шагать по 10 МГЦ
    /// uhf_prm - 0
    /// dopler_prm - 0
    ///

    str = "write " + QString::number(status_izl) + " " + QString::number(att) + " " + QString::number(freq_prd) + " " +
            QString::number(uhf_prd) + " " + QString::number(dopler_prd) + " " + QString::number(freq_prm) + " "  + QString::number(uhf_prm)
            + " " + QString::number(dopler_prm) + " ";


    ///freq_dds - Частота (Синтезатлора IQ) (0)
    /// ampl_i - Амплитуда I  (4095*8)
    /// ampl_q - Амплитуда Q  (4095*8)
    /// ph_i - 0
    /// ph_q - 0
    /// offset_i -0
    /// offset_q - 0
    ///
    str += QString::number(freq_dds) + " " + QString::number(ampl_i*8) + " " + QString::number(ampl_q*8) + " " +
            QString::number(ph_i) + " " + QString::number(ph_q) + " " + QString::number(offset_i) + " " + QString::number(offset_q) + " end_datafull ";


    arrBlock.append(str);

    m_pUdpSocket->writeDatagram(arrBlock, QHostAddress(ip_addr), 5548);
    QCoreApplication::processEvents();

}

void GTS::Work()
{
    GnFREQuencyStart = 950;
    GnFREQuencyEnd = 2150;
    GnFREQuencyStep = 10;
    GnPower    = 0;


    if(listProverka.value(0) == true)
    {
        emit next(0);
        emit nextList(0);
        emit nextList(1);
        proverka_1();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }


    if(listProverka.value(1) == true)
    {
        emit next(1);
        emit nextList(2);
        proverka_2();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(2) == true)
    {
        emit next(2);
        emit nextList(3);
        proverka_3();

        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(3) == true)
    {
        emit next(3);
        emit nextList(4);
        proverka_4();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }


    if(listProverka.value(4) == true)
    {
        emit next(4);
        emit nextList(5);
        proverka_5();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(5) == true)
    {
        emit next(5);
        emit nextList(6);
        proverka_6();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(6) == true)
    {
        emit next(6);
        emit nextList(7);
        emit nextList(8);
        proverka_7();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(7) == true)
    {
        emit next(7);
        emit nextList(9);
        proverka_8();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(8) == true)
    {
        emit next(8);
        emit nextList(10);
        emit nextList(11);
        proverka_9();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(9) == true)
    {
        emit next(9);
        emit nextList(12);
        proverka_10();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(10) == true)
    {
        emit next(10);
        emit nextList(13);
        proverka_11();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
     }

    if(listProverka.value(11) == true)
    {
        emit next(11);
        emit nextList(14);
        proverka_12();
        viPrintf(N9000->vi, ViString("SYST:PRESet"));
    }

    if(listProverka.value(12) == true)
    {
        emit next(12);
        emit nextList(15);
        proverka_13();
    }

    if(listProverka.value(13) == true)
    {
        emit nextList(16);
        proverka_14();
    }

    if(listProverka.value(14) == true)
    {
        emit nextList(17);
        proverka_15();
    }


    emit endProverk();


}

void GTS::proverka_1()
{
    log("=================\n");
    log("Старт 1 проверка\n");

    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep = 10 ; //(МГЦ)

    GnFREQuencyStep_kHz = 10; // Кгц

    // Присвоили значения условий из таблицы
    GnFREQuencyStart = ListYSL_Nominal.value(0).split(" ").first().toInt();
    GnFREQuencyEnd = ListYSL_Nominal.value(0).split(" ").value(1).toInt();

    //(МГЦ)
    int end = GnFREQuencyStart;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;


    viPrintf(N9000->vi,ViString("BWidth:RES 100 kHz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 100 kHz\r\n")); // Video


    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    double freq = 0;
    double NeravnACHX =0;

    // МГЦ
    while(GnFREQuencyEnd >= end)
    {


        // МГЦ
        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd*1000 << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        //Задает полосу просмотра для отображения сигнала на анализаторе....
        viPrintf(N9000->vi, ViString("FREQuency:STARt %d MHz\r\n"),(end-GnFREQuencyStep)); //*1000
        N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

        viPrintf(N9000->vi, ViString("FREQuency:STOP %d MHz\r\n"),(end+GnFREQuencyStep)); //*1000
        N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        Sleep(200);


        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
        log("Захватить максимум.\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n"); //MHz

    //    Sleep(100);
    //    write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
        log("Захватить максимум.\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n"); //MHz

     //   Sleep(100);
      //  write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
        log("Захватить максимум.\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n"); //MHz

      //  Sleep(100);

        //МГЦ
        freq = dResultX/pow(10,6);



        x.append(freq);


        emit imgUpdate();

        if(dResultY >= ListYSL_prim.value(0).split(" ").first().toDouble())
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            emit imgUpdate();
        }



        auto min1 = std::min_element(y.begin(),y.end());
        auto max1 = std::max_element(y.begin(),y.end());


        NeravnACHX = (*max1)-(*min1);

        emit addPointGraph(x.last(),y.last(),NeravnACHX);


        // МГЦ
        end+=GnFREQuencyStep;


        QDateTime  date = QDateTime::currentDateTime();

        Sleep(200);


        qDebug() << "signal  updateGraph";

    }

    int kol_sr=0;

    for(int i=0; i < x.count();i++)
    {
        if(y.value(i) <= -10)
        {
            kol_sr++;
        }
    }

    if(kol_sr > 0)
    {
        emit goodProverka(0,false);
    }
    else
    {
        emit goodProverka(0,true);
    }

    emit nextList(1);

    qDebug ()  << ListYSL_pred_znach.value(1).toDouble()+ListYSL_prim.value(1).split(" ").first().toDouble();

    if(NeravnACHX <= ListYSL_pred_znach.value(1).toDouble()+ListYSL_prim.value(1).split(" ").first().toDouble())
    {
        emit goodProverka(1,true);
    }
    else
    {
        emit goodProverka(1,false);
    }



    emit imgUpdate();

    qDebug() << "END  Срывов: " <<   kol_sr;
}

void GTS::stepPoint_n9000(int end)
{

    //Задает полосу просмотра для отображения сигнала на анализаторе....
    viPrintf(N9000->vi, ViString("FREQuency:STARt %d kHz\r\n"),(end-GnFREQuencyStep_kHz*1000)); // кГц
    N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

    viPrintf(N9000->vi, ViString("FREQuency:STOP %d kHz\r\n"),(end+GnFREQuencyStep_kHz*1000)); // кГц
    N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");

}

void GTS::getPoint_n9000(double& dResultX,double& dResultY)
{
    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
    log("Захватить максимум.\n");

    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");
}

void GTS::getUpdateYSL(QStringList getListYSL_Nominal, QStringList gretListYSL_pred_otkl, QStringList getListYSL_pred_znach, QStringList getListYSL_prim)
{
     ListYSL_Nominal = getListYSL_Nominal;
     ListYSL_pred_otkl = gretListYSL_pred_otkl;
     ListYSL_pred_znach = getListYSL_pred_znach;
     ListYSL_prim = getListYSL_prim;
}

void GTS::proverka_2()
{
    log("=================\n");
    log("Старт 2 проверки\n");

    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep_kHz = ListYSL_Nominal.value(2).toInt(); // Кгц

    //Кгц
    int end = GnFREQuencyStart*1000;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;


    viPrintf(N9000->vi, ViString("BWidth:RES 100 kHz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 100 kHz\r\n")); // Video


    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    double freq = 0;

    int kol_sr=0;


    // КГЦ
    while(GnFREQuencyEnd*1000 >= end)
    {

        // КГЦ
        freq_prd = (end - GnFREQuencyStart*1000)/10;
        freq_prm = (end - GnFREQuencyStart*1000)/10;


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd*1000 << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        stepPoint_n9000(end);

        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        Sleep(700);


        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);

        //КГЦ
        freq = dResultX/pow(10,3);

        x.append(freq);


        emit imgUpdate();


        if(dResultY >= ListYSL_prim.value(0).split(" ").first().toDouble())
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            kol_sr++;
            emit imgUpdate();
        }

        // auto min1 = std::min_element(y.begin(),y.end());
        //  auto max1 = std::max_element(y.begin(),y.end());


        // double NeravnACHX = (*max1)-(*min1);

        //  emit addPointGraph(x.last(),y.last(),NeravnACHX);


        //Первая точка 950 МГЦ (5 шагов по 10 kHz)
        if( end < (950*1000+(GnFREQuencyStep_kHz*4)))
        {
            end+=GnFREQuencyStep_kHz;
        }
        else
        {


            //Cмена точки 950 МГЦ на 1250 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 950*1000+(GnFREQuencyStep_kHz*4))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate(950,false);
                }
                else
                {
                    emit radioUpdate(950,true);
                }


                kol_sr=0;

                end = 1250*1000-(GnFREQuencyStep_kHz*5);

            }

            //Cмена точки 1250 МГЦ на 1500 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 1250*1000+(GnFREQuencyStep_kHz*5))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate(1250,false);
                }
                else
                {
                    emit radioUpdate(1250,true);
                }
                kol_sr=0;

                end = 1500*1000-(GnFREQuencyStep_kHz*5);
            }

            //Cмена точки 1500 МГЦ на 1750 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 1500*1000+(GnFREQuencyStep_kHz*5))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate(1500,false);
                }
                else
                {
                    emit radioUpdate(1500,true);
                }
                kol_sr=0;

                end = 1750*1000-(GnFREQuencyStep_kHz*5);
            }

            //Cмена точки 1750 МГЦ на 2000 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 1750*1000+(GnFREQuencyStep_kHz*5))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate(1750,false);
                }
                else
                {
                    emit radioUpdate(1750,true);
                }
                kol_sr=0;

                end = 2000*1000-(GnFREQuencyStep_kHz*5);
            }


            //Cмена точки 2000 МГЦ на 2150 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 2000*1000+(GnFREQuencyStep_kHz*5))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate(2000,false);
                }
                else
                {
                    emit radioUpdate(2000,true);
                }
                kol_sr=0;

                end = 2150*1000-(GnFREQuencyStep_kHz*5);
            }


            //точка 1250 МГц (10 шагов по 10 kHz)
            if(end <= end+(GnFREQuencyStep_kHz*10))
            {
                end+=GnFREQuencyStep_kHz;
            }


        }




        QDateTime  date = QDateTime::currentDateTime();


        qDebug() << "signal  updateGraph";



        /////////////////////////////////////////
    }

    if(kol_sr > 0)
    {
        emit radioUpdate(2150,false);
    }
    else
    {
        emit radioUpdate(2150,true);
    }

    kol_sr=0;

    for(int i=0; i < x.count();i++)
    {
        if(y.value(i) <= -10)
        {
            kol_sr++;
        }
    }

    emit imgUpdate();

    if(kol_sr > 0)
    {
        emit goodProverka(2,false);
    }
    else
    {
        emit goodProverka(2,true);
    }

    qDebug() << "END  Срывов: " <<   kol_sr;
    qDebug() << "END";
    qDebug() << "END";
}

void GTS::proverka_3()
{
    log("=================\n");
    log("Старт 3 проверки\n");

    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep_kHz = 10; // Кгц

    //Кгц
    int end = GnFREQuencyStart*1000;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;


    viPrintf(N9000->vi, ViString("BWidth:RES 100 kHz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 100 kHz\r\n")); // Video


    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    double freq = 0;

    int kol_sr=0;

    int kol_good = 0;


    // КГЦ
    while(GnFREQuencyEnd*1000 >= end)
    {

        // КГЦ
        freq_prd = (end - GnFREQuencyStart*1000)/10;
        freq_prm = (end - GnFREQuencyStart*1000)/10;


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd*1000 << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        stepPoint_n9000(end);

        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        Sleep(700);


        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);

        //КГЦ
        freq = dResultX/pow(10,3);

        x.append(freq);


        emit imgUpdate();


        if(dResultY >= ListYSL_prim.value(0).split(" ").first().toDouble())
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            kol_sr++;
            emit imgUpdate();
        }


        //Cмена точки 950 МГЦ на 1550 МГц
        if(end == 950*1000)
        {
            qDebug () << ListYSL_Nominal.value(3).split(" ").first().toDouble() + ListYSL_prim.value(3).split(" ").first().toDouble();

            if(ListYSL_Nominal.value(3).split(" ").first().toDouble() + ListYSL_prim.value(3).split(" ").first().toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(3).split(" ").first().toDouble()-ListYSL_prim.value(3).split(" ").first().toDouble())
            {
                emit radioUpdate_proverka3(950,true);
                kol_good++;
            }
            else
            {
                emit radioUpdate_proverka3(950,false);
            }


            kol_sr=0;

            end = 1550*1000;


        }
        else
        {
            //Cмена точки 1550 МГЦ на 2150 МГц
            if(end == 1550*1000)
            {
                if(ListYSL_Nominal.value(3).split(" ").first().toDouble() + ListYSL_prim.value(3).split(" ").first().toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(3).split(" ").first().toDouble()-ListYSL_prim.value(3).split(" ").first().toDouble())
                {
                    emit radioUpdate_proverka3(1550,true);
                    kol_good++;
                }
                else
                {
                    emit radioUpdate_proverka3(1550,false);

                }


                kol_sr=0;

                end = 2150*1000;


            }
            else
            {
                //Cмена точки 1550 МГЦ на 2150 МГц
                if(end == 2150*1000)
                {
                    if(ListYSL_Nominal.value(3).split(" ").first().toDouble() + ListYSL_prim.value(3).split(" ").first().toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(3).split(" ").first().toDouble()-ListYSL_prim.value(3).split(" ").first().toDouble())
                    {
                        emit radioUpdate_proverka3(2150,true);
                        kol_good++;
                    }
                    else
                    {
                        emit radioUpdate_proverka3(2150,false);

                    }


                    kol_sr=0;

                    end = 2160*1000;


                }
            }


        }





        QDateTime  date = QDateTime::currentDateTime();


        qDebug() << "signal  updateGraph";



        /////////////////////////////////////////
    }


    kol_sr=0;

    for(int i=0; i < x.count();i++)
    {
        if(y.value(i) <= -10)
        {
            kol_sr++;
        }
    }

    emit imgUpdate();

    if(kol_good == 3)
    {
        emit goodProverka(3,true);
    }
    else
    {
        emit goodProverka(3,false);
    }

    qDebug() << "END  Срывов: " <<   kol_sr;
    qDebug() << "END";
    qDebug() << "END";

}

void GTS::proverka_4()
{
    log("=================\n");
    log("Старт 4 проверки\n");

    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep_kHz = 10; // Кгц

    //Кгц
    int end = GnFREQuencyStart*1000;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;


    viPrintf(N9000->vi, ViString("BWidth:RES 100 kHz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 100 kHz\r\n")); // Video


    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    double freq = 0;


    bool kol_good = true;

    double att=60;


    // КГЦ
    while(GnFREQuencyEnd*1000 >= end)
    {

        // КГЦ
        freq_prd = (end - GnFREQuencyStart*1000)/10;
        freq_prm = (end - GnFREQuencyStart*1000)/10;


        write(1,static_cast<int>(floor(att*2)),freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd*1000 << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        stepPoint_n9000(end);

        write(1,static_cast<int>(floor(att*2)),freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        Sleep(700);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,static_cast<int>(floor(att*2)),freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,static_cast<int>(floor(att*2)),freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);

        //КГЦ
        freq = dResultX/pow(10,3);

        emit imgUpdate();


        x.append(freq);
        y.append(dResultY);


        for(double i = 59.5; i > 0; i-=0.5)
        {

            getPoint_n9000(dResultX,dResultY);

            Sleep(100);
            write(1,static_cast<int>(floor(i*2)),freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

            getPoint_n9000(dResultX,dResultY);

            Sleep(100);
            write(1,static_cast<int>(floor(i*2)),freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

            getPoint_n9000(dResultX,dResultY);

            Sleep(100);

            //КГЦ
            freq = dResultX/pow(10,3);

            emit imgUpdate();

            x.append(freq);
            y.append(dResultY);


            //Cмена точки 950 МГЦ на 1550 МГц
            if(end == 950*1000)
            {
                end = 1550*1000;

                qDebug () << abs(abs(static_cast<int>(y.value(y.count())))-abs(static_cast<int>(y.value(y.count()-1))));

                 qDebug () << ListYSL_Nominal.value(4).split(" ").value(1).toDouble() << " " << ListYSL_Nominal.value(4).split(" ").first().toDouble();

                if(ListYSL_Nominal.value(4).split(" ").value(1).toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(4).split(" ").first().toDouble()
                        && abs(abs(static_cast<int>(y.value(y.count())))-abs(static_cast<int>(y.value(y.count()-1)))) == 0.5
                        )
                {
                    emit radioUpdate_proverka4(950,true);
                    kol_good = true;
                }
                else
                {
                    kol_good = false;
                    emit radioUpdate_proverka4(950,false);
                    break;
                }




            }
            else
            {
                //Cмена точки 1550 МГЦ на 2150 МГц
                if(end == 1550*1000)
                {
                    end = 2150*1000;

                    if(ListYSL_Nominal.value(4).split(" ").value(1).toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(4).split(" ").first().toDouble()
                            && abs(abs(static_cast<int>(y.value(y.count())))-abs(static_cast<int>(y.value(y.count()-1)))) == 0.5
                            )
                    {
                        emit radioUpdate_proverka4(1550,true);
                        kol_good = true;
                    }
                    else
                    {
                        kol_good = false;
                        emit radioUpdate_proverka4(1550,false);
                        break;
                    }

                }
                else
                {
                    //Cмена точки 1550 МГЦ на 2150 МГц
                    if(end == 2150*1000)
                    {
                        end = 2160*1000;

                        if(ListYSL_Nominal.value(4).split(" ").value(1).toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(4).split(" ").first().toDouble()  && abs(abs(static_cast<int>(y.value(y.count())))-                  abs(static_cast<int>(y.value(y.count()-1)))) == 0.5)
                        {
                            emit radioUpdate_proverka4(2150,true);
                            kol_good = true;
                        }
                        else
                        {
                            kol_good = false;
                            emit radioUpdate_proverka4(2150,false);
                            break;
                        }
                    }
                }

            }

        }



        QDateTime  date = QDateTime::currentDateTime();


        qDebug() << "signal  updateGraph";



        /////////////////////////////////////////
    }


    emit imgUpdate();

    if(kol_good)
    {
        emit goodProverka(4,true);
    }
    else
    {
        emit goodProverka(4,false);
    }

    qDebug() << "END";
    qDebug() << "END";
}

void GTS::proverka_5()
{
    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep = 10; // Мгц

    //Кгц
    int end = GnFREQuencyStart;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;

    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));


    viPrintf(N9000->vi, ViString("BWidth:RES:AUTO ON\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 1 kHz\r\n")); // Video

    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    bool flagGood = true;

    bool flagGood_2 = true;

    while(GnFREQuencyEnd >= end)
    {


        stepPoint_n9000(end);

        // МГЦ
        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;

        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";



        //Задает полосу просмотра для отображения сигнала на анализаторе....
        viPrintf(N9000->vi, ViString("FREQuency:STARt %d MHz\r\n"),(end-3)); // кГц
        N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

        viPrintf(N9000->vi, ViString("FREQuency:STOP %d MHz\r\n"),(end+3)); // кГц
        N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");


        int point = 0;

        Sleep(200);

        viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));

        Sleep(200);

        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));


        QList<QPointF> list;
        QList<QPointF> list_delta;

        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");


        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



        list.append(QPointF(dResultX/pow(10,6),dResultY));




        do
        {
            viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";



            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


            list.append(QPointF(dResultX/pow(10,6),dResultY));

            Sleep(200);

            if(list.last() == list.value(list.count()-2) && list.count() > 2)
            {
                //point = 0;
                list.removeLast();
                break;
            }



            point++;

        }while(point != 20);


        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

        viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


        list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

        for(int i=0; i < point;i++)
        {
            viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";




            list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

            Sleep(200);


            //проверить числа на ошибку с МГЦ и кГЦ
            if(list.last().x() < (end*1000)-3000 && (end*1000)+3000 > list.last().x() &&  list_delta.last().y() < ListYSL_pred_znach.value(5).split(" ").value(0).toDouble()  && list.count() > 2)
            {
                qDebug () << true;
            }
            else
            {
                flagGood = false;
                qDebug () << flagGood;
            }
        }

        // МГЦ
        end+=GnFREQuencyStep;

        viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
        viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

        qDebug () << list;
        qDebug () << "==============";

        qDebug () << list_delta;
    }



    qDebug () << "Проверка прошла: " << flagGood;

    emit radioUpdate_proverka5(1,flagGood);


    //Задает полосу просмотра для отображения сигнала на анализаторе....
    viPrintf(N9000->vi, ViString("FREQuency:STARt %d MHz\r\n"),GnFREQuencyStart-50); // кГц
    N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

    viPrintf(N9000->vi, ViString("FREQuency:STOP %d MHz\r\n"),GnFREQuencyEnd+50); // кГц
    N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");


    end = GnFREQuencyStart;

    while(GnFREQuencyEnd >= end)
    {

        // МГЦ
        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;

        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";

        int point = 0;

        Sleep(200);

        viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));

        Sleep(200);

        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));


        QList<QPointF> list;
        QList<QPointF> list_delta;

        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");


        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


        list.append(QPointF(dResultX/pow(10,6),dResultY));


        do
        {
            viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";



            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";




            list.append(QPointF(dResultX/pow(10,6),dResultY));

            Sleep(200);

            if(list.last() == list.value(list.count()-2) && list.count() > 2)
            {
                //point = 0;
                list.removeLast();
                break;
            }



            point++;

        }while(point != 20);


        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

        viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


        list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

        for(int i=0; i < point;i++)
        {
            viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


            list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

            Sleep(200);

            if(list_delta.last().y() != 0.0 && list.count() > 2)
            {

                if(abs(static_cast<int>(list_delta.last().x())) > 3 &&  list_delta.last().y() < ListYSL_pred_znach.value(5).split(" ").value(1).toDouble() && list.count() > 2 )
                {
                    qDebug () << true;
                }
                else
                {
                    qDebug () << "Ошибка (отстройка сильно большая): ";
                    flagGood_2 = false;
                    qDebug () << flagGood_2;
                }

            }
            else
            {
                if(list.last().x() < end+3 && list.last().x() > end-3)
                {

                    if(list.last().y() > ListYSL_pred_znach.value(5).split(" ").value(0).toDouble())
                    {
                        qDebug () << "Нет побочек";
                        qDebug () << true;
                    }
                    else
                    {
                        qDebug () << "Ошибка (маленькая мощность): " <<  list.last().y()  << " > "<<ListYSL_pred_znach.value(5).split(" ").value(0).toDouble() <<" dBm";
                        flagGood_2 = false;
                        qDebug () << flagGood_2;
                    }

                }
                else
                {
                    qDebug () << "Ошибка (не входит в диапазон): " <<  (end-3) << " < " << list.last().x() << " < " << (end+3) ;
                    flagGood_2 = false;
                    qDebug () << flagGood_2;
                }


            }


        }

        // МГЦ
        end+=GnFREQuencyStep;

        viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
        viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

        qDebug () << list;
        qDebug () << "==============";

        qDebug () << list_delta;
    }

    qDebug () << "Проверка прошла часть 1 : " << flagGood;
    qDebug () << "Проверка прошла часть 2 : " << flagGood_2;

    emit radioUpdate_proverka5(2,flagGood);

    emit imgUpdate();

    if(flagGood && flagGood_2)
    {
        emit goodProverka(5,true);
    }
    else
    {
        emit goodProverka(5,false);
    }



    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n")); //POS
    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));
    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT OFF\r\n"));


}

void GTS::proverka_6()
{
    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep = 10; // Мгц

    //Кгц
    int end = GnFREQuencyStart;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;

    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));


    viPrintf(N9000->vi, ViString("BWidth:RES 1 Hz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 1 Hz\r\n")); // Video

    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    viPrintf(N9000->vi, ViString("FREQ:TUNE:IMM \r\n"));

    bool flagGood = true;


    double freq = 0;

    int kol_sr=0;



    while(GnFREQuencyEnd >= end)
    {

        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        //Задает полосу просмотра для отображения сигнала на анализаторе....
        //   viPrintf(N9000->vi, "FREQuency:STARt %d MHz\r\n",end-10); // кГц
        N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

        //    viPrintf(N9000->vi, "FREQuency:STOP %d MHz\r\n",end+10); // кГц
        N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");




        qDebug () << GnFREQuencyEnd << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        //Задает полосу просмотра для отображения сигнала на анализаторе....
        viPrintf(N9000->vi, ViString("FREQ:TUNE:IMM \r\n")); // кГц


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        Sleep(1000);


        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);

        //КГЦ
        freq = dResultX/pow(10,6);

        x.append(freq);


        emit imgUpdate();


        if(dResultY >= -10)
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            kol_sr++;
            emit imgUpdate();
        }


        int point =0;



        //Cмена точки 950 МГЦ на 1550 МГц
        if(end == 950)
        {

            N9000->write_AVER_STAT(true);

            viPrintf(N9000->vi, ViString("FREQ:SPAN 300 Hz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 10 Hz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



            Sleep(5000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            QList<QPointF> list;
            QList<QPointF> list_delta;

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 100 Hz\n"));
            emit imgUpdate();

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 120 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10) < ListYSL_pred_znach.value(6).split(" ").value(0).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6(950,1,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6(950,1,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

            ////////////////////////////////////////////


            viPrintf(N9000->vi, ViString("FREQ:SPAN 3 kHz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 100 Hz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



            Sleep(5000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            list.clear();
            list_delta.clear();

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 1 kHz\n"));
            emit imgUpdate();

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10*2) < ListYSL_pred_znach.value(6).split(" ").value(1).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6(950,2,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6(950,2,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

            ////////////////////////////////////////////


            viPrintf(N9000->vi, ViString("FREQ:SPAN 30 kHz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



            Sleep(5000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            list.clear();
            list_delta.clear();

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 10 kHz\n"));
            emit imgUpdate();

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10*3) < ListYSL_pred_znach.value(6).split(" ").value(2).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6(950,3,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6(950,3,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


            ////////////////////////////////////////////


            viPrintf(N9000->vi, ViString("FREQ:SPAN 300 kHz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



            Sleep(40000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            list.clear();
            list_delta.clear();

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 100 kHz\n"));
            emit imgUpdate();

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10*3) < ListYSL_pred_znach.value(6).split(" ").value(3).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6(950,4,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6(950,4,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


            ////////////////////////////////////////////


            viPrintf(N9000->vi, ViString("FREQ:SPAN 3 MHz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 10 kHz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 1 kHz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));

            emit imgUpdate();

            Sleep(40000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            list.clear();
            list_delta.clear();

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 1 MHz\n"));


            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10*4) < ListYSL_pred_znach.value(6).split(" ").value(4).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6(950,5,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6(950,5,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


            kol_sr=0;

            end = 1550;


        }
        else
        {
            //Cмена точки 1550 МГЦ на 2150 МГц
            if(end == 1550)
            {

                N9000->write_AVER_STAT(true);

                viPrintf(N9000->vi, ViString("FREQ:SPAN 300 Hz\r\n"));

                viPrintf(N9000->vi, ViString("BWidth:RES 10 Hz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(5000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                QList<QPointF> list;
                QList<QPointF> list_delta;

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 100 Hz\n"));
                emit imgUpdate();

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 120 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10) < ListYSL_pred_znach.value(6).split(" ").value(0).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6(1550,1,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6(1550,1,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

                ////////////////////////////////////////////


                viPrintf(N9000->vi, ViString("FREQ:SPAN 3 kHz\r\n")); // RES

                viPrintf(N9000->vi, ViString("BWidth:RES 100 Hz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(5000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                list.clear();
                list_delta.clear();

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 1 kHz\n"));
                emit imgUpdate();

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10*2) < ListYSL_pred_znach.value(6).split(" ").value(1).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6(1550,2,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6(1550,2,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

                ////////////////////////////////////////////


                viPrintf(N9000->vi, ViString("FREQ:SPAN 30 kHz\r\n")); // RES

                viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(5000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                list.clear();
                list_delta.clear();

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 10 kHz\n"));

                emit imgUpdate();
                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10*3) < ListYSL_pred_znach.value(6).split(" ").value(2).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6(1550,3,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6(1550,3,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                ////////////////////////////////////////////


                viPrintf(N9000->vi, ViString("FREQ:SPAN 300 kHz\r\n")); // RES

                viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(40000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                list.clear();
                list_delta.clear();

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 100 kHz\n"));
                emit imgUpdate();

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10*3) < ListYSL_pred_znach.value(6).split(" ").value(3).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6(1550,4,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6(1550,4,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                ////////////////////////////////////////////


                viPrintf(N9000->vi, ViString("FREQ:SPAN 3 MHz\r\n")); // RES

                viPrintf(N9000->vi, ViString("BWidth:RES 10 kHz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 1 kHz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(40000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                list.clear();
                list_delta.clear();

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 1 MHz\n"));
                emit imgUpdate();

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10*4) < ListYSL_pred_znach.value(6).split(" ").value(4).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6(1550,5,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6(1550,5,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));



                kol_sr=0;

                end = 2150;


            }
            else
            {
                //Cмена точки 1550 МГЦ на 2150 МГц
                if(end == 2150)
                {

                    N9000->write_AVER_STAT(true);

                    viPrintf(N9000->vi, ViString("FREQ:SPAN 300 Hz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 10 Hz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                    Sleep(5000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    QList<QPointF> list;
                    QList<QPointF> list_delta;

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 100 Hz\n"));

                    emit imgUpdate();
                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 120 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi,ViString( "CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10) < ListYSL_pred_znach.value(6).split(" ").value(0).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6(2150,1,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6(2150,1,false);
                                flagGood =false;
                            }
                        }
                    }
                    emit imgUpdate();
                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

                    ////////////////////////////////////////////


                    viPrintf(N9000->vi, ViString("FREQ:SPAN 3 kHz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 100 Hz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                    Sleep(5000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    list.clear();
                    list_delta.clear();

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1 kHz\n"));
                    emit imgUpdate();

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10*2) < ListYSL_pred_znach.value(6).split(" ").value(1).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6(2150,2,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6(2150,2,false);
                                flagGood =false;
                            }
                        }
                    }
                    emit imgUpdate();
                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

                    ////////////////////////////////////////////


                    viPrintf(N9000->vi, ViString("FREQ:SPAN 30 kHz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                    Sleep(5000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    list.clear();
                    list_delta.clear();

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 10 kHz\n"));
                    emit imgUpdate();

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10*3) < ListYSL_pred_znach.value(6).split(" ").value(2).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6(2150,3,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6(2150,3,false);
                                flagGood =false;
                            }
                        }
                    }

                    emit imgUpdate();
                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                    ////////////////////////////////////////////


                    viPrintf(N9000->vi, ViString("FREQ:SPAN 300 kHz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                    viPrintf(N9000->vi,ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi,ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                    Sleep(40000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    list.clear();
                    list_delta.clear();

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 100 kHz\n"));

                    emit imgUpdate();

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10*3) < ListYSL_pred_znach.value(6).split(" ").value(3).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6(2150,4,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6(2150,4,false);
                                flagGood =false;
                            }
                        }
                    }

                    emit imgUpdate();

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                    ////////////////////////////////////////////


                    viPrintf(N9000->vi, ViString("FREQ:SPAN 3 MHz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 10 kHz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 1 kHz\r\n")); // Video

                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));


                    Sleep(40000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    list.clear();
                    list_delta.clear();

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1 MHz\n"));


                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"),ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10*4) < ListYSL_pred_znach.value(6).split(" ").value(4).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6(2150,5,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6(2150,5,false);
                                flagGood =false;
                            }
                        }
                    }

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                    kol_sr=0;

                    end = 2160;


                }
            }


        }


        QDateTime  date = QDateTime::currentDateTime();


        qDebug() << "signal  updateGraph";



        /////////////////////////////////////////
    }



    emit imgUpdate();

    if(flagGood)
    {
        emit goodProverka(6,true);
    }
    else
    {
        emit goodProverka(6,false);
    }

    qDebug() << "END  Срывов: " <<   kol_sr;
    qDebug() << "END";
    qDebug() << "END";


    viPrintf(N9000->vi, ViString("SYST:PRESet"));

}

void GTS::proverka_7()
{
    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep = 10; // Мгц


    int end = GnFREQuencyStart+100;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;

    int freq_dds = 10000; // 10 МГц

    int offset_i = 0;
    int offset_q = 0;

    int ph_i = 0;
  //  int ph_q = 0;


    bool flagGood_950_20 = false;
    bool flagGood_950_10 = false;

    bool flagGood_1550_20 = false;
    bool flagGood_1550_10 = false;

    bool flagGood_2150_20 = false;
    bool flagGood_2150_10 = false;

    double freq;

    while(GnFREQuencyEnd >= end)
    {

        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;


        write(1,0,freq_prd,0,0,freq_prm,0,0,freq_dds,ampl_i,ampl_q,0,0,offset_i,offset_q);

        viPrintf(N9000->vi, ViString("FREQ:TUNE:IMM \r\n"));

        viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
        viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));

        viPrintf(N9000->vi, ViString("FREQ:SPAN 50 MHz\r\n"));
        viPrintf(N9000->vi, ViString("BWidth:RES 510 kHz\r\n")); // RES
        viPrintf(N9000->vi, ViString("BWidth:VID 3 kHz\r\n")); // Video

        N9000->write_DISP_WIND_TRAC_Y_RLEV(10);


        Sleep(1000);

        getPoint_n9000(dResultX,dResultY);

        //МГЦ
        freq = dResultX/pow(10,6);

        x.append(freq);


        emit imgUpdate();


        if(dResultY >= -10)
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            emit imgUpdate();
        }


        //Cмена точки 950 МГЦ на 1550 МГц
        if(end == 950+100)
        {

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"),ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            QList<QPointF> list;
            QList<QPointF> list_delta;

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if(static_cast<int>((list.last().x())) == static_cast<int>(list.value(list.count()-2).x()))
                {
                    list.removeLast();
                    break;
                }

            }while(1);



            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            emit imgUpdate();


            for(int i =0 ; i < list.count();i++)
            {

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,6))<<" MHz";


                list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

                QVector<double> list_point;

                if(static_cast<int>(list_delta.value(i).x()) == -20)
                {


                    ph_i = 0; //65535

                    offset_i = 0;
                    offset_q = 0;



                    while(ph_i != 65535)
                    {


                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                       // qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n");


                        list_point.append(dResultY);



                        if( dResultY < ListYSL_pred_znach.value(7).split(" ").value(0).toDouble() && dResultY > -50.0)
                        {
                            qDebug () << "good";
                            flagGood_950_20 = true;
                            break;
                        }


                        ph_i += 10;

                        write(1,0,freq_prd,0,0,freq_prm,0,0,freq_dds,ampl_i,ampl_q,ph_i,0,offset_i,offset_q);

                        Sleep(100);


                    };

                    qDebug () << ph_i;

                    list_point.clear();

                    emit radioUpdate_proverka7(950,1,flagGood_950_20);


                }
                else
                {
                    if(static_cast<int>(list_delta.value(i).x()) == -10)
                    {

                        offset_i = -200;

                        while(offset_i != 200)
                        {


                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                           // qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n");


                            list_point.append(dResultY);



                            if( dResultY < ListYSL_pred_znach.value(8).split(" ").value(0).toDouble())
                            {
                                qDebug () << "good";
                                flagGood_950_10 = true;
                                break;
                            }


                            offset_i += 1;

                            write(1,0,freq_prd,0,0,freq_prm,0,0,freq_dds,ampl_i,ampl_q,ph_i,0,offset_i,offset_q);

                        };

                        qDebug () << ph_i;

                        list_point.clear();
                        emit radioUpdate_proverka7(950,2,flagGood_950_10);
                }


            }
                 viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
            }

            end = 1550;

            ////////////////////////////////////////////
        }
        else
        {
            if( end == 1550)
            {

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"),ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                QList<QPointF> list;
                QList<QPointF> list_delta;

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if(static_cast<int>((list.last().x())) == static_cast<int>(list.value(list.count()-2).x()))
                    {
                        list.removeLast();
                        break;
                    }

                }while(1);



                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                emit imgUpdate();


                for(int i =0 ; i < list.count();i++)
                {

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,6))<<" MHz";


                    list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

                    QVector<double> list_point;

                    if(static_cast<int>(list_delta.value(i).x()) == -20)
                    {


                        ph_i = 0; //65535

                        offset_i = 0;
                        offset_q = 0;



                        while(ph_i != 65535)
                        {


                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                           // qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n");


                            list_point.append(dResultY);



                            if( dResultY < ListYSL_pred_znach.value(7).split(" ").value(0).toDouble() && dResultY > -50.0)
                            {
                                qDebug () << "good";
                                flagGood_1550_20 = true;
                                break;
                            }


                            ph_i += 10;

                            write(1,0,freq_prd,0,0,freq_prm,0,0,freq_dds,ampl_i,ampl_q,ph_i,0,offset_i,offset_q);

                            Sleep(50);


                        };

                        qDebug () << ph_i;

                        list_point.clear();
                        emit radioUpdate_proverka7(1550,1,flagGood_1550_20);


                    }
                    else
                    {
                        if(static_cast<int>(list_delta.value(i).x()) == -10)
                        {

                            offset_i = -200;

                            while(offset_i != 200)
                            {


                                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                               // qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                                log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n");


                                list_point.append(dResultY);



                                if( dResultY < ListYSL_pred_znach.value(8).split(" ").value(0).toDouble())
                                {
                                    qDebug () << "good";
                                    flagGood_1550_10 = true;
                                    break;
                                }


                                offset_i += 1;

                                write(1,0,freq_prd,0,0,freq_prm,0,0,freq_dds,ampl_i,ampl_q,ph_i,0,offset_i,offset_q);

                            };

                            qDebug () << ph_i;

                            list_point.clear();
                            emit radioUpdate_proverka7(1550,2,flagGood_1550_10);
                    }


                }
                     viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                }

                end = 2150;
                ////////////////////////////////////////////
            }
            else {

            if( end == 2150)
            {

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"),ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                QList<QPointF> list;
                QList<QPointF> list_delta;

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if(static_cast<int>((list.last().x())) == static_cast<int>(list.value(list.count()-2).x()))
                    {
                        list.removeLast();
                        break;
                    }

                }while(1);



                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                emit imgUpdate();


                for(int i =0 ; i < list.count();i++)
                {

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,6))<<" MHz";


                    list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

                    QVector<double> list_point;

                    if(static_cast<int>(list_delta.value(i).x()) == -20)
                    {


                        ph_i = 0; //65535

                        offset_i = 0;
                        offset_q = 0;



                        while(ph_i != 65535)
                        {


                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                           // qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n");


                            list_point.append(dResultY);



                            if( dResultY < ListYSL_pred_znach.value(7).split(" ").value(0).toDouble() && dResultY > -50.0)
                            {
                                qDebug () << "good";
                                flagGood_2150_20 = true;
                                break;
                            }


                            ph_i += 10;

                            write(1,0,freq_prd,0,0,freq_prm,0,0,freq_dds,ampl_i,ampl_q,ph_i,0,offset_i,offset_q);

                            Sleep(50);


                        };

                        qDebug () << ph_i;

                        list_point.clear();

                       emit radioUpdate_proverka7(2150,1,flagGood_2150_20);


                    }
                    else
                    {
                        if(static_cast<int>(list_delta.value(i).x()) == -10)
                        {

                            offset_i = -200;

                            while(offset_i != 200)
                            {


                                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                               // qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                                log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n");


                                list_point.append(dResultY);



                                if( dResultY < ListYSL_pred_znach.value(8).split(" ").value(0).toDouble())
                                {
                                    qDebug () << "good";
                                    flagGood_2150_10 = true;
                                    break;
                                }


                                offset_i += 1;

                                write(1,0,freq_prd,0,0,freq_prm,0,0,freq_dds,ampl_i,ampl_q,ph_i,0,offset_i,offset_q);

                            };

                            qDebug () << ph_i;

                            list_point.clear();

                             emit radioUpdate_proverka7(2150,2,flagGood_2150_10);
                    }


                }
                     viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                }
                end = 2160;

                ////////////////////////////////////////////
            }
            }
        }
    }


    if(flagGood_950_10 && flagGood_1550_10  && flagGood_2150_10)
    {
         emit goodProverka(7,true);
    }
    else
    {
         emit goodProverka(7,false);
    }

    if(flagGood_950_20 && flagGood_1550_20 && flagGood_2150_20)
    {
        emit goodProverka(8,true);
    }
    else
    {
        emit goodProverka(8,false);
    }


}

void GTS::proverka_8()
{
      emit goodProverka(9,false);
}

void GTS::proverka_9()
{
    log("=================\n");
    log("Старт 10 проверка\n");

    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep = 10 ; //(МГЦ)

    GnFREQuencyStep_kHz = 10; // Кгц

    // Присвоили значения условий из таблицы
    GnFREQuencyStart = ListYSL_Nominal.value(10).split(" ").first().toInt();
    GnFREQuencyEnd = ListYSL_Nominal.value(10).split(" ").value(1).toInt();


    //(МГЦ)
    int end = GnFREQuencyStart;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;


    viPrintf(N9000->vi,ViString("BWidth:RES 100 kHz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 100 kHz\r\n")); // Video


    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    double freq = 0;
    double NeravnACHX =0;

    // МГЦ
    while(GnFREQuencyEnd >= end)
    {

        // МГЦ
        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd*1000 << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        //Задает полосу просмотра для отображения сигнала на анализаторе....
        viPrintf(N9000->vi, ViString("FREQuency:STARt %d MHz\r\n"),(end-GnFREQuencyStep)); //*1000
        N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

        viPrintf(N9000->vi, ViString("FREQuency:STOP %d MHz\r\n"),(end+GnFREQuencyStep)); //*1000
        N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");



        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
        log("Захватить максимум.\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n"); //MHz


        Sleep(200);


        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
        log("Захватить максимум.\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n"); //MHz


        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
        log("Захватить максимум.\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,6))+" MHz\n"); //MHz


        //МГЦ
        freq = dResultX/pow(10,6);


        x.append(freq);


        emit imgUpdate();


        double ysl = ListYSL_prim.value(10).split(" ").first().toDouble();

        if(dResultY >= ysl)
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            emit imgUpdate();
        }



        auto min1 = std::min_element(y.begin(),y.end());
        auto max1 = std::max_element(y.begin(),y.end());


        NeravnACHX = (*max1)-(*min1);

        emit addPointGraph_GPRM(x.last(),y.last(),NeravnACHX);


        // МГЦ
        end+=GnFREQuencyStep;


        QDateTime  date = QDateTime::currentDateTime();


        Sleep(100);


        qDebug() << "signal  updateGraph";

    }

    int kol_sr=0;

    for(int i=0; i < x.count();i++)
    {
        if(y.value(i) <= -10)
        {
            kol_sr++;
        }
    }

    if(kol_sr > 0)
    {
        emit goodProverka(10,false);
    }
    else
    {
        emit goodProverka(10,true);
    }

    if(NeravnACHX <= ListYSL_pred_znach.value(11).toDouble()+ListYSL_prim.value(11).split(" ").first().toDouble())
    {
        emit goodProverka(11,true);
    }
    else
    {
        emit goodProverka(11,false);
    }


    emit imgUpdate();

    qDebug() << "END  Срывов: " <<   kol_sr;
}

void GTS::proverka_10()
{
    log("=================\n");
    log("Старт 12 проверки\n");

    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep_kHz = ListYSL_Nominal.value(12).toInt(); // Кгц

    //Кгц
    int end = GnFREQuencyStart*1000;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;


    viPrintf(N9000->vi, ViString("BWidth:RES 100 kHz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 100 kHz\r\n")); // Video


    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    double freq = 0;

    int kol_sr=0;


    // КГЦ
    while(GnFREQuencyEnd*1000 >= end)
    {

        // КГЦ
        freq_prd = (end - GnFREQuencyStart*1000)/10;
        freq_prm = (end - GnFREQuencyStart*1000)/10;


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd*1000 << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        stepPoint_n9000(end);

        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        Sleep(700);


        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);

        //КГЦ
        freq = dResultX/pow(10,3);

        x.append(freq);


        emit imgUpdate();


        if(dResultY >= -10)
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            kol_sr++;
            emit imgUpdate();
        }


        //Первая точка 950 МГЦ (5 шагов по 10 kHz)
        if( end < (950*1000+(GnFREQuencyStep_kHz*4)))
        {
            end+=GnFREQuencyStep_kHz;
        }
        else
        {


            //Cмена точки 950 МГЦ на 1250 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 950*1000+(GnFREQuencyStep_kHz*4))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate_GPRM(950,false);
                }
                else
                {
                    emit radioUpdate_GPRM(950,true);
                }


                kol_sr=0;

                end = 1250*1000-(GnFREQuencyStep_kHz*5);

            }

            //Cмена точки 1250 МГЦ на 1500 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 1250*1000+(GnFREQuencyStep_kHz*5))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate_GPRM(1250,false);
                }
                else
                {
                    emit radioUpdate_GPRM(1250,true);
                }
                kol_sr=0;

                end = 1500*1000-(GnFREQuencyStep_kHz*5);
            }

            //Cмена точки 1500 МГЦ на 1750 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 1500*1000+(GnFREQuencyStep_kHz*5))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate_GPRM(1500,false);
                }
                else
                {
                    emit radioUpdate_GPRM(1500,true);
                }
                kol_sr=0;

                end = 1750*1000-(GnFREQuencyStep_kHz*5);
            }

            //Cмена точки 1750 МГЦ на 2000 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 1750*1000+(GnFREQuencyStep_kHz*5))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate_GPRM(1750,false);
                }
                else
                {
                    emit radioUpdate_GPRM(1750,true);
                }
                kol_sr=0;

                end = 2000*1000-(GnFREQuencyStep_kHz*5);
            }


            //Cмена точки 2000 МГЦ на 2150 МГц ушли нзад на (5 шагов по 10 kHz)
            if(end == 2000*1000+(GnFREQuencyStep_kHz*5))
            {
                if(kol_sr > 0)
                {
                    emit radioUpdate_GPRM(2000,false);
                }
                else
                {
                    emit radioUpdate_GPRM(2000,true);
                }
                kol_sr=0;

                end = 2150*1000-(GnFREQuencyStep_kHz*5);
            }


            //точка 1250 МГц (10 шагов по 10 kHz)
            if(end <= end+(GnFREQuencyStep_kHz*10))
            {
                end+=GnFREQuencyStep_kHz;
            }


        }




        QDateTime  date = QDateTime::currentDateTime();


        qDebug() << "signal  updateGraph";



        /////////////////////////////////////////
    }

    if(kol_sr > 0)
    {
        emit radioUpdate_GPRM(2150,false);
    }
    else
    {
        emit radioUpdate_GPRM(2150,true);
    }

    kol_sr=0;

    for(int i=0; i < x.count();i++)
    {
        if(y.value(i) <= -10)
        {
            kol_sr++;
        }
    }

    emit imgUpdate();

    if(kol_sr > 0)
    {
        emit goodProverka(12,false);
    }
    else
    {
        emit goodProverka(12,true);
    }

    qDebug() << "END  Срывов: " <<   kol_sr;
    qDebug() << "END";
    qDebug() << "END";
}

void GTS::proverka_11()
{
    log("=================\n");
    log("Старт 3 проверки\n");

    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep_kHz = 10; // Кгц

    //Кгц
    int end = GnFREQuencyStart*1000;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;


    viPrintf(N9000->vi, ViString("BWidth:RES 100 kHz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 100 kHz\r\n")); // Video


    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    double freq = 0;

    int kol_sr=0;

    int kol_good = 0;


    // КГЦ
    while(GnFREQuencyEnd*1000 >= end)
    {

        // КГЦ
        freq_prd = (end - GnFREQuencyStart*1000)/10;
        freq_prm = (end - GnFREQuencyStart*1000)/10;


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd*1000 << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        stepPoint_n9000(end);

        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        Sleep(700);


        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);

        //КГЦ
        freq = dResultX/pow(10,3);

        x.append(freq);


        emit imgUpdate();


        if(dResultY >= -10)
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            kol_sr++;
            emit imgUpdate();
        }



        //Cмена точки 950 МГЦ на 1550 МГц
        if(end == 950*1000)
        {
            if(ListYSL_Nominal.value(13).split(" ").first().toDouble() + ListYSL_prim.value(13).split(" ").first().toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(13).split(" ").first().toDouble()-ListYSL_prim.value(13).split(" ").first().toDouble())
            {
                emit radioUpdate_proverka3_GPRM(950,true);
                kol_good++;
            }
            else
            {
                emit radioUpdate_proverka3_GPRM(950,false);
            }


            kol_sr=0;

            end = 1550*1000;


        }
        else
        {
            //Cмена точки 1550 МГЦ на 2150 МГц
            if(end == 1550*1000)
            {
                if(ListYSL_Nominal.value(13).split(" ").first().toDouble() + ListYSL_prim.value(13).split(" ").first().toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(13).split(" ").first().toDouble()-ListYSL_prim.value(13).split(" ").first().toDouble())
                {
                    emit radioUpdate_proverka3_GPRM(1550,true);
                    kol_good++;
                }
                else
                {
                    emit radioUpdate_proverka3_GPRM(1550,false);

                }


                kol_sr=0;

                end = 2150*1000;


            }
            else
            {
                //Cмена точки 1550 МГЦ на 2150 МГц
                if(end == 2150*1000)
                {
                    if(ListYSL_Nominal.value(13).split(" ").first().toDouble() + ListYSL_prim.value(13).split(" ").first().toDouble() <= y.last()  && y.last() <= ListYSL_Nominal.value(13).split(" ").first().toDouble()-ListYSL_prim.value(13).split(" ").first().toDouble())
                    {
                        emit radioUpdate_proverka3_GPRM(2150,true);
                        kol_good++;
                    }
                    else
                    {
                        emit radioUpdate_proverka3_GPRM(2150,false);

                    }


                    kol_sr=0;

                    end = 2160*1000;


                }
            }


        }





        QDateTime  date = QDateTime::currentDateTime();


        qDebug() << "signal  updateGraph";



        /////////////////////////////////////////
    }


    kol_sr=0;

    for(int i=0; i < x.count();i++)
    {
        if(y.value(i) <= -10)
        {
            kol_sr++;
        }
    }

    emit imgUpdate();

    if(kol_good == 3)
    {
        emit goodProverka(13,true);
    }
    else
    {
        emit goodProverka(13,false);
    }

    qDebug() << "END  Срывов: " <<   kol_sr;
    qDebug() << "END";
    qDebug() << "END";
}

void GTS::proverka_12()
{
    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep = 10; // Мгц

    //Кгц
    int end = GnFREQuencyStart;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;

    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));


    viPrintf(N9000->vi, ViString("BWidth:RES:AUTO ON\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 1 kHz\r\n")); // Video

    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    bool flagGood = true;

    bool flagGood_2 = true;

    while(GnFREQuencyEnd >= end)
    {


        stepPoint_n9000(end);

        // МГЦ
        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;

        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";



        //Задает полосу просмотра для отображения сигнала на анализаторе....
        viPrintf(N9000->vi, ViString("FREQuency:STARt %d MHz\r\n"),(end-3)); // кГц
        N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

        viPrintf(N9000->vi, ViString("FREQuency:STOP %d MHz\r\n"),(end+3)); // кГц
        N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");


        int point = 0;

        Sleep(200);

        viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));

        Sleep(200);

        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));


        QList<QPointF> list;
        QList<QPointF> list_delta;

        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");


        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



        list.append(QPointF(dResultX/pow(10,6),dResultY));




        do
        {
            viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";



            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";




            list.append(QPointF(dResultX/pow(10,6),dResultY));

            Sleep(200);

            if(list.last() == list.value(list.count()-2) && list.count() > 2)
            {
                //point = 0;
                list.removeLast();
                break;
            }



            point++;

        }while(point != 20);


        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

        viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


        list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

        for(int i=0; i < point;i++)
        {
            viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";




            list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

            Sleep(200);

            //проверить числа на ошибку с МГЦ и кГЦ
            if(list.last().x() < (end*1000)-3000 && (end*1000)+3000 > list.last().x() &&  list_delta.last().y() < list_delta.last().y() < ListYSL_pred_znach.value(14).split(" ").value(0).toDouble()  && list.count() > 2)
            {
                qDebug () << true;
            }
            else
            {

                flagGood = false;
                qDebug () << flagGood;
            }


        }

        // МГЦ
        end+=GnFREQuencyStep;

        viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
        viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

        qDebug () << list;
        qDebug () << "==============";

        qDebug () << list_delta;
    }



    qDebug () << "Проверка прошла: " << flagGood;

    emit radioUpdate_proverka5(1,flagGood);


    //Задает полосу просмотра для отображения сигнала на анализаторе....
    viPrintf(N9000->vi, ViString("FREQuency:STARt %d MHz\r\n"),GnFREQuencyStart-50); // кГц
    N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

    viPrintf(N9000->vi, ViString("FREQuency:STOP %d MHz\r\n"),GnFREQuencyEnd+50); // кГц
    N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");


    end = GnFREQuencyStart;


    while(GnFREQuencyEnd >= end)
    {

        // МГЦ
        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;

        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        qDebug () << GnFREQuencyEnd << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";

        int point = 0;

        Sleep(200);

        viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));

        Sleep(200);

        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));


        QList<QPointF> list;
        QList<QPointF> list_delta;

        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");


        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



        list.append(QPointF(dResultX/pow(10,6),dResultY));




        do
        {
            viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";



            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";




            list.append(QPointF(dResultX/pow(10,6),dResultY));

            Sleep(200);

            if(list.last() == list.value(list.count()-2) && list.count() > 2)
            {
                //point = 0;
                list.removeLast();
                break;
            }



            point++;

        }while(point != 20);


        viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

        viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


        list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

        for(int i=0; i < point;i++)
        {
            viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


            list_delta.append(QPointF(dResultX/pow(10,6),dResultY));

            Sleep(200);

            if(list_delta.last().y() != 0.0 && list.count() > 2)
            {

                if(abs(static_cast<int>(list_delta.last().x())) > 3 &&  list_delta.last().y() < ListYSL_pred_znach.value(14).split(" ").value(1).toDouble()  && list.count() > 2 )
                {
                    qDebug () << true;
                }
                else
                {
                    qDebug () << "Ошибка (отстройка сильно большая): ";
                    flagGood_2 = false;
                    qDebug () << flagGood_2;
                }

            }
            else
            {
                if(list.last().x() < end+3 && list.last().x() > end-3)
                {

                    if(list.last().y() > ListYSL_pred_znach.value(14).split(" ").value(0).toDouble())
                    {
                        qDebug () << "Нет побочек";
                        qDebug () << true;
                    }
                    else
                    {
                        qDebug () << "Ошибка (маленькая мощность): " <<  list.last().y()  << " > "<<ListYSL_pred_znach.value(14).split(" ").value(0).toDouble() <<" dBm";
                        flagGood_2 = false;
                        qDebug () << flagGood_2;
                    }

                }
                else
                {
                    qDebug () << "Ошибка (не входит в диапазон): " <<  (end-3) << " < " << list.last().x() << " < " << (end+3) ;
                    flagGood_2 = false;
                    qDebug () << flagGood_2;
                }


            }


        }

        // МГЦ
        end+=GnFREQuencyStep;

        viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
        viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

        qDebug () << list;
        qDebug () << "==============";

        qDebug () << list_delta;
    }

    qDebug () << "Проверка прошла часть 1 : " << flagGood;
    qDebug () << "Проверка прошла часть 2 : " << flagGood_2;

    emit radioUpdate_proverka5_GPRM(2,flagGood_2);

    emit imgUpdate();

    if(flagGood && flagGood_2)
    {
        emit goodProverka(14,true);
    }
    else
    {
        emit goodProverka(14,false);
    }



    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n")); //POS
    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));
    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT OFF\r\n"));


}

void GTS::proverka_13()
{
    double dResultY = 0;
    double dResultX = 0;

    x.clear();
    y.clear();

    GnFREQuencyStep = 10; // Мгц

    //Кгц
    int end = GnFREQuencyStart;

    int freq_prd = GnFREQuencyStart;
    int freq_prm = GnFREQuencyStart;

    int ampl_i = 4095;
    int ampl_q = ampl_i;

    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));


    viPrintf(N9000->vi, ViString("BWidth:RES 1 Hz\r\n")); // RES
    viPrintf(N9000->vi, ViString("BWidth:VID 1 Hz\r\n")); // Video

    N9000->write_DISP_WIND_TRAC_Y_RLEV(10);

    viPrintf(N9000->vi, ViString("FREQ:TUNE:IMM \r\n"));

    bool flagGood = true;


    double freq = 0;

    int kol_sr=0;



    while(GnFREQuencyEnd >= end)
    {

        freq_prd = (end-950)*100;
        freq_prm = (end-950)*100;


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        //Задает полосу просмотра для отображения сигнала на анализаторе....
        //   viPrintf(N9000->vi, "FREQuency:STARt %d MHz\r\n",end-10); // кГц
        N9000->Log("Установить начальную частоту просмотра "+QString::number(end-GnFREQuencyStep)+" MHz\n");

        //    viPrintf(N9000->vi, "FREQuency:STOP %d MHz\r\n",end+10); // кГц
        N9000->Log("Установить конечную частоту просмотра "+QString::number(end+GnFREQuencyStep)+" MHz\n");




        qDebug () << GnFREQuencyEnd << " GnFREQuencyEnd > = end " << end <<  " MHz"; // " kHZ";


        //Задает полосу просмотра для отображения сигнала на анализаторе....
        viPrintf(N9000->vi, ViString("FREQ:TUNE:IMM \r\n")); // кГц


        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);


        Sleep(1000);


        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);
        write(1,0,freq_prd,0,0,freq_prm,0,0,0,ampl_i,ampl_q,0,0,0,0);

        getPoint_n9000(dResultX,dResultY);

        Sleep(100);

        //КГЦ
        freq = dResultX/pow(10,6);

        x.append(freq);


        emit imgUpdate();


        if(dResultY >= -10)
        {
            y.append(dResultY);
        }
        else
        {
            emit imgUpdate();
            y.append(dResultY);
            qDebug () << "СРЫВ";
            kol_sr++;
            emit imgUpdate();
        }


        int point =0;



        //Cмена точки 950 МГЦ на 1550 МГц
        if(end == 950)
        {

            N9000->write_AVER_STAT(true);

            viPrintf(N9000->vi, ViString("FREQ:SPAN 300 Hz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 10 Hz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



            Sleep(5000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            QList<QPointF> list;
            QList<QPointF> list_delta;

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 100 Hz\n"));
            emit imgUpdate();

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 120 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10) < ListYSL_pred_znach.value(15).split(" ").value(0).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6_GPRM(950,1,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6_GPRM(950,1,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

            ////////////////////////////////////////////


            viPrintf(N9000->vi, ViString("FREQ:SPAN 3 kHz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 100 Hz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



            Sleep(5000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            list.clear();
            list_delta.clear();

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 1 kHz\n"));
            emit imgUpdate();

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10*2) < ListYSL_pred_znach.value(15).split(" ").value(1).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6_GPRM(950,2,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6_GPRM(950,2,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

            ////////////////////////////////////////////


            viPrintf(N9000->vi, ViString("FREQ:SPAN 30 kHz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



            Sleep(5000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            list.clear();
            list_delta.clear();

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 10 kHz\n"));
            emit imgUpdate();

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10*3) < ListYSL_pred_znach.value(15).split(" ").value(2).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6_GPRM(950,3,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6_GPRM(950,3,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


            ////////////////////////////////////////////


            viPrintf(N9000->vi, ViString("FREQ:SPAN 300 kHz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



            Sleep(40000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            list.clear();
            list_delta.clear();

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 100 kHz\n"));
            emit imgUpdate();

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10*3) < ListYSL_pred_znach.value(15).split(" ").value(3).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6_GPRM(950,4,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6_GPRM(950,4,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


            ////////////////////////////////////////////


            viPrintf(N9000->vi, ViString("FREQ:SPAN 3 MHz\r\n")); // RES

            viPrintf(N9000->vi, ViString("BWidth:RES 10 kHz\r\n")); // RES
            viPrintf(N9000->vi, ViString("BWidth:VID 1 kHz\r\n")); // Video

            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
            viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));

            emit imgUpdate();

            Sleep(40000);

            viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
            log("Захватить максимум.\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            list.clear();
            list_delta.clear();

            list.append(QPointF(dResultX,dResultY));

            do
            {
                viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                list.append(QPointF(dResultX,dResultY));

                if((list.last() == list.value(list.count()-2)))
                {
                    list.removeLast();
                    break;
                }


                point++;

            }while(1);

            viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

            viPrintf(N9000->vi, ViString("CALC:MARK:X 1 MHz\n"));


            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



            for(int i =0 ; i < list.count();i++)
            {
                if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                }
                else
                {

                    if((dResultY-10*4) < ListYSL_pred_znach.value(15).split(" ").value(4).toDouble())
                    {
                        qDebug () << "good";
                        emit radioUpdate_proverka6_GPRM(950,5,true);
                    }
                    else
                    {
                        emit radioUpdate_proverka6_GPRM(950,5,false);
                        flagGood =false;
                    }
                }
            }
            emit imgUpdate();
            viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
            viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


            kol_sr=0;

            end = 1550;


        }
        else
        {
            //Cмена точки 1550 МГЦ на 2150 МГц
            if(end == 1550)
            {

                N9000->write_AVER_STAT(true);

                viPrintf(N9000->vi, ViString("FREQ:SPAN 300 Hz\r\n"));

                viPrintf(N9000->vi, ViString("BWidth:RES 10 Hz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(5000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                QList<QPointF> list;
                QList<QPointF> list_delta;

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 100 Hz\n"));
                emit imgUpdate();

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 120 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10) < ListYSL_pred_znach.value(15).split(" ").value(0).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6_GPRM(1550,1,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6_GPRM(1550,1,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

                ////////////////////////////////////////////


                viPrintf(N9000->vi, ViString("FREQ:SPAN 3 kHz\r\n")); // RES

                viPrintf(N9000->vi, ViString("BWidth:RES 100 Hz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(5000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                list.clear();
                list_delta.clear();

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 1 kHz\n"));
                emit imgUpdate();

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10*2) < ListYSL_pred_znach.value(15).split(" ").value(1).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6_GPRM(1550,2,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6_GPRM(1550,2,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

                ////////////////////////////////////////////


                viPrintf(N9000->vi, ViString("FREQ:SPAN 30 kHz\r\n")); // RES

                viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(5000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                list.clear();
                list_delta.clear();

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 10 kHz\n"));

                emit imgUpdate();
                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10*3) < ListYSL_pred_znach.value(15).split(" ").value(2).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6_GPRM(1550,3,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6_GPRM(1550,3,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                ////////////////////////////////////////////


                viPrintf(N9000->vi, ViString("FREQ:SPAN 300 kHz\r\n")); // RES

                viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(40000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                list.clear();
                list_delta.clear();

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 100 kHz\n"));
                emit imgUpdate();

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10*3) < ListYSL_pred_znach.value(15).split(" ").value(3).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6_GPRM(1550,4,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6_GPRM(1550,4,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                ////////////////////////////////////////////


                viPrintf(N9000->vi, ViString("FREQ:SPAN 3 MHz\r\n")); // RES

                viPrintf(N9000->vi, ViString("BWidth:RES 10 kHz\r\n")); // RES
                viPrintf(N9000->vi, ViString("BWidth:VID 1 kHz\r\n")); // Video

                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                Sleep(40000);

                viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                log("Захватить максимум.\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                list.clear();
                list_delta.clear();

                list.append(QPointF(dResultX,dResultY));

                do
                {
                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                    list.append(QPointF(dResultX,dResultY));

                    if((list.last() == list.value(list.count()-2)))
                    {
                        list.removeLast();
                        break;
                    }


                    point++;

                }while(1);

                viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                viPrintf(N9000->vi, ViString("CALC:MARK:X 1 MHz\n"));
                emit imgUpdate();

                viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                for(int i =0 ; i < list.count();i++)
                {
                    if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                        qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                        qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                    }
                    else
                    {

                        if((dResultY-10*4) < ListYSL_pred_znach.value(15).split(" ").value(4).toDouble())
                        {
                            qDebug () << "good";
                            emit radioUpdate_proverka6_GPRM(1550,5,true);
                        }
                        else
                        {
                            emit radioUpdate_proverka6_GPRM(1550,5,false);
                            flagGood =false;
                        }
                    }
                }
                emit imgUpdate();
                viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));



                kol_sr=0;

                end = 2150;


            }
            else
            {
                //Cмена точки 1550 МГЦ на 2150 МГц
                if(end == 2150)
                {

                    N9000->write_AVER_STAT(true);

                    viPrintf(N9000->vi, ViString("FREQ:SPAN 300 Hz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 10 Hz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                    Sleep(5000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    QList<QPointF> list;
                    QList<QPointF> list_delta;

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 100 Hz\n"));

                    emit imgUpdate();
                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 120 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi,ViString( "CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10) < ListYSL_pred_znach.value(15).split(" ").value(0).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6_GPRM(2150,1,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6_GPRM(2150,1,false);
                                flagGood =false;
                            }
                        }
                    }
                    emit imgUpdate();
                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

                    ////////////////////////////////////////////


                    viPrintf(N9000->vi, ViString("FREQ:SPAN 3 kHz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 100 Hz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                    Sleep(5000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    list.clear();
                    list_delta.clear();

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1 kHz\n"));
                    emit imgUpdate();

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10*2) < ListYSL_pred_znach.value(15).split(" ").value(1).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6_GPRM(2150,2,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6_GPRM(2150,2,false);
                                flagGood =false;
                            }
                        }
                    }
                    emit imgUpdate();
                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));

                    ////////////////////////////////////////////


                    viPrintf(N9000->vi, ViString("FREQ:SPAN 30 kHz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                    Sleep(5000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    list.clear();
                    list_delta.clear();

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 10 kHz\n"));
                    emit imgUpdate();

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10*3) < ListYSL_pred_znach.value(15).split(" ").value(2).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6_GPRM(2150,3,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6_GPRM(2150,3,false);
                                flagGood =false;
                            }
                        }
                    }

                    emit imgUpdate();
                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                    ////////////////////////////////////////////


                    viPrintf(N9000->vi, ViString("FREQ:SPAN 300 kHz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 1 kHz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 100 Hz\r\n")); // Video

                    viPrintf(N9000->vi,ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi,ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));



                    Sleep(40000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    list.clear();
                    list_delta.clear();

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 100 kHz\n"));

                    emit imgUpdate();

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10*3) < ListYSL_pred_znach.value(15).split(" ").value(3).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6_GPRM(2150,4,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6_GPRM(2150,4,false);
                                flagGood =false;
                            }
                        }
                    }

                    emit imgUpdate();

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                    ////////////////////////////////////////////


                    viPrintf(N9000->vi, ViString("FREQ:SPAN 3 MHz\r\n")); // RES

                    viPrintf(N9000->vi, ViString("BWidth:RES 10 kHz\r\n")); // RES
                    viPrintf(N9000->vi, ViString("BWidth:VID 1 kHz\r\n")); // Video

                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:TABL:STAT ON\r\n"));
                    viPrintf(N9000->vi, ViString("CALC:MARK:PEAK:SORT:STAT AMPL\r\n"));


                    Sleep(40000);

                    viPrintf(N9000->vi, ViString(":INIT:CONT OFF\r\n"));


                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));
                    log("Захватить максимум.\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    list.clear();
                    list_delta.clear();

                    list.append(QPointF(dResultX,dResultY));

                    do
                    {
                        viPrintf(N9000->vi, ViString("CALC:MARK:MAX:NEXT\n"));
                        log("Захватить максимум.\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                        log("Считанный Y :"+QString::number(dResultY)+" дб\n");

                        viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                        log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");


                        list.append(QPointF(dResultX,dResultY));

                        if((list.last() == list.value(list.count()-2)))
                        {
                            list.removeLast();
                            break;
                        }


                        point++;

                    }while(1);

                    viPrintf(N9000->vi, ViString("CALC:MARK:MAX\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE DELT\n"));

                    viPrintf(N9000->vi, ViString("CALC:MARK:X 1 MHz\n"));


                    viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                    log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                    qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                    viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"),ViString("%lf"), &dResultX);
                    log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                    qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";



                    for(int i =0 ; i < list.count();i++)
                    {
                        if(static_cast<int>(list.value(i).x()) == 950000 + static_cast<int>(dResultX))
                        {
                            viPrintf(N9000->vi, ViString("CALC:MARK:X 1200 Hz\n"));

                            viQueryf(N9000->vi, ViString("CALC:MARK:Y?\n"), ViString("%lf"), &dResultY);
                            log("Считанный Y :"+QString::number(dResultY)+" дб\n");
                            qDebug () << "Считанный Y : " << QString::number(dResultY)<<" дб";

                            viQueryf(N9000->vi, ViString("CALC:MARK:X?\n"), ViString("%lf"), &dResultX);
                            log("Считанный X :"+QString::number(dResultX/pow(10,3))+" kHz\n");

                            qDebug () << "Считанный X : " << QString::number(dResultX/pow(10,3))<<" kHz";


                        }
                        else
                        {

                            if((dResultY-10*4) < ListYSL_pred_znach.value(15).split(" ").value(4).toDouble())
                            {
                                qDebug () << "good";
                                emit radioUpdate_proverka6_GPRM(2150,5,true);
                            }
                            else
                            {
                                emit radioUpdate_proverka6_GPRM(2150,5,false);
                                flagGood =false;
                            }
                        }
                    }

                    viPrintf(N9000->vi, ViString("CALC:MARK:MODE OFF\n"));
                    viPrintf(N9000->vi, ViString(":INIT:CONT ON\r\n"));


                    kol_sr=0;

                    end = 2160;


                }
            }


        }


        QDateTime  date = QDateTime::currentDateTime();


        qDebug() << "signal  updateGraph";



        /////////////////////////////////////////
    }



    emit imgUpdate();

    if(flagGood)
    {
        emit goodProverka(15,true);
    }
    else
    {
        emit goodProverka(15,false);
    }

    qDebug() << "END  Срывов: " <<   kol_sr;
    qDebug() << "END";
    qDebug() << "END";


    viPrintf(N9000->vi, ViString("SYST:PRESet"));

}

void GTS::proverka_14()
{
     emit goodProverka(16,false);
}

void GTS::proverka_15()
{
     emit goodProverka(17,false);
}
