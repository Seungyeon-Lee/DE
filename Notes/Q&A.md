# Q&A (21. 11. 25)
[Notion Link](https://www.notion.so/4-Q-A-21-11-25-0aaee26fc8094ee6b53f8b5fe3ffdf4c)

Window를 만들기 위해서는 Init을 해야한다.

책 예제는 아래 페이지에서 참고 가능 (Init Direct3D)

[https://github.com/d3dcoder/d3d12book/tree/master/Chapter 4 Direct3D Initialization/Init Direct3D](https://github.com/d3dcoder/d3d12book/tree/master/Chapter%204%20Direct3D%20Initialization/Init%20Direct3D)

우리는 기본적으로 포함된 Util (d3dUtil) 일부를 사용하지 않고 만든다. (EX. 수학 함수)

1주차 실습까지 완료했다면 수학 함수만 만들어진 상태일 것이고, 이 프로젝트 위에 DirectX를 추가해야 한다.

d3dApp

**기본적으로 헤더를 잘 구성하면 프로젝트가 잘 돌아가게 된다.**

d3dcompiler.lib를 사용하지 않는 이유?

우리가 만든 라이브러리를 사용해야 할 때,

lib를 직접적으로 헤더에 적은 경우 (링커 - 추가 종속성에 추가)에는 헤더에 있는 내용을 보고 빌드를 실행하게 되고, 사용하는 테스트 앱에서는 해당 lib가 없어서 오류가 날 수 있다. (함께 제공하지 않는 경우엔 프로젝트 세팅에 적어야 한다. 스태틱 lib가 만들어지는 곳에 합쳐져서 들어가게 된다.) 참조를 통한 경우에는 알아서 해준다.

(r.f [#pragma comment(lib, file) 을 쓰면 안되는 이유](https://www.notion.so/pragma-comment-lib-file-c253026f920447e988607fe4250b2a2a))

기본 Tip : 잘 돌아가는 프로젝트를 분석한다.

프로그램이 들어가는 흐름이 궁금할 때 어떻게 돌아가는지 확인하고 싶으면 `F12`를 눌러본다.

(순차적으로 코드가 실행되는 것을 볼 수 있음)

**windows.h**

[MainWindPRoc](https://docs.microsoft.com/ko-kr/windows/win32/winmsg/using-window-procedures) 

```cpp
LRESULT CALLBACK MainWndProc(
    HWND hwnd,        // handle to window, 어떤 Window가 발생시켰는 지
    UINT uMsg,        // message identifier, 메시지
    WPARAM wParam,    // first message parameter, 가변 사이즈
    LPARAM lParam)    // second message parameter 
```

함수명 뒤에 W로 변경하여 유니코드를 사용할 것이라 명시한다.

링커 - 시스템 - 창 (세팅을 변경하여 기존 console 창 외에 보여지도록 변경)

기존에 게임에서 익숙한 loop를 만들어주는 함수가 Update (Run) 함수라고 볼 수 있다.

**헤더의 <xxx.h>와 "xxx.h" 차이**
<>는 보통 sdk나 시스템에 포함 되어있는 헤더를 의미한다.
""는 로컬에 있는 헤더를 의미한다.

[d3dApp.cpp](https://github.com/d3dcoder/d3d12book/blob/4cfd00afa59210a272f62caf0660478d18b9ffed/Common/d3dApp.cpp)의 72Line Run 함수는 스레드로 작업한다.
멀티스레드는 차후 작업 예정이므로 싱글스레드로 진행한다.

```cpp
if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        debugController->EnableDebugLayer();
        dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
    }
```

adpater는 그래픽 카드라고 생각하면 된다. 이를테면 그래픽 카드가 2개인 경우 어떠한 그래픽 카드를 가져올 것인지 정하는 로직으로, `null인 경우에는 주 그래픽 카드`를 가져온다.

그래픽 카드가 없거나 사양이 안 맞을때 warp라는 걸로 소프트웨어가 그래픽 카드가 하는 일을 하게끔 만들어준다. 소프트웨어로 구현한 레스터 라이저이기 때문에 상대적으로 그래픽 카드로 구현된 것보단 느리다. (GPU가 할 일을 CPU로 돌리는 것)

**수정사항**

- wstring -> wchar로 바꾸기
- 사용할 일 없는 것 지우기
- constsbuffer 쓸때 사용
- 로드 디폴트 버퍼도 필요없음
- 익셉션도 thow로 대체하면 필요없음

**Q. Spin Lock이란?**

Lock을 자주걸면 Context Switching(어떠한 스레드가 다른 스레드로 바뀌기 위해서 정보를 저장하고 적재하는 과정)이 일어나기 때문에 Spin Lock이 나오게 되었다.

스레드가 잠깐만 락을 걸거면 무한루프 돌면서 그냥 쉬도록 하는 방식 (busy waiting)을 사용한다.

대부분의 상황에선 스핀락이 무조건 빠르다.

일반적인 스레드 락 (Sleep)보다 빠르다.

**Q. 파일 디렉터리 구조 변경 시 헤더 리네임이 필수인가요?**

assist의 refactor 기능 사용하면 간단히 할 수 있다.

**Q. NULL과 nullptr은 무슨 차이인가요?**

nullptr는 null임을 명확히 명시해준다.

NULL은 숫자 0으로 define되어있다. (버전 차이)

(+) 초기화 관련 ([Initialization](https://www.notion.so/Initialization-cfb7054491424f98863a9991c7bf82f0))