#include "preference.h"
#include <limits>
#include <QSettings>

Preference::Preference() :
    m_type(Invalid)
{
}

Preference::Preference(InterfaceOptions interfaceOptions, double defaultValue, double lowerBound, double upperBound, double stepSize, const QString &suffix, const QString &specialValueText) :
    m_type(Double),
    m_interfaceOptions(interfaceOptions),
    m_default(defaultValue),
    m_value(defaultValue),
    m_lowerBound(lowerBound),
    m_upperBound(upperBound),
    m_stepSize(stepSize),
    m_suffix(suffix),
    m_specialValueText(specialValueText)
{
}

Preference::Preference(InterfaceOptions interfaceOptions, double defaultValue, double lowerBound, double upperBound, const QString& suffix, const QString& specialValueText) :
    Preference(interfaceOptions, defaultValue, lowerBound, upperBound, 1, suffix, specialValueText)
{

}

Preference::Preference(InterfaceOptions interfaceOptions, double defaultValue, double stepSize, const QString &suffix, const QString &specialValueText) :
    Preference(interfaceOptions, defaultValue, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), stepSize, suffix, specialValueText)
{

}

Preference::Preference(InterfaceOptions interfaceOptions, const QString& defaultValue, QFileDialog::AcceptMode acceptMode, QFileDialog::FileMode fileMode, QFileDialog::Options options, const QString& placeHolderText) :
    m_type(String),
    m_interfaceOptions(interfaceOptions),
    m_default(defaultValue),
    m_value(defaultValue),
    m_acceptMode(acceptMode),
    m_fileMode(fileMode),
    m_FileDialogOptions(options),
    m_placeHolderText(placeHolderText)
{

}

Preference::Preference(InterfaceOptions interfaceOptions, const QStringList& options, int defaultIndex) :
    m_type(Options),
    m_interfaceOptions(interfaceOptions),
    m_default(defaultIndex),
    m_value(defaultIndex),
    m_options(options)
{

}

Preference::Preference(InterfaceOptions interfaceOptions, bool defaultValue) :
    m_type(Bool),
    m_interfaceOptions(interfaceOptions),
    m_default(defaultValue),
    m_value(defaultValue)
{

}

Preference::Preference(const QVariant &defaultValue) :
    m_type(Unknown),
    m_default(defaultValue),
    m_value(defaultValue)
{
}

void Preference::setValue(const QVariant &value)
{
    if (m_value != value)
    {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void Preference::reset()
{
    setValue(m_default);
}
