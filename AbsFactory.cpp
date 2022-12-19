#include <iostream>
#include <string>

class User
{
public:
	User(std::size_t id = 1, std::string name = "default") : m_UserId(id), m_UserName(name) {}
	void setId(std::size_t id)
	{
		m_UserId = id;
	}
	std::size_t getId()
	{
		return m_UserId;
	}
	void setName(std::string name)
	{
		m_UserName = name;
	}
	std::string getName()
	{
		return m_UserName;
	}

private:
	std::size_t m_UserId;
	std::string m_UserName;
};

class Department
{
public:
	Department(std::size_t id = 1, std::string name = "default") : m_UserId(id), m_UserName(name) {}

	void setId(std::size_t id)
	{
		m_UserId = id;
	}
	std::size_t getId()
	{
		return m_UserId;
	}
	void setName(std::string name)
	{
		m_UserName = name;
	}
	std::string getName()
	{
		return m_UserName;
	}

private:
	std::size_t m_UserId;
	std::string m_UserName;
};

class DBuser
{
public:
	virtual void Insert(User user) = 0;
	virtual User getUser(std::size_t id) = 0;
	virtual ~DBuser() = default;
};

class DBdepart
{
public:
	virtual void Insert(Department depart) = 0;
	virtual Department getDepart(std::size_t id) = 0;
	virtual ~DBdepart() = default;
};

class SqlServerUser : public DBuser
{
public:
	void Insert(User user) override
	{
		std::cout << "SQL Server 中 给User表加入一条记录: " << std::endl;
	}
	User getUser(std::size_t id) override
	{
		std::cout << "SQL Server 中 从User表返回用户Id对应的记录: " << std::endl;
		return User();
	}
};

class SqlServerDepart : public DBdepart
{
public:
	void Insert(Department depart) override
	{
		std::cout << "SQL Server 中 给 Department 表加入一条记录: " << std::endl;
	}
	Department getDepart(std::size_t id) override
	{
		std::cout << "SQL Server 中 从 Department 表返回用户Id对应的记录: " << std::endl;
		return Department();
	}
};

class AccessUser : public DBuser
{
public:
	void Insert(User user) override
	{
		std::cout << "Access 中 给User表加入一条记录: " << std::endl;
	}
	User getUser(std::size_t id) override
	{
		std::cout << "Access 中 从User表返回用户Id对应的记录: " << std::endl;
		return User();
	}
};

class AccessDepart : public DBdepart
{
public:
	void Insert(Department depart) override
	{
		std::cout << "Access 中 给 Department 表加入一条记录: " << std::endl;
	}
	Department getDepart(std::size_t id) override
	{
		std::cout << "Access 中 从 Department 表返回用户Id对应的记录: " << std::endl;
		return Department();
	}
};

class IFactory
{
public:
	virtual DBuser *CreateUser() = 0;
	virtual DBdepart *CreateDepartment() = 0;
	virtual ~IFactory() = default;
};

class SqlFactory : public IFactory
{
public:
	DBuser *CreateUser() override
	{
		return new SqlServerUser();
	}
	DBdepart *CreateDepartment() override
	{
		return new SqlServerDepart();
	}
};

class AccessFactory : public IFactory
{
public:
	DBuser *CreateUser() override
	{
		return new AccessUser();
	}
	DBdepart *CreateDepartment() override
	{
		return new AccessDepart();
	}
};

/// @brief 可用于取代工厂类
class DataAccess
{
public:
	static DBuser *CreateUser()
	{

		if ("Sqlserver" == m_strDb)
		{
			return new SqlServerUser();
		}
		else if ("Access" == m_strDb)
		{
			return new AccessUser();
		}
	}
	static DBdepart *CreateDepartment()
	{
		if ("Sqlserver" == m_strDb)
		{
			return new SqlServerDepart();
		}
		else if ("Access" == m_strDb)
		{
			return new AccessDepart();
		}
	}

private:
	static std::string m_strDb;
};
int main()
{
	User *user = new User();
	Department *depart = new Department();
	IFactory *factory = new AccessFactory();

	DBuser *db = factory->CreateUser();
	db->Insert(*user);
	db->getUser(1);

	DBdepart *dbdepart = factory->CreateDepartment();
	dbdepart->Insert(*depart);
	dbdepart->getDepart(1);

	delete user;
	user = nullptr;
	delete depart;
	depart = nullptr;
	delete factory;
	factory = nullptr;
	delete db;
	db = nullptr;
	delete dbdepart;
	dbdepart = nullptr;
	return 0;
}