#include "studentmodel.h"
#include <QSqlError>
#include <QCoreApplication>

StudentModel::StudentModel(QObject *parent) : QAbstractTableModel(parent)
{
}

bool StudentModel::initDB(const QString &dbPath)
{
    qDebug() << QCoreApplication::libraryPaths();
    qDebug() << "Drivers:" << QSqlDatabase::drivers();
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);
    if (!m_db.open()) {
        qWarning() << "打开数据库失败:" << m_db.lastError().text();
        return false;
    }

    // 初始化表（如果不存在）
    QSqlQuery q;
    q.exec("CREATE TABLE IF NOT EXISTS departments (departID INTEGER PRIMARY KEY, department TEXT NOT NULL)");
    q.exec("CREATE TABLE IF NOT EXISTS majors (majorID INTEGER PRIMARY KEY, major TEXT NOT NULL, departID INTEGER NOT NULL REFERENCES departments(departID))");
    q.exec("CREATE TABLE IF NOT EXISTS studInfo (studID INTEGER PRIMARY KEY, name TEXT, gender TEXT, departID INTEGER REFERENCES departments(departID), majorID INTEGER REFERENCES majors(majorID))");

    loadData();
    return true;
}

void StudentModel::loadData()
{
    beginResetModel();
    m_students.clear();

    QSqlQuery q(m_db);
    q.exec(R"(SELECT s.studID, s.name, s.gender, s.departID, d.department, s.majorID, m.major
              FROM studInfo s
              LEFT JOIN departments d ON s.departID = d.departID
              LEFT JOIN majors m ON s.majorID = m.majorID
              ORDER BY s.studID)");

    while (q.next()) {
        Student s;
        s.studID = q.value(0).toLongLong();
        s.name = q.value(1).toString();
        s.gender = q.value(2).toString();
        s.departID = q.value(3).toInt();
        s.department = q.value(4).toString();
        s.majorID = q.value(5).toInt();
        s.major = q.value(6).toString();
        m_students.append(s);
    }

    endResetModel();
}

int StudentModel::rowCount(const QModelIndex &parent) const { Q_UNUSED(parent); return m_students.size(); }
int StudentModel::columnCount(const QModelIndex &parent) const { Q_UNUSED(parent); return 1; }

QVariant StudentModel::data(const QModelIndex &index, int role) const
{
   if (!index.isValid()) return {};

    const Student &s = m_students.at(index.row());

    switch(role) {
    case NameRole: return s.name;
    case GenderRole: return s.gender;
    case DepartmentRole: return s.department;
    case MajorRole: return s.major;
    case StudIDRole: return s.studID;
    default: return {};
    }
}

QHash<int, QByteArray> StudentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole+1] = "name";
    roles[Qt::UserRole+2] = "gender";
    roles[Qt::UserRole+3] = "department";
    roles[Qt::UserRole+4] = "major";
    roles[Qt::UserRole+5] = "studID";
    return roles;
}

void StudentModel::addStudent(const QString &name, const QString &gender, int departID, int majorID)
{
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO studInfo (name, gender, departID, majorID) VALUES (?, ?, ?, ?)");
    q.addBindValue(name); q.addBindValue(gender); q.addBindValue(departID); q.addBindValue(majorID);
    if (!q.exec()) qWarning() << "Insert failed:" << q.lastError().text();
    loadData();
}

void StudentModel::editStudent(int row, const QString &name, const QString &gender, int departID, int majorID)
{
    if (row < 0 || row >= m_students.size()) return;
    qint64 id = m_students[row].studID;
    QSqlQuery q(m_db);
    q.prepare("UPDATE studInfo SET name=?, gender=?, departID=?, majorID=? WHERE studID=?");
    q.addBindValue(name); q.addBindValue(gender); q.addBindValue(departID); q.addBindValue(majorID); q.addBindValue(id);
    if (!q.exec()) qWarning() << "Update failed:" << q.lastError().text();
    loadData();
}

void StudentModel::deleteStudent(int row)
{
    if (row < 0 || row >= m_students.size()) return;
    qint64 id = m_students[row].studID;
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM studInfo WHERE studID=?");
    q.addBindValue(id);
    if (!q.exec()) qWarning() << "Delete failed:" << q.lastError().text();
    loadData();
}

QVariantMap StudentModel::getStudent(int row) const
{
    QVariantMap m;
    if (row < 0 || row >= m_students.size()) return m;
    const Student &s = m_students.at(row);
    m["name"] = s.name;
    m["gender"] = s.gender;
    m["departID"] = s.departID;
    m["majorID"] = s.majorID;
    return m;
}