#ifndef LUNARCALENDAR_H
#define LUNARCALENDAR_H

#include <QObject>

#include <QDate>
#include <QString>
#include <QObject>
#include <QDebug>

class LunarCalendar : public QObject
{
    Q_OBJECT
public:
    explicit LunarCalendar(QObject *parent = nullptr);

    /* 调用该函数后，获取到的信息可以get回来 */
    Q_INVOKABLE void getLunarDate(QDate date);
    /* 农历:xx月xx日 */
    Q_PROPERTY(QString lunarMD READ getLunarMD NOTIFY statusChanged)
    /* 农历: xx月 */
    Q_PROPERTY(QString lunarM READ getLunarM NOTIFY statusChanged)
    /* 农历: xx日 */
    Q_PROPERTY(QString lunarD READ getLunarD NOTIFY statusChanged)
    /* 农历：天支年[属相]*/
    Q_PROPERTY(QString lunarYear READ getLunarYear NOTIFY statusChanged)
    /* 农历：天支月 */
    Q_PROPERTY(QString lunarMonth READ getLunarMonth NOTIFY statusChanged)
    /* 农历：天支日 */
    Q_PROPERTY(QString lunarDay READ getLunarDay NOTIFY statusChanged)
    /* 二十四节气 */
    Q_PROPERTY(QString lunarTerms READ getLunarTerms NOTIFY statusChanged)
    /* 农历节日 */
    Q_PROPERTY(QString lunarFestival READ getLunarFestival NOTIFY statusChanged)

    /* 获取所有节日
     * 中外主要节日 > 农历节日 > 农历: xx日
     */
    Q_PROPERTY(QStringList festivals READ getFestivals NOTIFY statusChanged)
    Q_PROPERTY(QString festival READ getFestival NOTIFY statusChanged)
    Q_PROPERTY(bool isFestival READ getIsFestival NOTIFY statusChanged)

    QString getLunarMD() { return m_lunarMD; }
    QString getLunarM() { return m_lunarM; }
    QString getLunarD() { return m_lunarD; }
    QString getLunarYear() { return m_lunarYear; }
    QString getLunarMonth() { return m_lunarMonth; }
    QString getLunarDay() { return m_lunarDay; }
    QString getLunarTerms() { return m_lunarTerms; }
    QString getLunarFestival() { return m_lunarFestival; }
    QStringList getFestivals() { return m_festivals; }
    QString getFestival() { return m_festival; }
    bool getIsFestival() { return m_isFestival; }

signals:
    void statusChanged();

private:
    void init();
    /*
     * 计算二十四节气
     * a1: 当月第一个节气日
     * a2: 当月第二个节气日
     */
    bool _getSolarTerms(QDate date,
                       unsigned int &a1,
                       unsigned int &a2);
    /* 计算农历日期 */
    bool _getLunarDay(QDate date,                 /* 公历日期 */
                     QString &outLunarMD,        /* 农历:xx月xx日 */
                     QString &outLunarM,         /* 农历: xx月 */
                     QString &outLunarD,         /* 农历: xx日 */
                     QString &outLunarYear,      /* 农历：天支年【属相】*/
                     QString &outLunarMonth,     /* 农历：天支月 */
                     QString &outLunarDay,       /* 农历：天支日 */
                     QString &outLunarTerms,     /* 二十四节气 */
                     QString &outLunarFestival); /* 农历节日 */

    QString _outLunarMonth(QDate date);

    /* 中外主要节日 */
    QStringList getChinaAndWestFestival(QDate date);

    /* 复活节: 每年春分后月圆第一个星期天 */
    bool isEasterDay(QDate date);
    /* 母亲节: 每年5月份的第2个星期日 */
    bool isMothersDay(QDate date);

    /* 父亲节: 每年6月份的第3个星期日 */
    bool isFathersDay(QDate date);

    /* 感恩节: 每年11月最后一个星期四 */
    bool isThanksgivingDay(QDate date);

    /* targetDate目标日期是否符合 =>
     * month: 5月; weekOfMonth: 第2个; week:星期日(7)
     */
    bool isDay(QDate targetDate, int month, int weekOfMonth, int week);

private:
    /* 农历: xx月xx日 */
    QString m_lunarMD;
    /* 农历: xx月 */
    QString m_lunarM;
    /* 农历: xx日 */
    QString m_lunarD;
    /* 农历：天支年【属相】*/
    QString m_lunarYear;
    /* 农历：天支月 */
    QString m_lunarMonth;
    /* 农历：天支日 */
    QString m_lunarDay;
    /* 二十四节气 */
    QString m_lunarTerms;
    /* 农历节日 */
    QString m_lunarFestival;
    /* 获取所有节日 */
    QStringList m_festivals;
    QString m_festival;
    bool m_isFestival;
};

#endif // LUNARCALENDAR_H
