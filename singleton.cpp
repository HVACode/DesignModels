#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

namespace npSimple
{
	class Singleton
	{
	public:
		static Singleton *getInstance()
		{
			if (nullptr == pInstance)
			{
				// std::cout << "new Singleton" << std::endl;
				pInstance = new Singleton();
			}
			return pInstance;
		}

	private:
		Singleton()
		{
			std::cout << "simple::Singleton()" << std::endl;
		}

	private:
		static Singleton *pInstance;
	};
	Singleton *Singleton::pInstance = nullptr;

}

namespace npThreadsSingleton
{
	class Singleton
	{
	public:
		static Singleton *getInstance()
		{
			if (nullptr == pInstance)
			{
				// std::cout << "new Singleton" << std::endl;
				pInstance = new Singleton();
			}
			return pInstance;
		}

	private:
		Singleton()
		{
			std::cout << "threads::Singleton()" << std::endl;
		}

	private:
		static Singleton *pInstance;
	};
	Singleton *Singleton::pInstance = nullptr;

	void *ThreadFunc(void *pArg)
	{
		Singleton *p = Singleton::getInstance();
		pthread_exit(NULL);
	}

}

/// @brief 简单加锁实例化的单例模式
namespace npInitLock
{
	pthread_mutex_t lock;

	class Singleton
	{
	public:
		static Singleton *getInstance()
		{
			pthread_mutex_lock(&lock); // 总是加锁再判断
			if (nullptr == pInstance)
			{
				pInstance = new Singleton();
			}
			pthread_mutex_unlock(&lock);
			return pInstance;
		}

	private:
		Singleton()
		{
			std::cout << "initlock::Singleton()" << std::endl;
		}

		static Singleton *pInstance;
	};

	Singleton *Singleton::pInstance = nullptr;

	void *ThreadFunc(void *pArg)
	{
		Singleton *p = Singleton::getInstance();

		pthread_exit(NULL);
	}

}

/// @brief 双重锁定的单例模式
namespace npDoubleCheckSingleton
{
	pthread_mutex_t lock;

	class Singleton
	{
	public:
		static Singleton *getInstance()
		{
			if (nullptr == pInstance) // 减少加锁的时间
			{
				pthread_mutex_lock(&lock);
				if (nullptr == pInstance) // 必须要二次判断
				{
					// std::cout << "new Singleton" << std::endl;
					pInstance = new Singleton();
				}
				pthread_mutex_unlock(&lock);
			}
			return pInstance;
		}

	private:
		Singleton()
		{
			std::cout << "doubleCheck::Singleton()" << std::endl;
		}

		static Singleton *pInstance;
	};

	Singleton *Singleton::pInstance = nullptr;

	void *ThreadFunc(void *pArg)
	{
		Singleton *p = Singleton::getInstance();

		pthread_exit(NULL);
	}

}

/// @brief 饿汉模式的单例类（加载初始化对象）
namespace npHungrySingleton
{
	class Singleton
	{
	public:
		static Singleton *getInstance()
		{
			return pInstance;
		}

	private:
		Singleton()
		{
			std::cout << "hungry::Singleton()" << std::endl;
		}

		static Singleton *pInstance;
	};

	Singleton *Singleton::pInstance = new Singleton();

	void *ThreadFunc(void *pArg)
	{
		Singleton *p = Singleton::getInstance();

		pthread_exit(NULL);
	}
}

/// @brief C++11后的
/// 如果变量在初始化时，并发线程同时进入到static声明语句，并发线程会阻塞等待初始化结束。
namespace npLocalStaticSingleton
{
	class Singleton
	{
	public:
		static Singleton *getInstance()
		{
			static Singleton instance;
			return &instance;
		}

	private:
		Singleton()
		{
			std::cout << "localStatic::Singleton()" << std::endl;
		}
	};
	void *ThreadFunc(void *pArg)
	{
		Singleton *p = Singleton::getInstance();

		pthread_exit(NULL);
	}
}

// int main(void)
// {
// 	npSimple::Singleton *p1 = npSimple::Singleton::getInstance();
// 	npSimple::Singleton *p2 = npSimple::Singleton::getInstance();

// 	return 0;
// }

// /// @brief 简单单例可能在多线程环境下失效，而创建多个实例
// int main(void)
// {
// 	pthread_t threaId;
// 	pthread_create(&threaId, NULL, npThreadsSingleton::ThreadFunc, NULL);
// 	npThreadsSingleton::Singleton *p = npThreadsSingleton::Singleton::getInstance();
// 	sleep(1);
// 	return 0;
// }

// /// @brief 相比双重锁定，这种先加锁再判断的单例耗时更多
// int main(void)
// {
// 	pthread_t threaId;
// 	struct timeval start, end;

// 	gettimeofday(&start, NULL);

// 	for (std::size_t i = 0; i < 1000; ++i)
// 	{

// 		pthread_create(&threaId, NULL, npInitLock::ThreadFunc, NULL);
// 		npInitLock::Singleton *p = npInitLock::Singleton::getInstance();
// 	}

// 	gettimeofday(&end, NULL);

// 	time_t s = end.tv_sec - start.tv_sec;
// 	time_t us = end.tv_usec - start.tv_usec;
// 	if (us < 0)
// 	{
// 		us += 1000000;
// 		s--;
// 	}
// 	printf("total time: %ld s %ld us\n", s, us);

// 	return 0;
// }

// /// @brief 双重锁定的单例避免了在多线程环境下可能创建多个实例的情况
// int main(void)
// {
// 	pthread_t threaId;
// 	struct timeval start, end;

// 	gettimeofday(&start, NULL);

// 	for (std::size_t i = 0; i < 1000; ++i)
// 	{

// 		pthread_create(&threaId, NULL, npDoubleCheckSingleton::ThreadFunc, NULL);
// 		npDoubleCheckSingleton::Singleton *p = npDoubleCheckSingleton::Singleton::getInstance();
// 	}

// 	gettimeofday(&end, NULL);

// 	time_t s = end.tv_sec - start.tv_sec;
// 	time_t us = end.tv_usec - start.tv_usec;
// 	if (us < 0)
// 	{
// 		us += 1000000;
// 		s--;
// 	}
// 	printf("total time: %ld s %ld us\n", s, us);

// 	return 0;
// }

/// @brief 饿汉模式的单例
// int main(void)
// {
// 	pthread_t threaId;
// 	pthread_create(&threaId, NULL, npHungrySingleton::ThreadFunc, NULL);
// 	npHungrySingleton::Singleton *p = npHungrySingleton::Singleton::getInstance();
// 	sleep(1);
// 	return 0;
// }

/// @brief 局部静态量特性实现线程安全的单例模式
int main(void)
{
	pthread_t threaId;
	pthread_create(&threaId, NULL, npLocalStaticSingleton::ThreadFunc, NULL);
	npLocalStaticSingleton::Singleton *p = npLocalStaticSingleton::Singleton::getInstance();
	sleep(1);
	delete p;
	p = nullptr;
	return 0;
}