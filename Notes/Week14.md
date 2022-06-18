# 4주차 (22. 05. 24)
[Notion Link](https://www.notion.so/4-22-05-24-cd21a9098777480ca0bc08308a8a31cc)

### **atomic**

멀티스레드 환경에서 뮤텍스와 같이 lock, unlock을 사용하지 않고 값을 증감시킬 수 있는 기능을 제공하는 변수.

atomic 변수는 초기에만 값을 대입할 수 있고, 이후에는 증가, 감소 역할만 수행한다.

### C++ 20 문법

**concepts** : template에 대한 특정 제약에 이름을 붙이는 용도로 사용.

**requires** : concept bool을 반환. 템플릿에 대한 타입 제한을 위한 기능.

**enable_if**

```cpp
template <bool B, class T = void>
using enable_if_t = typename enable_if<B,T>::type;
```

특정한 타입들에게만 작동하는 template을 작성할 때 사용.

멀티플랫폼 사용 시 allocator가 할당할 플랫폼에 맞추어 전처리 나누어서 할당하는 방법.

dll로 export하려면 dllexport에 맞는 지시문을 붙여주어야 한다.

### concept ↔ is_convertible

is_convertible은 서로 변환 가능한 두 타입인지 아닌 지에 대해 참 거짓을 반환.

기존의 template 정의 시 제약 조건을 추가해야 할 때 변환 가능하다면 그에 대한 operator를 정의하는 등의 방식으로 자주 사용된다.

### template에서 typename / class 차이

```cpp
template<class T> class A;
template<typename T> class B;
```

참고자료 : [https://wikidocs.net/433](https://wikidocs.net/433)

template에서 typename과 class의 차이는 없다. (C++17 이상부터 중첩문에서 유효하지 않던 이슈도 변경되었다.) 그러나 template 정의 시가 아닌 template type에 typename 키워드를 사용할 때에는 주의할 사항들이 있다. 기본적으로 의존적인 이름(type을 나타낸다)이고 한정된 이름이어야 한다.

기반 클래스 이름이나 멤버 초기화 리스트에서는 사용할 수 없다.

### args

`void print(T arg, Types... args) {`

가변 길이 템플릿(Variadic template) 기능 중 하나. 함수에 인자로 … args를 받으면 추론된 인자를 제외한 나머지 인자를 자동적으로 나타낸다.

가변 길이 템플릿은 `template <typename T, typename... Types>` 와 같이 작성하여 사용한다. … 뒤에 오는 것을 템플릿 파라미터 팩(parameter pack) 이라 하며, 0개 이상의 템플릿 인자를 나타낸다.

### **mutable**

const 함수에서도 변경 가능하도록 만들어주는 키워드이다.

const 함수는 기본적으로 기존의 값들을 변경하지 않고, 내부 함수 내에서 선언된 값들만 변경할 수 있다. 이때 기존 값 중 mutable 키워드가 붙은 경우에는 예외적으로 변경할 수 있도록 하는 것이다.

### GPU Buffer

DirectX에서는 Buffer가 Resource이다.

메모리에 맞추어 Align이 되어있지 않으면 오류를 발생시킨다.