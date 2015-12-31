#include "preferencedialog.h"
#include "ui_preferencedialog.h"
#include <QHBoxLayout>
#include "preferences.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include "filedialogwidget.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QScrollArea>
#include <QFormLayout>
#include <QTabWidget>

PreferenceDialog::PreferenceDialog(Preferences* preferences, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceDialog),
    m_preferences(preferences)
{
    ui->setupUi(this);

    QTabWidget* tabWidget = new QTabWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    layout->addWidget(ui->buttonBox);
    setLayout(layout);

    for (const QString& category : preferences->categories())
    {
        QScrollArea* scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget( createCategoryPage(preferences->preferences(category), scrollArea) );
        tabWidget->addTab(scrollArea, category );
    }

    m_preferences->save();
}

PreferenceDialog::~PreferenceDialog()
{
    delete ui;
}

void PreferenceDialog::reject()
{
    m_preferences->restore();
    QDialog::reject();
}

void PreferenceDialog::accept()
{
    m_preferences->save();
    QDialog::accept();
}

QWidget* PreferenceDialog::createCategoryPage(QList<Preference *> preferences, QWidget *parent)
{
    QWidget* widget = new QWidget(parent);
    QFormLayout* formLayout = new QFormLayout(widget);
    widget->setLayout(formLayout);
    for (Preference* preference : preferences)
    {
        formLayout->addRow( new QLabel(preference->interfaceOptions().caption() + ":", widget),
                            createPreferenceWidget(preference, widget) );
    }
    return widget;
}

QWidget* lineEdit(Preference* preference, QWidget* parent)
{
    QLineEdit* edit = new QLineEdit(parent);
    edit->setPlaceholderText(preference->placeHolderText());
    edit->setText(preference->value().toString());
    PreferenceDialog::connect(edit, &QLineEdit::textChanged, [preference](const QString& text)
    {
        preference->setValue(text);
    });
    QMetaObject::Connection connection = PreferenceDialog::connect(preference, &Preference::valueChanged, [edit](const QVariant& value)
    {
        edit->setText(value.toString());
    });
    PreferenceDialog::connect(edit, &QObject::destroyed, [connection]()
    {
        PreferenceDialog::disconnect(connection);
    });
    return edit;
}

QWidget* textEdit(Preference* preference, QWidget* parent)
{
    QTextEdit* edit = new QTextEdit(parent);
    edit->setPlaceholderText(preference->placeHolderText());
    edit->setText(preference->value().toString());
    PreferenceDialog::connect(edit, &QTextEdit::textChanged, [preference, edit]()
    {
        preference->setValue(edit->toPlainText());
    });
    QMetaObject::Connection connection = PreferenceDialog::connect(preference, &Preference::valueChanged, [edit](const QVariant& value)
    {
        edit->setText(value.toString());
    });
    PreferenceDialog::connect(edit, &QObject::destroyed, [connection]()
    {
        PreferenceDialog::disconnect(connection);
    });
    return edit;
}

QWidget* checkBox(Preference* preference, QWidget* parent)
{
    QCheckBox* edit = new QCheckBox(parent);
    edit->setChecked(preference->value().toBool());
    PreferenceDialog::connect(edit, &QCheckBox::clicked, [preference](bool value)
    {
        preference->setValue(value);
    });
    QMetaObject::Connection connection = PreferenceDialog::connect(preference, &Preference::valueChanged, [edit](const QVariant& value)
    {
        edit->setChecked(value.toBool());
    });
    PreferenceDialog::connect(edit, &QObject::destroyed, [connection]()
    {
        PreferenceDialog::disconnect(connection);
    });
    return edit;
}

QWidget* checkButton(Preference* preference, QWidget* parent)
{
    QPushButton* edit = new QPushButton(parent);
    edit->setCheckable(true);
    edit->setChecked(preference->value().toBool());
    PreferenceDialog::connect(edit, &QPushButton::clicked, [preference](bool value)
    {
        preference->setValue(value);
    });
    QMetaObject::Connection connection = PreferenceDialog::connect(preference, &Preference::valueChanged, [edit](const QVariant& value)
    {
        edit->setChecked(value.toBool());
    });
    PreferenceDialog::connect(edit, &QObject::destroyed, [connection]()
    {
        PreferenceDialog::disconnect(connection);
    });
    return edit;
}

QWidget* comboBox(Preference* preference, QWidget* parent)
{
    QComboBox* edit = new QComboBox(parent);
    edit->addItems(preference->options());
    edit->setCurrentIndex(preference->value().toInt());
    PreferenceDialog::connect(edit, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [edit, preference](int value)
    {
        preference->setValue(value);
    });
    QMetaObject::Connection connection = PreferenceDialog::connect(preference, &Preference::valueChanged, [edit](const QVariant& value)
    {
        edit->setCurrentIndex(value.toInt());
    });
    PreferenceDialog::connect(edit, &QObject::destroyed, [connection]()
    {
        PreferenceDialog::disconnect(connection);
    });

    return edit;
}

QWidget* fileDialog(Preference* preference, QWidget* parent)
{
    FileDialogWidget* edit = new FileDialogWidget(preference->acceptMode(), preference->fileMode(), preference->fileDialogOptions(), parent);
    edit->setPath(preference->value().toString());
    PreferenceDialog::connect(edit, &FileDialogWidget::pathChanged, [preference](const QString& path)
    {
        preference->setValue(path);
    });
    QMetaObject::Connection connection = PreferenceDialog::connect(preference, &Preference::valueChanged, [edit](const QVariant& value)
    {
        edit->setPath(value.toString());
    });
    PreferenceDialog::connect(edit, &QObject::destroyed, [connection]()
    {
        PreferenceDialog::disconnect(connection);
    });
    return edit;
}

QWidget* spinBox(Preference* preference, QWidget* parent)
{
    QDoubleSpinBox* edit = new QDoubleSpinBox(parent);
    edit->setRange(preference->lowerBound(), preference->upperBound());
    edit->setSingleStep(preference->stepSize());
    edit->setValue(preference->value().toDouble());
    edit->setSpecialValueText(preference->specialValueText());
    PreferenceDialog::connect(edit, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [preference](double value)
    {
        preference->setValue(value);
    });
    QMetaObject::Connection connection = PreferenceDialog::connect(preference, &Preference::valueChanged, [edit](const QVariant& value)
    {
        edit->setValue(value.toDouble());
    });
    PreferenceDialog::connect(edit, &QObject::destroyed, [connection]()
    {
        PreferenceDialog::disconnect(connection);
    });
    return edit;
}


QWidget* PreferenceDialog::createPreferenceEditor(Preference *preference, QWidget *parent)
{
    switch (preference->interfaceOptions().interface())
    {
    case InterfaceOptions::LineEdit:
        return lineEdit(preference, parent);
    case InterfaceOptions::CheckBox:
        return checkBox(preference, parent);
    case InterfaceOptions::CheckButton:
        return checkButton(preference, parent);
    case InterfaceOptions::ComboBox:
        return comboBox(preference, parent);
    case InterfaceOptions::FileDialog:
        return fileDialog(preference, parent);
    case InterfaceOptions::SpinBox:
        return spinBox(preference, parent);
    case InterfaceOptions::TextEdit:
        return textEdit(preference, parent);
    default:
        Q_UNREACHABLE();
        return nullptr;
    }
}

QWidget* PreferenceDialog::createPreferenceWidget(Preference *preference, QWidget* parent)
{
    QWidget* widget = new QWidget(parent);
    QHBoxLayout* layout = new QHBoxLayout(widget);

    layout->addWidget( createPreferenceEditor(preference, widget) );
    QPushButton* defaultButton = new QPushButton(widget);
    defaultButton->setIcon(QIcon("://icons/1411737168_POWER - RESTART.png"));
    connect(defaultButton, SIGNAL(clicked()), preference, SLOT(reset()));
    defaultButton->setFixedSize(27, 27);
    layout->addWidget( defaultButton );
    widget->setLayout(layout);
    return widget;
}
