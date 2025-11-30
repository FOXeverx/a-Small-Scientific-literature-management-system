#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QCompleter>
#include <QListView>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Table_1->setColumnWidth(0, static_cast<int>(width() * 0.3));
    ui->a_AuthorCount->setChecked(false);
    main_parser = new Parse(this);
    main_finder = new Find(this);
    Find::initializeIndex();
    connect(main_parser, &Parse::done,
            main_finder, &Find::initializeIndex);
    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);
    searchTimer->setInterval(400);
    connect(ui->fuzzy, &QCheckBox::stateChanged, this, [this](int state){
        if (state == Qt::Checked) {
            if(ui->a_FuzzyOpen->isChecked()){
                connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::FuzzyChanged);
                connect(searchTimer, &QTimer::timeout, this, &MainWindow::FuzzyChanged);
            }
            else {
                QMessageBox:: information(this, "tips", "未打开模糊搜素功能！");
                ui->fuzzy->setCheckState(Qt::Unchecked);
            }
        }
        else {
            disconnect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::FuzzyChanged);
            disconnect(searchTimer, &QTimer::timeout, this, &MainWindow::FuzzyChanged);
        }
    });
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(ui->Table_1);
    layout->addWidget(ui->Table_2);
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Resize(QResizeEvent *event)
{
    Q_UNUSED(event)
    ui->Table_1->setColumnWidth(0, static_cast<int>(width() * 0.5));
}

void MainWindow::FuzzyChanged(){
    if(ui->a_FuzzyOpen->isChecked()){
        QString key = ui->lineEdit->text();
        wordList.clear();
        if(key.length()>2&&previousText!=key){
            previousText=key; QVector<int> result;
            QString filtered = filter_Non_Punctuation(previousText);
            QStringList words = filtered.split(" ", Qt::SkipEmptyParts);
            for (const QString& word : words)result.append(keypos[lemma(word)]);
            for (const auto& str : result) {
                wordList.append(alltitle[str]);
                if(wordList.size()>500)break;
            }
        }
        //输入触发自动补全
        QCompleter *pCompleter = new QCompleter(wordList, this);
        pCompleter->setFilterMode(Qt::MatchContains);
        pCompleter->setCompletionMode(QCompleter::PopupCompletion);
        pCompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->lineEdit->setCompleter(pCompleter);
    }

}

void MainWindow::on_Search_clicked()
{

    // 获取输入的搜索关键词
    QString key = ui->lineEdit->text();
    // 如果关键词为空，则显示消息框提示输入搜索关键词，并返回
    if(key.isEmpty()){
        QMessageBox::information(this, tr("information"), tr("请输入关键词."));
        return ;
    }
    // 读取设置中的最后打开的文件名
    QSettings settings;
    //Q_ASSERT(settings.contains("lastOpenFileName"));
    QString fileName = settings.value("lastOpenFileName").toString();

    // 根据选中的搜索方式执行相应操作

    // 以作者姓名搜索，并在表格中显示搜索结果
    if(ui->b_Author->isChecked()){

        auto list = main_finder->findAuthorIndices(key);
        if(list.isEmpty()){
            QMessageBox::information(this, tr("information"), tr("未找到作者。"));
            return ;
        }

        // 清除表格内容并设置行数
        ui->Table_1->clearContents();
        ui->Table_1->setRowCount(list.size());

        // 填充表格数据
        for(int i = 0; i < list.size(); ++i){
            auto pos = list.at(i);
            Recorder record(Util::findRecord(fileName, pos));
            // 获取记录的作者列表
            QStringList authorList = record.authors();
            // 使用逗号将作者列表连接成一个字符串
            QString allAuthors = authorList.join(", ");

            // 将结果显示在界面上
            ui->Table_1->setItem(i, 0, new QTableWidgetItem(record.title()));
            ui->Table_1->setItem(i, 1, new QTableWidgetItem(allAuthors));
            ui->Table_1->setItem(i, 2, new QTableWidgetItem(record.mdate()));
            ui->Table_1->setItem(i, 3, new QTableWidgetItem(record.publisher()));
            ui->Table_1->setItem(i, 4, new QTableWidgetItem(record.key()));
        }
        ui->Table_1->setColumnWidth(0, 100);
        ui->Table_1->setColumnWidth(1, 100);  // 将第2列的宽度设置为300像素
        ui->Table_1->resizeRowsToContents(); // 调整行高
        ui->Table_1->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格不可编辑
    }

    // 以文章标题搜索，并在标签中显示搜索结果的详细信息
    else if(ui->b_Title->isChecked()){
        auto list = main_finder->findTitleIndices(key);
        if(list.isEmpty()){
            QMessageBox::information(this, tr("information"), tr("未找到对应标题的文章."));
            return ;
        }

        // 清空标签内容
        ui->Label->clear();
        QString text;

        // 构建详细信息文本
        for(int i = 0; i < list.size(); ++i){
            auto pos = list.at(i);
            Recorder record(Util::findRecord(fileName, pos));
            QString authorText;

            // 构建作者信息文本
            foreach(QString author, record.authors()){
                authorText.append(tr("作者：%1 <br/>").arg(author));
            }

            // 构建完整记录文本
            text.append(tr(R"(<b>记录详情</b><br/>
                            标题：%1 <br/>
                            %2
                            修改日期：%3 <br/>
                            发布者: %4 <br/>
                            关键词：%5 <br/><br/>
                            )").arg(record.title()).arg(authorText).arg(record.mdate()).arg(record.publisher()).arg(record.key()));
        }

        // 在标签中显示详细信息
        ui->Label->setText(text);
    }

    // 以合著作者搜索，并在文本浏览器中显示搜索结果的合著作者
    else if(ui->b_Coauthor->isChecked()){
        auto list = main_finder->findAuthorIndices(key);
        if(list.isEmpty()){
            QMessageBox::information(this, tr("information"), tr("未找到合著者。"));
            return ;
        }

        // 构建合著作者文本
        QString text;
        QStringList coauthorlist;
        for(int i = 0; i < list.size(); ++i){
            quint32 pos = list.at(i);
            Recorder record(Util::findRecord(fileName, pos));
            QStringList tmplist=record.coauthors();
            for(int j = 0; j< tmplist.size();++j){
                coauthorlist.append(tmplist.at(j));
            }
            record.clearCoauthors();
        }

        // 去重并构建文本
        QSet<QString> coauthorSet;
        foreach (const QString &str, coauthorlist) {
            coauthorSet.insert(str);
        }
        coauthorSet.remove(key);
        foreach (const QString &value, coauthorSet)
            text.append(tr(R"(coauthor：%1 <br/>)").arg(value));

        // 在文本浏览器中显示合著作者
        ui->Browser->setText(text);
    }

    // 以关键字搜索，并在表格中显示搜索结果
    else if(ui->b_Key->isChecked()){

        auto list = main_finder->findKeywordIndices(key);
        if(list.isEmpty()){
            QMessageBox::information(this, tr("information"), tr("未找到对应关键词的文章."));
            return ;
        }

        // 清除表格内容并设置行数
        ui->Table_1->clearContents();
        ui->Table_1->setRowCount(list.size());

        // 填充表格数据
        for(int i = 0; i < list.size(); ++i){
            auto pos = list.at(i);
            Recorder record(Util::findRecord(fileName, pos));
            // 获取记录的作者列表
            QStringList authorList = record.authors();
            // 使用逗号将作者列表连接成一个字符串
            QString allAuthors = authorList.join(", ");

            // 将结果显示在界面上
            ui->Table_1->setItem(i, 0, new QTableWidgetItem(record.title()));
            ui->Table_1->setItem(i, 1, new QTableWidgetItem(allAuthors));
            ui->Table_1->setItem(i, 2, new QTableWidgetItem(record.mdate()));
            ui->Table_1->setItem(i, 3, new QTableWidgetItem(record.publisher()));
            ui->Table_1->setItem(i, 4, new QTableWidgetItem(record.key()));
        }
        ui->Table_1->setColumnWidth(0, 200);
        ui->Table_1->setColumnWidth(1, 150);  // 将第2列的宽度设置为300像素
        // 调整行高
        ui->Table_1->resizeRowsToContents();
    }

    else if(ui->b_Fuzzy->isChecked())
    {
        if(ui->a_FuzzyOpen->isChecked()){
            QList<quint32>list;
            QString key = ui->lineEdit->text();
            QVector<int> result;//=keypos[lemma(previousText)];
            QString filtered = filter_Non_Punctuation(key);
            QStringList words = filtered.split(" ", Qt::SkipEmptyParts);
            for (const QString& word : words)result.append(keypos[lemma(word)]);
            for (const auto& str : result) {
                //qDebug() << alltitle[str] << "\n";
                list.append(main_finder->findTitleIndices(alltitle[str]));
                if(list.size()>1000)break;
            }

            // 清除表格内容并设置行数
            ui->Table_2->clearContents();
            ui->Table_2->setRowCount(list.size());
            // 填充表格数据
            for(int i = 0; i < list.size(); ++i){
                auto pos = list.at(i);
                Recorder record(Util::findRecord(fileName, pos));


                // 将结果显示在界面上
                ui->Table_2->setItem(i, 0, new QTableWidgetItem(record.title()));
                ui->Table_2->setItem(i, 1, new QTableWidgetItem(record.mdate()));
                ui->Table_2->setItem(i, 2, new QTableWidgetItem(record.key()));
            }
            ui->Table_2->setColumnWidth(0, 200);
            //ui->Table_1->setColumnWidth(1, 150);  // 将第2列的宽度设置为300像素
            // 调整行高
            ui->Table_2->resizeRowsToContents();

        }
    }
}

void MainWindow::on_a_AuthorCount_triggered()
{
    main_parser->condi=1;
    // 获取最后打开的文件名
    QString lastOpenFileName;
    QSettings settings;
    if(settings.contains("lastOpenFileName")){
        lastOpenFileName = settings.value("lastOpenFileName").toString();
    }
    // 打开文件选择对话框，让用户选择要打开的XML文件
    QString fileName = lastOpenFileName;
    // 如果未选择文件，则返回
    if(fileName.isEmpty()) return ;
    // 当文件大小超过64MiB时询问用户
    if(QFile(fileName).size() > (1 << 26)){
        QMessageBox box(this);
        if(main_parser->author_flag==1){
            box.setText(tr("作者文章计数统计已经存在,重新进行耗时较长. "));
            box.setInformativeText(tr("是否重新进行?"));
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setButtonText(QMessageBox::Yes,"是");
            box.setButtonText(QMessageBox::No,"否");
            box.setDefaultButton(QMessageBox::No);
            int ret = box.exec();
            if(ret == QMessageBox::No) main_parser->author_flag=1 ;
            if(ret == QMessageBox::Yes) main_parser->author_flag=0 ;
        }
        else if(main_parser->author_flag==0){
            box.setText(tr("作者文章计数统计耗时较长. "));
            box.setInformativeText(tr("是否进行?"));
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setButtonText(QMessageBox::Yes,"是");
            box.setButtonText(QMessageBox::No,"否");
            box.setDefaultButton(QMessageBox::No);
            int ret = box.exec();

            if(ret == QMessageBox::No) {ui->a_AuthorCount->setChecked(false);return ;}

            if(ret == QMessageBox::Yes) {ui->a_AuthorCount->setChecked(true);}
        }
    }
    // 创建ParseDialog对话框，连接解析器的信号和ParseDialog的槽，显示对话框并启动解析器
    Progresswindow *window = new Progresswindow(this);
    connect(main_parser, &Parse::state_Changed,
            window, &Progresswindow::showStatus);
    connect(main_parser, &Parse::done,
            window, &Progresswindow::activeButton);
    window->open();
    main_parser->set_FileName(fileName);
    main_parser->start();
}

void MainWindow::on_a_Open_triggered()
{

    main_parser->condi=0;
    // 获取最后打开的文件名
    QString lastOpenFileName;
    QSettings settings;
    if(settings.contains("lastOpenFileName")){
        lastOpenFileName = settings.value("lastOpenFileName").toString();
    }else{
        // 使用文档位置作为默认路径
        lastOpenFileName = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    }

    // 打开文件选择对话框，让用户选择要打开的XML文件
    QString fileName = QFileDialog::getOpenFileName(this,tr("choose XML file"),lastOpenFileName,tr("XML file (*.xml)"));
    // 如果未选择文件，则返回
    if(fileName.isEmpty()) return ;

    // 将选择的文件名保存到设置中的最后打开文件名
    settings.setValue("lastOpenFileName", fileName);

    // 当文件大小超过64MiB时询问用户
    if(QFile(fileName).size() > (1 << 26)){
        QMessageBox box(this);
        box.setText(tr("xml文件分析消耗大量内存"));
        box.setInformativeText(tr("是否进行?"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        box.setButtonText(QMessageBox::Yes,"是");
        box.setButtonText(QMessageBox::No,"否");
        box.setDefaultButton(QMessageBox::No);
        int ret = box.exec();
        if(ret == QMessageBox::No) return ;
    }

    // 创建ParseDialog对话框，连接解析器的信号和ParseDialog的槽，显示对话框并启动解析器
    Progresswindow *window = new Progresswindow(this);
    connect(main_parser, &Parse::state_Changed,
            window, &Progresswindow::showStatus);
    connect(main_parser, &Parse::done,
            window, &Progresswindow::activeButton);
    window->open();
    main_parser->set_FileName(fileName);
    main_parser->start();
}

void MainWindow::on_a_Exit_triggered(){close();}

void MainWindow::on_a_Help_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(tr("使用该工具首先要导入文件，如需进行模糊搜索先启用模糊匹配功能，以下为功能说明\n"
                      "打开文件：导入xml文件\n"
                      "查询状态：查询是否已导入xml文件\n"
                      "清除文件：清除已经导入的xml文件\n"
                      "模糊匹配：启动模糊匹配功能（该功能耗时较长）\n"
                      "作者统计：输出写文章最多的前100名作者\n"
                      "聚团分析：统计作者合作关系图中各阶完全子图的个数\n"
                      "热词统计：分析每一年发表的文章题目所包含的单词中出现频率排名前10的关键词"));
    msgBox.exec();
}

void MainWindow::on_a_Clear_triggered()
{
    main_parser->clear_Index();
    main_finder->clearIndex();
    QMessageBox::information(this, tr("information"), tr("已清除索引文件."));
}

void MainWindow::on_a_Status_triggered()
{
    // 创建消息框对象，将窗口作为消息框的父对象
    QMessageBox msgBox(this);

    // 如果XML文件已解析，则设置消息文本和按钮
    if(main_finder->isIndexParsed()){
        msgBox.setText(tr("XML文件已解析。"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Yes,"是");
        msgBox.setDefaultButton(QMessageBox::Ok);
    }else{
        // 如果XML文件未解析，则设置消息文本和按钮，并修改按钮文本
        msgBox.setText(tr("没有解析任何XML文件。"));
        msgBox.setStandardButtons(QMessageBox::Open|QMessageBox::Cancel);
        msgBox.button(QMessageBox::Open)->setText(tr("打开xml文件"));
        msgBox.button(QMessageBox::Cancel)->setText(tr("取消"));
        msgBox.setDefaultButton(QMessageBox::Cancel);
    }

    // 显示消息框并等待用户操作
    int ret = msgBox.exec();

    // 如果用户点击打开按钮，则触发打开文件操作
    if(ret == QMessageBox::Open){
        on_a_Open_triggered();
    }
}

void MainWindow::on_a_GroupAnalyze_triggered()
{
    main_parser->condi=3;
    // 获取最后打开的文件名
    QString lastOpenFileName;
    QSettings settings;
    if(settings.contains("lastOpenFileName")){
        lastOpenFileName = settings.value("lastOpenFileName").toString();
    }
    // 打开文件选择对话框，让用户选择要打开的XML文件
    QString fileName = lastOpenFileName;
    // 如果未选择文件，则返回
    if(fileName.isEmpty()) return ;
    // 当文件大小超过64MiB时询问用户
    if(QFile(fileName).size() > (1 << 26)){
        QMessageBox box(this);
        if(main_parser->group_flag==1){
            box.setText(tr("作者群组分析已经完成.再次进行耗时较长 "));
            box.setInformativeText(tr("是否进行?"));
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setButtonText(QMessageBox::Yes,"是");
            box.setButtonText(QMessageBox::No,"否");
            box.setDefaultButton(QMessageBox::No);
            int ret = box.exec();
            if(ret == QMessageBox::No) main_parser->group_flag=1 ;
            if(ret == QMessageBox::Yes) main_parser->group_flag=0 ;
        }
        else if(main_parser->group_flag==0){
            box.setText(tr("作者群组分析耗时较长. "));
            box.setInformativeText(tr("是否进行?"));
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setButtonText(QMessageBox::Yes,"是");
            box.setButtonText(QMessageBox::No,"否");
            box.setDefaultButton(QMessageBox::No);
            int ret = box.exec();
            if(ret == QMessageBox::No) {ui->a_GroupAnalyze->setChecked(false);return ;}
            if(ret == QMessageBox::Yes) {ui->a_GroupAnalyze->setChecked(true);}
        }
    }
    // 创建对话框，连接解析器的信号和槽，显示对话框并启动解析器
    Progresswindow *window = new Progresswindow(this);
    connect(main_parser, &Parse::state_Changed,
            window, &Progresswindow::showStatus);
    connect(main_parser, &Parse::done,
            window, &Progresswindow::activeButton);
    window->open();
    main_parser->set_FileName(fileName);
    main_parser->start();
}

void MainWindow::on_a_KeyWordCount_triggered()
{
    main_parser->condi=4;
    // 获取最后打开的文件名
    QString lastOpenFileName;
    QSettings settings;
    if(settings.contains("lastOpenFileName")){
        lastOpenFileName = settings.value("lastOpenFileName").toString();
    }
    // 打开文件选择对话框，让用户选择要打开的XML文件
    QString fileName = lastOpenFileName;
    // 如果未选择文件，则返回
    if(fileName.isEmpty()) return ;
    // 当文件大小超过64MiB时询问用户
    if(QFile(fileName).size() > (1 << 26)){
        QMessageBox box(this);
        if(main_parser->key_flag==1){
            box.setText(tr("关键词统计已经完成，重新进行耗时较长. "));
            box.setInformativeText(tr("是否进行?"));
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setButtonText(QMessageBox::Yes,"是");
            box.setButtonText(QMessageBox::No,"否");
            box.setDefaultButton(QMessageBox::No);
            int ret = box.exec();
            if(ret == QMessageBox::No) main_parser->key_flag=1 ;
            if(ret == QMessageBox::Yes) main_parser->key_flag=0 ;
        }
        else if(main_parser->key_flag==0){
            box.setText(tr("关键词统计耗时较长. "));
            box.setInformativeText(tr("是否进行?"));
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setButtonText(QMessageBox::Yes,"是");
            box.setButtonText(QMessageBox::No,"否");
            box.setDefaultButton(QMessageBox::No);
            int ret = box.exec();
            if(ret == QMessageBox::No) {ui->a_KeyWordCount->setChecked(false);return ;}
            if(ret == QMessageBox::Yes) {ui->a_KeyWordCount->setChecked(true);}
        }
    }
    // 创建对话框，连接解析器的信号和槽，显示对话框并启动解析器
    Progresswindow *window = new Progresswindow(this);
    connect(main_parser, &Parse::state_Changed,
            window, &Progresswindow::showStatus);
    connect(main_parser, &Parse::done,
            window, &Progresswindow::activeButton);
    window->open();
    main_parser->set_FileName(fileName);
    main_parser->start();
    if(main_parser->key_flag==1){ui->a_KeyWordCount->setChecked(true);}
}

void MainWindow::on_a_FuzzyOpen_triggered()
{
    main_parser->condi=2;
    // 获取最后打开的文件名
    QString lastOpenFileName;
    QSettings settings;
    if(settings.contains("lastOpenFileName")){
        lastOpenFileName = settings.value("lastOpenFileName").toString();
    }
    // 打开文件选择对话框，让用户选择要打开的XML文件
    QString fileName = lastOpenFileName;int flag=0;
    // 如果未选择文件，则返回
    if(fileName.isEmpty()) return ;
    // 当文件大小超过64MiB时询问用户
    if(QFile(fileName).size() > (1 << 26)){
        QMessageBox box(this);
        if(main_parser->title_flag==1){
            box.setText(tr("模糊搜索已经启用，重新启用耗时较长. "));
            box.setInformativeText(tr("是否进行?"));
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setButtonText(QMessageBox::Yes,"是");
            box.setButtonText(QMessageBox::No,"否");
            box.setDefaultButton(QMessageBox::No);
            int ret = box.exec();
            if(ret == QMessageBox::No) main_parser->title_flag=1 ;
            if(ret == QMessageBox::Yes) {main_parser->title_flag=0 ;flag=1;}
        }
        else if(main_parser->title_flag==0){
            box.setText(tr("启用模糊搜索功能耗时较长. "));
            box.setInformativeText(tr("是否启用?"));
            box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            box.setButtonText(QMessageBox::Yes,"是");
            box.setButtonText(QMessageBox::No,"否");
            box.setDefaultButton(QMessageBox::No);
            int ret = box.exec();
            if(ret == QMessageBox::No) {ui->a_FuzzyOpen->setChecked(false);main_parser->title_flag=0 ;return ;}
            if(ret == QMessageBox::Yes) {ui->a_FuzzyOpen->setChecked(true);flag=1;}
        }
    }
    // 创建对话框，连接解析器的信号和槽，显示对话框并启动解析器
    if(flag==1){
        Progresswindow *window = new Progresswindow(this);
        connect(main_parser, &Parse::state_Changed,
                window, &Progresswindow::showStatus);
        connect(main_parser, &Parse::done,
                window, &Progresswindow::activeButton);
        window->open();
        main_parser->set_FileName(fileName);
        main_parser->start();

    }
}

void MainWindow::on_b_Author_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_b_Coauthor_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_b_Title_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_b_Key_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_b_Fuzzy_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

