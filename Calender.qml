import QtQuick 2.6
import LunarCalendar 1.0

GridView {
    id: root

    /**
     * @brief 在日历中的有效日期上单击鼠标时发出。
     * @param date: 鼠标被单击的日期。
     */
    signal clicked(variant date)

    /**
     * @brief 重定位到当天日期
     */
    function today() {
        var today = new Date()
        setDate(today)
    }

    /**
     * @brief 获取日历当前日期
     */
    function getDate() {
        return privateVar.getYMD(root.currentIndex)
    }

    /**
     * @brief 设置日历的日期
     */
    function setDate(date) {
        privateVar.monthAndYearNumber = [date.getMonth() + 1, date.getFullYear()]
        root.currentIndex = privateVar.getIndexByDate(date.getDate(), date.getMonth()+1, date.getFullYear())

        /* 更新日期任务列表 */
        __setNoteDates(privateVar.noteDates)
    }

    width: 600; height: 480
    cellHeight: (2*height)/13; cellWidth: width/7
    clip: true
    interactive: false
    header: weekStatus
    model: 42
    delegate: dateGridDelegate

    Component {
        id: weekStatus
        Item {
            id: weekItem
            width: root.width; height: root.height/13
            Repeater {
                model: ["日", "一", "二", "三", "四", "五", "六"]
                Item {
                    x: index * width
                    width: root.cellWidth; height: weekItem.height

                    Text {
                        anchors.centerIn: parent
                        text: model.modelData
                        font.pixelSize: dpW(14)
                        color: "#666666"
                    }
                }
            }
        }
    }

    Component {
        id: dateGridDelegate
        Rectangle {
            id: cellContent
            width: root.cellWidth; height: root.cellHeight
            color: privateVar.getCellBgColor(root.currentIndex === index)

            Column {
                anchors.centerIn: parent
                spacing: dpH(12)

                Item {
                    width: cellContent.width; height: number.font.pixelSize
                    Text {
                        id: number
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        text: privateVar.getDate(index, privateVar.monthAndYearNumber[1], privateVar.monthAndYearNumber[0])
                        onTextChanged: {
                            lunarCalendar.getLunarDate(privateVar.getYMD(index))
                            festival.text = String(lunarCalendar.festivals[0])
                            isFestival = lunarCalendar.isFestival
                        }
                        font.pixelSize: dpW(25)
                        font.bold: true
                        property bool isFestival: lunarCalendar.isFestival
                        color: privateVar.getDateColor(index,
                                                       privateVar.monthAndYearNumber[1],
                                                       privateVar.monthAndYearNumber[0],
                                                       root.currentIndex === index ||
                                                       isFestival)
                    }
                }
                Item {
                    width: cellContent.width; height: festival.font.pixelSize
                    Text {
                        id: festival
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        font.pixelSize: dpW(13)
                        color: number.color
                    }
                }
            }

            Image {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 6
                anchors.leftMargin: 6
                visible: privateVar.curMonthScheduleTable[index]
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.currentIndex = index
                    var selectDate = getDate()
                    setDate(selectDate)
                    root.clicked(selectDate)
                }
            }
        }
    }

    Item {
        id: privateVar
        property var monthAndYearNumber: [(new Date()).getMonth() + 1, (new Date()).getFullYear()]
        property  variant curMonthScheduleTable: [
            false, false, false, false, false, false, false,
            false, false, false, false, false, false, false,
            false, false, false, false, false, false, false,
            false, false, false, false, false, false, false,
            false, false, false, false, false, false, false,
            false, false, false, false, false, false, false,
        ]
        property variant noteDates: []

        function reduceMonth(monthYear) {
            var newMonthYear = monthYear
            if (newMonthYear[0] === 1 && newMonthYear[1] === 0)
                return newMonthYear

            if (newMonthYear[0] === 1) {
                newMonthYear[0] = 12
                newMonthYear[1] = newMonthYear [1] - 1
            }
            else
                newMonthYear[0] = newMonthYear[0] - 1

            return newMonthYear
        }

        function addMonth(monthYear) {
            var newMonthYear = monthYear

            if (newMonthYear[0] === 12) {
                newMonthYear[0] = 1
                newMonthYear[1] = newMonthYear[1] + 1
            }
            else
                newMonthYear[0] = newMonthYear[0] + 1

            return newMonthYear
        }

        function getWeek(iYear, iMonth, iDay) {
            var week = new Date(iYear, iMonth-1, iDay, 0, 0, 0).getDay()
            if (week === 0)
                week = 7;
            return week;
        }

        function getDateColor(index, iYear, iMonth, status) {
            var day = index - privateVar.getWeek(iYear, iMonth, 1) + 1
            if (day < 1 || day > privateVar.judgmentDay(iYear, iMonth))
                return "#90999999";

            var week = privateVar.getWeek(iYear, iMonth, day)

            if (status)
                return "#e74543"

            if (index % 7 === 6 || index % 7 === 0)
                return "#4aa9e7";

            return "black"
        }

        // return (0~31)
        function getDate(index, iYear, iMonth) {
            var day = index - privateVar.getWeek(iYear, iMonth, 1) + 1

            var preMonthYear = privateVar.reduceMonth([iMonth, iYear])

            if (day < 1)
                return (privateVar.judgmentDay(preMonthYear[1], preMonthYear[0]) + day);
            else if (day > privateVar.judgmentDay(iYear, iMonth))
                return day - privateVar.judgmentDay(iYear, iMonth)
            else
                return day;
        }

        // return Date
        function getYMD(index) {
            var nMonthYearList = privateVar.monthAndYearNumber;
            if (nMonthYearList === undefined)
                return new Date
            var sYear = nMonthYearList[1]
            var sMonth = nMonthYearList[0]
            var day = index - privateVar.getWeek(sYear, sMonth, 1) + 1

            if (day < 1) {
                var preMonthYear = privateVar.reduceMonth([sMonth, sYear])
                sMonth = preMonthYear[0]
                sYear = preMonthYear[1]
                day = (privateVar.judgmentDay(preMonthYear[1], preMonthYear[0]) + day)
            }
            else if (day > privateVar.judgmentDay(sYear, sMonth)) {
                var nextMonthYear = privateVar.addMonth([sMonth, sYear])
                day = day - privateVar.judgmentDay(sYear, sMonth)
                sMonth = nextMonthYear[0]
                sYear = nextMonthYear[1]
            }
            else {
                day = day
            }

            var sDate = new Date(sYear, sMonth-1, day, 0, 0, 0)

            return sDate
        }

        function getIndexByDate(iDay, iMonth, iYear) {
            var index = iDay + privateVar.getWeek(iYear, iMonth, 1) - 1
            return index;
        }

        function judgmentDay(year, month){
            var day;
            switch(month){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:return (day=31);
            case 4:
            case 6:
            case 9:
            case 11:return (day=30);
            case 2: if( (year%4 === 0 && (year%100) !== 0) || year%400 === 0)
                    return (day = 29);
                else
                    return (day = 28)
            }
        }

        function isCurMonth() {
            var day = root.currentIndex - privateVar.getWeek(sYear, sMonth, 1) + 1

            if (day < 1) {
                return -1
            }
            else if (day > privateVar.judgmentDay(sYear, sMonth)) {
                return 1
            }
            else {
                return 0
            }
        }

        function updateCurMonthScheduleTable(noteDates) {
            privateVar.noteDates = noteDates
            privateVar.initCurMonthScheduleTable()

            var cpyTable = privateVar.curMonthScheduleTable

            var firstGridDate = privateVar.getYMD(0)

            for (var i = 0; i < noteDates.length; i++) {
                var rtnDay = privateVar.dateMinus(noteDates[i], firstGridDate)

                if (rtnDay >= 0 && rtnDay <= 41)
                    cpyTable[rtnDay] = true
            }

            privateVar.curMonthScheduleTable = cpyTable
        }

        function initCurMonthScheduleTable() {
            var cpyTable = [
                        false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                    ]

            privateVar.curMonthScheduleTable = cpyTable
        }

        function dateMinus(leftDate, rightDate){
            var days = leftDate.getTime() - rightDate.getTime();
            var day = days / (1000 * 60 * 60 * 24)
            return day;
        }

        function getCellBgColor(status) {
            return status ? "#e2e2e2" : "#00000000"
        }
    }

    LunarCalendar {
        id: lunarCalendar
    }

    Component.onCompleted: {
        today()
        __setNoteDates([new Date])
    }

    function dpW(w) { return (width/480)*w }
    function dpH(h) { return (height/853)*h }

    /* 私有方法
     * 该方法是根据输入的日期列表标记其日期是否被标记
     * 日期列表格式 [new Date(), new Date(), new Date()]
     */
    function __setNoteDates(dates) {
        privateVar.updateCurMonthScheduleTable(dates)
    }
}
