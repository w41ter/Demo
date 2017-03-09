#include <vector>
#include <string>
#include <iostream>
#include <functional>

template <typename T, typename E>
struct Callback {
    typedef std::function<void(T)> OnSuccess;
    typedef std::function<void(E)> OnError;

    Callback(OnSuccess s, OnError e) 
        : success(s), error(e) {}
    
    OnSuccess success;
    OnError error;
};

template<class R, class T>
struct Func {
	typedef std::function<R(T)> Call;
	Func(Call c) : call(c) {}

	Call call;
};

template<typename E, typename F>
struct AsycJob {
	typedef std::function<void(Callback<E, F>)> Call;

	AsycJob(Call c) : call(c) {}
	Call call;

	template<class R, class T>
	AsycJob<R, F> map(Func<R, T> func) {
		auto &self = *this;
		return AsycJob<R, F>([func, self](Callback<R, F> call) {
			self.call(Callback<T, F>([func, call](T t) {
				call.success(func.call(t));
			}, [call](F f) {
				call.error(f);
			}));
		});
	}

	template<class R, class T>
	AsycJob<R, F> flatMap(Func<AsycJob<R, F>, T> func) {
		auto &self = *this;
		return AsycJob<R, F>([func, self](Callback<R, F> call) {
			self.call(Callback<T, F>([func, call](T t) {
				AsycJob<R, F> map = func.call(t);
				map.call(Callback<R, F>([call](R r) {
					call.success(r);
				}, [call](F f) {
					call.error(f);
				}));
			}, [call](F f) {
				call.error(f);
			}));
		});
	}
};

struct Cat {
	std::string name;
};

struct Api {
	typedef Callback<std::vector<Cat>, std::string> QueryCatsCallback;
    static void queryCats(std::string name, QueryCatsCallback b) {
		if (name == "cats") {
			b.success({ {"cat1"}, {"cat2"} });
		}
		else {
			b.error("not cat");
		}
    }

	typedef Callback<std::string, std::string> SaveCatsCallback;
	static void saveCat(Cat cat, SaveCatsCallback b) {
		b.success(cat.name);
    }
};

struct ApiWrapper {
	typedef AsycJob<std::vector<Cat>, std::string> queryCatsAsycJob;
	typedef Callback<std::vector<Cat>, std::string> queryCatsCallback;
	static queryCatsAsycJob queryCats(std::string name) {
		typedef std::vector<Cat> Cats;
        return queryCatsAsycJob([name](queryCatsCallback callback) {
            auto call = queryCatsCallback([callback](Cats cats){
                callback.success(cats);
            }, [callback](std::string s) {
                callback.error(s);
            });

			Api::queryCats(name, call);
        });
    }

	typedef AsycJob<std::string, std::string> saveCatAsycJob;
	typedef Callback<std::string, std::string> saveCatCallback;
	static saveCatAsycJob saveCat(Cat cat) {
        typedef Callback<std::string, std::string> Call;
        return saveCatAsycJob([cat](Call call) {
            auto callback = saveCatCallback([call](std::string s) {
                call.success(s);
            }, [call](std::string s) {
                call.error(s);
            });
            Api::saveCat(cat, callback);
        });
    }
};

struct CatsHelper {
    static Cat findCat(std::vector<Cat> cats) {
        return cats[0];
    }

	static AsycJob<std::string, std::string> saveCat(std::string name) {
		typedef std::vector<Cat> Cats;
		typedef Func<Cat, std::vector<Cat>> FindCatFunc;
		typedef Func<AsycJob<std::string, std::string>, Cat> SaveCatFunc;

		auto map = FindCatFunc([](Cats cats) { return findCat(cats); });
		auto flatMap = SaveCatFunc([](Cat cat) { return ApiWrapper::saveCat(cat); });
        return ApiWrapper::queryCats(name)
            .map(map)
            .flatMap(flatMap);
    }
};

int main() {
	auto call = Callback<std::string, std::string>([](std::string s) {
		std::cout << "result : " << s << std::endl;
	}, [](std::string s) {
		std::cout << "error : " << s << std::endl;
	});

    CatsHelper::saveCat("name")
		.call(call);
	CatsHelper::saveCat("cats")
		.call(call);

	return 0;
}