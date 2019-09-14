//懒汉式 （创建的时候采取new实例）以时间换取空间，线程不安全
class Singleton {
private:
	Singleton() {
		cout << "Constructor of the singleton object." << endl;
	}

	~Singleton() { 
		// 必须用私有析构函数，不可以在外部用delete来释放，Singleton消亡时，也不可以调用
		// -->只能通过Garbo对象来析构，作为成员对象的garbo对象析构时，调用Singleton的析构函数把pm释放掉
		// 如果析构函数是public的，（当然这时候应该在析构时释放内存），
		// 那么线程可以显式调用析构函数，这样会导致单例被提前释放了，必然出现错误。
		cout << "Deconstructor of the singleton object." << endl;
	}

	class Garbo {
	public: 
	// 这里必须是public，因为要在外部析构（对象消亡），这里static对象相当于全局对象，在程序结束时析构
	// 发现一个问题，在VS中，如果定义一个对象，必须有public的构造、析构函数
	// 如果是new出来的对象，析构函数可以是private，但是，如果手动delete这个堆指针，依然会编译报错，
	// 综上，析构函数也是成员函数，并且必定是在外部调用的（对象消亡时），要想正确析构这个对象，必须用public析构函数
		~Garbo() {
			if (pm != NULL) {
				cout << "Delete the Singleton." << endl;
				delete pm; // 类内调用Singleton的析构函数
				pm = NULL;
			}
		}
	};

public:
	static Singleton* getInstance() {//为什么这里要用static: 因为单例不允许构造对象，无法访问成员函数
		if(pm==NULL){
			pm = new Singleton();
		}
		return pm;
	}

private:
	static Singleton* pm;
	static Garbo garbo; // 静态对象在类外定义，在main之前构造
};

Singleton::Garbo Singleton::garbo;//类外定义, 全局对象在程序结束时会被自动调用
Singleton* Singleton::pm = NULL;//类外定义


// 懒汉式，线程安全，C++标准版
// 双检锁，实际不能保证线程安全，因为sm_pInstance = new Singleton();

class Singleton {
private:
	Singleton() {
		cout << "Constructor of the singleton object." << endl;
	}
	~Singleton() {
		cout << "Deconstructor of the singleton object." << endl;
	}

private:
	class Garbo {
	public:
		~Garbo() {
			if (sm_pInstance != NULL) {
				cout << "Garbo deconstruct the singleton object." << endl;
				delete sm_pInstance;
				sm_pInstance = NULL;
			}
		}
	};

public:
	static Singleton* getInstance() {
		if (sm_pInstance == NULL) {
			sm_mutex.lock(); // TODO： 会不会发生锁竞争
			if (sm_pInstance == NULL) // 进入临界区，再次检查，确保安全
				sm_pInstance = new Singleton(); // 不能保证安全，因为：
			// new一个对象，逻辑上的顺序是，先申请空间，然后构造对象，最后返回指针；
			// 但是可能因为编译器的优化，实际执行顺序是，先申请空间，然后返回指针，最后构造对象，
			// 在返回指针之后，上面的语句就已经返回了，
			sm_mutex.unlock();
		}
		return sm_pInstance;
	}

private:
	static Singleton* sm_pInstance;
	static Garbo sm_garbo;
	static mutex sm_mutex;
};

Singleton* Singleton::sm_pInstance=NULL;
Singleton::Garbo Singleton::sm_garbo;
mutex Singleton::sm_mutex;


//懒汉式 线程安全式（双检锁）
//Linux版
class Singleton_L_Lock {
private:
	Singleton_L_Lock() {
		cout << "Constructor of the singleton object." << endl;
	}
	~Singleton_L_Lock() {
		cout << "Deconstructor of the singleton object." << endl;
	}

	class GGarbo {
	public:
		~GGarbo() {
			if (pm != NULL) {
				cout << "Garbo deconstructs the single object." << endl;
				delete pm;
				pm = NULL;
			}
		}
	};

public:
	static Singleton_L_Lock* getInstance() {
		if (pm == NULL) {//因为加锁非常耗时，并且因为实例只会创建一次，所以只需要在实例还没有创建的时候加锁，之后就不需要再加锁了（也不需要再创建实例了），直接return这个实例即可。
			pthread_mutex_lock(&mutex);
			if (pm == NULL)
				pm = new Singleton_L_Lock;
			pthread_mutex_unlock(&mutex);
		}
		return pm;
	}

private:
	static Singleton_L_Lock* pm;
	static pthread_mutex_t mutex;
	static GGarbo garbo;
};

Singleton_L_Lock::GGarbo Singleton_L_Lock::garbo;
pthread_mutex_t Singleton_L_Lock::mutex;
Singleton_L_Lock* Singleton_L_Lock::pm = NULL;

// 双检锁存在数据竞争
// 这是由于编译器的优化，可能的执行顺序是：申请内存，返回指针，构造对象
// 改进为 std::call_once或者返回一个static变量，C++11保证了初始化不存在竞争
// @Athor zzg
// static局部变量
// TODO: 正确吗？
class Singleton {
	Singleton() {
		cout << "Singleton()" << endl;
	}
	~Singleton() { // 为什么作为private也可以被析构呢？
		cout << "~Singleton()" << endl;
	}
public:
	static Singleton* getInstance() {
		static Singleton instance; // static局部变量在C++11是线程安全的，static全局只有一份，所以是单例
		return &instance;
	}
};

// @Athor zzg
// std::call_once和std::once_flag
class Singleton {
	static Singleton* instance;
	static std::once_flag init_flag;

	Singleton() {
		cout << "Singleton()" << endl;
	}
	~Singleton() {
		cout << "~Singleton()" << endl;
	}

	static void getInit() {
		instance = new Singleton;
	}

	class Garbo {
	public:
		~Garbo() {
			delete instance;
		}
	};
	static Garbo garbo;

public:
	static Singleton* getInstance() {
		std::call_once(init_flag, &Singleton::getInit);
		return instance;
	}
};

// 必须在头文件中定义static变量
Singleton* Singleton::instance = nullptr;
std::once_flag Singleton::init_flag;
Singleton::Garbo Singleton::garbo;


// 饿汉式，以空间换时间
// 由于饿汉式在main函数之前就实例化了，此时还是单线程环境，所以本身就是线程安全的
class Singleton_E {
private:
	Singleton_E() {
		cout << "Construtor of the singleton object." << endl;
	}
	~Singleton_E() {
		cout << "Deconstrctor of the singleton object." << endl;
	}

	class Garbo_E {
	public:
		~Garbo_E() {
			cout << "Garbo deconstructor the singleton object." << endl;
			if (pm != NULL) {
				delete pm;
				pm = NULL;
			}
		}
	};

public:
	static Singleton_E* getInstance() {
		return pm;
	}

private:
	static Singleton_E *pm;
	static Garbo_E garbo_e;
};

Singleton_E* Singleton_E::pm = new Singleton_E();
Singleton_E::Garbo_E Singleton_E::garbo_e;



int main() {
	Singleton* p=Singleton::getInstance();
	//delete p;//这样也不会报错？？？？怎么避免，需不需要避免？如果p=NULL，如果p=野指针;-->把Singleton的析构函数定义为私有
	//delete p;//不允许delete两次
	Singleton_E p_e=Singleton_E::getInstance();

	return 0;
}


