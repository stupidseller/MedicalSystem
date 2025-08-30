#include "user_dao.h"
#include "app_database.h"
#include "crypto_utils.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

static QDateTime fromMs(qint64 ms) { return QDateTime::fromMSecsSinceEpoch(ms, Qt::UTC); }
static qint64    toMs (const QDateTime& dt){ return dt.toMSecsSinceEpoch(); }

UserEntity UserDao::mapRow(const QSqlQuery& q){
    UserEntity u;
    u.userId          = q.value("user_id").toLongLong();
    u.userType        = userTypeFromString(q.value("user_type").toString());
    u.name            = q.value("name").toString();
    u.gender          = genderFromString(q.value("gender").toString());
    u.birthDate       = QDate::fromString(q.value("birth_date").toString(), Qt::ISODate);
    u.idCard          = q.value("id_card").toString();
    u.phone           = q.value("phone").toString();
    u.email           = q.value("email").toString();
    u.passwordEncoded = q.value("password").toString();
    u.createdAt       = fromMs(q.value("created_at").toLongLong());
    u.updatedAt       = fromMs(q.value("updated_at").toLongLong());
    return u;
}

QList<UserEntity> UserDao::getAll() const {
    QList<UserEntity> v; QSqlQuery q(AppDatabase::instance().db());
    q.setForwardOnly(true);
    if (q.exec("SELECT * FROM users ORDER BY user_id")) while(q.next()) v.append(mapRow(q));
    return v;
}

QList<UserEntity> UserDao::getByType(UserType t) const {
    QList<UserEntity> v; QSqlQuery q(AppDatabase::instance().db());
    q.prepare("SELECT * FROM users WHERE user_type=:t ORDER BY user_id");
    q.bindValue(":t", toString(t));
    if (q.exec()) while(q.next()) v.append(mapRow(q));
    return v;
}

std::optional<UserEntity> UserDao::getById(qint64 id) const {
    QSqlQuery q(AppDatabase::instance().db());
    q.prepare("SELECT * FROM users WHERE user_id=:id"); q.bindValue(":id", id);
    if (!q.exec() || !q.next()) return std::nullopt; return mapRow(q);
}

std::optional<UserEntity> UserDao::getByEmail(const QString& email) const {
    QSqlQuery q(AppDatabase::instance().db());
    q.prepare("SELECT * FROM users WHERE email=:e"); q.bindValue(":e", email);
    if (!q.exec() || !q.next()) return std::nullopt; return mapRow(q);
}

qint64 UserDao::insert(UserEntity u, QString* err) {
    // 由 DB 触发器填 updated_at；created_at 默认表达式填充
    // 若未提供 passwordEncoded，则根据明文 name 当示例生成（实际应来自调用方）
    if (u.passwordEncoded.isEmpty()) u.passwordEncoded = encodePassword("ChangeMe123!");

    QSqlQuery q(AppDatabase::instance().db());
    q.prepare(
      "INSERT INTO users (user_type,name,gender,birth_date,id_card,phone,email,password)"
      " VALUES (:t,:n,:g,:bd,:idc,:ph,:em,:pwd)");
    q.bindValue(":t",  toString(u.userType));
    q.bindValue(":n",  u.name);
    q.bindValue(":g",  toString(u.gender).isEmpty()? QVariant(QVariant::String): toString(u.gender));
    q.bindValue(":bd", u.birthDate.isValid()? u.birthDate.toString(Qt::ISODate): QVariant(QVariant::String));
    q.bindValue(":idc",u.idCard);
    q.bindValue(":ph", u.phone);
    q.bindValue(":em", u.email);
    q.bindValue(":pwd",u.passwordEncoded);

    if (!q.exec()) { if (err) *err = q.lastError().text(); return 0; }
    return q.lastInsertId().toLongLong();
}

bool UserDao::update(const UserEntity& u, QString* err) {
    QSqlQuery q(AppDatabase::instance().db());
    q.prepare(
      "UPDATE users SET user_type=:t, name=:n, gender=:g, birth_date=:bd,"
      " id_card=:idc, phone=:ph, email=:em WHERE user_id=:id");
    q.bindValue(":t",  toString(u.userType));
    q.bindValue(":n",  u.name);
    q.bindValue(":g",  toString(u.gender).isEmpty()? QVariant(QVariant::String): toString(u.gender));
    q.bindValue(":bd", u.birthDate.isValid()? u.birthDate.toString(Qt::ISODate): QVariant(QVariant::String));
    q.bindValue(":idc",u.idCard);
    q.bindValue(":ph", u.phone);
    q.bindValue(":em", u.email);
    q.bindValue(":id", u.userId);

    if (!q.exec()) { if (err) *err = q.lastError().text(); return false; }
    return q.numRowsAffected() > 0;
}

bool UserDao::remove(qint64 id, QString* err) {
    QSqlQuery q(AppDatabase::instance().db());
    q.prepare("DELETE FROM users WHERE user_id=:id"); q.bindValue(":id", id);
    if (!q.exec()) { if (err) *err = q.lastError().text(); return false; }
    return q.numRowsAffected() > 0;
}

bool UserDao::setPassword(qint64 id, const QString& plain, QString* err) {
    const QString enc = encodePassword(plain);
    QSqlQuery q(AppDatabase::instance().db());
    q.prepare("UPDATE users SET password=:p WHERE user_id=:id");
    q.bindValue(":p", enc); q.bindValue(":id", id);
    if (!q.exec()) { if (err) *err = q.lastError().text(); return false; }
    return q.numRowsAffected() > 0;
}

std::optional<UserEntity> UserDao::authenticate(const QString& email, const QString& plain) const {
    if (auto u = getByEmail(email)) {
        if (verifyPassword(plain, u->passwordEncoded)) return u;
    }
    return std::nullopt;
}
