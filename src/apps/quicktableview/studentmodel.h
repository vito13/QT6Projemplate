#pragma once
#include <QAbstractTableModel>
#include <QtSql>
#include <QVariantList>
#include <QDebug>

class StudentModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum StudentRoles {
        NameRole = Qt::UserRole + 1,
        GenderRole,
        DepartmentRole,
        MajorRole,
        StudIDRole
    };

    struct Student {
        qint64 studID;
        QString name;
        QString gender;
        int departID;
        QString department;
        int majorID;
        QString major;
    };

    explicit StudentModel(QObject *parent = nullptr);

    // QAbstractTableModel 必须实现
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // CRUD 方法
    Q_INVOKABLE void addStudent(const QString &name, const QString &gender, int departID, int majorID);
    Q_INVOKABLE void editStudent(int row, const QString &name, const QString &gender, int departID, int majorID);
    Q_INVOKABLE void deleteStudent(int row);
    Q_INVOKABLE QVariantMap getStudent(int row) const;

    bool initDB(const QString &dbPath);

private:
    QList<Student> m_students;
    QSqlDatabase m_db;

    void loadData();
};