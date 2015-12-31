#include "filedialogwidget.h"
#include "ui_filedialogwidget.h"
#include <QFileDialog>

FileDialogWidget::FileDialogWidget(QFileDialog::AcceptMode acceptMode, QFileDialog::FileMode fileMode, QFileDialog::Options options, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileDialogWidget),
    m_acceptMode(acceptMode),
    m_fileMode(fileMode),
    m_options(options)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(spwanFileDialog()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setPath(QString)));
}

FileDialogWidget::~FileDialogWidget()
{
    delete ui;
}

void FileDialogWidget::spwanFileDialog()
{
    QFileDialog dialog(this);
    dialog.setOptions(m_options);
    dialog.setFileMode(m_fileMode);
    dialog.setAcceptMode(m_acceptMode);

    if (dialog.exec() == QDialog::Accepted && !dialog.selectedFiles().isEmpty())
    {
        setPath(dialog.selectedFiles().first());
    }
}

void FileDialogWidget::setPath(const QString &path)
{
    if (m_path != path)
    {
        m_path = path;
        emit pathChanged(m_path);
    }
}
