# 7주차 (22. 01. 17)
[Notion Link](https://www.notion.so/7-22-01-17-d48523d2f81b409e856c2ceab6c2c719)

## Direct3D12

Mircrosoft에서 만들어진 인터페이스.

그래픽 카드에 명령을 보낼 때 어셈블리로 보낼 것을 미리 알고 있기 때문에, 사용자가 개발하기 편하게 끔 이를 위한 인터페이스를 만들어준 것이다.

12와 11의 차이점은 CPU 부담을 줄이기 위해서 다중 스레드 특화를 한 점이다. 이 과정에서 레이어를 줄여서 저수준(Row Level)의 API가 되었다.. (거의 다이렉트로 GPU에 명령을 보낼 수 있음)

### 초기화 방법

DirectX Init 복습.

**Device** : 가상 Adapter - 물리적인 그래픽 카드 인터페이스
자원 생성이나 기능 지원 점검에 사용한다.

### DXGI(DirectX Graphics Infrastructure)

편의 함수. SwapChain이나 디스플레이 정보를 얻는 데에 사용할 수 있다.

그래픽 카드가 없거나 굉장히 사양이 낮은 경우 MS에서 미리 정의해준다.

보통 그래픽 카드에서 하는 일은 Rasterizer이기 때문에 소프트웨어에서 돌아가도록 한다.

그러나 CPU에서 돌아가기 때문에 능력이 떨어진다.

설치된 그래픽 카드 정보를 얻어오는 함수

IDXGIFactory::EnumAdapters : 어댑터들에 대한 정보를 가져온다. 0번부터 순회한다.

D3D_FEATURE_LEVEL_11_0 : 제일 메모리가 높은 그래픽 카드를 찾는 옵션.

description에서 그래픽 카드 정보를 어느 정도 알 수 있다.

CommandList는 그래픽 카드에 명령 내리는 것.

CommandAllocator : CommandQueue를 만들 때 Type을 설정 가능

TYPE_DIRECT, TYPE_COPY 둘 다 가능. Device당 하나만 생성하는 게 좋다.

구조의 유연성 때문에 Cashe의 이점 등이 있다.

CommandAllocator 하나 당 CommandList 하나로 구현한다.

CommandList는 명령어들을 List에 기록해 놓는다. Queue에 보내라고 요청이 된 후에야 사용 될 수 있는 상태가 된다. 명령어 작성을 위해선 Reset(), 보내기 위해서는 Close() 되어야 한다.

SwapChain

Double Buffering 개념 제공. (Buffer를 몇 개 생성할 지) 보통 2~3개를 사용한다.

Window랑 겹치게 화면을 바로 출력할 수 있는 기능.

CommandList를 통해서 작성 후 Present를 하면 Window에 그려진다.

## Descriptor

DirectX 12부터 생긴 개념이다. 12에서는 모든 자원을 Resource(Texture나 Buffer 동일)라고 취급한다.

GPU 입장에선 Resource는 메모리 덩어리에 해당한다. GPU는 이게 RenderTarget인지 Texture인지 Buffer인지 알 수 없다. 이 부분에 대해서 설명해주는 것이 Descriptor이다.

구조가 2개로 나누어진다.

Descriptor : View, Resource가 무엇인 지를 설명하는 것.
Descriptor Heap : Descriptor들의 메모리 할당 관리

Descriptor Heap을 쓸 수 밖에 없는 이유는 GPU에 올릴 수 있는 크기가 정해져 있고, Heap에 여러 개를 묶어서 올리면 더욱 많이 업로드할 수 있게 된다.

View는 Descriptor Heap에 들어간다.

할당 받은 자원에 대한 걸 넣어주고 해당 자원에 대한 Descriptor는 Descriptor Heap에 넣는다.

### SwapChain

내부에서 이미 RenderTarget을 생성해둔다. 따라서 RenderTarget(Resource)을 꺼내와서 그것에 대한 RenderTarget을 다시 만들어야 한다.

### RenderTarget

GPU한테 명령내릴 때 그려줄 것(Texture)라고 보면 된다.

Presenter를 어떤 Texture로 할지 알기 위해서 SwapChain 내부에서 생성한다.

Descriptor의 사이즈는 하드웨어마다 다르다.

### Depth Stencil

깊이 맵 + 마스킹.

Depth Map을 만들고 메모리가 남았을 때 Stencil에 할당다.

Resource는 어떻게 만들까?

CreatePlacedResource, CreateCommittedResource로 Buffer를 만들고 Descriptor로 알려준다.
(= GPU에 바로 할당하겠다)

Type을 설정하지 않고 만드는 방식.

하나의 Resource에 View가 여러 개 있을 수 있다.

Flag가 조금 차이가 난다. Depth Stencil 용으로 쓸 건지 한정 지으면 GPU에서 최적화가 가능하다.

Bit Flag를 설정하면 할수록 최적화가 될 수도 아닐 수도 있다. (보통 최적화에 대한 가이드가 있다)

### Viewport, Scissorect

Viewport : 그릴 영역을 정하는 것

Scissorect : 최적화 기법. 안 그려질 부분을 제외하고 계산하도록 한다.

### Application

- Init : Window 생성
- OnResize
- Update
- Draw

Fence : GPU와 동기화하기 위한 객체. 타임라인 기반으로 Synchronized한다. Signal이란 걸 통해서 번호를 설정한다.

windowEvent : CreateEvent 함수로 생성한다. 이벤트 핸들로 스레드를 멈출 수 있다. Fence가 내부적으로 깨워주는 Event를 날려준다.

Fence로 막아두는 동안 GPU가 놀고 있다면 그때 일 시키는 방법도 존재한다.

Descriptor가 하드웨어 별로 사이즈가 다르다.