#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "preferences_global.h"
#include <QMap>
#include <QVariant>
#include "preference.h"

class PREFERENCESSHARED_EXPORT Preferences
{
public:
    Preferences();
    ~Preferences();

    void save() const;
    void restore() const;

    void registerPreference(const QString& key, Preference* preference);

    Preference* get(const QString& key) const;
    void setValue(const QString& key, const QVariant& value);

    QStringList categories() const;
    QList<Preference*> preferences(const QString& category) const;

private:
    QMap<QString, Preference*> m_preferences;
    bool m_enableSaveRestore;
};

#endif // PREFERENCES_H
