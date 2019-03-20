//懒汉式 （创建的时候采取new实例）以时间换取空间，线程不安全
class Singleton {
private:
	Singleton() {
		cout << "Constructor of the singleton object." << endl;
	}

	~Singleton() {
		cout << "Deconstructor of the singleton object." << endl;
	}

	class Garbo {
	public:
		~Garbo() {
			if (pm != NULL) {
				cout << "Delete the Singleton." << endl;
				delete pm;
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
	static Garbo garbo;
};

Singleton::Garbo Singleton::garbo;//类外定义, 全局对象在程序结束时会被自动调用
Singleton* Singleton::pm = NULL;//类外定义


//懒汉式，线程安全，C++标准版
class Singleton {
private:
	Singleton() {
		file_name = "output1.txt";
		ofstream out(file_name);
		cout << "Constructor of the singleton object." << endl;
		out << "Constructor of the singleton object." << endl;
		out.close();
	}
	~Singleton() {
		ofstream out(file_name,ofstream::app);
		cout << "Deconstructor of the singleton object." << endl;
		out << "Deconstructor of the singleton object." << endl;
		out.close();
	}

private:
	string file_name;

	class Garbo {
	public:
		~Garbo() {
			if (sm_pInstance != NULL) {
				ofstream out("output1.txt", ofstream::app);
				cout << "Garbo deconstruct the singleton object." << endl;
				out << "Garbo deconstruct the singleton object." << endl;
				out.close();
				delete sm_pInstance;
				sm_pInstance = NULL;
			}
		}
	};

public:
	static Singleton* getInstance() {
		if (sm_pInstance == NULL) {
			sm_mutex.lock();
			if (sm_pInstance == NULL)
				sm_pInstance = new Singleton();
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


//饿汉式，以空间换时间，不涉及线程安全
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