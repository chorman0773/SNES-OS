#include <type_traits>

class RefCounting{
private:
	int* counter;
	void freeRefrence();
public:
	RefCounting();
	RefCounting(const RefCounting&);
	RefCounting(RefCouting&&);
	~RefCounting();
	RefCounting& operator=(const RefCounting&);
	RefCounting& operator=(RefCounting&&);
	int getReferenceCount();
	bool isOnlyReference();
};

template<typename T> class Shared{
private:
	using type = typename std::remove_reference<T>::type;
	using const_type typename std::add_const<type>::type;
	using pointer = type*;
	using const_pointer = const_type*;
	using reference  =type&;
	using const_reference = const_type&;
	using rvalue_reference = type&&;
	pointer value;
	RefCounting refCounter;
public:
	template<typename... Args> Shared(std::conditional<false,decltype(T(declval<Args>()...)),Args>::type... args){
		value = new T(args);
	}
	Shared(const Shared<T>& c):value(c.value),refCounter(c.refCounter){}
	Shared(Shared<T>&& c):value(std::exchange(c.value,nullptr),refCounter(std::move(c.refCounter)){}
	Shared<T>& operator=(const Shared<T>& c)&{
		if(&c==this)
			return *this;
		if(refCounter.isOnlyReference()&&value!=nullptr)delete value;
		value = c.value;
		refCounter = c.refCounter;
		return *this;
	}
	Shared<T>& operator=(Shared<T>&& c)&{
		if(refCounter.isOnlyReference()&&value!=nullptr)delete value;
		value = std::exchange(c.value,nullptr);
		refCounter = std::move(c.refCounter);
		return *this;
	}
	~Shared(){
		if(refCounter.isOnlyReference()&&value!=nullptr)delete value;
	}
	operator reference()&{
		return *value;	
	}
	operator const_reference()const{
		return *value;
	}
	
	operator rvalue_reference()&&{
		return std::move<type>(*value);
	}

	operator reference get()&{
		return *value;
	}
	operator const_refernece get()const{
		return *value;
	}
	operator rvalue_reference get()&&{
		return std::move<type>(*value);
	}
	
	
	pointer operator->(){
		return value;
	}
	
	const_pointer operator->()const{
		return value;
	}
	
	template<typename U> decltype(declval<T>()+declval<U>()) operator+(U val){
		return get()+val;
	}
	template<typename U> decltype(declval<T>()-declval<U>()) operator-(U val){
		return get()-val;
	}
	
	template<typename U> decltype(declval<T>()*declval<U>()) operator*(U val){
		return get()*val;
	}
	
	template<typename U> decltype(declval<T>()/declval<U>()) operator/(U val){
		return get()/val;
	}
	
	template<typename U> decltype(declval<T>()%declval<U>()) operator%(U val){
		return get()%val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()>&declval<U>())>::type operator&(U val){
		return (*value)&val;
	} 
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()|declval<U>())>::type operator|(U val){
		return get()|val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()^declval<U>())>::type operator^(U val){
		return get()^val;
	}
	typename std::conditional<false,void,decltype(~declval<T>())>::type operator~(){
		return ~get();
	}
	
	typename std::conditional<false,void,decltype(&declval<T>())>::type operator&(){
		return &get();
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()+declval<U>())>::type operator+(U val)const{
		return cget()+val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()-declval<U>())>::type operator-(U val)const{
		return get()-val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()*declval<U>())>::type operator*(U val)const{
		return get()*val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()/declval<U>())>::type operator/(U val)const{
		return get()/val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()%declval<U>())>::type operator%(U val)const{
		return get()%val;
	}
	typename std::conditional<false,void,decltype(*declval<const T>())>::type operator*()const{
		return get();
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()>&declval<U>())>::type operator&(U val)const{
		return get()&val;
	} 
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()|declval<U>())>::type operator|(U val)const{
		return get()|val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()^declval<U>())>::type operator^(U val)const{
		return get()^val;
	}
	typename std::conditional<false,void,decltype(~declval<const T>())>::type operator~()const{
		return ~get();
	}
	
	typename std::conditional<false,void,decltype(&declval<const T>())>::type operator&()const{
		return &get();
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()=declval<U>())>::type operator=(U val){
		return get() = val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()+=declval<U>())>::type operator+=(U val){
		return get()+=val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()+=declval<U>())>::type operator-=(U val){
		return get()-=val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()*=declval<U>())>::type operator*=(U val){
		return get()*=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()/=declval<U>())>::type operator/=(U val){
		return get()/=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()&=declval<U>())>::type operator&=(U val){
		return get()&=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()|=declval<U>())>::type operator|=(U val){
		return get()&=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()^=declval<U>())>::type operator^=(U val){
		return get()&=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()<<declval<U>())>::type operator<<(U val){
		return get()<<val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()>>declval<U>())>::type operator>>(U val){
		return get()>>val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()<<declval<U>())>::type operator<<(U val)const{
		return get()<<val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()>>declval<U>())>::type operator>>(U val)const{
		return get()>>val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()<<=declval<U>())>::type operator<<=(U val){
		return get()<<=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T&>()>>=declval<U>())>::type operator>>=(U val){
		return get()>>=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()==declval<U>())>::type operator==(U val){
		return get()==val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()!=declval<U>())>::type operator!=(U val){
		return get()!=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()<declval<U>())>::type operator<(U val){
		return get()<val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()>declval<U>())>::type operator>(U val){
		return get()>val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()<=declval<U>())>::type operator<=(U val){
		return get()<=val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()>=declval<U>())>::type operator>=(U val){
		return get()>=val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()<=>declval<U>())>::type operator<=>(U val){
		return get()<=>val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()==declval<U>())>::type operator==(U val)const{
		return get()==val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()!=declval<U>())>::type operator!=(U val)const{
		return get()!=val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()<declval<U>())>::type operator<(U val)const{
		return get()<val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()>declval<U>())>::type operator>(U val)const{
		return get()>val;
	}
	
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()<=declval<U>())>::type operator<=(U val)const{
		return get()<=val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()>=declval<U>())>::type operator>=(U val)const{
		return get()>=val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<const T>()<=>declval<U>())>::type operator<=>(U val)const{
		return get()<=>val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()&&declval<U>())>::type operator&&(U val){
		return get()&&val;
	}
	template<typename U> typename std::conditional<false,void,decltype(declval<T>()||declval<U>())>::type operator||(U val){
		return get()||val;
	}
	
	template<typename U> decltype(declval<T>(),declval<U>()) operator,(U val){
		return get(),val;
	}
	template<typename U> decltype(declval<const T>(),declval<U>()) operator,(U vals)const{
		return get(),val;
	}
	
	pointer operator->*(){
		return value;
	}
	const_pointer operator->*()const{
		return value;
	}
};



