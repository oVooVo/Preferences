# Preferences

Often applications are heavily parameterisable. Some of the parameters may be depent on the user's taste while others should at least be defined at one central place by the coders (and invisible for the user).

Preferences library provides a class similar to `QSettings` (and infact it relies on `QSettings`). Differences are:
- a preference has to be registered. Setting or getting the value of a preference without registerting it will result in an assertion fail and possible crash.
- a preference has a default values
- a preference may be hidden or visible. Visible preferences have options for editing widgets (range, type of widget, ...)

I recommend to subclass QApplication and create a field of type `Preferences`. You must explicitly save the preferences before quitting the application and restore them after application start.

The `PreferenceDialog` displays all preferences of a given `Preferences` object. You can modify preferences or restore them to default value.



