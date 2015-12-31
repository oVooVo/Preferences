#include "preferences.h"
#include <QSettings>
#include <QSet>

Preferences::Preferences()
{
}

void Preferences::setValue(const QString &key, const QVariant &value)
{
    m_preferences.value(key)->setValue(value);
}

Preference* Preferences::get(const QString &key) const
{
    return m_preferences.value(key);
}

void Preferences::registerPreference(const QString &key, Preference *preference)
{
    Q_ASSERT(!m_preferences.contains(key));
    m_preferences.insert(key, preference);
}

void Preferences::restore() const
{
    QSettings settings;
    settings.beginGroup("Preferences");
    for (const QString& key : m_preferences.keys())
    {
        if (settings.contains(key))
        {
            // options of the preference object are hard coded and never change.
            QVariant value = settings.value(key);
            m_preferences[key]->setValue(value);
        }

    }
    settings.endGroup();    //Preferences
}

void Preferences::save() const
{
    QSettings settings;
    settings.beginGroup("Preferences");
    for (const QString& key : m_preferences.keys())
    {
        settings.setValue(key, m_preferences[key]->value());
    }
    settings.endGroup();    //Preferences
}

QStringList Preferences::categories() const
{
    QSet<QString> categories;
    for (const QString& key : m_preferences.keys())
    {
        categories << m_preferences[key]->interfaceOptions().category();
    }
    categories.remove("");
    QStringList sortedCategories = categories.toList();
    std::sort(sortedCategories.begin(), sortedCategories.end());
    return sortedCategories;
}

QList<Preference *> Preferences::preferences(const QString& category) const
{
    QList<Preference*> preferences;
    for (const QString& key : m_preferences.keys())
    {
        if (m_preferences[key]->interfaceOptions().category() == category)
        {
            preferences << m_preferences[key];
        }
    }
    return preferences;
}
