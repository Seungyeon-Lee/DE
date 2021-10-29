[Notion Link](https://www.notion.so/2-de91b25e2d604c55aaa0b9e9ae8ecb8d)

## Code Review

**전방선언 (Forward declarations)**

header에는 최대한 include를 안하는게 좋다.

쌍방으로 include 참조할 경우 컴파일 오류가 난다.

참조를 할 때, 레퍼런스 타입인 경우에는 4byte or 8byte이기때문에 인클루드를 안해도 전방선언을 하게 되면 나중에 확인한다.

header에서는 include를 하지 않고, cpp에서 include를 한다.

**friend 함수**

a에 대한 Operator *를 선언한 경우

a * f만 사용가능하다.

f * a가 동작 가능하도록 만들기 위해서 friend declearation를 사용한다.

항상 inline이어야만 한다는 조건이 있다.

header에서 선언을 하고, 정의는 cpp에서 한다.

반환 타입이 &레퍼런스일 때는 inline이 되지않는다.

inline 키워드 사용 시 컴파일러에 따라서 다르게 동작한다.

함수 내에서 함수를 쓰는 경우 call 비용이 들어간다.

따라서 직접 풀어서 써주는 비용이 조금 더 싸므로, 일부러 함수 내부에서 함수 호출을 하지 않고 직접 써주는 경우가 있다. (단, 컴파일러에 따라서 알아서 inline으로 만들어주는 경우가 있다. 이 경우는 컴파일러의 성능에 좌우된다)

* volatile 키워드를 사용하면 컴파일러가 알아서 최적화하지 않고 개발자가 작성한 코드 그대로 컴파일하도록 만든다.

**rvo = return type value optimize**

이름 있는 r, 이름 없는 r value

생성 시에 생성 비용 + 복사 비용이 들어간다. 

⇒ 따라서 생성 비용만 들어가도록 완전히 같은 것으로 대체하는 방식이다.

**.editorconfig**

파일을 만들 때마다 Encoding 타입을 utf-8로 고정하고 싶을 때 등, 에디터의 구성을 적어두는 파일이다.

## Graphics

**Antialiasing**

`초과표본화(super sampling, SSAA)`는 실제로 정확도가 매우 높다.

그러나 렌더링할 때 gpu에서 제일 느린 부분이 픽셀쉐이더이다.

즉, 4배로 그리는 것은 연산이 매우 많기때문에 실제로는 사용하지 않는다.

따라서 해당 초과표본화를 개선한 것이 `다중표본화(multisampling, MSAA)`이다.

다중표본화는 직전에 계산했던 것을 바탕으로 캐싱해두고 갖다쓴다. 초과표본화보다는 조금 더 최적화되었다. 그러나 디퍼드 렌더링 (지연 렌더링)하는 과정에서 MSAA를 사용하기는 힘들다.

**Double Buffering**

렌더 타겟을 2개 이상써서 계속 그려지는 과정이 보여지는 것을 방지하는 것.

프론트 버퍼에선 화면을 보여주고, 백 버퍼에서는 계속 그린다.

**Depth Buffer**

3d 공간에서 z(깊이)값을 기준으로 위에 그려질지, 밑에 그려질지를 결정한다.

컬러속성이 1개밖에 없다. 0~1 사이의 값.

0은 가깝고, 1이 멀다.

화면에 그릴지 말지를 판별한다. (뒤에 있는 것은 그릴 필요없으므로)

**Stencil Buffer**

Depth Buffer를 만들고 남은 Memory Buffer를 Stencil Buffer로 쓰는 경우가 많다.

Image Masking을 만들때 유용하다.

## DirectX 12 API

**COM (Component Object Model)**

ms에서 제공하는 com 객체

바이너리 표준을 지키기 위해 만들어진 오브젝트

**IUnknown**

ReferenceCount를 관리한다.

IUnknown을 편하게 사용하도록 (스마트 포인터와 비슷하도록) ComPtr이 만들어졌다.

우리가 만든 객체는 comptr을 사용하지 않아도 된다.

하지만 DirectX 객체를 사용하려는 경우에는 comptr을 사용해야 한다.

**Device**

DirectX 관련 객체를 생성할 때 사용한다.

**Resource**

Resource는 GPU에서는 texture나 buffer를 의미한다.

Resource는 아래의 명령어로 생성한다.

`CreateCommittedResource()`

**Descriptor**

서술자 : 만들어준 Resource에 대해서 정보를 가지고 있는 자료구조

Descriptor + Resource를 binding해서 사용하는 형태로 사용한다.

실제로 사용 시에는 리소스를 다이렉트로 사용하는게 아니라 서술자에 접근하고 사용하는 식이다.

**Descriptor heap**

서술자가 엄청 많을 때 서술자 힙에 등록한다.

해당 힙을 GPU에 binding해서 사용한다.

**리소스 생성 순서**

서술자 힙 생성 → 리소스 생성 (보통 heap 타입을 디폴트로 생성한다. 이 때, CPU에서 접근할 수 없고 GPU에 메모리가 있다. 따라서 CPU를 거치지 않기 때문에 이 모드가 제일 속도가 빠르다) → 서술자 생성 (리소스를 가리키도록 생성한다)

DirectX에서는 descriptor를 view라고 말한다. (어떤 것을 바라보는 방식 - 서술자)

Resource마다 state가 저장되어있다. 이 부분은 DirectX11에는 없던 개념 (11에서는 하드웨어에서 관리)이다.

GPU에서 사용할 때 멀티스레드 동기화로 인해 어떠한 상태인지를 알아야 사용할 수 있다.

어떠한 자원이 어떠한 상태에 있고 어떻게 해주어야하는 지를 관리 해야한다.

GPU에서 사용하려면 DEPTH_WHITE 상태로 변경해주어야 한다.

Resource가 생성되었을 때에 이전 상태 / 이후 상태를 적어준다.

Resource는 크게 3가지 종류로 나뉘어진다.

실제 메모리 (데이터)를 가지고 있는 리소스.

리소스를 정의하는 서술자

서술자를 가지고 있는 서술자 힙

DirectX12가 성능 최적화에 굉장히 어렵다. DirectX11은 하드웨어가 알아서 리소스의 상태를 변경해주었지만 직접 개발자가 해주도록 바뀌었기 때문이다. 다만, 잘 관리할 경우 하드웨어의 성능에 구애받지 않고 성능 효율을 올릴 수 있다.

**Render Command**

DirectX12에서 성능을 가리는 가장 중요한 부분이다.

이전에는 싱글 스레드에서만 command를 넣을 수 있었다. DirectX12부터는 비동기를 위한 Render Command이다.

**Command Queue**

GPU와 1:1 대응된다. (스레드가 8개면 커맨드 리스트도 8개)

여러 스레드에서 각자 커맨드 리스트를 사용할 수 있다.
gpu가 cpu보다 성능이 낮을 때에는 별로 효과가 좋지 않다.

커맨드 큐 : 스레드 세이프하다.
아무리 다른 스레드에서 넘겨줘도 세이프하게 받음

**Command Allocator**

메모리를 할당한다.

한 Allocator 당 여러 개의 Command List에 할당해줄 수 있음

그러나 동시에 1개만 기록 가능하다. 따라서 보통 1:1 매칭하여 생성한다.

**Command List**

GPU에서 할 일들을 명령어로 기록해두고 날려주는 역할을 한다.

성능상 응용프로그램 시작 때 다 초기화가 되어있어야 한다.

Resource처럼 상태가 존재한다. 초기는 open 상태(명령들을 추가할 수 있는 상태)이다.

close를 하게 되면 Render Command를 더 추가할 수 없다.

Command queue에 제출 시에 close 상태가 되어있어야만 한다.

Resource는 Resource대로, Command List는 Command List 대로 상태를 관리한다.

**Swap Chain**

Double Buffering을 수행해주는 기능이다.

front-back buffer를 계속 바꿔준다.

Swap Chain은 Resource를 Swap Chain이 알아서 생성해준다.

CreateSwapChain으로 생성해도 되지만 권장하지 않는다. (옛날 인터페이스이기 때문에 권장하지 않는 것으로 추측된다)

함수명 뒤에 붙는 Ex는 Extend의 약자이다. Window 관련 함수에서 Ex는 스몰 아이콘이 생겼다는 차이점이 있다. 그 밖에도 W 문자열, A 아스키 코드 관련에 차이가 있다.

* 스레드 간 통신에서는 dispatchQueue와 같은 것을 사용한다. iOS에서는 CentralDispatch라는 기능이 있다고 한다.

barrier는 fence와 비슷한 개념이다. 일종의 동기화 기법이다.

fence는 일정 숫자에 도달하기 전까지 실행하지 않는다.

dll 사용 시 메모리를 같은 것을 사용한다. 따라서 코드 변경 시 주의해야 한다.

static 라이브러리를 사용할 때 md/mt인지 프로젝트 설정을 맞춰주어야 한다.